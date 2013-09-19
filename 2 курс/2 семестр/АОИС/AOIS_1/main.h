#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <qmath.h>

int coll = 0; // число коллизий и обращений для статистики

int  getXOR         (const QString);
int  getMultiply    (const int,     const int);
int  makeHash       (const QString, const int);
void LoadDB         (QStringList *, QString = "DB.file");
void showTable      (QStringList *, const int);
void addLineTable   (QStringList *, const int,bool = true);
void modTable       (QStringList *, const int,bool = true);
void writeToFile    (QStringList *, const int,QString);
void deleteLineTable(QStringList *, const int);
void findByKey      (QStringList *, QString,  const int, bool = true);
int  getDoubleHash  (QStringList *, const int,const int, int);
void makeHashTable  (QStringList *, QStringList *,const int);
void menu           (QStringList *, const int, bool = true);

#endif // MAIN_H
