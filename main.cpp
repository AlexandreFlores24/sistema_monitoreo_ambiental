#include <iostream>
using namespace std;
/*Sistema de Monitoreo Ambiental con Red de Sensores*/
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
            std::cout << "Sensor " << actual->id 
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
            std::cout << "? " << actual->mensaje << " (Sensor " << actual->sensorId << ")\n";
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

int main() {

    return 0;
}
