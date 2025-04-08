//
// Created by Julian on 28/03/2025.
//

#include "Clientes.h"

#include <iostream>
#include <ostream>

#include "Banco.h"
#include "Ahorros.h"
#include "Corriente.h"
#include "json.hpp"

using nlohmann::json;

Clientes::Clientes(int i, string nom, string dir) : id(i), nombre(nom), direccion(dir) {}

Clientes::~Clientes() {
    for (auto cuenta : cuentas) {
        delete cuenta;
    }
    cuentas.clear();
}

int Clientes::getId() const {
    return id;
}

string Clientes::getNombre() const {
    return nombre;
}

string Clientes::getDireccion() const {
    return direccion;
}

vector<Cuentas*> Clientes::getCuentas() const {
    return cuentas;
}

void Clientes::agregarCuenta(Cuentas* cuenta) {
    cuentas.push_back(cuenta);
}

void Clientes::mostrarCuentas() {
    cout << "Cuentas de " << nombre << " (ID: " << id << "):\n";
    if (cuentas.empty()) {
        cout << "  → No tiene cuentas registradas.\n";
        return;
    }

    for (auto& cuenta : cuentas) {
        if (!cuenta) {
            cout << "  → Cuenta inválida (nullptr)\n";
            continue;
        }
        try {
            cout << "  → Cuenta con ID: " << cuenta->getId() << "\n";
            cuenta->mostrarInformacion(cout);
        } catch (...) {
            cout << "  → ERROR al acceder a la cuenta ID (puntero dañado)\n";
        }
    }
}


void Clientes::aplicarIntereses() {
    for (auto& cuenta : cuentas) {
        if (cuenta->getTipo() == "Ahorros") {
            dynamic_cast<Ahorros*>(cuenta)->aplicarIntereses();
        }
    }
}

bool Clientes::consignar(const int& id, const int& cantidad) {
    for (auto& cuenta : cuentas) {
        if (cuenta->getId() == id) {
            cuenta->setSaldo(cuenta->getSaldo() + cantidad);
            cout << "$" << cantidad << " consignada a la cuenta: " << id << endl;
            return true;
        }
    }
    return false; // No se encontró la cuenta
}


bool Clientes::retirar(const int &id, const int &cantidad) {
    for (auto& cuenta : cuentas) {
        if (cuenta->getId() == id) {
            if (cuenta->getTipo() == "Corriente") {
                auto* corriente = dynamic_cast<Corriente*>(cuenta);
                if (cuenta->getSaldo() - cantidad >= -corriente->getLimiteSobreGiro()) {
                    cuenta->setSaldo(cuenta->getSaldo() - cantidad);
                    cout << "[¡CUENTA EN SOBREGIRO!] Se retiraron $" << cantidad << " de la cuenta: " << id << endl;
                    return true;
                } else {
                    cout << "No se puede retirar: supera el límite de sobregiro." << endl;
                    return false;
                }
            } else { // Tipo Ahorros
                if (cuenta->getSaldo() >= cantidad) {
                    cuenta->setSaldo(cuenta->getSaldo() - cantidad);
                    cout << "$" << cantidad << " retirados de la cuenta: " << id << endl;
                    return true;
                } else {
                    cout << "Saldo insuficiente para retirar $" << cantidad << " de la cuenta: " << id << endl;
                    return false;
                }
            }
        }
    }
    return false;
}

array<int, 2> Clientes::contarCuentas() const {
    int contador[2] = { 0, 0 };
    for (auto& cuenta : cuentas) {
        if (cuenta->getTipo() == "Ahorros") {
            contador[0]++;
        } else if (cuenta->getTipo() == "Corriente") {
            contador[1]++;
        }
    }
    return {contador[0], contador[1]};
}

int Clientes::cantidadCuentas() const {
    return cuentas.size();
}

double Clientes::promedioSaldo() {
    if (cuentas.empty()) return 0.0;  // Evitar división por cero

    double total = 0;
    for (const auto& cuenta : cuentas) {
        total += cuenta->getSaldo();
    }
    return total / cuentas.size();
}

ostream& operator<<(ostream& os, const Clientes& cliente) {
    os << "ID: " << cliente.getId()  << " Nombre: " << cliente.getNombre() << ", Direccion: " << cliente.getDireccion() << endl;
    return os;
}
