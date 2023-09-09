#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "Cliente.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

void mostrarLinea (Cliente &dCliente);
void pausa();

int main () {

    ifstream archivoCreditoEntrada; // Objeto para el flujo de datos
    Cliente datosCliente; // Objeto para guardar datos del cliente

    // Menu del programa
    int opc;
    do {
        system(CLEAR);
        cout << "Menu - Integracion de Sueldos" <<endl<<endl;
        cout << "1) Consulta Individual (Numero de Cuenta)." <<endl;
        cout << "2) Consulta Grupal (Formato de Tabla)." <<endl;
        cout << "3) Salir." <<endl<<endl;
        cout << "Elige tu opcion >> ";
        cin >> opc;

        switch (opc) {
        case 1: {
            // Abrir el archivo y revisar si existe
            archivoCreditoEntrada.open("credito.dat", ios::in | ios::binary);
            if (!archivoCreditoEntrada) {
                cerr << "No se puede abrir el archivo" <<endl;
                exit(1);
            }
            
            int numeroCuentaBuscado;

            cout << endl << "Dame el numero de cuenta del registro a buscar: ";
            cin >> numeroCuentaBuscado;

            // Calcular la posición en el archivo
            archivoCreditoEntrada.seekg((numeroCuentaBuscado - 1) * int(sizeof(Cliente))); // Casteo

            // Intentar leer el registro
            if (archivoCreditoEntrada.read(reinterpret_cast<char*>(&datosCliente), sizeof(Cliente))) {
                if (datosCliente.getNumeroCuenta() != 0) {
                    // El registro se encontró y se leyó correctamente
                    cout << "CUENTA : " << datosCliente.getNumeroCuenta() << endl;
                    cout << "APELLIDO : " << datosCliente.getApellidoPaterno() << endl;
                    cout << "PRIMER NOMBRE: " << datosCliente.getPrimerNombre() << endl;
                    cout << "SALDO : " << datosCliente.getSaldo() << endl;
                } else {
                    // No se pudo leer el registro (puede ser que el número de cuenta no exista)
                    cout << "EL NÚMERO DE CUENTA NO EXISTE" << endl;
                }
            } else {
                // No se pudo leer el registro (puede ser que el número de cuenta no exista)
                cout << "EL NÚMERO DE CUENTA NO EXISTE" << endl;
            } pausa();
            // Cerrar archivo
            archivoCreditoEntrada.close();
        }break;
        
        case 2:
            // Abrir el archivo y revisar si existe
            archivoCreditoEntrada.open("credito.dat", ios::in | ios::binary);
            if (!archivoCreditoEntrada) {
                cerr << "No se puede abrir el archivo" <<endl;
                exit(1);
            }
        
            cout<<endl<<endl;
            cout << left << setw(10) << "Cuenta" << setw(16)
                << "Apellido" << setw(11) << "Nombre" << left
                << setw(10) << right << "Saldo" <<endl;

            // Lee el primer registro del archivo
            archivoCreditoEntrada.read(reinterpret_cast<char*>(&datosCliente), sizeof(Cliente));
            
            // lee todos los registros del archivo
            while (archivoCreditoEntrada && !archivoCreditoEntrada.eof()) {
                // Muestra un archivo
                if (datosCliente.getNumeroCuenta() != 0) {
                    mostrarLinea(datosCliente);
                }
                // Lee el siguiente registro del archivo
                archivoCreditoEntrada.read(reinterpret_cast<char*>(&datosCliente), sizeof(Cliente));
            } pausa();
            archivoCreditoEntrada.close(); // Cerrar el archivo
            break;

        case 3: break;

        default:
            cout << "La opcion \"" << opc << "\" no es una opcion valida..."; pausa();
            break;
        }

    } while (opc != 3);

    return 0;
}

void mostrarLinea (Cliente &dCliente) {
    cout << left << setw(10) << dCliente.getNumeroCuenta() << setw(16) << dCliente.getApellidoPaterno() 
    << setw(11) << dCliente.getPrimerNombre() 
    << setw(10) << setprecision(2) << right << fixed 
    << showpoint << dCliente.getSaldo() << endl;
}

void pausa() { cin.clear(); cin.sync(); cin.ignore(); }