# Tarea2-Algoco
a continuacion explicare como usar cada archivo de codigo, sin contar los ".txt"
## fb.cpp y pdm.cpp
para el correcto uso de estos archivos:
- se deben ejecutar en la terminal de linux, aunque sea un subsistema, en caso de no poderse debe eliminarse la linea "#include <sys/resource.h>" y la funcion "size_t obtenerUsoMemoria()" junto a su llamada en el main, para no modificar tanto la llamada a la funcion que escribe el archivo de salida, solo pasar un 1, aunque esto claramente afecta a los resultados de las graficas de memoria
- deben estar ubicados en la misma carpeta que "casos.txt", "cost_delete.txt", "cost_insert.txt", "cost_replace.txt" y "cost_transpose.txt"
- para replicar los resultados obtenidos se debe ejecutar tando "fb.cpp", como "pdm.cpp" 5 veces, cambiando el nombre del archivo cada vez para evitar que se sobreescriban y guardarlo en la carpeta "Resultados-sin-filtrar", aunque esto es más que nada por orden

## calculos-promedios.cpp
Para el correcto uso de este codigo:
- debe estar ubicado en la misma carpeta que los 5 resultados de cada codigo, "fb.cpp" y "pdm.cpp"
- los nombres de los archivos pueden ser cualquiera, idealmente separarlo entre los de fuerza bruta y programacion dinamica
- en el main del codigo, en las lineas 21 a 25, se debe colocar el nombre de los 5 archivos resultantes de fuerza bruta o programacion dinamica, no se debe mezclar para obtener los mismos resultados
- en la linea 39 se le coloca el nombre al archivo de salida, idealmente poner "promedio_fb.txt" y "promedio_pdm.txt" para fuerza bruta y programacion dinamica respectivamente.
- los 2 archivos resultantes se pueden dejar ahi o moverlos a la carpeta "Resultados-filtrados", como mejor le parezca

## generar_tabla.py
Para este codigo se necesita:
- que este en la misma ubicacion que "promedio_fb.txt" y "promedio_pdm.txt", en la linea 10 se coloca el nombre del archivo a generar la tabla

## generar_grafico.py
Para el funcionamiento de este codigo se necesita:
- los archivos "promedio_fb.txt" y "promedio_pdm.txt" subdividirlos en los siguientes archivos, los que deben estar en la misma ubicacion que **generar_graficos.py**:
  - "promedio_fb_cadv.txt" y "promedio_pdm_cadv.txt", que son las primeras 10 lineas de "promedio_fb.txt" y "promedio_pdm.txt"
  - "promedio_fb_rep.txt" y "promedio_pdm_rep.txt", que son desde la linea 11 hasta la linea 19 de "promedio_fb.txt" y "promedio_pdm.txt"
  - "promedio_fb_trans.txt" y "promedio_pdm_trans.txt", que son desde la linea 20 hasta la linea 31 de "promedio_fb.txt" y "promedio_pdm.txt"
- en las linea 15 y 16 se debe colocar de a pares, para un mejor analisis y para no afectar al texto que aparece, los pares deben ser los siguientes:
  - par 1: "promedio_fb_cadv.txt" y "promedio_pdm_cadv.txt"
  - par 2: "promedio_fb_rep.txt" y "promedio_pdm_rep.txt"
  - par 3: "promedio_fb_trans.txt" y "promedio_pdm_trans.txt"
- en la lineas 28 y 41 se debe cambiar al titulo más adecuado para cada grafico
