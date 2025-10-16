lista_gastos = []
#los items empiezan en 0, los ids en 1 xq se le muestran al usuario

respuesta = 0
while (respuesta != 5):
    print('''
    1. Agregar gasto
    2. Visualizar gastos
    3. Eliminar un gasto
    4. Ver un resumen de gastos
    5. Salir
    ''')
    respuesta = int(input("Ingrese una opcion: "))

    match (respuesta):
        case 1:

            cant_gastos = int(input("\nCuantos gastos queres añadir?: "))
            for i in range(cant_gastos):
                nombre_g = str(input("\nNombre del gasto: ")).capitalize()
                valor_g = int(input("Valor del gasto: "))
                #categoria_g = str(input("Categoria del gasto: ")).capitalize()

                id_inicial = len(lista_gastos)
                id_gasto = id_inicial + 1

                lista_gastos.append(
                    {"id" : id_gasto, 
                    "nombre" : nombre_g, 
                    "valor" : valor_g, 
                    })
                    #"Categoria" : categoria_g})

        case 2:

            print("\nCantidad de gastos: ", len(lista_gastos))
            print("Lista de gastos: \n", lista_gastos)

        case 3:
            item_eliminar = int(input("Ingrese el id del gasto a eliminar: "))
            
            for indice, gasto in enumerate(lista_gastos):
                #devuelve (indice, elemento)
                if gasto["id"] == item_eliminar:
                    lista_gastos.remove(gasto)
                    encontrado = True
                    break #para que no recorra al pepe
                
            
            if encontrado == False:
                print("\nNo se encontro ese id.")
            else:
                for nuevo_id, gasto in enumerate(lista_gastos, start=1):
                    gasto["id"] = nuevo_id
            
            print("Nueva lista: \n", lista_gastos)
            

        case 4:
            if lista_gastos == []:
                print("No hay nada en la lista.")
            
            gasto_max = lista_gastos[0]
            for gasto in lista_gastos:
                if gasto["valor"] > gasto_max["valor"]:
                    gasto_max = gasto
            print("Mayor gasto: ", gasto_max["nombre"], ", con un valor de: ", gasto_max["valor"])

            suma_gasto = 0
            for gasto in lista_gastos:
                suma_gasto += gasto["valor"]
            promedio = suma_gasto / len(lista_gastos)
            print("Promedio de gasto: ", round(promedio, 2))

        case 5:
            print("Fin del programa.")
        case _: #default
            print("No existe esa opcion.")