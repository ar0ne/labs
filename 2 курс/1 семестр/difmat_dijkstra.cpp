/*
 *1.Вычислить максимальное количество чисел, которые можно представить
 * в двоичной системе восьмиразрядным числом.
2. Сколькими способами можно составить трехцветный полосатый флаг, если
имеется материал пяти различных цветов?
3. Сколькими способами можно составить набор из 8 пирожных, если имеется
4 сорта пирожных?
4. Сколько существует перестановок элементов 1, 2, ...,n , в которых элемент
 1 находится не на своём месте?
5. При опросе 13 человек, каждый из которых знает, по крайней мере, один иностранный
 язык, выяснилось, что 10 человек знают английский язык, 7 - немецкий,
 6 - испанский, 5 - английский и немецкий, 4 - английский и испанский,
 3 - немецкий и испанский. Сколько человек знают: а) все три языка?
 б) ровно два языка? в) только английский?
*/
/*
 *1. Написать программу генерации перестановок (рекурсивный вариант).
 * Четные номера – реализуют лексикографический порядок генерации.
 * Нечетные номера – реализуют антилексикографический порядок генерации.
  2. Написать  программу генерации k- элементных подмножеств n-элементного
  множества в  лексикографическом порядке. Вход: k – мощность подмножества,
  n - мощность множества.
*/


#include <iostream>
#include <cstring>

using namespace std;

void DoReverse  (int *, int );
void MakeAntilex(int *, int);


int N;

///////////// FIRST TASK /////////////////////////
int SSSmain(void){
    cout<<"Введите число перестановок\n";
    cin>>N;

    int *mass = new int[N];

    for(int i=0; i<N; i++)
        mass[i]=i+1;

    MakeAntilex(mass, N-1);
    return 0;
}

void MakeAntilex(int *M, int size){
    if(size == 0){
        for(int i=0; i<N; i++){
            cout<<M[i]<<" ";
        }
        cout<<endl;
    }else{
        for(int i=0; i<= size; i++){
            MakeAntilex(M, size - 1);
            if(i < size){
                swap(M[i], M[size]);
                DoReverse(M, size-1);
            }
        }
    }
}

void DoReverse(int *M, int size){
    int i=0, j = size;
    while(i < j){
        swap(M[i],M[j]);
        i++;
        j--;
    }
}

///////// SECOND TASK //////////////////////
/*
 * 2. Написать  программу генерации k- элементных подмножеств n-элементного
  	  множества в  лексикографическом порядке. Вход: k – мощность подмножества,
  	  n - мощность множества.
 */




#include <iostream>
#include <vector>
#include <algorithm>

void PrintSubset( vector<bool> bit_mask, int req_size ) {
    if( count( bit_mask.begin(), bit_mask.end(), true ) == req_size ){
        static int cnt = 0 ;
        cout << ++cnt << ". [ " ;
        for( size_t i = 0 ; i < bit_mask.size() ; ++i )
            if( bit_mask[i] ) cout << i+1 << ' ' ;
        cout << "]\n" ;
    }
}

bool NextBitmask( vector<bool> & bit_mask ) {
    size_t i = 0 ;  // unsigned int
    for( ; ( i < bit_mask.size() ) && bit_mask[i] ; ++i ) {
        bit_mask[i] = false ;
    }
    if( i < bit_mask.size() ) {
    	bit_mask[i] = true ;
    	return true ;
    } else
    	return false ;
}

int mainssss() {
    int k, n ;
    cout << "n? " && std::cin >> n ;
    cout << "k? " && std::cin >> k ;
    vector<bool> bit_mask(n) ;
    do {
    	PrintSubset( bit_mask, k ) ;

    } while( NextBitmask(bit_mask) ) ;

	return 0;
}









///////// dijkstra ////////////////////////////////////
///
///http://acmp.ru/index.asp?main=task&id_task=132
///

/*

    Дан ориентированный взвешенный граф. Для него вам необходимо найти кратчайшее расстояние от вершины S до вершины F.
Входные данные

В первой строке входного файла INPUT.TXT записаны три числа: N, S и F (1 <= N <= 100; 1 <= S, F <= N),
где N - количество вершин графа. В следующих N строках записаны по N чисел - матрица смежности графа,
где число в i-ой строке j-ом столбце соответствует ребру из i в j: -1 означает отсутствие ребра между вершинами,
а любое неотрицательное целое число (от 0 до 100) - наличие ребра данного веса .
 На главной диагонали матрицы всегда записаны нули.
Выходные данные

В выходной файл OUTPUT.TXT необходимо вывести искомое расстояние или -1, если пути между указанными вершинами не существует.
Пример
№	INPUT.TXT	OUTPUT.TXT
3  1   2           6
0 -1   2
3  0  -1
-1 4    0


Кол.
вер-
шин		6

Кол.
ре-
бер		9

Ребра
и веса	{1,2},{1,4}{2,3},{2,4},{3,4}
		{3,5},{3,6},{4,5},{5,6};
		[4,3,6,5,4,7,8,5,6,7];





 */

#include <fstream>
#include <vector>
#include <algorithm>

/////////////////////////////////////////////////////////
int main(){

    ifstream in("input");
    ofstream out("output");

    const int INF = 1000000000;


        int n,s,f;
        in>>n>>s>>f;
        int temp;
        s--;
        f--;


        vector < vector < pair<int,int> > > g (n);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                in>>temp;
                if(i == j || temp < 0) continue;
                else {
                    g[i].push_back(make_pair(j,temp));
                }
            }
        }


        vector<int> d (n, INF),  p (n);
        d[s] = 0;
        vector<char> u (n);
        for (int i=0; i<n; ++i) {
            int v = -1;
            for (int j=0; j<n; ++j)
                if (!u[j] && (v == -1 || d[j] < d[v]))
                    v = j;
            if (d[v] == INF)
                break;
            u[v] = true;

            for (size_t j=0; j<g[v].size(); ++j) {
                int to = g[v][j].first, len = g[v][j].second;
                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                }
            }
        }

        vector<int> path;
        for (int v=f,max; v!=s || max > 50; v=p[v],max++){
        	path.push_back (v);
        }
        path.push_back (s);
        reverse (path.begin(), path.end());

        for(size_t i=0; i<path.size(); i++){
        	out<<path[i]+1<<" ";
        }
        out<<"\n"<<d[f];

    return 0;
}
