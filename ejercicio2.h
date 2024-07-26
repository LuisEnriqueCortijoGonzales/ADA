//
// Created by lecor on 24/07/2024.
//

#ifndef REPECHAJE_EJERCICIO2_H
#define REPECHAJE_EJERCICIO2_H
#include "generador_aleatorios.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//la eleccion voras es tomar el primer intervalo no cubierto por el punto de cobertura
//al estar ordenados por punto inicial y en caso de empate primero ira el que termine al final, garantizamos cubir todos los puntos
//de forma optima
vector<int> greedy2(const vector<Interval>& I) {
    vector<int> rpta;
    int n = I.size();

    // Ordenar intervalos por punto inicial y luego por punto final en orden descendente
    vector<pair<Interval, int>> Indices_intervalos(n);
    for (int i = 0; i < n; ++i) {
        Indices_intervalos[i] = { I[i], i + 1 }; // Guardar el índice original (usando 1 como primer indice para las respuestas)
    }//por eso el i+1 en la linea superior

    sort(Indices_intervalos.begin(), Indices_intervalos.end(), [](const pair<Interval, int>& a, const pair<Interval, int>& b) {
        if (a.first.s == b.first.s) return a.first.t > b.first.t;
        return a.first.s < b.first.s;
    }); //sort con condicion especial para cuando haya elementos con el mismo inicio

    int t_final = INT_MIN; // para representar un infinito negativo y comparar
    for (const auto& [intervalo, indice] : Indices_intervalos) {
        // Si el intervalo actual empieza después del punto actual de cobertura
        if (intervalo.s > t_final || intervalo.t > t_final) {
            // Añadir el índice del intervalo actual a la solución
            rpta.push_back(indice);
            t_final = intervalo.t; // Actualizar el punto de cobertura
        }
    }

    return rpta;
} // O(n) + O(nlgn) por el sort inicial = O(n*lgn)

int ejercicio2(){
    int n;
    cout<<"ingrese la cantidad n de intervalos: "<<endl;
    cin >> n;

    vector<Interval> I(n);

    for (int i = 0; i < n; ++i) {
        cout<<"Ingrese el "<<i+1<<" intervalo\n";
        cin >> I[i].s >> I[i].t;
    }

    vector<int> rpta = greedy2(I);

    cout <<"Numero de intervalos en la cobertura optima: "<<rpta.size() << endl;
    for (int index : rpta) {
        cout << "Indices de los intervalos en la solucion optima" <<index << " ("<<I[index-1].s<<" ; "<<I[index-1].t<<")\n";
    }
    cout << endl;

    return 0;
}

void experimentarGreedy2(int p) {
    ofstream file("resultados_ejercicio2.csv");
    file << "n,algoritmo,tiempo_ns\n";

    for (int b = 1; b <= p; b++) {
        int n = pow(10, b);
        //generar intervalos aleatorios
        vector<Interval> intervalos = generarIntervalosAleatorios(n, 0, 10000);

        auto inicio = chrono::high_resolution_clock::now();
        greedy2(intervalos);
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
        file << n << ",greedy," << duracion.count() << "\n";
    }

    file.close();
}


#endif //REPECHAJE_EJERCICIO2_H
