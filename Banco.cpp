//
// Created by Julian on 28/03/2025.
//

#include "Banco.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "json.hpp"
#include "Ahorros.h"
#include "Corriente.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Banco::Banco(string n): nombre(n) {}

Banco::~Banco() {}

void Banco::agregarCliente(const string& nombre, const string& direccion) {
    int id = clientes.size() + 1;
    Clientes nuevoCliente(id, nombre, direccion);
    clientes.push_back(nuevoCliente);
}


void Banco::agregarCuenta(int &idCliente, int &saldo) {
    for (auto& cliente : clientes) {
        if (cliente.getId() == idCliente) {
            cout << "Seleccione el tipo de cuenta:\n";
            cout << "1. Ahorros\n";
            cout << "2. Corriente\n";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                double tasaInteres;
                cout << "Ingrese la tasa de interés: ";
                cin >> tasaInteres;

                cliente.agregarCuenta(new Ahorros(tasaInteres, contadorCuentas++, saldo));
            } else if (opcion == 2) {
                double limiteSobregiro;
                cout << "Ingrese el límite de sobregiro: ";
                cin >> limiteSobregiro;

                cliente.agregarCuenta(new Corriente(limiteSobregiro, contadorCuentas++, saldo));
            } else {
                cout << "Opción no válida.\n";
            }
            return;
        }
    }
    cout << "Cliente no encontrado.\n";
}


void Banco::listarClientes() {
    cout << "Informacion de clientes:" << endl;
    if (!clientes.empty()) {
        for (auto& cliente: clientes) {
            cout << cliente << endl;
        }
    } else cout << "No hay clientes."<<endl;
}

void Banco::listarCuentas() {
    if (!clientes.empty()) {
        for (auto& cliente: clientes) {
            cout << "Cuentas de " << cliente.getNombre() << " (ID: " << cliente.getId() << "):\n";

            auto cuentas = cliente.getCuentas();  // Asumiendo que tienes un getter
            if (cuentas.empty()) {
                cout << "  → Este cliente no tiene cuentas registradas.\n";
                continue;
            }

            for (Cuentas* cuenta : cuentas) {
                if (cuenta != nullptr) {
                    cout << *cuenta;// O lo que uses para mostrar info
                } else {
                    cout << "  ⚠ Cuenta inválida encontrada.\n";
                }
            }
        }
    } else cout << "No hay cuentas." << endl;

}


void Banco::mostrarInformacion() {
    array<int, 2> cuentasExistentes = cantidadCuentas();
    cout << "Informacion Banco: " << nombre  << endl;
    listarClientes();
    listarCuentas();
    cout << "Promedio de saldo de cuentas: " << "$" << fixed << setprecision(2) << promedioSaldo() << endl;
    cout << "Numero de cuentas Ahorros: "  << cuentasExistentes[0] << endl;
    cout << "Numero de cuentas Corrientes: "  << cuentasExistentes[1] << endl;
}

void Banco::aplicarTasasDeInteres() {
    cout << "Aplicando tasas de interes a cuentas..." << endl;
    for (auto& cliente: clientes) {
        cliente.aplicarIntereses();
    }
    cout<<"Aplicada tasa de interes correctamente a cuentas de ahorros." << endl;
}

void Banco::consignar(const int& id, const int& cantidad) {
    if (cantidad <= 0) {
        cout << "Debes ingresar un valor positivo a consignar."<<endl;
        return;
    }
    for (auto& cliente : clientes) {
        if (cliente.consignar(id, cantidad)) {
            return;
        }
    }
    cout << "No se encontró ninguna cuenta con el id: " << id << endl;
}

void Banco::retirar(const int& id, const int& cantidad) {
    if (cantidad <= 0) {
        cout << "Debes ingresar un valor positivo a retirar."<<endl;
        return;
    }
    for (auto& cliente : clientes) {
        if (cliente.retirar(id, cantidad)) {
            return;
        }
    }
    cout << "No se encontró ninguna cuenta con el ID: " << id << endl;
}

double Banco::promedioSaldo() {

    if (!clientes.empty()) {
        return clientes.front().promedioSaldo();
    }
    return 0.0;
}
array<int,2> Banco::cantidadCuentas() const {
    array total = {0, 0};
    for (const auto& cliente : clientes) {
        array<int, 2> tipos = cliente.contarCuentas();
        total[0] += tipos[0];  // Ahorros
        total[1] += tipos[1];  // Corriente
    }
    return total;
}
void Banco::guardarDatos(const string& filename) {
    json j;
    j["clientes"] = json::array();
    j["cuentas"] = json::array();

    for (const auto& cliente : clientes) {
        json jCliente;
        jCliente["id"] = cliente.getId();
        jCliente["nombre"] = cliente.getNombre();
        jCliente["direccion"] = cliente.getDireccion();
        j["clientes"].push_back(jCliente);

        for (auto* cuenta : cliente.getCuentas()) {
            json jCuenta;
            jCuenta["id"] = cuenta->getId();
            jCuenta["saldo"] = cuenta->getSaldo();
            jCuenta["clienteId"] = cliente.getId();

            if (dynamic_cast<Ahorros*>(cuenta)) {
                jCuenta["tipo"] = "Ahorros";
                jCuenta["tasa"] = dynamic_cast<Ahorros*>(cuenta)->getTasaDeInteres();
            } else if (dynamic_cast<Corriente*>(cuenta)) {
                jCuenta["tipo"] = "Corriente";
                jCuenta["limite"] = dynamic_cast<Corriente*>(cuenta)->getLimiteSobreGiro();
            }

            j["cuentas"].push_back(jCuenta);
        }
    }

    std::ofstream archivo(filename);
    archivo << j.dump(4);
    archivo.close();
    std::cout << "Datos guardados exitosamente en " << filename << std::endl;
}

void Banco::cargarDatos(const string& filename) {
    std::ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo/no se encontro." << std::endl;
        return;
    }

    json j;
    archivo >> j;
    archivo.close();

    // Limpiamos lo anterior
    clientes.clear();
    int contadorClientes = 1;
    contadorCuentas = 100;

    // 1. Cargar Clientes
    for (const auto& jCliente : j["clientes"]) {
        Clientes nuevo(jCliente["id"], jCliente["nombre"], jCliente["direccion"]);
        clientes.push_back(nuevo);
        contadorClientes = std::max(contadorClientes, jCliente["id"].get<int>() + 1);
    }

    // 2. Cargar Cuentas
    for (const auto& jCuenta : j["cuentas"]) {
        int idCliente = jCuenta["clienteId"];
        Cuentas* cuenta = nullptr;

        if (jCuenta["tipo"] == "Ahorros") {
            cuenta = new Ahorros(jCuenta["tasa"], jCuenta["id"], jCuenta["saldo"]);
        } else if (jCuenta["tipo"] == "Corriente") {
            cuenta = new Corriente(jCuenta["limite"], jCuenta["id"], jCuenta["saldo"]);
        }

        contadorCuentas = std::max(contadorCuentas, jCuenta["id"].get<int>() + 1);

        // Agregar la cuenta al cliente correcto
        auto it = std::find_if(clientes.begin(), clientes.end(), [idCliente](const Clientes& c) {
            return c.getId() == idCliente;
        });

        if (it != clientes.end() && cuenta != nullptr) {
            it->agregarCuenta(cuenta);
        }
    }

    std::cout << "Datos cargados correctamente desde " << filename << std::endl;
    std::cout << " → contadorCuentas actualizado a: " << contadorCuentas << std::endl;
}

int Banco::cantidadClientes() const {
    return clientes.size();
}


