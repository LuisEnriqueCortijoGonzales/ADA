import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_path = 'resultados_ejercicio2.csv'
data = pd.read_csv(file_path)

data_algoritmo = data[data['algoritmo'] == 'greedy']

#greedy
plt.figure(figsize=(12, 6))
plt.plot(data_algoritmo['n'], data_algoritmo['tiempo_ns'], label='Datos obtenidos')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Tiempo vs Tamaño n para el Algoritmo Greedy')
plt.legend()
plt.show()

#comp
plt.figure(figsize=(12, 6))
plt.plot(data_algoritmo['n'], data_algoritmo['tiempo_ns'], label='Datos obtenidos')
n_values = data_algoritmo['n']
log2_n = np.log2(n_values)
n_log2_n = n_values * log2_n
plt.plot(n_values, n_log2_n, label='$n * log_2(n)$', linestyle='--')
plt.plot(n_values, 100 * n_log2_n, label='$100*n*log_2(n)$', linestyle='dotted')
plt.plot(n_values, n_values, label='Funcion lineal', linestyle='-')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Comparación con $n * log_2(n)$')
plt.legend()
plt.show()

# k/n
plt.figure(figsize=(12, 6))
plt.plot(data_algoritmo['n'], data_algoritmo['k/n'], label='$k/n$', marker='o')
plt.xlabel('Tamaño n')
plt.ylabel('$k/n$')
plt.xscale('log')
plt.yscale('log')
plt.title('Tamaño Relativo de la Solución ($k/n$) vs Tamaño n')
plt.legend()
plt.show()
