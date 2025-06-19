comics = []

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
    comics.append([id, nombre, universo])

print("\nLista completa:\n")

for comics in comics:
    print(f"ID {comics[0]}: {comics[1]}. Universo {comics[2]}")
