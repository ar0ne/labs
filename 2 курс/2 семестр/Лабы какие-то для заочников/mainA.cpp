#include <QCoreApplication>
#include <QVector>
#include <QtDebug>


int Smain(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

   /**
    Задание 1. Дана последовательность действительных чисел. Необходимо сформировать новую последовательность
    по некоторому правилу. Для представления исходной и результирующей последовательности используйте
    библиотечный шаблон QVector.

    7.      Новая последовательность должна содержать сначала все нулевые элементы исходной, затем все остальные
    элементы (с сохранением исходного относительного порядка).
   **/

    // чтобы числа каждый раз были случайными
    srand(time(NULL));
    // объявили 2 контейнера
    QVector <double> in, out;
    // заполнили вектор случайными числами(от 4 до 9 шт) значениями 0.0 до 9.9
    for(size_t i=0; i < rand()%9 + 4; i++){
        in << (rand()%9 + (rand()%9 + 1) * 0.1)* ((rand()%9 + 1) > 5 ? -1 : 1)  * ((rand()%5+1) > 4 ? 0 : 1 );
    }
    //объявили итератор в стиле STL С++
    QVector<double>::const_iterator it;
    //выведем на экран
//    qDebug() << "Input :" << in;
    //цикл для прохода с начала в конец и проверяем, если 0 то в начало выходного контейнера, иначе то в конец
    for( it = in.constBegin(); it != in.constEnd(); ++it){
        if( *it == .0){
            out.push_front(*it);
            continue;
        }
        out.push_back(*it);
    }
    //выводим результат
//    qDebug() << "Output :" << out;
    // или построчно
    /**
    for( it = out.constBegin(); it != out.constEnd(); ++it){
        qDebug() << *it;
    }
    */

   /**
    Задание 2 выполнять используя итераторы.
    Задание 2. Дана последовательность действительных чисел. Необходимо вычислить:

    7.   Сумму элементов последовательности, расположенных между первым и последним положительными элементами.
   */

    //выполним с помощью итераторов в стиле java и используя другой контейнер - QList
    QList <double> list;
    for(size_t i=0; i < rand()%9 + 4; i++){
       list << (rand()%9 + (rand()%9 + 1) * 0.1)* ((rand()%9 + 1) > 5 ? -1 : 1) ;
    }
    qDebug() << "Input: " << list;
    //итератор для чтения-записи
    QMutableListIterator<double>  lit(list);

    double sum;
    // удаляем с начала контейнера не положительные числа
    while( lit.hasNext()){
        if(lit.next() <= 0){
            lit.remove();
            continue;
        }
        lit.remove();
        break;
    }
    //переместим итератор в конец
    lit.toBack();

    while(lit.hasPrevious()){
        if(lit.previous() <= 0){
            lit.remove();
            continue;
        }
        lit.remove();
        break;
    }
    //итератор в начале
    lit.toFront();

    //считаем все что в между
    while(lit.hasNext()){
        sum += lit.next();
    }

    qDebug() << "Summa is " << sum;



    return a.exec();
}



