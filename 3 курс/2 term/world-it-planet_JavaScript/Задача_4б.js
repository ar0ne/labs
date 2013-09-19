;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_4б.txt Тесты_4б.txt

        Копия тестов Тесты_4б.txt:
        5
        -1 1 0 4 2
        ---
        10
        1 5 2 6 7 -4 0 -2 3 6
        ---
        6
        -10 10 -15 -30 -20 20
        ---
        4
        0 0 1 0
        ---
        7
        2 4 6 -4 5 8

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


    var maxLength = function (options) {
        // console.warn(options);
        var n = parseInt( options[0]),
            arr = [];

        arr = options[1].split(' ').map(function(el) {
            return parseInt(el);
        });

        var j = 0,
            i = 1,
            cur_length = -2; // 0

        while( i < n - 1) {
            if ( ( (arr[i] > arr[i+1])  &&  (arr[i] > arr[i-1]) )  ||
                 ( (arr[i] < arr[i+1])  &&  (arr[i] < arr[i-1]) ) ) {

                if (cur_length < ++j) {
                    cur_length = j;
                }

            i++;

            } else {

                j = 0;
                i++;

            }
            // console.log(j);
        }

        return cur_length + 2; // 
    }


    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(maxLength(test));
        }
    };



}());