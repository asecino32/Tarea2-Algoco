#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <unistd.h>
#include <ios>
#include <sys/resource.h>

using namespace std;

int matriz_costos[26][26];
int matriz_trans[26][26];
int arr_insert[26];
int arr_elim[26];

// Función para escribir los resultados obtenidos en un archivo (función extraida de chatgpt)
void escribirResultados(int largo_s1, int largo_s2, double tiempo_ms, size_t memoria_usada = 0) {
    ofstream archivo("resultados_fb.txt", ios::app); // 'ios::app' abre el archivo en modo append
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo 'resultados_fb.txt' para escribir" << endl;
        return;
    }
    
    // Escribir en el archivo el largo de las cadenas, el tiempo y la memoria usada (si está disponible)
    archivo << largo_s1 << " " << largo_s2 << " " << tiempo_ms;
    if (memoria_usada > 0) {
        archivo << " " << memoria_usada; // Añadir el uso de memoria si está disponible
    }
    archivo << endl;

    archivo.close();
}

// Función para obtener el uso de memoria en bytes (función extraida de chatgpt)
size_t obtenerUsoMemoria() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss * 1024; // Convertir de KB a bytes
}

// Función para leer una matriz de 26x26 desde un archivo (función extraida de chatgpt)
void leerMatriz(const string& nombreArchivo, int matriz[26][26]) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }
    // Leer los valores y asignarlos a la matriz
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close();
}

// Función para leer un arreglo de tamaño 26 desde un archivo (función extraida de chatgpt)
void leerArreglo(const string& nombreArchivo, int arreglo[26]) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }
    // Leer los valores y asignarlos al arreglo
    for (int i = 0; i < 26; ++i) {
        archivo >> arreglo[i];
    }
    archivo.close();
}


// Calcula el costo de sustituir el carácter ‘a’ por ‘b’.
// Parámetros:
//−a: carácter original
//−b: carácter con el que se sustituye
// Return: costo de sustituir ’a’ por ’b’
int costo_sub(char a, char b) {
    int costo;
    int fila= a-97;
    int columna= b-97;
    costo=matriz_costos[fila][columna];
    // Implementación
    return costo;
}

// Calcula el costo de insertar el carácter ‘b’.
// Parámetros:
//−b: carácter a insertar
// Return: costo de insertar ’b’
int costo_ins(char b) {
    int costo;
    int pos= b-97;
    costo=arr_insert[pos];
    // Implementación
    return costo;
}

// Calcula el costo de eliminar el carácter ’a ’.
// Parámetros:
//−a: carácter a eliminar
// Return: costo de eliminar ’a’
int costo_del(char a) {
    int costo;
    int pos= a-97;
    costo=arr_elim[pos];
    // Implementación
    return costo;
}

// Calcula el costo de transponer los caracteres ’a’ y ’b’.
// Parámetros:
//−a: primer carácter a transponer
//−b: segundo carácter a transponer
// Return: costo de transponer ’a’ y ’b’
int costo_trans(char a, char b) {
    int costo;
    int fila= a-97;
    int columna= b-97;
    costo=matriz_trans[fila][columna];
    // Implementación
    return costo;
}

int edicion_cadenas(string &p1, string &p2,int indice){
    int s1=p1.size(),s2=p2.size(), costo=0;
    if(p1==p2){
        return costo;
    }
    if(s1-1==indice && s2-1==indice){
        if(p1[indice]!=p2[indice]){
            costo+=costo_sub(p1[indice],p2[indice]);
            p1[indice]=p2[indice];
        }
        return costo;
    }
    //p1 mas pequeño que p2
    if(s1 < s2 && indice>=s1){
        p1.push_back(p2[indice]);
        costo+=costo_ins(p2[indice]);
    }
    //p2 mas pequeño que p1
    if(s1>s2 && indice>=s2){
        costo+=costo_del(p1[s1-1]);
        p1.pop_back();
        indice--;  
    }
    else if(p1[indice]!=p2[indice]){
        
        if (indice + 1 < s1 && p1[indice + 1] == p2[indice]) {
            string p1_aux = p1, p1_saux = p1;
            swap(p1_aux[indice], p1_aux[indice+1]);

            if (costo_trans(p1[indice], p1[indice + 1]) + edicion_cadenas(p1_aux, p2, indice + 1) <= 
                edicion_cadenas(p1_saux, p2, indice + 1) + costo_sub(p1[indice], p2[indice])) {
                costo += costo_trans(p1[indice], p1[indice + 1]);
                swap(p1[indice], p1[indice+1]);
            } else {
                costo += costo_sub(p1[indice], p2[indice]);
                p1[indice] = p2[indice];
            }
        } 
        
        else if (indice + 1 < s2 && p1[indice] == p2[indice + 1]) {
            string p1_aux = p1, p1_saux = p1;
            p1_aux[indice + 1] = p2[indice];
            swap(p1_aux[indice], p1_aux[indice+1]);

            if (p1[indice + 1] != p2[indice]) {
                if (costo_trans(p1[indice], p1[indice + 1]) + costo_sub(p1[indice + 1], p2[indice]) + edicion_cadenas(p1_aux, p2, indice + 1) <= 
                    edicion_cadenas(p1_saux, p2, indice + 1) + costo_sub(p1[indice], p2[indice])) {
                    costo += costo_trans(p1[indice], p1[indice + 1]);
                    costo += costo_sub(p1[indice + 1], p2[indice]);
                    p1[indice + 1] = p2[indice];
                    int aux = p1[indice];
                    p1[indice] = p1[indice + 1];
                    p1[indice + 1] = aux;
                } else {
                    costo += costo_sub(p1[indice], p2[indice]);
                    p1[indice] = p2[indice];
                }
            } else if (costo_trans(p1[indice], p1[indice + 1]) + edicion_cadenas(p1_aux, p2, indice + 1) <= 
                       edicion_cadenas(p1_aux, p2, indice + 1) + costo_sub(p1[indice], p2[indice])) {
                costo += costo_trans(p1[indice], p1[indice + 1]);
                int aux = p1[indice];
                p1[indice] = p1[indice + 1];
                p1[indice + 1] = aux;
            } else {
                costo += costo_sub(p1[indice], p2[indice]);
                p1[indice] = p2[indice];
            }
        } 
        
        else {
            costo += costo_sub(p1[indice], p2[indice]);
            p1[indice] = p2[indice];
        }
        
    }

    return costo + edicion_cadenas(p1,p2,indice+1);
}


int main(){
    leerArreglo("cost_insert.txt", arr_insert);
    leerArreglo("cost_delete.txt", arr_elim);
    leerMatriz("cost_replace.txt", matriz_costos);
    leerMatriz("cost_transpose.txt", matriz_trans);
    /*
    // Mostrar los valores leídos para verificar (opcional)
    cout << "Valores de arr_insert:" << endl;
    for (int i = 0; i < 26; ++i) {
        cout << arr_insert[i] << " ";
    }
    cout << endl;

    cout << "Valores de arr_elim:" << endl;
    for (int i = 0; i < 26; ++i) {
        cout << arr_elim[i] << " ";
    }
    cout << endl;

    cout << "Valores de matriz_costos:" << endl;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            cout << matriz_costos[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Valores de matriz_trans:" << endl;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            cout << matriz_trans[i][j] << " ";
        }
        cout << endl;
    }
    */
    ifstream archivo("casos.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo 'casos.txt'" << endl;
        return 1;
    }
    while(true){
        string palabra1, palabra2;
        if(archivo.eof()){
            break;
        }
        if(!getline(archivo, palabra1)) break;
        if(!getline(archivo, palabra2)) break;
        palabra1.pop_back();
        palabra2.pop_back();
        string a(palabra1.begin(), palabra1.end());
        string b(palabra2.begin(), palabra2.end());
        using chrono::high_resolution_clock;
        using chrono::duration_cast;
        using chrono::duration;
        using chrono::milliseconds;
        auto t1 = high_resolution_clock::now();
        int costo=edicion_cadenas(a,b,0);
        auto t2 = high_resolution_clock::now();
        duration<double, milli> ms_double = t2 - t1;
        size_t memoria_usada = obtenerUsoMemoria();
        int tam1=a.size(),tam2=b.size();
        cout<<"palabra 1 pos edicion: ";
        for(int i=0;i<tam1;i++){
            cout<<a[i]<<"";
        }
        cout<<'\n'<<"palabra 2 pos edicion: ";
        for(int i=0;i<tam2;i++){
            cout<<b[i]<<"";
        }
        cout<<'\n';
        cout << ms_double.count() << " ms\n";
        cout<<"costo: "<<costo<<'\n';
        cout<<"------------------------------------------------------\n";
        

        escribirResultados(palabra1.size(), palabra2.size(), ms_double.count(), memoria_usada);
        a.clear();
        b.clear();
    }
    archivo.close();
    return 0;
}