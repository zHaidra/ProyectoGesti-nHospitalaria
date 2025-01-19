#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <regex>
//#include "Windows.h"

using namespace std; // Para evitar escribir continuamente std

class Paciente {
public:
    Paciente(string nombre, int edad, string dni) : nombre(nombre), edad(edad), dni(dni) {}

    void mostrarDetalles() const {
        cout << "Nombre: " << nombre << ", Edad: " << edad << " años, DNI: " << dni << endl;
    }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    string getDni() const { return dni; }

    void agregarHistorial(const string& historial) {
        this->historialMedico = historial;
    }

    void mostrarHistorial() const {
        cout << "Historial Médico: " << (historialMedico.empty() ? "No disponible" : historialMedico) << endl;
    }

private:
    string nombre;
    int edad;
    string dni;
    string historialMedico;
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

class CitaMedica {
public:
    CitaMedica(string paciente, string medico, string fecha, string hora, string sintomas = "")
        : paciente(paciente), medico(medico), fecha(fecha), hora(hora), sintomas(sintomas) {}

    void mostrarDetalles() const {
        cout << "Paciente: " << paciente << ", Médico: " << medico
            << ", Fecha: " << fecha << ", Hora: " << hora
            << ", Síntomas: " << sintomas << endl;
    }

    string getPaciente() const { return paciente; }
    string getMedico() const { return medico; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    string getSintomas() const { return sintomas; }

private:
    string paciente;
    string medico;
    string fecha;
    string hora;
    string sintomas;
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

bool validarFecha(const string& fecha) {
    regex formatoFecha("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    return regex_match(fecha, formatoFecha);
}

bool validarHora(const string& hora) {
    regex formatoHora("^([01][0-9]|2[0-3]):([0-5][0-9])$");
    return regex_match(hora, formatoHora);
}

bool validarDNI(const string& dni) {
    regex formatoDNI("^[0-9]{8}[A-Za-z]$");
    if (!regex_match(dni, formatoDNI)) {
        return false;
    }

    string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
    int numeros = stoi(dni.substr(0, 8));
    char letraEsperada = letras[numeros % 23];
    char letraProporcionada = toupper(dni.back());

    return letraEsperada == letraProporcionada;
}

string leerDNI() {
    string dni;
    do {
        cout << "Ingrese el DNI (8 dígitos seguidos de una letra): ";
        cin >> dni;
        if (!validarDNI(dni)) {
            cout << "DNI no válido. Intente nuevamente." << endl;
        }
    } while (!validarDNI(dni));
    return dni;
}

string leerFecha() {
    string fecha;
    do {
        cout << "Ingrese la fecha (DD/MM/YYYY): ";
        cin >> fecha;
        if (!validarFecha(fecha)) {
            cout << "Formato de fecha incorrecto. Intente de nuevo." << endl;
        }
    } while (!validarFecha(fecha));
    return fecha;
}

string leerHora() {
    string hora;
    do {
        cout << "Ingrese la hora (HH:MM): ";
        cin >> hora;
        if (!validarHora(hora)) {
            cout << "Formato de hora incorrecto. Intente de nuevo." << endl;
        }
    } while (!validarHora(hora));
    return hora;
}

string leerSintomas() {
    cin.ignore();
    cout << "Describa los síntomas: ";
    string sintomas;
    getline(cin, sintomas);
    return sintomas;
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

void guardarCitas(const vector<CitaMedica>& citas) {
    ofstream archivo("citas.txt", ios::out);
    if (!archivo) {
        cerr << "Error al abrir el archivo citas.txt." << endl;
        return;
    }

    for (const auto& cita : citas) {
        archivo << cita.getPaciente() << ","
            << cita.getMedico() << ","
            << cita.getFecha() << ","
            << cita.getHora() << endl;
    }

    archivo.close();
    cout << "Citas guardadas correctamente." << endl;
}

void registrarCita(vector<CitaMedica>& citas, const vector<Paciente>& pacientes, const vector<Medico>& medicos) {
    if (pacientes.empty()) {
        cout << "Sin pacientes registrados" << endl;
        return;
    }

    if (medicos.empty()) {
        cout << "Sin medicos registrados." << endl;
        return;
    }

    cout << "\n=== Selecciona un Paciente ===" << endl;
    for (size_t i = 0; i < pacientes.size(); ++i) {
        cout << i + 1 << ". ";
        pacientes[i].mostrarDetalles();
    }

    int pacienteSeleccionado;
    do {
        pacienteSeleccionado = leerNumero("Selecciona el paciente (1-" + to_string(pacientes.size()) + "): ");
        if (pacienteSeleccionado < 1 || pacienteSeleccionado > static_cast<int>(pacientes.size())) {
            cout << "No válido." << endl;
        }
    } while (pacienteSeleccionado < 1 || pacienteSeleccionado > static_cast<int>(pacientes.size()));
    string paciente = pacientes[pacienteSeleccionado - 1].getNombre();

    cout << "\n=== Selecciona un Médico ===" << endl;
    for (size_t i = 0; i < medicos.size(); ++i) {
        cout << i + 1 << ". ";
        medicos[i].mostrarDetalles();
    }

    int medicoSeleccionado;
    do {
        medicoSeleccionado = leerNumero("Selecciona el médico (1-" + to_string(medicos.size()) + "): ");
        if (medicoSeleccionado < 1 || medicoSeleccionado > static_cast<int>(medicos.size())) {
            cout << "No válido" << endl;
        }
    } while (medicoSeleccionado < 1 || medicoSeleccionado > static_cast<int>(medicos.size()));
    string medico = medicos[medicoSeleccionado - 1].getNombre();

    string fecha = leerFecha();
    string hora = leerHora();
    string sintomas = leerSintomas();

    citas.emplace_back(paciente, medico, fecha, hora, sintomas);
    cout << "Cita registrada." << endl;
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
        string nombre, dni;
        int edad;

        getline(ss, nombre, ',');
        ss >> edad;
        if (!nombre.empty()) {
            pacientes.emplace_back(nombre, edad, dni);
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

void cargarCitas(vector<CitaMedica>& citas, const vector<Paciente>& pacientes, const vector<Medico>& medicos) {
    ifstream archivo("citas.txt", ios::in);
    if (!archivo) {
        cout << "No se encontró el archivo citas.txt. Creando nuevo..." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string paciente, medico, fecha, hora;

        getline(ss, paciente, ',');
        getline(ss, medico, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');

        citas.emplace_back(paciente, medico, fecha, hora);
    }

    archivo.close();
    cout << "Citas cargadas correctamente." << endl;
}

void gestionarPacientes(vector<Paciente>& pacientes) {
    int opcion;
    do {
        cout << "\n=== Gestión de Pacientes ===" << endl;
        cout << "1. Registrar paciente" << endl;
        cout << "2. Listar pacientes" << endl;
        cout << "3. Eliminar paciente" << endl;
        cout << "4. Añadir historial médico" << endl;
        cout << "5. Volver al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, dni;
            int edad;
            cout << "Ingrese el nombre del paciente: ";
            cin.ignore();
            getline(cin, nombre);
            edad = leerNumero("Ingrese la edad: ");
            cout << "Ingrese el DNI del paciente: ";
            dni = leerDNI();

            pacientes.emplace_back(nombre, edad, dni);
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
        case 4: {
            if (pacientes.empty()) {
                cout << "No hay pacientes registrados." << endl;
                break;
            }

            for (size_t i = 0; i < pacientes.size(); ++i) {
                cout << i + 1 << ". ";
                pacientes[i].mostrarDetalles();
            }
            int seleccion = leerNumero("Seleccione el paciente para añadir historial médico: ");
            if (seleccion < 1 || seleccion > static_cast<int>(pacientes.size())) {
                cout << "Selección no válida." << endl;
                break;
            }

            cin.ignore();
            cout << "Ingrese el historial médico: ";
            string historial;
            getline(cin, historial);
            pacientes[seleccion - 1].agregarHistorial(historial);
            cout << "Historial médico añadido con éxito." << endl;
            break;
        }
        case 5:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
        }
    } while (opcion != 5);
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
    } while (opcion != 4);
}

void listarCitas(const vector<CitaMedica>& citas) {
    cout << "\n=== Lista de Citas ===" << endl;
    if (citas.empty()) {
        cout << "No hay citas registradas." << endl;
    }
    else {
        for (const auto& cita : citas) {
            cita.mostrarDetalles();
        }
    }
}

void eliminarCita(vector<CitaMedica>& citas) {
    if (citas.empty()) {
        cout << "No hay citas que eliminar." << endl;
        return;
    }

    cout << "\n=== Eliminar Cita ===" << endl;
    for (size_t i = 0; i < citas.size(); ++i) {
        cout << i + 1 << ". ";
        citas[i].mostrarDetalles();
    }
    cout << "0. Cancelar" << endl;

    int seleccion;
    do {
        seleccion = leerNumero("Selecciona que cita (0 para cancelar): ");
        if (seleccion == 0) {
            cout << "Cancelando operación..." << endl;
            return;
        }
        else if (seleccion < 1 || seleccion > static_cast<int>(citas.size())) {
            cout << "Selección no válida." << endl;
        }
    } while (seleccion < 0 || seleccion > static_cast<int>(citas.size()));

    citas.erase(citas.begin() + (seleccion - 1));
    cout << "Cita eliminada." << endl;
}

void gestionarCitas(vector<CitaMedica>& citas, const vector<Paciente>& pacientes, const vector<Medico>& medicos) {
    int opcion;
    do {
        cout << "\n=== Gestión de Citas ===" << endl;
        cout << "1. Registrar cita" << endl;
        cout << "2. Listar citas" << endl;
        cout << "3. Eliminar cita" << endl;
        cout << "4. Volver al menú principal" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarCita(citas, pacientes, medicos);

            break;
        case 2:
            listarCitas(citas);
            break;
        case 3:
            eliminarCita(citas);
            break;
        case 4:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
        }
    } while (opcion != 4);
}

int main() {
    // SetConsoleOutputCP(1252);  // Para el texto en Windows
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<CitaMedica> citas;

    cargarPacientes(pacientes);
    cargarMedicos(medicos);
    cargarCitas(citas, pacientes, medicos);

    int opcion;
    do {
        cout << "\n=== Menú Principal ===" << endl;
        cout << "1. Gestionar pacientes" << endl;
        cout << "2. Gestionar médicos" << endl;
        cout << "3. Gestionar citas" << endl;
        cout << "4. Guardar y Salir" << endl;
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
            gestionarCitas(citas, pacientes, medicos);
            break;
        case 4:
            guardarPacientes(pacientes);
            guardarMedicos(medicos);
            guardarCitas(citas);
             
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "No válido." << endl;
            break;
        }
    } while (opcion != 4);

    return 0;
}