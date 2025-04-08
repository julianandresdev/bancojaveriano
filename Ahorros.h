//
// Created by Julian on 28/03/2025.
//

#ifndef AHORROS_H
#define AHORROS_H
#include "Cuentas.h"

class Ahorros : public Cuentas {
private:
    double tasaDeInteres;
public:
    Ahorros(double tasa, int id, int saldo);
    virtual ~Ahorros() = default;
    double getTasaDeInteres() const;
    void mostrarInformacion(ostream& os) const override;
    void setSaldo(const int &saldo) override;
    string getTipo() const override;
    void aplicarIntereses() override;

};




#endif //AHORROS_H
