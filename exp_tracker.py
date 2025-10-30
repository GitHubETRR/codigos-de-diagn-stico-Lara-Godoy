import pandas as pd
from datetime import datetime

#los items empiezan en 0, los ids en 1 xq se le muestran al usuario

#strip()    solo elimina los caracteres de los extremos, no del centro de la cadena. 
#           devuelve una nueva cadena y no modifica la cadena original. 

#replace()  se utiliza para reemplazar todas las ocurrencias de una subcadena especifica por una nueva subcadena

#isalpha()  es un método de cadena que comprueba si todos los caracteres de una cadena son alfabeticos
#           Si es asi, devuelve True; de lo contrario, devuelve False

lista_categorias = ["Comida", "Educacion", "Gusto", "Transporte", "Tecnologia", "Facturas"]

def reasignar_ids(lista):
    for nuevo_id, gasto in enumerate(lista_gastos, start=1):
        gasto["id"] = nuevo_id

def printear_lista(lista):
    for gasto in lista_gastos:
        print(f"\033[37;3mID {gasto['id']}\033[0m, \033[37;4m{gasto['nombre']}\033[0m, \033[1;32m${gasto['valor']}\033[0m. \033[36m{gasto['fecha']}\033[0m.")

def printear_categorias(lista):
    print("Diferentes categorias del gasto: \n")
    for cat in lista_categorias:
        print("- ", cat)

def validar_int(mensaje):
    while True:
        try:
            valor = int(input(mensaje))
            if valor <= 0:
                print("Intente nuevamente, solo con numeros positivos.")
                continue
            return valor
        except ValueError:
            print("Error. Debe ingresar un numero entero.")

def validar_str(mensaje):
    while True:
        texto = input(mensaje).strip()
        if texto.replace(" ", "").isalpha():
            return texto.capitalize()
        else:
            print("Error. Debe ingresar solo cadena.")

try:
    df = pd.read_excel("gastos.xlsx")
    lista_gastos = df.to_dict(orient="records")
    print("Datos cargados correctamente desde Excel.")
    
    if not lista_gastos:
        print("No hay nada en la lista.")
        lista_gastos = []
    else: 
        printear_lista(lista_gastos)
except FileNotFoundError:
    lista_gastos = []
    print("No se encontró el archivo 'gastos.xlsx'. Se creará uno nuevo al salir.")

respuesta = 0
while (respuesta != 5):
    print('''
    \033[31;1m--- MENU ---\033[0m
    1. Agregar gasto
    2. Visualizar gastos
    3. Eliminar un gasto
    4. Ver un resumen de gastos
    5. Salir
    ''')
    
    respuesta = validar_int("\nIngrese una opcion: ")

    match (respuesta):
        case 1:
            cant_gastos = validar_int("\nCuantos gastos queres añadir?: ")
            
            for i in range(cant_gastos):
                nombre_g = validar_str("\nNombre del gasto: ")
                
                printear_categorias(lista_categorias)
                categoria_g = validar_str("Categoria del gasto: ")
                
                valor_g = validar_int("Valor del gasto: ")

                nuevo_gasto = {
                    "id" : len(lista_gastos) + 1, 
                    "nombre" : nombre_g.capitalize(), 
                    "valor" : valor_g, 
                    "categoria" : categoria_g.capitalize(),
                    "fecha": datetime.now().strftime("%Y-%m-%d")} #da el año completo, mes y dia

                lista_gastos.append(nuevo_gasto)

        case 2:

            if not lista_gastos:
                print("No hay nada en la lista.")
                continue
            else:
                print("\nCantidad de gastos: ", len(lista_gastos))
                printear_lista(lista_gastos)

        case 3:
            if not lista_gastos:
                print("No hay nada en la lista.")
                continue
            
            item_eliminar = validar_int("Ingrese el id del gasto a eliminar: ")
            
            encontrado = False
            for indice, gasto in enumerate(lista_gastos):
                #devuelve (indice, elemento)
                if gasto["id"] == item_eliminar:
                    lista_gastos.remove(gasto)
                    encontrado = True
                    break #para que no recorra al pepe

            if encontrado == False:
                print("\nNo se encontro ese id.")
                continue
            else:
                reasignar_ids(lista_gastos)

        case 4:
            if not lista_gastos:
                print("No hay nada en la lista.")
                continue
            
            gasto_max = lista_gastos[0]
            for gasto in lista_gastos:
                if gasto["valor"] > gasto_max["valor"]:
                    gasto_max = gasto
            print("\nMayor gasto: ", gasto_max["nombre"], ", con un valor de: ", gasto_max["valor"], "$")

            suma_gasto = 0
            for gasto in lista_gastos:
                suma_gasto += gasto["valor"]
            promedio = suma_gasto / len(lista_gastos)
            print("\nPromedio de gasto: ", round(promedio, 2))
            
            totales = {} #diccionario vacio para guardar el total acumulado por categoria   
            
            for gasto in lista_gastos:
                cat = gasto["categoria"]
                totales[cat] = totales.get(cat, 0) + gasto["valor"]
            
            categoria_max = None
            valor_max = 0

            for categoria, total in totales.items():
                if total > valor_max:
                    categoria_max = categoria
                    valor_max = total
            
            print("\nCategoria con mayor gasto: ", categoria_max, ", con un total de: ", valor_max, "$")
        case 5:
            df = pd.DataFrame(lista_gastos)
            df.to_excel("gastos.xlsx", index=False)
            print("Datos guardados. Fin del programa.")
        case _: #default
            print("No existe esa opcion.")

