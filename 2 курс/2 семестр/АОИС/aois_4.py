"""
var.10 
Тип кэш-памяти:    полностью ассоциативный кэш
Размерность кэш-памяти (количество кэш-строк на количество блоков 
(количество наборов)):   4 х 8
"""

from random import random, randint
             
if __name__ == '__main__':
    N = 4
    M = 8
    
    def show_memory(cache, tags):
        print('\n%-4s | %-7s' % ('Тэг','Данные'))
        print('-' * 44)
        for i in range(N):
            print('%-4d' % (tags[i]), end=' | ')
            for j in range(M):
                print('%-4d' % (cache[i][j]), end=" ")
            print()
    
    cache = [[ randint(0, 50) for j in range(M)] for i in range(N)]         
    tags = []
    spam = 0
    while spam < N:
        try:
            rand = randint(0, 20)
            tags.index(rand)    # если не содержит такой индекс выбрасывает исключение
            continue
        except:
            tags.append(rand)
            spam += 1   
            print(tags[-1], " - ", bin(tags[-1]))

    show_memory(cache, tags)

    while True:
        spam = input("Введите физический адрес 5 - тэг, 4 - смещение : ")
        input_tag = int(spam[:-4], 2)
        offset = int(spam[-5:], 2)
        
        print(input_tag, " " ,offset)
        
        if 0 <= input_tag < 20 and 0 <= offset < M:
            for i in range(N):
                if input_tag == tags[i]:
                    if cache[i][offset] != 0:
                        print("В кэше хранится :", cache[i][offset])
                        break
                    else:
                        print("Кэш-промах!")
                        break
        else:
            print("Кэш-промах!")            

    

