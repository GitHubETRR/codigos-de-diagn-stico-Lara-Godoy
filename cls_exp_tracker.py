import pandas as pd
from datetime import datetime

class Gasto:
    def __init__(self, id, nombre, valor, categoria, fecha=None):
        self.id = id
        self.nombre = nombre
        self.valor = valor
        self.categoria = categoria
        self.fecha = fecha if fecha else datetime.now().strftime("%Y-%m-%d")

class GestorGastos:
    def __init__(self):
        self.lista_gastos = []
        self.lista_categorias = ["Comida", "Educacion", "Gusto", "Transporte", "Tecnologia", "Facturas", "Regalo"]
    
    def printear_lista(self):
        if not self.lista_gastos:
            print("No hay gastos registrados.")
            return
        for gasto in self.lista_gastos:
            print(f"\033[37;3mID {gasto.id}\033[0m, \033[37;4m{gasto.nombre}\033[0m, \033[1;32m${gasto.valor}\033[0m. \033[36m{gasto.fecha}\033[0m.")

    def printear_categorias(self):
        print("Diferentes categorias del gasto: \n")
        for cat in self.lista_categorias: 
            print("- ", cat)
    
    def reasignar_ids(self):
        for nuevo_id, gasto in enumerate(self.lista_gastos, start=1):
            gasto.id = nuevo_id
    
    def agregar_gasto(self, nombre, valor_g, categoria_g, fecha_g=None):
        if not fecha_g:
            fecha_g = datetime.now().strftime("%Y-%m-%d")
        nuevo = Gasto(len(self.lista_gastos) + 1, nombre.capitalize(), valor_g, categoria_g.capitalize())
        self.lista_gastos.append(nuevo)
        print(f"Gasto '{nombre}' agregado correctamente.")
    
    def eliminar_gasto(self, item_eliminar):
        for gasto in self.lista_gastos:
            if gasto.id == item_eliminar:
                self.lista_gastos.remove(gasto)
                self.reasignar_ids()
                return True
        return False

    def resumen_gastos(self):
        if not self.lista_gastos:
            print("No hay nada en la lista.")
            return
        
        gasto_max = self.lista_gastos[0]
        for gasto in self.lista_gastos:
            if gasto.valor > gasto_max.valor:
                gasto_max = gasto
        print(f"\nMayor gasto: {gasto_max.nombre}, con un valor de: {gasto_max.valor}$")

        promedio = sum(g.valor for g in self.lista_gastos) / len(self.lista_gastos)
        print("\nPromedio de gasto: ", round(promedio, 2), "$")
        
        totales = {} #diccionario vacio para guardar el total acumulado por categoria   
        for gasto in self.lista_gastos:
            totales[gasto.categoria] = totales.get(gasto.categoria, 0) + gasto.valor
        
        categoria_max = max(totales, key=totales.get)
        
        print(f"\nCategoria con mayor gasto: {categoria_max}, con un total de: {totales[categoria_max]}$")

    def cargar_excel(self, archivo="gastos.xlsx"):
        try:
            df = pd.read_excel(archivo)
            for _, fila in df.iterrows():
                gasto = Gasto(
                    id=int(fila["id"]),
                    nombre=fila["nombre"],
                    valor=int(fila["valor"]),
                    categoria=fila["categoria"],
                    fecha=fila["fecha"]
                    #pasa cada dato de fila a un objeto de Gasto
                )
                self.lista_gastos.append(gasto)
            print("Datos cargados correctamente desde Excel.\n")
            self.printear_lista()
        except FileNotFoundError:
            self.lista_gastos = []
            print("No se encontró el archivo 'gastos.xlsx'. Se creará uno nuevo al salir.")

    def guardar_en_excel(self, archivo="gastos.xlsx"):
        df = pd.DataFrame([vars(g) for g in self.lista_gastos])
        #vars(g) hace un diccionario con los datos de g
        #los [] hacen una lista de esos diccionarios
        df.to_excel(archivo, index=False)
        print("Datos guardados. Fin del programa.")

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

def main():
    gestor = GestorGastos()
    gestor.cargar_excel()

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
                    nombre = validar_str("\nNombre del gasto: ")
                    
                    gestor.printear_categorias()
                    categoria_g = validar_str("Categoria del gasto: ")
                    
                    valor_g = validar_int("Valor del gasto: ")
                    
                    fecha_g = input("Fecha del gasto (YYYY-MM-DD) o Enter para hoy: ").strip()
                    if not fecha_g:
                        fecha_g = None
                    gestor.agregar_gasto(nombre, valor_g, categoria_g, fecha_g)

            case 2:
                gestor.printear_lista()

            case 3:
                gestor.printear_lista()
                item_eliminar = validar_int("\nIngrese el id del gasto a eliminar: ")
                
                if gestor.eliminar_gasto(item_eliminar):
                    print("Gasto eliminado correctamente.")
                else:
                    print("No se pudo eliminar.")
                
                gestor.printear_lista()

            case 4:
                gestor.resumen_gastos()
            case 5:
                gestor.guardar_en_excel()
            
            case _: #default
                print("No existe esa opcion.")

if __name__ == "__main__":
    main()
    #hace que compile todo