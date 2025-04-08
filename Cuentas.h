//
// Created by Julian on 28/03/2025.
//

#ifndef CUENTAS_H
#define CUENTAS_H

#include "json.hpp"

using namespace std;

class Cuentas {
protected:
    int id;
    int saldo;
public:
    Cuentas(int id, int saldo);
    virtual ~Cuentas() = default;
    virtual void mostrarInformacion(ostream& os) const = 0;
    virtual void setSaldo(const int &saldo) = 0;
    virtual void aplicarIntereses();
    virtual string getTipo() const = 0;
    int getId() const;
    double getSaldo() const;
    int getCantidadCuentas() const;

    friend ostream& operator<<(ostream& os, const Cuentas& cuenta);
};



#endif //CUENTAS_H
