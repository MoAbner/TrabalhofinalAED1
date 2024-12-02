import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

sns.set(style='whitegrid')
plt.rcParams.update({'figure.autolayout': True})

plt.rcParams['font.family'] = 'DejaVu Sans'

data = u"""
QuickSort,Crescente,100,0.00,345
InsertionSort,Crescente,100,0.00,0
QuickSort,Decrescente,100,0.01,399
InsertionSort,Decrescente,100,0.02,4950
QuickSort,Aleatório,100,0.01,439
InsertionSort,Aleatório,100,0.01,2617
QuickSort,Crescente,1000,0.03,4960
InsertionSort,Crescente,1000,0.01,0
QuickSort,Decrescente,1000,0.03,5506
InsertionSort,Decrescente,1000,0.74,499500
QuickSort,Aleatório,1000,0.06,6401
InsertionSort,Aleatório,1000,0.51,258753
QuickSort,Crescente,10000,0.40,66421
InsertionSort,Crescente,10000,0.02,0
QuickSort,Decrescente,10000,0.40,72675
InsertionSort,Decrescente,10000,77.69,49995000
QuickSort,Aleatório,10000,0.97,82028
InsertionSort,Aleatório,10000,41.33,25088677
QuickSort,Crescente,100000,4.19,846100
InsertionSort,Crescente,100000,0.19,0
QuickSort,Decrescente,100000,5.54,899854
InsertionSort,Decrescente,100000,7661.35,4999950000
QuickSort,Aleatório,100000,9.63,1057075
InsertionSort,Aleatório,100000,3773.15,2495315711
QuickSort,Crescente,1000000,46.37,9933573
InsertionSort,Crescente,1000000,-1.00,-1
QuickSort,Decrescente,1000000,51.58,10549175
InsertionSort,Decrescente,1000000,-1.00,-1
QuickSort,Aleatório,1000000,112.66,13634882
InsertionSort,Aleatório,1000000,-1.00,-1
QuickSort,Crescente,10000000,535.35,116046024
InsertionSort,Crescente,10000000,-1.00,-1
QuickSort,Decrescente,10000000,575.47,122326263
InsertionSort,Decrescente,10000000,-1.00,-1
QuickSort,Aleatório,10000000,1353.53,164699703
InsertionSort,Aleatório,10000000,-1.00,-1
"""

from io import StringIO

df = pd.read_csv(StringIO(data), header=None, names=['Algoritmo', 'Tipo', 'Tamanho', 'Tempo', 'Trocas'])

df['Tempo'] = df['Tempo'].replace(-1, np.nan)
df['Trocas'] = df['Trocas'].replace(-1, np.nan)

df['Tamanho'] = df['Tamanho'].astype(int)
df['Tempo'] = pd.to_numeric(df['Tempo'], errors='coerce')
df['Trocas'] = pd.to_numeric(df['Trocas'], errors='coerce')



algoritmos = df['Algoritmo'].unique()
tipos = df['Tipo'].unique()

for algoritmo in algoritmos:
    plt.figure(figsize=(10,6))
    for tipo in tipos:
        subset = df[(df['Algoritmo'] == algoritmo) & (df['Tipo'] == tipo)]
        plt.plot(subset['Tamanho'], subset['Tempo'], marker='o', label=tipo)
    plt.title(f'Tempo de Execução - {algoritmo}')
    plt.xlabel('Tamanho do Vetor (n)')
    plt.ylabel('Tempo (ms)')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.savefig(f'{algoritmo}_tempo.png')
    plt.show()

for algoritmo in algoritmos:
    plt.figure(figsize=(10,6))
    for tipo in tipos:
        subset = df[(df['Algoritmo'] == algoritmo) & (df['Tipo'] == tipo)]
        plt.plot(subset['Tamanho'], subset['Trocas'], marker='o', label=tipo)
    plt.title(f'Número de Trocas - {algoritmo}')
    plt.xlabel('Tamanho do Vetor (n)')
    plt.ylabel('Número de Trocas')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.savefig(f'{algoritmo}_trocas.png')
    plt.show()
