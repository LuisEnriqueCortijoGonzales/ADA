//
// Created by lecor on 25/07/2024.
//

#ifndef REPECHAJE_GENERADOR_ALEATORIOS_H
#define REPECHAJE_GENERADOR_ALEATORIOS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <unordered_set>
using namespace std;

//la estructura usada para representar los intervalos en el ejercicio 2
struct Interval {
    int s, t;
};


vector<int> cadenas_rotadas(int n, int b) {
    unsigned long long size = 1;
    for (int i = 0; i < b; ++i) {
        size *= n;
    }
    unsigned long long techo_numeros = size * 10; // Una potencia de 10 extra para que los arrays no sean series del 1 al n^b
    unordered_set<int> numeros_unicos;

    random_device rd;  // Para obtener una semilla aleatoria
    mt19937 gen(rd()); // Motor de generación Mersenne Twister, el más eficiente que encontre para estas grandes cantidades de datos
    uniform_int_distribution<int> dis(0, techo_numeros - 1);

    while (numeros_unicos.size() < size) {
        numeros_unicos.insert(dis(gen));
    }

    vector<int> A(numeros_unicos.begin(), numeros_unicos.end());
    sort(A.begin(), A.end()); // Ordenar el vector
    return A;
}

vector<int> k_rotacion(const vector<int>& A, int k) {
    int n = A.size();
    vector<int> B(n);

    for (int i = 0; i < n; ++i) {
        B[i] = A[(i + k) % n];
    }

    return B;
}
// Función para generar intervalos aleatorios
vector<Interval> generarIntervalosAleatorios(int n, int rangoInicio, int rangoFin) {
    vector<Interval> intervalos(n);
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    for (int i = 0; i < n; ++i) {
        int s = rand() % (rangoFin - rangoInicio + 1) + rangoInicio;
        int t = rand() % (rangoFin - rangoInicio + 1) + rangoInicio;
        if (s > t) swap(s, t); // Asegurarse de que s <= t
        intervalos[i] = {s, t};
    }

    return intervalos;
}

vector<int> generarCortesAleatorios(int n, int l) {
    set<int> cortesSet;
    cortesSet.insert(0); // Insertar el primer corte en 0
    cortesSet.insert(l); // Insertar el último corte en l

    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    while (cortesSet.size() < n + 2) { // Hasta tener n+2 elementos (incluyendo 0 y l)
        int nuevoCorte = rand() % (l - 1) + 1; // Generar cortes aleatorios entre 1 y l-1
        cortesSet.insert(nuevoCorte); // Insertar el corte en el set (automáticamente evitará duplicados)
    }

    vector<int> cortes(cortesSet.begin(), cortesSet.end()); // Convertir el set en un vector
    sort(cortes.begin(), cortes.end()); // Ordenar los cortes (opcional, ya que el set los mantiene ordenados)

    return cortes;
}



#endif //REPECHAJE_GENERADOR_ALEATORIOS_H
