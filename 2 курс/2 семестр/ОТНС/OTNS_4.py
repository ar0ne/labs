#! /usr/bin/env python3

from math import sin,cos,exp
from random import random
from sys import argv

# w - весовые коэфф
# eth - 3 эталонных значения
# @return выходное значение   
def getY(w, eth, T):
    S = w[0]*eth[0] + w[1]*eth[1] + w[2]*eth[2] - T
    return (1 / (1 + exp(1) **(-S)))

def show(ls, res, eth):
    print ('%-2s | %-10s | %-10s | %-10s' % ('#','Результат','Эталон','Разность'))
    print('-' * 40)
    for i in ls:
        print('%-2d | %-10f | %-10f | %-10f' % (i+1, res[i], eth[i], eth[i] - res[i] ))

# обучение НС с сигмоидной функцией активации
# ls - список чисел от 0 до n
# @return T - т.к. он изменяемый тип(float) на выходе из ф-ции - утрачивается
def learning(ethalon, w, ls, T, result): 

    ErrMin = 0.001
    Err = 1            # среднеквадратичная ошибка сети
    alpha = 0.5        # скорость обучения
    u = 0              # число итераций

    while Err > ErrMin:
        Err = 0
        for i in ls[:len(ls)-3]:
            Y = getY(w, ethalon[i:i+3], T)
            gamma = Y - ethalon[i+3]
            w[0] -= alpha * gamma * Y * (1 - Y) * ethalon[i]
            w[1] -= alpha * gamma * Y * (1 - Y) * ethalon[i+1]
            w[2] -= alpha * gamma * Y * (1 - Y) * ethalon[i+2]
            T += alpha * gamma * Y * (1 - Y)
        u += 1
        for i in range(len(ls)-3):
            Y = getY(w, ethalon[i:i+3], T)
            Err += (0.5 * ((Y - ethalon[i+3]) ** 2))
        #print(Err)
        
    print('Итоги обучения: ')

    for i in range(3):
        result.append(ethalon[i])
    
    for i in ls[:27]:
        S = w[0] * ethalon[i] + w[1] * ethalon[i+1] + w[2] * ethalon[i+2] - T
        result.append(1/(1 + exp(1) **(-S)))
    print('итераций = ', u, 'alpha = ',alpha)
    
    show(ls[:30], result, ethalon)  
 
    return T      

# прогнозирование
def forecast(_ethalon, _w, _list, T):
    mass = []
    for i in range(3):
        mass.append(_ethalon[i])
 
    for i in _list[:len(ls)-3]:
        S = mass[i] * _w[0] + mass[i+1] * _w[1] + mass[i+2] * _w[2] - T
        mass.append(1 / (1 + exp(1) **(-S)))
    
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
       
    w =  [random(),random(),random()]       # весовые коэфициенты          
    ls = [i for i in range(n+15)]           # список чисел от 0 до n + 15       
    x =  [i * 0.1 for i in ls]              # список из чисел 0..3 с шагом 0.1
    
    # y = a * cos(b*x) + c*sin(d*x)
    # 0.2    0.4    0.09    0.4
    ethalon = [(0.2 * cos(0.4 * i) + 0.09 * sin(0.4 * i))  for i in x]     # эталонные значения для моего варианта
         
    result = []     
    T = learning(ethalon, w, ls, random(), result)
        
    forecast(ethalon, w, ls, T) 
