//
// Created by Julian on 28/03/2025.
//

#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
#include <vector>

#include "Cuentas.h"

using namespace std;
class Clientes {
private:
    int id;
    string nombre;
    string direccion;
    vector<Cuentas*> cuentas;
public:
    Clientes(int i, string nom, string dir);
    ~Clientes();  // Destructor para liberar memoria

    int getId() const;
    string getNombre() const;
    string getDireccion() const;

    vector<Cuentas*> getCuentas() const;

    void agregarCuenta(Cuentas* cuenta);
    void mostrarCuentas();
    void aplicarIntereses();
    bool consignar(const int &id, const int &cantidad);
    bool retirar(const int &id, const int &cantidad);
    array<int,2> contarCuentas() const;
    int cantidadCuentas() const;
    double promedioSaldo();

    friend ostream& operator<<(ostream& os, const Clientes& cliente);
};


#endif //CLIENTES_H
