import pandas as pd
import matplotlib.pyplot as plt

# Función para leer datos desde el archivo usando pandas
def leer_datos(filename):
    # Leer el archivo con pandas y asignar nombres a las columnas
    df = pd.read_csv(filename, sep=' ', header=None, names=['Tamaño1', 'Tamaño2', 'Tiempo_ms', 'Memoria_bytes'])
    # Crear una nueva columna con la tupla (Tamaño1, Tamaño2)
    df['Tamaño'] = df.apply(lambda row: (int(row['Tamaño1']), int(row['Tamaño2'])), axis=1)
    # Ordenar el DataFrame basado en las tuplas para evitar líneas de retorno
    df.sort_values(by=['Tamaño1', 'Tamaño2'], inplace=True)
    return df

# Leer datos de ambos archivos (ajusta los nombres de archivos según tu caso)
df_sin = leer_datos('promedio_fb_trans.txt')
df_con = leer_datos('promedio_pdm_trans.txt')

# Convertir la columna 'Tamaño' a cadenas en un formato limpio
df_sin['Tamaño_str'] = df_sin['Tamaño'].apply(lambda x: f"({x[0]}, {x[1]})")
df_con['Tamaño_str'] = df_con['Tamaño'].apply(lambda x: f"({x[0]}, {x[1]})")

# Graficar Tiempo vs (Tamaño1, Tamaño2)
plt.figure(figsize=(10, 5))
plt.plot(df_sin['Tamaño_str'], df_sin['Tiempo_ms'], label='Fuerza Bruta', marker='o')
plt.plot(df_con['Tamaño_str'], df_con['Tiempo_ms'], label='Programacion dinamica', marker='x')
plt.xlabel('(Tamaño S1, Tamaño S2)')
plt.ylabel('Tiempo (ms)')
plt.title('Comparación de Tiempos para Diferentes Tamaños de Palabras con transposiciones')
plt.xticks(rotation=45)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# Graficar Memoria vs (Tamaño1, Tamaño2)
plt.figure(figsize=(10, 5))
plt.plot(df_sin['Tamaño_str'], df_sin['Memoria_bytes'], label='Fuerza Bruta', marker='o')
plt.plot(df_con['Tamaño_str'], df_con['Memoria_bytes'], label='Programacion dinamica', marker='x')
plt.xlabel('(Tamaño S1, Tamaño S2)')
plt.ylabel('Memoria (bytes)')
plt.title('Comparación de Uso de Memoria para Diferentes Tamaños de Palabras con transposiciones')
plt.xticks(rotation=45)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
