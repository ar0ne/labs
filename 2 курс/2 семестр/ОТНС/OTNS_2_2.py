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


# обучение НС
# ls - список чисел от 0 до n
# @return T - т.к. он изменяемый тип(float) на выходе из ф-ции - утрачивается
def learning(ethalon, w, ls, T, result): 

    ErrMin = 0.0001
    Err = 1             # среднеквадратичная ошибка сети
    alpha = 0.1     # скорость обучения
    u = 0               # число итераций
    Y = [0]*30

    while Err > ErrMin:
        
        for i in range(27):
            Y[i] = w[0] * ethalon[i] + w[1] * ethalon[i+1] + w[2] * ethalon[i+2] - T
            
            for j in range(3):
                w[j] = w[j] - alpha * (Y[i] - ethalon[i+3]) * ethalon[i+j]
            T += alpha * (Y[i] - ethalon[i+3])
        
        for i in range(27):
            Y[i] = w[0] * ethalon[i] + w[1] * ethalon[i+1] + w[2] * ethalon[i+2] - T 
            Err += ((Y[i] - ethalon[i+3]) ** 2)
        Err /= 2
        print(Err)   
   


# main
if __name__ == '__main__':
    
    # передача аргумента в терминале, argv[1] - кол-во входных образов
    try: 
        if(argv[1]): 
            n = int(argv[1])
    except:
        n = 30  
       
    w = [random(),random(),random()]    #весовые коэфициенты          
       
    ls = [i for i in range(n)]          # список чисел от 0 до n 
                
    x = [i * 0.1 for i in ls]           # список из чисел 0..3 с шагом 0.1
    
    ethalon = [ (4 * sin(8 * i) + 0.4) for i in x]     # эталонные значения для моего варианта
         
    result = []     
    T = learning(ethalon, w, ls, random(), result)
        
    #forecast(ethalon, w, ls, T) 