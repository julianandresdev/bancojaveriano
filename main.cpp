#include <windows.h>
#include <iostream>
#include "Banco.h"

using namespace std;

void menu() {
    cout << "\n===== MENU BANCO JAVERIANO =====\n";
    cout << "1) MANTENIMIENTO DE CLIENTES\n";
    cout << "   1.1) Agregar Cliente\n";
    cout << "   1.2) Listar Clientes\n";
    cout << "2) MANTENIMIENTO DE CUENTAS\n";
    cout << "   2.1) Agregar Cuenta\n";
    cout << "   2.2) Listar Cuentas\n";
    cout << "3) ESTADÍSTICAS\n";
    cout << "   3.1) Total de Clientes\n";
    cout << "   3.2) Total de Cuentas\n";
    cout << "   3.3) Promedio del Saldo de las Cuentas\n";
    cout << "   3.4) Número de Cuentas de Ahorro\n";
    cout << "   3.5) Número de Cuentas Corrientes\n";
    cout << "4) OPERACIONES FINANCIERAS\n";
    cout << "   4.1) Aplicar Tasa de Interés a Cuentas de Ahorro\n";
    cout << "   4.2) Consignar Dinero en una Cuenta\n";
    cout << "   4.3) Retirar Dinero de una Cuenta\n";
    cout << "5) SALIR\n";
    cout << "   5.1) Guardar los datos en BancoJaveriano.json y cerrar el programa\n";
    cout << "================================\n";
    cout << "Seleccione una opción (ej: 1.1): ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Banco BancoJaveriano("Banco de la Republica Javeriana");
    BancoJaveriano.cargarDatos("../BancoJaveriano.json");
    string comando, nombre, direccion;
    int cantidad, id;

    while (true) {
        menu();
        cin >> comando;

        if (comando == "1.1") {
            cout << "Ingresa nombre completo del cliente: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nombre);
            cout << "Ingresa la dirección del cliente: ";
            getline(cin, direccion);
            BancoJaveriano.agregarCliente(nombre, direccion);
            cout << "Cliente agregado correctamente.\n";

        } else if (comando == "1.2") {
            BancoJaveriano.listarClientes();

        } else if (comando == "2.1") {
            cout << "Ingresa el ID del cliente al cual se asociará la cuenta: ";
            cin >> id;
            cout << "Ingrese el saldo inicial de la cuenta: ";
            cin >> cantidad;
            BancoJaveriano.agregarCuenta(id, cantidad);

        } else if (comando == "2.2") {
            BancoJaveriano.listarCuentas();

        } else if (comando == "3.1") {
            cout << "Total de clientes: " << BancoJaveriano.cantidadClientes() << "\n";

        } else if (comando == "3.2") {
            int cuentast =  BancoJaveriano.cantidadCuentas()[0] + BancoJaveriano.cantidadCuentas()[1];
            cout << "Total de cuentas: " << cuentast << "\n";

        } else if (comando == "3.3") {
            cout << "Promedio de saldo: $" << BancoJaveriano.promedioSaldo() << "\n";

        } else if (comando == "3.4") {
            cout << "Número de cuentas de ahorro: " << BancoJaveriano.cantidadCuentas()[0] << "\n";

        } else if (comando == "3.5") {
            cout << "Número de cuentas corrientes: " << BancoJaveriano.cantidadCuentas()[1] << "\n";

        } else if (comando == "4.1") {
            BancoJaveriano.aplicarTasasDeInteres();

        } else if (comando == "4.2") {
            cout << "Ingresa el ID de la cuenta a la cual se va a consignar: ";
            cin >> id;
            cout << "Ingresa la cantidad a consignar: ";
            cin >> cantidad;
            BancoJaveriano.consignar(id, cantidad);

        } else if (comando == "4.3") {
            cout << "Ingresa el ID de la cuenta de la cual se va a retirar: ";
            cin >> id;
            cout << "Ingresa la cantidad a retirar: ";
            cin >> cantidad;
            BancoJaveriano.retirar(id, cantidad);

        } else if (comando == "5.1") {
            BancoJaveriano.guardarDatos("../BancoJaveriano.json");
            cout << "Datos guardados exitosamente. Cerrando programa...\n";
            break;

        } else {
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}
