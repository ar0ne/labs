#! /usr/bin/env python3
""" 
laba 2 OTНС  "Линейная искусственная нейронная сеть. Правило обучения Видроу-Хоффа."
y = a * sin (b * x) + d
вариант 4:
a = 4    b=8    d = 0.4    кол-во входов ИНС = 3
"""
from math import sin
from random import random
from sys import argv

# w - весовые коэфф
# eth - 3 эталонных значения
# @return выходное значение   
def getY(w, eth, T):
    Y = 0
    for i in range(3):
        Y += w[i]*eth[i]
    return (Y - T)

# пересчет порогового значения T
# t_k - эталонное значение НС для k-го образа
def nextT(T, alpha, y_k, t_k):
    return (T + alpha * (y_k - t_k))
 
# пересчет среднеквадратичной ошибки сети для k-го образа 
def getErr(Y, t_k):
    return (0.5 * ((Y - t_k) ** 2))

def show(ls, res, eth):
    print ('%-2s | %-10s | %-10s | %-10s' % ('#','Результат','Эталон','Разность'))
    print('-' * 40)
    for i in ls:
        print('%-2d | %-10f | %-10f | %-10f' % (i+1, res[i], eth[i], eth[i] - res[i] ))

# обучение НС
# ls - список чисел от 0 до n
# @return T - т.к. он изменяемый тип(float) на выходе из ф-ции - утрачивается
def learning(ethalon, w, ls, T, result): 

    ErrMin = 0.0001
    Err = 1             # среднеквадратичная ошибка сети
    alpha = 0.05        # скорость обучения
    u = 0               # число итераций

    #обучение
    while Err > ErrMin:
        Err = 0
        for i in ls[:len(ls)-3]:
            Y = getY(w, ethalon[i:i+3], T)
            #Err += 0.5 * ((Y - ethalon[i+3]) ** 2)
            w[0] -= alpha * (Y - ethalon[i+3]) * ethalon[i]
            w[1] -= alpha * (Y - ethalon[i+3]) * ethalon[i+1]
            w[2] -= alpha * (Y - ethalon[i+3]) * ethalon[i+2]
            T = nextT(T,alpha,Y,ethalon[i+3])
        u += 1
        for i in range(len(ls)-3):
            Y = getY(w, ethalon[i:i+3], T)
            Err += getErr(Y, ethalon[i+3])
        
    print('Итоги обучения: ')

    for i in range(3):
        result.append(ethalon[i])
    
    for i in ls[:27]:
        result.append(w[0] * ethalon[i] + w[1] * ethalon[i+1] + w[2] * ethalon[i+2] - T)
    print('итераций = ', u, 'alpha = ',alpha)
    
    show(ls[:30], result, ethalon)  
 
    return T      

# прогнозирование
def forecast(_ethalon, _w, _list, T):
    mass = []
    for i in range(3):
        mass.append(_ethalon[i])
 
    for i in _list[:len(ls)-3]:
        mass.append(mass[i] * _w[0] + mass[i+1] * _w[1] + mass[i+2] * _w[2] - T)
    
    print("\nИтоги прогнозирования:")
    show(_list, mass, _ethalon)
      
# main
if __name__ == '__main__':
    
    # передача аргумента в терминале, argv[1] - кол-во входных образов
    try: 
        if(argv[1]): 
            n = int(argv[1])
    except:
        n = 30  
       
    w = [random(),random(),random()]      #весовые коэфициенты          
       
    ls = [i for i in range(n+15)]          # список чисел от 0 до n + 15
                
    x = [i * 0.1 for i in ls]       # список из чисел 0..3 с шагом 0.1
    
    ethalon = [ (4 * sin(8 * i) + 0.4) for i in x]     # эталонные значения для моего варианта
         
    result = []     
    T = learning(ethalon, w, ls, random(), result)
        
    forecast(ethalon, w, ls, T) 
