/*
 Задание:
1)	Написать на ЯВУ программу, осуществляющую просмотр, модификацию и сохранение таблицы записей.
 Реализовать добавление, удаление, редактирование записей и поиск по ключу перебором.
 Таблица должна содержать N строк (в таблицу заносится n записей) и не менее трех полей
 (с одним ключевым полем).
2)	Написать на ЯВУ программу, которая преобразует таблицу данных из первого задания в хэш-таблицу
 на N строк (n записей). Для хэш-таблицы реализовать возможности добавления, удаления, модификации
 и поиска записей. Хэш-функция и метод обработки коллизий выбираются согласно варианту. Рассчитать
 вероятность возникновения коллизий (количество возникших коллизий при добавлении данных разделить
 на количество добавленных в хэш-таблицу записей) и среднее количество обращений к таблице во время
 поиска записи по ключу (сумма количества обращений к таблице при поиске каждой записи в хэш-таблице
 деленная на количество записей в хэш-таблице).

вариант         Тип хэш-функции                     Метод обработки коллизий   Количест-во  Объем хэш-таблицы
                                                                                записей n         N

  10.         XOR со сдвигом + метод умножения        двойное хеширование           40          1.1*n
*/

#include "main.h"

int getXOR(const QString key){
    int hash = 0;
    for(int i = 0; i < key.length(); i++){
        hash = (hash << 1) ^ key[i].toLatin1();
    }
    return hash;
}

int getMultiply(const int key,const int N){
    const double C = (sqrt(5)-1)/2;
    return round(N * (( C * key ) - (int)(C * key)));
}

int makeHash(const QString key,const int N){
    return getMultiply(getXOR(key),N-1);
}

void LoadDB(QStringList * vl_str, QString filename){
    QString _str;
    bool flag = false;
    QFile file;
    do{
        try{
            file.setFileName(filename);
            if(!file.open( QIODevice::ReadOnly)) {
                throw false;
            }
            flag = false;
        }catch(bool){
            qDebug() << "File not found\nPlease Enter the name of file.";
            flag=true;
            QTextStream in(stdin);
            filename.clear();
            filename = in.readLine();
        }
    }while(flag);

    QTextStream str_stream(&file);
    int i = 0;

    while(!str_stream.atEnd()){
        _str = str_stream.readLine();
        if(!_str.isEmpty())
            vl_str[i] = _str.split("::");
        i++;
    }
    file.close();
}

void showTable(QStringList * DB,const int N){
    QTextStream out(stdout);
    out << "---------------------\n";
    for(int i=0; i<N; i++){
        for(QStringList::ConstIterator it = DB[i].constBegin(); it != DB[i].constEnd(); ++it){
            out << qSetFieldWidth(14) << left << (*it) <<" ";
        }
        out << '\n';
    }
    out << "---------------------\n";
}

void addLineTable(QStringList * DB,const int N, bool mode){
    qDebug() << "Inter new line what need add to DB.";
    QTextStream in(stdin);
    QString say;
    say = in.readLine();
    if(mode){
        for(int i=0; i<N; i++){
            if(DB[i].isEmpty()){
                DB[i] = say.split(QRegExp(" "),QString::SkipEmptyParts);
                break;
            }
            if(i+1 == N){
                qDebug() << "DB is full. You must replace or delete some lines in table if u wanna still add.";
                break;
            }
        }
    }else{      // hash-table mode
        QStringList ltemp = say.split(QRegExp(" "),QString::SkipEmptyParts);
        int index = makeHash(ltemp.first(), N);
        try{
            if(!DB[index].isEmpty()){
                index = getDoubleHash(DB,0,N,index);
            }
            DB[index] = ltemp;
        }catch(...){    // если было исключение в getDoubleHash
            qDebug() << "Error. Db is full. You must delete something!";
        };
    }
}

/*
 * новые данные для строки таблицы вводятся через пробел
 */
void modTable(QStringList * DB, const int N, bool mode){
    QTextStream in(stdin);
    QString say;
    bool flag = true;
    do{
        qDebug() << "Do u wanna change some field?(y)" ;
        say = in.readLine();
        if(say == "y"){
            qDebug() << "Please enter the key-field of field what u wanna change." ;
            say = in.readLine();
            for(int i=0; i<N; ++i){
                if(DB[i].isEmpty()) continue;
                if(say == DB[i].first()){
                    qDebug() << "Enter new data by the space." ;
                    say = in.readLine();
                    QString t = DB[i].first();
                    DB[i] = say.split(QRegExp(" "), QString::SkipEmptyParts);
                    DB[i].push_front(t);
                    break;
                }
                if(i+1 == N && say != DB[i].first()){
                    qDebug() << "Key-field not found! Add to Table?";
                    say = in.readLine();
                    if(say == "y"){
                        addLineTable(DB,N,mode);
                    }
                    break;
                }
            }
        }else{
            flag=false;
        }
    }while(flag);
}

void writeToFile(QStringList * DB, const int N, QString filename){
    QFile file;
    try{
        file.setFileName(filename);
        if(!file.open( QIODevice::WriteOnly)) {
            throw "file_err";
        }
    }catch(...){
        qDebug() << "Something wrong with file, I save to FILE_";
        filename = "FILE_";
    }
    QTextStream str_stream(&file);
    for(int i=0; i<N; ++i){
        for(QStringList::ConstIterator it = DB[i].constBegin(); it != DB[i].constEnd(); ++it){
            str_stream << (*it);
            if(it+1 != DB[i].constEnd()){
                str_stream << "::";
            }
        }
        if(i != N-1) {
            str_stream << '\n';
        }
    }
    file.close();
}

void deleteLineTable(QStringList * DB,const int N){
    qDebug() << "Delete line with key-field:";
    QTextStream in(stdin);
    QString say;
    say = in.readLine();
    for(int i=0; i<N; i++){
        if(DB[i].isEmpty()) continue;
        if(DB[i].first() == say){
            DB[i].clear();
            break;
        }
        if(i+1 == N && DB[i].first() != say){
            qDebug() << "Check key-field, i can't find him in DataBase.";
            break;
        }
    }
}

// mode = false для хэш таблицы
void findByKey(QStringList * DB, QString say,const int N, bool mode){
    QTextStream out(stdout);
    if(mode){
        for(int i=0; i<N-1; ++i){
            if(DB[i].isEmpty()) continue;
            if(DB[i].first() == say){
                out << "OK.\n";
                for(QStringList::ConstIterator it = DB[i].constBegin(); it != DB[i].constEnd(); ++it){
                    out << (*it) << " ";
                }
                out << "\n";
                break;
            }
            if(i+1 == N-1 && DB[i+1].first() != say ){
                qDebug() << "Key didn't finded.";
                break;
            }
        }
    //hash-table mode
    }else{
        int index = makeHash(say, N);
        while(DB[index].isEmpty() || say != DB[index].first()){
            index = getDoubleHash(DB,0,N,index);
        }
        out << "OK.\n";
        for(QStringList::ConstIterator it = DB[index].constBegin(); it != DB[index].constEnd(); ++it){
            out << (*it) << " ";
        }
        out << "\n";
    }
}

/*
  метод двойного хэширования
  если не находим пустого места в хэш-табл, то вызываем себя
 */
int getDoubleHash(QStringList * hashTable,const int i,const int N, int h){
    //h(i+1) = (h(i) + i^2) % N
    try{
        coll++;     // глобальная переменная для подсчета коллизий
        if(i > 100) throw false;    // если зациклило
        if(hashTable[h].isEmpty()) return h;
        h = (h + i*i) % N;
        return (getDoubleHash( hashTable, i+1, N, h));
    }catch(bool){
        //в таблице нет пустого места
        qDebug() << "I can't find index for hash table. Sorry";
        throw 1;
    }
}

void makeHashTable(QStringList * hashTable, QStringList * db,const int N){
    //QString t;
    int index ;
   // int c;
    for(int i=0; i<N; ++i){
        if(db[i].isEmpty()) continue;

        index = makeHash(db[i].first(),N);
       // c = coll;
        if(!hashTable[index].isEmpty()){
            index = getDoubleHash(hashTable,0,N,index);
        }
      //  qDebug() << coll - c;
        hashTable[index] = db[i];
        //hashTable[index].push_back(t.setNum(index));
    }
}

void menu(QStringList * table,const int N, bool mode){
    QString say;
    bool flag = false;
    do{
        qDebug() << "Enter action what u wanna do.\n1.Show Table.\n2.Add Line to Table.\n3.Delete Line from Table.\n4.Modify Table.\n5.Find Line by Key.\n6.Save and write to file.";
        QTextStream in(stdin);
        say = in.readLine();
        switch (say.toInt()) {
        case 1:
            showTable(table, N);
            break;
        case 2:
            addLineTable(table,N,mode);
            break;
        case 3:
            deleteLineTable(table,N);
            break;
        case 4:
            modTable(table,N,mode);
            break;
        case 5: {
            showTable(table,N);
            qDebug() << "Enter key to find.";
            say = in.readLine();
            findByKey(table,say,N,mode);
            break;
        }
        case 6: {
            qDebug() << "Enter filename.";
            QTextStream in(stdin);
            say = in.readLine();
            writeToFile(table,N,say);
            break;
        }
        default:
            qDebug() << "Wrong command!";
            break;
        }
        qDebug() << "Continue?";
        say = in.readLine();
        if(say != "y"){
            flag = true;
        }
    }while(!flag);
}

int main(int argc, char * argv[]) {

    const int n = 40;
    const int N = n * 1.1;

    QStringList DB[N];
    if(argc == 1){
        LoadDB(DB);
    }else{
        LoadDB(DB,argv[1]); // DB filename
    }
    menu(DB, N);

    qDebug() << "--------------------\nHash-table.";
    QStringList hashDB[N];
    makeHashTable(hashDB, DB, N);

    // Вероятность возникновения ошибки( число коллизий / число добавленных элементов )
    int num_elem;
    for(int i=0; i<N; i++){
        if(!hashDB[i].isEmpty())
            num_elem++;
    }
    qDebug() << "Error probability: " << (double)coll/num_elem;

    //Среднее число обращений к таблице( общее число обращений к каждому ключу / число добавленных элементов )
    coll = 0;
    int k=0;
    for(int i=0; i<N; i++){
        if(DB[i].isEmpty()) continue;
        coll++;
        int index = makeHash(DB[i].first(),N);
        while( DB[i].first() != (hashDB[index].isEmpty() ? "NULL" : hashDB[index].first())){
            index = (index + k*k) % N;
            k++;
            coll++;
        }
        k=0;
    }
    qDebug() << "Average number of exec to table: " << (double)coll/num_elem;

    menu(hashDB, N, false);

    return 0;
}
