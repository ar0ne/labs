;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_3б.txt Тесты_3б.txt

        Копия тестов Тесты_3б.txt:
         1 0 -12 16
         ---
         1 0 -6 4
         ---
         1 3 -3 -14
         ---
         1 0 -19 30
         ---
         1 -6 57 -196

    */

    var fs = require('fs');

    if (process.argv.length !== 3) {
        console.error('Ошибка: Вы забыли указать имя файла с тестами!');
        console.error('Пример: $node Задача_1а.txt Тесты_1а.txt');
        process.exit(1);
    }
    // считываю имя Теста для задачи
    var input_file = process.argv[2];
    // открываю для чтения и запускаю main
    fs.readFile(input_file, 'utf-8', function (err, text) {
        if (err) throw err;
        main(text);
    });


    var quickSort  = function (A){

        if (A.length == 0) return [];
        var a = [], b = [], p = A[0];
        for (var i = 1; i < A.length; i++) {
        if (A[ i ] < p) a[a.length] = A[ i ];
           else b[b.length] = A[ i ];
        }
        return quickSort(a).concat( p,quickSort(b) );
    }


    var doStuff = function(options) {

        options = options[0].split(' ').map(function(el){
            return parseInt(el);
        })

        var a = options[0],
            b = options[1],
            c = options[2],
            d = options[3];

        var min = -100,
            max = 100;

        var ans = [];

        for(var i = min; i < max; i++) {
            if(a * Math.pow(i, 3) + b * Math.pow(i, 2) + c * i + d === 0 ) {
                ans[ans.length] = i;
            }
        }

        ans = quickSort(ans);

        var out = '';
        for(var i = 0; i < ans.length; i++) {
            out += ans[i] + " ";
        }

        return out;
    } 
   



    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(doStuff(test));
        }
    };



}());