//
// Created by Julian on 28/03/2025.
//

#ifndef CORRIENTE_H
#define CORRIENTE_H
#include "Cuentas.h"


class Corriente : public Cuentas {
private:
    int limiteSobreGiro;
public:
    Corriente(int limit, int id, int saldo);
    int getLimiteSobreGiro() const;
    void mostrarInformacion(ostream& os) const override;
    void setSaldo(const int &saldo) override;
    void aplicarIntereses() override {};
    string getTipo() const override;

};



#endif //CORRIENTE_H
