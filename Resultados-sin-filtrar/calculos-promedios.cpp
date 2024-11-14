#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Función para leer una línea de un archivo y obtener los 4 valores
bool leerLinea(ifstream &archivo, int &largo_s1, int &largo_s2, double &tiempo, int &memoria) {
    string linea;
    if (getline(archivo, linea)) {
        stringstream ss(linea);
        ss >> largo_s1 >> largo_s2 >> tiempo >> memoria;
        return true;
    }
    return false;
}

int main() {
    // Nombres de los archivos de entrada
    vector<string> archivos = {
        "resultados_pdm.txt",
        "resultados_pdm2.txt",
        "resultados_pdm3.txt",
        "resultados_pdm4.txt",
        "resultados_pdm5.txt"
    };
    
    // Abrir todos los archivos para lectura
    vector<ifstream> entradas(archivos.size());
    for (size_t i = 0; i < archivos.size(); ++i) {
        entradas[i].open(archivos[i]);
        if (!entradas[i].is_open()) {
            cerr << "Error al abrir el archivo: " << archivos[i] << endl;
            return 1;
        }
    }

    // Archivo de salida para escribir el promedio
    ofstream salida("promedio_pdm_v.txt");
    if (!salida.is_open()) {
        cerr << "Error al abrir el archivo de salida" << endl;
        return 1;
    }

    // Variables para almacenar los promedios
    int largo_s1, largo_s2, memoria;
    double tiempo;
    int sum_largo_s1, sum_largo_s2, sum_memoria;
    double sum_tiempo;
    int total_archivos = archivos.size();

    // Procesar línea por línea hasta que se alcancen todas las líneas
    while (true) {
        sum_largo_s1 = sum_largo_s2 = sum_memoria = 0;
        sum_tiempo = 0.0;
        bool fin_archivos = true;

        for (size_t i = 0; i < total_archivos; ++i) {
            if (leerLinea(entradas[i], largo_s1, largo_s2, tiempo, memoria)) {
                sum_largo_s1 += largo_s1;
                sum_largo_s2 += largo_s2;
                sum_tiempo += tiempo;
                sum_memoria += memoria;
                fin_archivos = false; // Si al menos un archivo tiene una línea, seguimos procesando
            }
        }

        // Si todos los archivos llegaron al final, salimos del bucle
        if (fin_archivos) break;

        // Calcular el promedio y escribir en el archivo de salida
        salida << (sum_largo_s1 / total_archivos) << " "
               << (sum_largo_s2 / total_archivos) << " "
               << (sum_tiempo / total_archivos) << " "
               << (sum_memoria / total_archivos) << endl;
    }

    // Cerrar todos los archivos
    for (auto &entrada : entradas) entrada.close();
    salida.close();

    cout << "Archivo 'promedio_fb_sv.txt' generado exitosamente." << endl;
    return 0;
}
