//
// Created by Julian on 28/03/2025.
//

#include "Ahorros.h"

#include <iostream>
#include <ostream>

Ahorros::Ahorros(double tasa, int id, int saldo): tasaDeInteres(tasa), Cuentas(id, saldo) {}

double Ahorros::getTasaDeInteres() const {
    return tasaDeInteres;
}

void Ahorros::mostrarInformacion(ostream& os) const {
    os << "[CUENTA DE AHORROS] " << "ID: " << id << " SALDO: " << saldo << " INTERES: " << tasaDeInteres << "%" << endl;
}

void Ahorros::setSaldo(const int &saldoNuevo) {
    saldo = saldoNuevo;
}

string Ahorros::getTipo() const {
    return "Ahorros";
}


void Ahorros::aplicarIntereses() {
    saldo *=  (1 + tasaDeInteres / 100);
}
