//
// Created by Julian on 28/03/2025.
//

#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>

#include "Clientes.h"

using namespace std;

class Banco {
private:
    string nombre;
    vector<Clientes> clientes;
    int contadorCuentas = 100;
    public:
    Banco(string n);
    ~Banco();
    void agregarCliente(const string &nombre, const string &direccion);
    void agregarCuenta(int &idCliente, int &saldo) ;
    void listarClientes();
    void listarCuentas();
    void mostrarInformacion();
    void aplicarTasasDeInteres();
    void consignar(const int& id, const int& cantidad);
    void retirar(const int& id, const int& cantidad);
    void cargarDatos(const string& archivo);
    int cantidadClientes() const;
    double promedioSaldo();
    array<int,2> cantidadCuentas() const;

    void guardarDatos(const string &nombreArchivo);
};



#endif //BANCO_H
