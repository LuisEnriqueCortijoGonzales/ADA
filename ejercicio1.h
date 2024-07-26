//
// Created by lecor on 24/07/2024.
//
#ifndef REPECHAJE_EJERCICIO1_H
#define REPECHAJE_EJERCICIO1_H


#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <algorithm>
#include "generador_aleatorios.h"


using namespace std;
//inspirado en la busqueda binaria, asi se asegura la complejidad lg(n) aplicando DYC
int ejer1_logn(const vector<int>& B, int primero, int ultimo) {
    if (ultimo < primero) return 0; // caso base
    if (ultimo == primero) return primero; //si solo queda un elemento en la recursion o es un array de 1 elemento

    int medio = primero + (ultimo - primero) / 2; //c++ maneja piso en caso de decimales

    //aplicacion de la logica de la busqueda binaria adaptada

    if (medio < ultimo && B[medio + 1] < B[medio])
        return medio + 1;

    if (medio > primero && B[medio] < B[medio - 1])
        return medio;

    if (B[ultimo] > B[medio])
        //paso recursivo a la izquierda
        return ejer1_logn(B, primero, medio - 1);
    //paso recursivo a la derecha
    return ejer1_logn(B, medio + 1, ultimo);

}

int ejer1_lineal(const vector<int>& B) {
    int n = B.size();
    for (int i = 0; i < n; i++) {
        if (B[i] > B[i + 1] && i+1 <n){ //itera y busca la condicion de la recurrencia
            return i + 1;
        }
    }
    return 0; //en caso no se encuentre rotacion (arreglo ordenado)
}

int ejercicio1(){
    int n;
    cout<<"ingrese la cantidad n de elementos: "<<endl;
    cin >> n;

    vector<int> array(n);

    for (int i = 0; i < n; ++i) {
        cout<<"Ingrese el "<<i<<"-esimo elemento: ";
        cin >> array[i];
        cout<<endl;
    }
    return 0;
}

void experimentar1(int p) {
    ofstream file("resultados_ejercicio1.csv");
    file << "n,algoritmo,tiempo_ns\n";

    for (int b = 1; b <= p; b++) {
        int n = 10;
        vector<int> vec = cadenas_rotadas(n, b);

        // Generacion de casos aleatorios
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, vec.size() - 1);
        int k = dis(gen);
        vector<int> vec_rotado = k_rotacion(vec, k);

        // lgn
        auto inicio = chrono::high_resolution_clock::now();
        ejer1_logn(vec_rotado, 0, vec_rotado.size() - 1);
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
        file << vec.size() << ",lg(n)," << duracion.count() << "\n";

        // lineal
        inicio = chrono::high_resolution_clock::now();
        ejer1_lineal(vec_rotado);
        fin = chrono::high_resolution_clock::now();
        duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
        file << vec.size() << ",lineal," << duracion.count() << "\n";
    }

    file.close();
}

#endif //REPECHAJE_EJERCICIO1_H
