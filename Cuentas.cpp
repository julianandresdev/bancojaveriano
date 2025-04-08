//
// Created by Julian on 28/03/2025.
//

#include "Cuentas.h"

using namespace std;

Cuentas::Cuentas(int id, int saldo) : id(id), saldo(saldo) {}

void Cuentas::aplicarIntereses() {}


int Cuentas::getId() const {
    return id;
}

double Cuentas::getSaldo() const {
    return saldo;
}

ostream & operator<<(ostream &os, const Cuentas &cuenta) {
    cuenta.mostrarInformacion(os);
    return os;
}
