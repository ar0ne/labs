#ifndef _MAIN_CPP_

    /*
        10. Таблица строится по методу дерева с использованием хеш-функции при сравнении идентификаторов. 
        В качестве хеш-функции выступает код первой буквы идентификатора. Внутри каждой ячейки дерева поиск идет простым перебором. 
    */

    #include "main.h"

    int main () {

        Tree tree;

        string str []  = {"abc", "brf", "mgf", "aan", "bbb", "aaa"};
        
        for(int i = 0, len = (sizeof (str))/sizeof(str[0]); i < len; i++) {
            tree.add(str[i]);
        }

        cout << "Find 'mgf': " << (tree.find("mgf") ? "Found identifier" : "Not found identifier") << endl << endl;
        cout << "\nFind 'abc': " << (tree.find("abc") ? "Found identifier" : "Not found identifier") << endl;
        cout << "\nFind 'brf': " << (tree.find("brf") ? "Found identifier" : "Not found identifier") << endl;
        cout << "\nFind 'aan': " << (tree.find("aan") ? "Found identifier" : "Not found identifier") << endl << endl;
        cout << "\nFind 'bbb': " << (tree.find("bbb") ? "Found identifier" : "Not found identifier") << endl;
        cout << "\nFind 'UHUDHA': " << (tree.find("UHUDHA") ? "Found identifier" : "Not found identifier") << endl;
        cout << "\nFind 'ana': " << (tree.find("ana") ? "Found identifier" : "Not found identifier") << endl;
        cout << "\nFind 'iii': " << (tree.find("iii") ? "Found identifier" : "Not found identifier") << endl << endl;
        cout << "Find 'aaa': " << (tree.find("aaa") ? "Found identifier" : "Not found identifier") << endl;

        
        return 0;
    }



#endif