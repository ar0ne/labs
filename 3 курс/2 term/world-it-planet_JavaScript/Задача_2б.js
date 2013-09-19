;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_2б.txt Тесты_2б.txt

        Копия тестов Тесты_2б.txt:
        10 3
        ---
        6 2
        ---
        8 4
        ---
        10 5
        ---
        12 3

        Результаты работы алгоритма результат_Задача_2б.txt:
        25
        15
        5
        6
        36

    */

    var fs = require('fs');

    if (process.argv.length !== 3) {
        console.error('Ошибка: Вы забыли указать имя файла с тестами!');
        console.error('Пример: $ node Задача_1а.txt Тесты_1а.txt');
        process.exit(1);
    }
    // считываю имя Теста для задачи
    var input_file = process.argv[2];
    // открываю для чтения и запускаю main
    fs.readFile(input_file, 'utf-8', function (err, text) {
        if (err) throw err;
        main(text);
    });


    var countTree = function (options) {

        options = options.split(' ').map(function(el){
            return parseInt(el);
        });

        var n = options[0],
            m = options[1],
            cnt = 0,
            step = 0,
            sum = 0;

        if ( m !== 0) {
            if (m === 1) {
                sum = n;
            } else {
                cnt = Math.round( (n - 1) / ( m - 1 ));
                step = m - 1;
                sum = Math.round( (2 + (cnt - 1) * step) * cnt / 2);
            }
        } else {
            sum = 1;
        }

        return sum;
    }

    

    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(countTree(test[0]));
        }
    };



}());