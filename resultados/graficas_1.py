import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



file_path = 'resultados_ejercicio1.csv'
data = pd.read_csv(file_path)

data_lg = data[data['algoritmo'] == 'lg(n)']
data_lineal = data[data['algoritmo'] == 'lineal']

#vs
plt.figure(figsize=(12, 6))
plt.plot(data_lg['n'], data_lg['tiempo_ns'], label='Algoritmo lg(n)')
plt.plot(data_lineal['n'], data_lineal['tiempo_ns'], label='Algoritmo lineal')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Comparación de Algoritmos')
plt.legend()
plt.show()

#lgn
plt.figure(figsize=(12, 6))
plt.plot(data_lg['n'], data_lg['tiempo_ns'], label='Algoritmo lg(n)')
positive_n = data_lg['n'] > 0
plt.plot(data_lg['n'], np.log2(data_lg['n']), label='$log_2(n)$', linestyle='--')
plt.plot(data_lg['n'], 1000*np.log2(data_lg['n']), label='$k*log_2(n)$', linestyle='dotted')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Algoritmo lg(n) vs $log_2(n)$')
plt.legend()
plt.show()

#n
plt.figure(figsize=(12, 6))
plt.plot(data_lineal['n'], data_lineal['tiempo_ns'], label='Algoritmo lineal')
plt.plot(data_lineal['n'], data_lineal['n'], label='$n$', linestyle='--')
plt.plot(data_lg['n'], 100*data_lineal['n'], label='$k*n$', linestyle='dotted')
plt.xlabel('Tamaño n')
plt.ylabel('Tiempo (ns)')
plt.xscale('log')
plt.yscale('log')
plt.title('Algoritmo lineal vs $n$')
plt.legend()
plt.show()