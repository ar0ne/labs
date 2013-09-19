#!/usr/bin/env python3
""" 
сделать НС из 3х входных образов в виде матрицы nXn из {0,1} в виде цифры
+ добавить адаптивный шаг с 3ей лабы
#   0 0 0 1 0
#   0 0 1 1 0
#   0 1 0 1 0
#   0 0 0 1 0
#   0 0 0 1 0
# потом обучаем по соответсвующему алгоритму(?), на этих эталонных матрицах
 далее проверяем работу на зашумленных образах
"""

from random import random, randint

# запихнули в список все 0 и 1 с файла
def read_image_from_file(filename = 'image_of_number'):
    f = open(filename, 'r')
    return make_list_imgs( f.read().split())

# @return список из N образов
def make_list_imgs(temp_list, N = 3):
    imgs = []
    size = int(len(temp_list) / N)

    for i in range(N):
        imgs.append(temp_list[i * size : (i + 1) * size])
        for j in range(len(imgs[i])):
            imgs[i][j] = int(imgs[i][j])
    
    print("Входные образы: ")
    for i in range(N):
        print_img(imgs[i])
        
    return imgs

# создаем N эталонных образов 
# For example: [[1,0],[0,1]]
def make_ethalon_lists(N = 3):
    eth = []
    for i in range(N):
        eth.append([])
        for j in range(N):
            if i == j:
                eth[i].append(1) 
            else:
                eth[i].append(0)
    return eth

# Максимальное делаем 1, остальные Y приравняем к 0
# @return выходной образ
def func(y1, y2, y3):
    if y1 > y2 and y1 > y3:
        y1 = 1
        y2 = y3 = 0
    elif y2 > y1 and y2 > y3:
        y2 = 1
        y1 = y3 = 0
    else:
        y3 = 1
        y1 = y2 = 0
    
    return y1,y2,y3 

# вывод образа img
def print_img(img ):
    size = len(img)
    for j in range(size):
        if j % size ** .5 == 0 and j!= 0:
            print("\n")
        print(img[j], end=' ')
    print("\n\n")    


def learning(imgs, eth, w, T, size):
    
    N = len(imgs)
    ErrMin = 0.001
    Err = 1         # среднеквадратичная ошибка сети     
    iter = 0        # число итераций
    S = 0
    y1 = y2 = y3 = 0
    
    while Err > ErrMin:
        Err = 0
        for img in range(N):
            S = 0
            for j in range(size):
                S += imgs[img][j] ** 2
            alpha = 1 / (1 + S)   # адаптивная скорость обучения
            
            for i in range(size):   
                y1 += w[0][i] * imgs[img][i] 
                y2 += w[1][i] * imgs[img][i] 
                y3 += w[2][i] * imgs[img][i] 
            
            y1, y2, y3 = func(y1 - T[0], y2 - T[1], y3 - T[2] )
            
            for i in range(size):
                w[0][i] -= alpha * (y1 - eth[img][0]) * imgs[img][i]
                w[1][i] -= alpha * (y2 - eth[img][1]) * imgs[img][i]
                w[2][i] -= alpha * (y3 - eth[img][2]) * imgs[img][i]
            
            T[0] += alpha * (y1 - eth[img][0])
            T[1] += alpha * (y2 - eth[img][1])
            T[2] += alpha * (y3 - eth[img][2])
            

        for img in range(N):
            for i in range(size):
                y1 += w[0][i] * imgs[img][i] 
                y2 += w[1][i] * imgs[img][i] 
                y3 += w[2][i] * imgs[img][i] 
                
            y1, y2, y3 = func(y1 - T[0], y2 - T[1], y3 - T[2] ) 
            
            Err += (y1 - eth[img][0]) ** 2 + (y2 - eth[img][1]) ** 2 + (y3 - eth[img][2]) ** 2
            
        Err /= 2    
        iter += 1
    
    print("Обучение заняло ", iter, " итераций.")
    return w, T

# main
if __name__ == '__main__':
    
    imgs = read_image_from_file()
    eth = make_ethalon_lists()
    w = [[random() for j in range(len(imgs[i]))] for i in range(len(imgs))]
    T = [random() for i in range(len(imgs)) ]
    size_img = len(imgs[0])
    w, T = learning(imgs, eth, w, T, size_img)
    
    it_img=0
    
    while True:
        # распознаем плохой образ с инвертированными битами
        # берем рандомный образ и инвертируем заданное число битов
        #num_bad_img = randint(0, len(imgs) - 1)
        if it_img > 2:
            it_img = 0
            
        bad_img = imgs[it_img]
        foo = int(input('Сколько битов инвертировать?'))
        invert_list = []
        while foo != 0:
            try:
                spam = randint(0, size_img - 1)
                invert_list.index(spam)      # если не содержит такой индекс выбрасывает исключение
                continue
            
            except:
                invert_list.append(spam)                
                bad_img[spam] = int(not bad_img[spam]) 
    
            foo -= 1
        
        print("Зашумлен образ ", it_img + 1, "\n") 
        print_img(bad_img)
            
        y1 = y2 = y3 = 0
        
        for i in range(len(imgs[1])):
            y1 += w[0][i] * int(bad_img[i]) 
            y2 += w[1][i] * int(bad_img[i]) 
            y3 += w[2][i] * int(bad_img[i]) 
        
        y1, y2, y3 = func(y1 - T[0], y2 - T[1], y3 - T[2])
        
        if y1 == 1:
            print("распознан 1ый образ")
        elif y2 == 1:
            print("распознан 2ой образ")
        else:
            print("распознан 3ий образ")
            
        it_img += 1    
    
        say = input("Выйти? (Y)").upper()
        if say == 'Y':
            break
