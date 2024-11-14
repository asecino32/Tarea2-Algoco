#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <chrono>
#include <algorithm>
#include <unistd.h>
#include <ios>
#include <sys/resource.h>

using namespace std;

map<pair<string, string>, int> valores_ya_resueltos;
string p1,p2;

int matriz_costos[26][26];
int matriz_trans[26][26];
int arr_insert[26];
int arr_elim[26];

// Función para escribir los resultados obtenidos en un archivo (función extraida de chatgpt)
void escribirResultados(int largo_s1, int largo_s2, double tiempo_ms, size_t memoria_usada = 0) {
    ofstream archivo("resultados_pdm.txt", ios::app); // 'ios::app' abre el archivo en modo append
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo 'resultados_pdm.txt' para escribir" << endl;
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

int cont;
int edicion_cadenas(string a, string b) {
    int costo = 0;
    cont++; //sumo al contador global para recorrer las palabras originales
    pair<string, string> key = make_pair(a, b); // creo la tupla para buscar en el map

    // veo en el map si ya se ha resuelto
    if (valores_ya_resueltos.find(key) != valores_ya_resueltos.end()) {
        p1=p2;
        return valores_ya_resueltos[key];
    }

    int s1 = a.size(), s2 = b.size();

    /*
    // Mostrar estado actual de las palabras
    cout << "palabra 1: ";
    for (char c : a) cout << c;
    cout<<"\nel tamaño de a es: "<<s1;
    cout << '\n' << "palabra 2: ";
    for (char c : b) cout << c;
    cout << '\n';
    cout<<"el tamaño de b es: "<<s2<<'\n';
    */

    // Caso base: las palabras son iguales
    if (a == b) {
        return costo;
    }
    else if(a.empty() && b.empty()){
        return costo;
    }
    // Caso base: ambas palabras con un solo carácter
    if (s1 == 1 && s2 == 1) {
        if (a[0] != b[0]) {
            costo += costo_sub(a[0], b[0]);
            p1[cont] = p2[cont];
        }
        return valores_ya_resueltos[key] = costo;
    }
    if (s1 < s2 && s1==0) { // Inserción al string a
        costo += costo_ins(b[0]);
        p1.push_back(b[0]); //modifico el string global
        string a_next(a.begin(), a.end());  // Copiar a en otro string
        a_next.insert(a_next.begin(), b[0]);  // Insertar b[0] en el inicio de a_next
        return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end()));
    } else if (s1 > s2 && s2==0) { // Eliminar elementos sobrantes de a
        costo += costo_del(a[0]); //costo de borrar la primera letra sobrante de a
        p1.pop_back(); //borrar un elemento de p1, no afecta al vector a, por lo que no importa cual sea
        cont--;
        return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a.begin() + 1, a.end()), b);
    } else if (a[0] != b[0]) {
        if (s1 > 1 && s2 > 1 && a[1] == b[0]) { //se transpone el primer por el segundo elemento
            costo += costo_trans(a[0], a[1]);
            swap(p1[cont], p1[cont+1]); //cambiar los elementos equivalentes del vector p1
            string a_next = a;
            swap(a_next[0], a_next[1]); //transponer el primer y segundo elemento de a
            if(costo_trans(a[0], a[1]) + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end())) <= costo_sub(a[0], b[0]) + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()))){
                return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end()));
            }
            else{
                costo += costo_sub(a[0], b[0]) - costo_trans(a[0], a[1]);
                swap(p1[cont], p1[cont+1]);
                p1[cont]=p2[cont];//se sutituye el valor en la posicion del contador en p1 equivalente en p2
                return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()));
            }
        }
        else if (s1 > 1 && s2 > 1 && a[0] == b[1]) {
            // Transposición
            costo += costo_trans(a[0], a[1]);
            if(a[1] != b[0]){//se sustituye el segundo elemento para dejar la palabra igual
                costo += costo_sub(a[1],b[0]);
                char aux= p1[cont+1];
                p1[cont+1]=p2[cont]; //sustituir en p1
                swap(p1[cont], p1[cont+1]); //transponer en p1
                string a_next = a;
                swap(a_next[0], a_next[1]); //transponer el primer y segundo elemento de a
                if(costo_trans(a[0], a[1]) + costo_sub(a[1],b[0]) + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end())) <= costo_sub(a[0], b[0]) + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()))){
                    return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end()));
                }
                else{
                    swap(p1[cont], p1[cont+1]);
                    costo += costo_sub(a[0], b[0]) - costo_trans(a[0], a[1]) - costo_sub(a[1],b[0]);
                    p1[cont+1]=aux;
                    p1[cont]=p2[cont];//se sutituye el valor en la posicion del contador en p1 equivalente en p2
                    return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()));
                }
            }
            else{
                swap(p1[cont], p1[cont+1]); //transponer en p1
                string a_next = a;
                swap(a_next[0], a_next[1]); //transponer el primer y segundo elemento de a
                if(costo_trans(a[0], a[1]) + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end())) <= costo_sub(a[0], b[0]) + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()))){
                    return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a_next.begin() + 1, a_next.end()), string(b.begin() + 1, b.end()));
                }
                else{
                    swap(p1[cont], p1[cont+1]);
                    costo += costo_sub(a[0], b[0]) - costo_trans(a[0], a[1]);
                    p1[cont]=p2[cont];//se sutituye el valor en la posicion del contador en p1 equivalente en p2
                    return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()));
                }
            }
            
        } 
        else {
            costo += costo_sub(a[0], b[0]);
            p1[cont]=p2[cont];//se sutituye el valor en la posicion del contador en p1 equivalente en p2
            return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()));
        }
    }

    // Llamada recursiva si los caracteres son iguales
    return valores_ya_resueltos[key] = costo + edicion_cadenas(string(a.begin() + 1, a.end()), string(b.begin() + 1, b.end()));
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

    // Leer de dos en dos líneas
    while (true) {
        if(archivo.eof()){
            break;
        }
        string palabra1, palabra2;
        if(!getline(archivo, palabra1)) break;
        if(!getline(archivo, palabra2)) break;
        palabra1.pop_back();
        palabra2.pop_back();
        cont= -1;
        string a(palabra1.begin(), palabra1.end());
        string b(palabra2.begin(), palabra2.end());
        p1=a;
        p2=b;
        using chrono::high_resolution_clock;
        using chrono::duration_cast;
        using chrono::duration;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        int costo=edicion_cadenas(a,b);
        auto t2 = high_resolution_clock::now();
        duration<double, milli> ms_double = t2 - t1;
        size_t memoria_usada = obtenerUsoMemoria();
        /*
        //mostrar contenidos del map
        for(const auto& entry : valores_ya_resueltos){
            const auto& key = entry.first;
            int value= entry.second;
            cout<<"clave: (";
            for(char c : key.first){
                cout<<c<<' ';
            }
            cout<<") y (";
            for(char c : key.second){
                cout<<c<<' ';
            }
            cout<<") valor: "<<value<<'\n';
        }
        */
        cout<<"palabra 1 pos edicion: "<<p1;
        cout<<'\n'<<"palabra 2 pos edicion: "<<p2<<"\n";
        cout << ms_double.count() << " ms\n";
        cout<<"costo: "<<costo<<'\n';
        cout<<"------------------------------------------------------\n";
        escribirResultados(palabra1.size(), palabra2.size(), ms_double.count(), memoria_usada);
        p1.clear();
        p2.clear();
        valores_ya_resueltos.clear();
    }
    
    archivo.close();
    return 0;
}