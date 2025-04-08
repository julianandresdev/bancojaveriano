//
// Created by Julian on 28/03/2025.
//

#include "Corriente.h"

#include <iostream>
#include <ostream>

Corriente::Corriente(int limit, int id, int saldo): limiteSobreGiro(limit), Cuentas(id, saldo) {}

string Corriente::getTipo() const {
    return  "Corriente";
}

int Corriente::getLimiteSobreGiro() const {
    return limiteSobreGiro;
}

void Corriente::mostrarInformacion(ostream& os) const {
    os << "[CUENTA DE CORRIENTE] " << "ID: " << id << " SALDO: " << saldo << " LIMITE SOBREGIRO: " << limiteSobreGiro << endl;
}

void Corriente::setSaldo(const int &saldoNuevo) {
    saldo = saldoNuevo;
}



