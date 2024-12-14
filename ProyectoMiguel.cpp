#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
//#include "Windows.h"

using namespace std;

class Paciente {
public:
    Paciente(string nombre, int edad) : nombre(nombre), edad(edad) {}

    void mostrarDetalles() const {
        cout << "Nombre: " << nombre << ", Edad: " << edad << " años" << endl;
    }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }

private:
    string nombre;
    int edad;
};

class Medico {
public:
    Medico(string nombre, string especialidad, bool disponible = true)
        : nombre(nombre), especialidad(especialidad), disponible(disponible) {}

    void mostrarDetalles() const {
        cout << "Nombre: " << nombre << ", Especialidad: " << especialidad
            << ", Disponibilidad: " << (disponible ? "Disponible" : "No disponible") << endl;
    }

    string getNombre() const { return nombre; }
    string getEspecialidad() const { return especialidad; }
    bool isDisponible() const { return disponible; }

    void setDisponibilidad(bool estado) { disponible = estado; }

private:
    string nombre;
    string especialidad;
    bool disponible;
};

int leerNumero(const string& mensaje) {
    int numero;
    while (true) {
        cout << mensaje;
        cin >> numero;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error, entrada no numérica." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
    }
}

void guardarPacientes(const vector<Paciente>& pacientes) {
    ofstream archivo("pacientes.txt", ios::out);
    if (!archivo) {
        cerr << "Error al abrir el archivo pacientes.txt." << endl;
        return;
    }

    for (const auto& paciente : pacientes) {
        archivo << paciente.getNombre() << "," << paciente.getEdad() << endl;
    }

    archivo.close();
    cout << "Pacientes guardados correctamente." << endl;
}

void guardarMedicos(const vector<Medico>& medicos) {
    ofstream archivo("medicos.txt", ios::out);
    if (!archivo) {
        cerr << "Error al abrir el archivo medicos.txt." << endl;
        return;
    }

    for (const auto& medico : medicos) {
        archivo << medico.getNombre() << "," << medico.getEspecialidad() << ","
            << medico.isDisponible() << endl;
    }

    archivo.close();
    cout << "Médicos guardados correctamente." << endl;
}

void cargarPacientes(vector<Paciente>& pacientes) {
    ifstream archivo("pacientes.txt", ios::in);
    if (!archivo) {
        cout << "No se encontró el archivo de pacientes. Creando nuevo..." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int edad;

        getline(ss, nombre, ',');
        ss >> edad;
        if (!nombre.empty()) {
            pacientes.emplace_back(nombre, edad);
        }
    }

    archivo.close();
    cout << "Pacientes cargados correctamente." << endl;
}

void cargarMedicos(vector<Medico>& medicos) {
    ifstream archivo("medicos.txt", ios::in);
    if (!archivo) {
        cout << "No se encontró el archivo de pacientes. Creando nuevo..." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, especialidad;
        bool disponible;

        getline(ss, nombre, ',');
        getline(ss, especialidad, ',');
        ss >> disponible;

        if (!nombre.empty()) {
            medicos.emplace_back(nombre, especialidad, disponible);
        }
    }

    archivo.close();
    cout << "Médicos cargados correctamente." << endl;
}

void gestionarPacientes(vector<Paciente>& pacientes) {
    int opcion;
    do {
        cout << "\n=== Gestión de Pacientes ===" << endl;
        cout << "1. Registrar paciente" << endl;
        cout << "2. Listar pacientes" << endl;
        cout << "3. Eliminar médico" << endl;
        cout << "4. Volver al menú principal" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre;
            int edad;
            cout << "Ingrese el nombre del paciente: ";
            cin.ignore();
            getline(cin, nombre);
            edad = leerNumero("Ingrese la edad del paciente: ");

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

        case 3: {
            if (pacientes.empty()) {
                cout << "No hay pacientes que eliminar." << endl;
                break;
            }

            cout << "\n=== Eliminar Paciente ===" << endl;
            for (size_t i = 0; i < pacientes.size(); ++i) {
                cout << i + 1 << ". ";
                pacientes[i].mostrarDetalles();
            }
            cout << "0. Cancelar eliminación" << endl;

            int seleccion;
            do {
                seleccion = leerNumero("Selecciona el paciente a eliminar (0 para cancelar): ");
                if (seleccion == 0) {
                    cout << "Cancelando eliminación..." << endl;
                    break;
                }
                else if (seleccion < 1 || seleccion > static_cast<int>(pacientes.size())) {
                    cout << "No válido." << endl;
                }
            } while (seleccion < 0 || seleccion > static_cast<int>(pacientes.size()));

            if (seleccion != 0) {
                pacientes.erase(pacientes.begin() + (seleccion - 1));
                cout << "Paciente eliminado con éxito." << endl;
            }
            break;
        }
        case 4:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "No válido." << endl;
            break;
        }
    } while (opcion != 3);
}

void gestionarMedicos(vector<Medico>& medicos) {
    vector<string> especialidades = { "Cardiología", "Pediatría", "Neurología", "Dermatología", "Traumatología" };

    int opcion;
    do {
        cout << "\n=== Gestión de Médicos ===" << endl;
        cout << "1. Registrar médico" << endl;
        cout << "2. Listar médicos" << endl;
        cout << "3. Eliminar médico" << endl;
        cout << "4. Volver al menú principal" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre;
            cout << "Ingrese el nombre del médico: ";
            cin.ignore();
            getline(cin, nombre);

            cout << "\n=== Especialidades Disponibles ===" << endl;
            for (size_t i = 0; i < especialidades.size(); ++i) {
                cout << i + 1 << ". " << especialidades[i] << endl;
            }

            int seleccion;
            do {
                seleccion = leerNumero("Selecciona la especialidad (1-" + to_string(especialidades.size()) + "): ");
                if (seleccion < 1 || seleccion > static_cast<int>(especialidades.size())) {
                    cout << "No válido." << endl;
                }
            } while (seleccion < 1 || seleccion > static_cast<int>(especialidades.size()));

            string especialidadSeleccionada = especialidades[seleccion - 1];

            medicos.emplace_back(nombre, especialidadSeleccionada);
            cout << "Médico registrado" << endl;
            break;
        }
        case 2: {
            cout << "\n=== Lista de Médicos ===" << endl;
            if (medicos.empty()) {
                cout << "No hay registros." << endl;
            }
            else {
                for (const auto& medico : medicos) {
                    medico.mostrarDetalles();
                }
            }
            break;
        }
        case 3: {
            if (medicos.empty()) {
                cout << "No hay médicos que eliminar." << endl;
                break;
            }

            cout << "\n=== Eliminar Médico ===" << endl;
            for (size_t i = 0; i < medicos.size(); ++i) {
                cout << i + 1 << ". ";
                medicos[i].mostrarDetalles();
            }
            cout << "0. Cancelar eliminación" << endl;

            int seleccion;
            do {
                seleccion = leerNumero("Selecciona el médico a eliminar (0 para cancelar): ");
                if (seleccion == 0) {
                    cout << "Cancelando eliminación..." << endl;
                    break;
                }
                else if (seleccion < 1 || seleccion > static_cast<int>(medicos.size())) {
                    cout << "No válido" << endl;
                }
            } while (seleccion < 0 || seleccion > static_cast<int>(medicos.size()));

            if (seleccion != 0) {
                medicos.erase(medicos.begin() + (seleccion - 1));
                cout << "Médico eliminado con éxito." << endl;
            }
            break;
        }

        case 4:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Error, pruebe de nuevo." << endl;
            break;
        }
    } while (opcion != 3);
}


int main() {
    // SetConsoleOutputCP(1252);  // Para el texto en Windows
    vector<Paciente> pacientes;
    vector<Medico> medicos;

    cargarPacientes(pacientes);
    cargarMedicos(medicos);

    int opcion;
    do {
        cout << "\n=== Menú Principal ===" << endl;
        cout << "1. Gestionar pacientes" << endl;
        cout << "2. Gestionar médicos" << endl;
        cout << "3. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestionarPacientes(pacientes);
            break;
        case 2:
            gestionarMedicos(medicos);
            break;
        case 3:
            guardarPacientes(pacientes);
            guardarMedicos(medicos);
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
        }
    } while (opcion != 3);

    return 0;
}
