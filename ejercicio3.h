//
// Created by lecor on 25/07/2024.
//

#ifndef REPECHAJE_EJERCICIO3_H
#define REPECHAJE_EJERCICIO3_H


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función auxiliar para devolver la secuencia de cortes optimos como se solicita (inspirada en division y conquista)
void orden_cortes(const vector<vector<int>>& orden, const vector<int>& cortes, int i, int j, vector<int>& rpta) {
    if (j - i <= 1) return; // caso base
    int k = orden[i][j]; // El punto de corte que proporciona el costo mínimo
    rpta.push_back(cortes[k]);
    orden_cortes(orden, cortes, i, k, rpta); // Reconstruir el orden en el subintervalo izquierdo
    orden_cortes(orden, cortes, k, j, rpta); // Reconstruir el orden en el subintervalo derecho
}//Olg(n)

//devuelve tanto la solucion como el orden de puntos
//el sort se hace fuera del algoritmo
pair<vector<vector<int>>, vector<int>> dp3(int n, vector<int> cortes, int l) {
    //agregar la longitud como punto final
    cortes.push_back(l);
    // Inicializar las matrices del opt y la de los puntos de corte
    vector<vector<int>> opt(n + 2, vector<int>(n + 2, 0));
    vector<vector<int>> orden(n + 2, vector<int>(n + 2, 0));

    for (int i = 2; i <= n + 1; ++i) {
        for (int j = 0; j + i <= n + 1; ++j) {
            int end = j + i;
            int mn = INT_MAX; // mn será el elemento a comparar inicialmente infinito positivo
            for (int k = j + 1; k < end; ++k) {
                int cost = opt[j][k] + opt[k][end];
                //usa resultados previos para evitar volver a calcularlos (dp)
                if (cost < mn) {
                    mn = cost;
                    orden[j][end] = k; // Registrar el punto de corte
                }
            }
            opt[j][end] = cortes[end] - cortes[j] + mn; // Actualizar la matriz opt con el mínimo
            //como se puede ver calcula todos los posibles resultados memorizando los que cumplen la condicion
        }
    }

    vector<int> rpta;
    orden_cortes(orden, cortes, 0, n + 1, rpta);

    return make_pair(opt, rpta);
}//complejidad total n^3 algortimo dp+ lg(n) de la recursion para el orden de cortes + n del primer sort => O(n^3)

int ejercicio3() {
    int n;
    cout << "Ingrese la cantidad n de puntos de corte: " << endl;
    cin >> n;
    vector<int> cortes(n + 1); // Incluye el corte inicial 0 (no es necesario ingresarlo)
    cortes[0] = 0; // Primer punto de corte es 0 (siempre)

    for (int i = 1; i <= n; ++i) {
        cout << "Punto " << i << ": " << endl;
        cin >> cortes[i];
    }
    //por si acaso no se ingresen en orden
    sort(cortes.begin(), cortes.end());
    int l;
    cout << "Ingrese la longitud: " << endl;
    cin >> l;
    //se asume que ingresara una longitud valida no menor a ningun punto de corte
    pair<vector<vector<int>>, vector<int>> resultado = dp3(n, cortes, l);
    vector<vector<int>> opt_matrix = resultado.first;
    vector<int> orden_cortes = resultado.second;

    // Imprimir la matriz opt
    cout << "Matriz de costos minimos:" << endl;
    for (const auto& row : opt_matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    // Imprimir el orden de cortes
    cout << "Orden de cortes:" << endl;
    for (int corte : orden_cortes) {
        cout << corte << " ";
    }
    cout << endl;

    // Imprimir el costo óptimo final
    cout << "Costo optimo final: " << opt_matrix[0][n + 1] << endl;

    return 0;
}

void experimentarDP3(int p) {
    ofstream file("resultados_ejercicio3.csv");
    file << "n,algoritmo,tiempo_ns\n";

    for (int b = 1; b <= p; b++) {
        int n = pow(10, b);
        int l = n*10;
        //garantizamos que l es mayor a cualquier n posible
        //datos aleatorios
        vector<int> cortes = generarCortesAleatorios(n, l);
        sort(cortes.begin(), cortes.end());

        auto inicio = chrono::high_resolution_clock::now();
        dp3(n, cortes, l);
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
        file << n << ",dp," << duracion.count() << "\n";
    }

    file.close();
}


#endif //REPECHAJE_EJERCICIO3_H
