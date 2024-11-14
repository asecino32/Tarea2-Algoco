import pandas as pd
import matplotlib.pyplot as plt

# Función para leer el archivo y convertirlo en una tabla
def leer_archivo_como_tabla(filename):
    df = pd.read_csv(filename, sep=' ', header=None, names=['Largo S1', 'Largo S2', 'Tiempo [ms]', 'Memoria [bytes]'])
    return df

# Leer los datos del archivo
filename = 'promedio_pdm.txt'  # Cambia 'datos.txt' por el nombre de tu archivo
df = leer_archivo_como_tabla(filename)

# Crear una imagen de la tabla
plt.figure(figsize=(8, 7))
plt.axis('off')
plt.table(cellText=df.values, colLabels=df.columns, loc='center')
plt.title("Tabla de Resultados Programación Dinamica", fontsize=14)
plt.savefig('tabla_resultados.png', bbox_inches='tight', dpi=300)  # Guardar como imagen
plt.show()
