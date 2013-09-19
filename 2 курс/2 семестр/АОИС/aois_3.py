"""
var 2
Наличие регистра маски        false
Способы сравнения             =,>,>=,<,<=,<>
Тип ассоциативной памяти      с полным параллельным доступом
"""

from random import randint

def print_result(data, regFind):
    print('%-3s|%-6s' % ('РП', 'Память'))
    for i in range(len(data)):
        print('\n%-3s' % (regFind[i]), end = '')
        for j in range(len(data[i])):
            print('%-1s' % (data[i][j]), end = '')
  
if __name__ == '__main__':
    
    # передача аргумента в терминале, argv[1] - кол-во входных образов
    try: 
        if(argv[1] and argv[2]): 
            N = int(argv[1])
            M = int(argv[2])
    except:
        N = 6  
        M = 6
    
    data = [str([randint(0,1) for j in range(M)]) for i in range(N)]
       
    while True:
        
        # Регистр поиска
        regFind = [1 for i in range(N)]
        
        print_result(data, regFind)
        
        spam = str([int(i) for i in (input("\nВведите ассоциативный признак для поиска в памяти: \n"))])
        
        foo = int(input("Введите способ сравнения: \n1. =\t2. >\t3. >=\t4. <\t5. <=\t6. <> \n"))
        
        if foo == 1:        # =
            for i in range(N):
                if spam != data[i]:
                    regFind[i] = 0
            print_result(data, regFind)
            
        elif foo == 2:      # >
            for i in range(N):
                if spam <= data[i]:
                    regFind[i] = 0
            print_result(data, regFind)
            
        elif foo == 3:      # >=
            for i in range(N):
                if spam < data[i]:
                    regFind[i] = 0
            print_result(data, regFind)            
            
        elif foo == 4:      # <
            for i in range(N):
                if spam >= data[i]:
                    regFind[i] = 0
            print_result(data, regFind)            
            
        elif foo == 5:      # <=
            for i in range(N):
                if spam > data[i]:
                    regFind[i] = 0
            print_result(data, regFind)
                                    
        elif foo == 6:      # <>
            for i in range(N):
                if spam == data[i]:
                    regFind[i] = 0
            print_result(data, regFind)
        
        else:
            print("Неправильная команда!")
        
        if 'Y' == input("\nВыйти?(Y)").upper():
            break