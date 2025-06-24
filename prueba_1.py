import pandas as pd
import os

comics = []

ruta_archivo = "C:/Users/ticia/Documents/curso python/proyecto excel/comics_intro.xlsx"

cant_com = int(input("Cantidad de comics a ingresar: "))

#for cantidad in range(cant_com):
    #nombre = input("Nombre del comic: ")
    #comics.append(nombre)

#haciendolo tipo tuplas:
#for i in range(cant_com):
    #nombre = input("Nombre del comic: ")
    #id = i + 1
    #comics.append((id, nombre))

#desempaquetando la tupla:
#for id_comic, nombre in comics:
    #print(f"ID {id_comic}: {nombre}")

for i in range(cant_com):
    nombre = input("\nNombre del comic: ").capitalize()
    id = i + 1
    universo = str(input("Universo: ")).upper()
    comics.append({
        "ID" : id,
        "Nombre" : nombre,
        "Universo" : universo,
    })

print("\nLista completa:\n")

for comic in comics:
    print(f"ID {comic['ID']}: {comic['Nombre']}. Universo {comic['Universo']}")


df = pd.DataFrame(comics)

df.to_excel(ruta_archivo, index=False)
print("Archivo 'comics_intro.xlsx' guardado correctamente.")