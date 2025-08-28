import pygame
import random
'''el rectangulo sigue al mouse y cambia cuando lo suelta'''

pygame.init()
colores = [
    (0, 255, 255),          #Aqua
    (0, 0, 255),            #azul
    (255, 0, 255),          #fucsia
    (128, 128, 128),        #gris
    (0, 128, 0),            #verde
    (0, 255, 0),            #lima
    (128, 0, 0),            #marron
    (0, 0, 128),            #azul marino
    (128, 128, 0),          #oliva
    (128, 0, 128),          #violeta
    (255, 0, 0),            #rojo
    (192, 192, 192),        #plateado
    (0, 128, 128),          #teal
    (255, 255, 0)           #amarillo
]

color_inicial = (255, 255, 255)
ANCHO, ALTO = 500, 500
RECT_W, RECT_H = 150, 200

screen = pygame.display.set_mode((ANCHO, ALTO))
'''(500 -> x, 400 -> y)'''

rect_x = (ANCHO - RECT_W) // 2
rect_y = (ALTO - RECT_H) // 2

running = True
color_actual = color_inicial
color_anterior = color_inicial
arrastrando = False
while running:
    screen.fill("black")
    '''rect=((left, top), (width, height)) --> (x, y, ancho, alto)'''
    rectangulo = pygame.Rect(rect_x, rect_y, RECT_W, RECT_H)
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            arrastrando = True
        if event.type == pygame.MOUSEBUTTONUP:
            arrastrando = False
            
            color_actual = random.choice(colores)
            print(color_actual)
            
            while color_actual == color_anterior:
                color_actual = random.choice(colores)
            color_anterior = color_actual
        if event.type == pygame.QUIT:
            running = False
    if arrastrando == True:
        mouse_x, mouse_y = pygame.mouse.get_pos()
        rect_x, rect_y = mouse_x - RECT_W // 2, mouse_y - RECT_H // 2
        rectangulo = pygame.Rect(rect_x, rect_y, RECT_W, RECT_H)
    pygame.draw.rect(screen, color_actual, rectangulo)
    pygame.display.flip()

pygame.quit()
