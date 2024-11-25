#include <iostream>
#include <string>
#include <vector>
#include "Windows.h"

using namespace std;  // Para evita escribir std::


class Paciente {
public:
    
    Paciente(string nombre, int edad) : nombre(nombre), edad(edad) {}

    
    void mostrarDetalles() const {
        cout << "Nombre: " << nombre << ", Edad: " << edad << " años" << endl;
    }

private:
    string nombre;
    int edad;  
};

// Función para gestionar pacientes 
void gestionarPacientes(vector<Paciente>& pacientes) {
    int opcion;
    do {
        cout << "\n=== Gestión de Pacientes ===" << endl;
        cout << "1. Registrar paciente" << endl;
        cout << "2. Listar pacientes" << endl;
        cout << "3. Volver al menú principal" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            // Registrar nuevo paciente
            string nombre;
            int edad;
            cout << "Ingrese el nombre del paciente: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese la edad del paciente: ";
            cin >> edad;

            pacientes.emplace_back(nombre, edad);
            cout << "Paciente registrado con éxito." << endl;
            break;
        }
        case 2: {
         
            cout << "\n=== Lista de Pacientes ===" << endl;
            if (pacientes.empty()) {
                cout << "No hay pacientes registrados." << endl;
            }
            else {
                for (const auto& paciente : pacientes) {
                    paciente.mostrarDetalles();
                }
            }
            break;
        }
        case 3:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
            break;
        }
    } while (opcion != 3);
}

// Menú principal
int main() {
    SetConsoleOutputCP(1252);
    vector<Paciente> pacientes;

    int opcion;
    do {
        cout << "\n=== Menú Principal ===" << endl;
        cout << "1. Gestionar pacientes" << endl;
        cout << "2. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestionarPacientes(pacientes);
            break;
        case 2:
            cout << "Saliendo del programa. ¡Hasta luego!" << endl;
            break;
        default:
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
            break;
        }
    } while (opcion != 2);

    return 0;
}
