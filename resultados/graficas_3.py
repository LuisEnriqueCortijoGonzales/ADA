import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_path = 'resultados_ejercicio3.csv' 
data = pd.read_csv(file_path)

data_algoritmo = data[data['algoritmo'] == 'dp']

# dp
plt.figure(figsize=(12, 6))
plt.plot(data_algoritmo['n'], data_algoritmo['tiempo_ns'], label='Datos obtenidos')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Tiempo vs Tamaño n para el Algoritmo DP')
plt.legend()
plt.show()

# comp
plt.figure(figsize=(12, 6))
plt.plot(data_algoritmo['n'], data_algoritmo['tiempo_ns'], label='Datos obtenidos')
n_values = data_algoritmo['n']
tiempo_ns = data_algoritmo['tiempo_ns']
cubic = n_values**3
plt.plot(n_values, cubic, label='$n^3$', linestyle='--')
plt.plot(n_values, 100*cubic, label='$k*n^3$', linestyle='--')
quadratic = n_values**2
plt.plot(n_values, quadratic, label='$n^2$', linestyle='--')
plt.plot(n_values, n_values, label='$n$', linestyle='--')
log2_n = np.log2(n_values)
n_log2_n = n_values * log2_n
plt.plot(n_values, n_log2_n, label='$n * log_2(n)$', linestyle='--')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Comparación con Funciones Cúbicas, Cuadráticas, Lineales y Logarítmicas')
plt.legend()
plt.show()
