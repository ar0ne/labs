#include <QCoreApplication>
#include <QVector>
#include <QtDebug>
//#include <iostream>
#include <cstdlib>
#include <time.h>

//using namespace std;

//void Bur2();

void FirstVar();
void SecondTask();
/*
 *  бурцев 4 вариант 2 лаба два задания

    нескей 5 вариант 1 задание
*/
int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);


//    Neskei_first();

    //Bur2();

  //  FirstVar();
    SecondTask();

    return a.exec();
}


void Neskei_first(){
/*
    Задание 1. Дана последовательность действительных чисел. Необходимо сформировать новую последовательность
    по некоторому правилу. Для представления исходной и результирующей последовательности используйте библиотечный шаблон QVector.
    5. В новую последовательность из исходной требуется занести те элементы исходной, модуль которых не превышает 1.
*/
    //cлучайные числа
    srand(time(NULL));

    QVector <double> in, out;
    // 5 случайных числа от -3.9 до 3.9
    for(int i=0; i < 5 ; i++){
        in << (rand()%6 - 3) + rand()%9 * 0.1;
    }
    // итератор в стиле STL С++
    QVector<double>::const_iterator it;
    //вывод на экран
    qDebug("Input QVector:");
    for( it = in.constBegin(); it != in.constEnd(); ++it){
        qDebug("%.1f ", *it);
    }
    // если модуль числа <= 1 , то добавляем его в выходной контейнер
    for( it = in.constBegin(); it != in.constEnd(); ++it){
        if(*it * (*it < 0 ? -1 : 1 ) <= 1.0){
            out.push_back(*it);
        }
    }
    // вывод результатов
    qDebug("Output QVector:");
    for( it = out.constBegin(); it != out.constEnd(); ++it){
        qDebug("%.1f ", *it);
    }

}

void Bur(){
    /*
     4. Новая последовательность сначала должна содержать все элементы исходной с четными
    индексами, затем - все остальные (с сохранением исходного относительного порядка).
     */

    //cлучайные числа
    srand(time(NULL));

    const unsigned int SIZE = rand()%5 + 5;
    QVector <double> in, out;

    // случайные числа от -10.9 до 10.9
    for(int i=0; i < SIZE ; i++){
        in << (rand()%20 - 10) + rand()%9 * 0.1;
    }

    qDebug() << "In:";
    for(int i=0; i < SIZE; i++){
        qDebug("%.1f", in[i]);
    }

    for(int i=0; i < SIZE; i+=2){
        out.push_back(in[i]);
    }
    for(int i=1; i < SIZE; i+=2){
        out.push_back(in[i]);
    }

    qDebug() << endl<< "Out:";
    for(int i=0; i < SIZE; i++){
        qDebug("%.1f", out[i]);
    }

}


void Bur2(){
    /*
     *  4. Произведение элементов последовательности, расположенных между максимальным по модулю
     *  и минимальным по модулю элементами.
     **/

    //cлучайные числа
    srand(time(NULL));
    // размер контейнера
    const unsigned int SIZE = rand()%5 + 5;

    QVector <double> in;
    double temp;

    // случайные числа от -10.9 до 10.9
    for(int i=0; i < SIZE ; i++){
        temp = (rand()%20 - 10) + rand()%9 * 0.1 ;
        // если уже содержится в контейнере, то не добавляем
        if(!in.contains(temp))
            in.push_back(temp);
        else i--;
    }
    // Вывод на экран входного контейнера
    qDebug() << "In:";
    for(int i=0; i < SIZE; i++){
        qDebug("%.1f", in[i]);
    }
    // итераторы для чтения в стиле STL,
    QVector<double>::const_iterator it,
            min = in.constBegin(), /* дополнительные итераторы для    */
            max = in.constBegin(); /* указания на мин и макс элементы */

    /* находим мин и макс элементы - для этого проходим по контейнеру */
    /* если элемент по модулю больше или меньше, то переприсваеваем   */
    for(it = in.constBegin(); it != in.constEnd(); ++it){
        if((*it > 0 ? *it : -*it)  > (*max > 0 ? *max : -*max) ){
            max = it;
        }
        if((*it > 0 ? *it : -*it ) < (*min > 0 ? *min : -*min)){
            min = it;
        }
    }

    double mult = 1;

    // если min левее, то идем до max
    if(in.indexOf(*min) < in.indexOf(*max)){
        for(it = min+1; it != max; ++it){
            mult *= *it;
        }
        // если max левее, то наоборот
    }  else {
        for(it = max+1; it != min; ++it){
            mult *= *it;
        }
    }

    qDebug() << endl << "Max: "<< *max << endl << "min: "<< *min<< endl << "Multiply: "<< (mult == 1 ? 0 : mult);
}


void FirstVar(){
    /*
    Задание 1. Дана последовательность действительных чисел. Необходимо сформировать новую последовательность по некоторому
    правилу. Для представления исходной и результирующей последовательности используйте библиотечный шаблон QVector.
    Варианты задания
    1. Новая последовательность должна содержать все ненулевые элементы исходной (с сохранением исходного относительного порядка).
    */

    //включаем генератор псевдоcлучайных чисел
    srand(time(NULL));

    QVector <double> in, out;
    for(size_t i=0; i < 7 ; i++){
        //генерируем 7 случайных чисел и выводим их
        //        от -10 до 10       от 0.0 до 0.9       { -1 , 0, 1 }
        in << (( rand()%20 - 10 ) + rand()%9 * 0.1 ) * ( rand()%2 - 1 );
        qDebug() << in[i];
    }

    // объявляем итератор для чтения в стиле STL
    QVector <double>::const_iterator it;
    for(it = in.constBegin(); it != in.constEnd(); ++it){
        // если значение равно 0, то отбрасываем его
        if(*it != .0){
            //иначе добавляем в конец выходного контейнера
            out.push_back(*it);
        }
    }

    qDebug() << endl << "Output:";
    for(size_t i=0; i<out.size(); ++i){
        qDebug() << out[i];
    }
}


void SecondTask(){
    /*
     Задание 2. Дана последовательность действительных чисел. Необходимо вычислить:
     1. Произведение элементов последовательности, расположенных между максимальным и минимальным элементами.
    */

    //включаем генератор псевдоcлучайных чисел
    srand(time(NULL));
    // случайный размер контейнера 5-10 элементов
    const size_t SIZE = rand()%5 + 5;

    QVector <double> in;
    double temp;

    // случайные числа от -10.9 до 10.9
    for(size_t i=0; i < SIZE ; i++){
        temp = (rand()%20 - 10) + rand()%9 * 0.1 ;
        // если уже содержится в контейнере, то не добавляем
        if(!in.contains(temp))
            in.push_back(temp);
        else i--;
    }
    // Вывод на экран входного контейнера
    qDebug() << "Input:";
    for(size_t i=0; i < SIZE; i++){
        qDebug("%.1f", in[i]);
    }

    // итераторы для чтения в стиле STL,
    QVector<double>::const_iterator it,
            min = in.constBegin(), /* дополнительные итераторы для    */
            max = in.constBegin(); /* указания на мин и макс элементы */

    /* находим мин и макс элементы - для этого проходим по контейнеру */
    /* если элемент по модулю больше или меньше, то переприсваеваем   */
    for(it = in.constBegin(); it != in.constEnd(); ++it){
        if(*it   > *max  ){
            max = it;
        }
        if(*it  < *min ){
            min = it;
        }
    }

    temp = 1;

    // если min левее, то идем до max
    if(in.indexOf(*min) < in.indexOf(*max)){
        for(it = min+1; it != max; ++it){
            temp *= *it;
        }
        // если max левее, то наоборот
    }  else {
        for(it = max+1; it != min; ++it){
            temp *= *it;
        }
    }

    qDebug("Max: %.1f min: %.1f Multiply: %.1f", *max, *min, (temp == 1 ? 0 : temp));
}
