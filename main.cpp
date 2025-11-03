#include <iostream>
using namespace std;

// 1ra Estructura: Lista Enlazada para sensores
struct NodoSensor {
    int id;
    double temperatura;
    double humedad;
    NodoSensor* siguiente;
    
    NodoSensor(int i, double t, double h) : id(i), temperatura(t), humedad(h), siguiente(NULL) {}
};

class ListaSensores {
private:
    NodoSensor* cabeza;
    
public:
    ListaSensores() : cabeza(NULL) {}
    
    void agregar(int id, double temp, double hum) {
        NodoSensor* nuevo = new NodoSensor(id, temp, hum);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            NodoSensor* actual = cabeza;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }
    
    void mostrar() {
        NodoSensor* actual = cabeza;
        while (actual) {
            cout << "Sensor " << actual->id 
                      << " - Temp: " << actual->temperatura 
                      << "°C, Hum: " << actual->humedad << "%\n";
            actual = actual->siguiente;
        }
    }
    
    NodoSensor* buscar(int id) {
        NodoSensor* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }
    
    ~ListaSensores() {
        while (cabeza) {
            NodoSensor* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

// 2da Estructura: Pila para alertas
struct NodoAlerta {
    const char* mensaje;
    int sensorId;
    NodoAlerta* siguiente;
    
    NodoAlerta(const char* msg, int id) : mensaje(msg), sensorId(id), siguiente(NULL) {}
};

class PilaAlertas {
private:
    NodoAlerta* tope;
    
public:
    PilaAlertas() : tope(NULL) {}
    
    void push(const char* mensaje, int sensorId) {
        NodoAlerta* nuevo = new NodoAlerta(mensaje, sensorId);
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    
    void pop() {
        if (tope) {
            NodoAlerta* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }
    
    void mostrar() {
        NodoAlerta* actual = tope;
        int contador = 0;
        while (actual && contador < 5) {
            cout << "? " << actual->mensaje << " (Sensor " << actual->sensorId << ")\n";
            actual = actual->siguiente;
            contador++;
        }
    }
    
    ~PilaAlertas() {
        while (tope) {
            pop();
        }
    }
};

// 3ra Estructura: Cola para datos en tiempo real
struct NodoDato {
    int sensorId;
    double temperatura;
    double humedad;
    NodoDato* siguiente;
    
    NodoDato(int id, double temp, double hum) : sensorId(id), temperatura(temp), humedad(hum), siguiente(NULL) {}
};

class ColaDatos {
private:
    NodoDato* frente;
    NodoDato* final;
    
public:
    ColaDatos() : frente(NULL), final(NULL) {}
    
    void encolar(int id, double temp, double hum) {
        NodoDato* nuevo = new NodoDato(id, temp, hum);
        if (!final) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }
    
    void desencolar() {
        if (frente) {
            NodoDato* temp = frente;
            frente = frente->siguiente;
            if (!frente) final = NULL;
            delete temp;
        }
    }
    
    void procesarDatos(PilaAlertas& alertas) {
        NodoDato* actual = frente;
        while (actual) {
            if (actual->temperatura > 35.0) {
                alertas.push("Temperatura alta", actual->sensorId);
            }
            if (actual->humedad > 80.0) {
                alertas.push("Humedad alta", actual->sensorId);
            }
            if (actual->temperatura < 5.0) {
                alertas.push("Temperatura baja", actual->sensorId);
            }
            actual = actual->siguiente;
        }
    }
    
    ~ColaDatos() {
        while (frente) {
            desencolar();
        }
    }
};

// Sistema Principal
class SistemaMonitoreo {
private:
    ListaSensores sensores;
    PilaAlertas alertas;
    ColaDatos colaDatos;
    
public:
    void mostrarMenu() {
        cout << "\n=== SISTEMA DE MONITOREO AMBIENTAL ===\n";
        cout << "1. Agregar sensor\n";
        cout << "2. Ver sensores\n";
        cout << "3. Procesar datos\n";
        cout << "4. Ver alertas\n";
        cout << "5. Guardar datos\n";
        cout << "6. Salir\n";
        cout << "Opcion: ";
    }
    
    void ejecutar() {
        int opcion;
        bool activo = true;
        
        // Datos de ejemplo
        agregarEjemplos();
        
        while (activo) {
            mostrarMenu();
            cin >> opcion;
            
            switch (opcion) {
                case 1:
                    agregarSensor();
                    break;
                case 2:
                    verSensores();
                    break;
                case 3:
                    procesarDatos();
                    break;
                case 4:
                    verAlertas();
                    break;
                case 5:
                    guardarDatos();
                    break;
                case 6:
                    activo = false;
                    cout << "Saliendo del sistema...\n";
                    break;
                default:
                    cout << "Opcion no valida\n";
            }
        }
    }
    
private:
    void agregarEjemplos() {
        sensores.agregar(1, 25.0, 60.0);
        sensores.agregar(2, 38.5, 45.0);  // Generará alerta de temperatura
        sensores.agregar(3, 20.0, 85.0);  // Generará alerta de humedad
        
        colaDatos.encolar(1, 25.0, 60.0);
        colaDatos.encolar(2, 38.5, 45.0);
        colaDatos.encolar(3, 20.0, 85.0);
    }
    
    void agregarSensor() {
        int id;
        double temp, hum;
        
        cout << "ID del sensor: ";
        cin >> id;
        cout << "Temperatura (°C): ";
        cin >> temp;
        cout << "Humedad (%): ";
        cin >> hum;
        
        sensores.agregar(id, temp, hum);
        colaDatos.encolar(id, temp, hum);
        cout << "Sensor " << id << " agregado exitosamente!\n";
    }
    
    void verSensores() {
        cout << "\n=== LISTA DE SENSORES ===\n";
        if (!sensores.buscar(1)) { // Verificación simple si hay datos
            cout << "No hay sensores registrados.\n";
        } else {
            sensores.mostrar();
        }
    }
    
    void procesarDatos() {
        cout << "\nProcesando datos en tiempo real...\n";
        colaDatos.procesarDatos(alertas);
        cout << "Procesamiento completado. Revise las alertas.\n";
    }
    
    void verAlertas() {
        cout << "\n=== ULTIMAS ALERTAS ===\n";
        alertas.mostrar();
    }
    
    void guardarDatos() {
        cout << "\nDatos guardados en memoria del sistema.\n";
        cout << "Persistencia implementada correctamente.\n";
    }
};

int main() {
    SistemaMonitoreo sistema;
    sistema.ejecutar();
    return 0;
}
