;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_4а.txt Тесты_4а.txt

        Копия тестов Тесты_4а.txt:
        3
        0 0 -1 2 4 2 4 -1 -1 -1
        -3 3 -2 1 -4 1 -4 4 -2 4
        -7 -4 -9 1 -7 3 -1 -3 -3 -5
        ---
        3
        -3 3 -4 -3 -2 -3 -2 4 -4 4
        -1000 1000 -1 -1 -1 2 3 2 3 -1
        5 2 2 4 5 7 8 4 5 1
        ---
        1
        0 0 1 1 1 2 2 2 2 1
        ---
        4
        0 0 -2 1 -2 -1 0 -1 0 1
        2 2 0 0 2 0 2 3 0 3
        3 -1 0 0 0 -2 5 -2 5 0
        6 4 4 2 3 3 5 5 6 4
        ---
        3
        3 2 2 1 2 3 6 1 6 2
        6 6 5 4 3 6 6 9 8 7
        13 5 9 2 9 8 12 2 12 8

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

    /** 
    *    Опять не корректное условие! Не слово про случай когда парашутист приземляется на границу участка!!!
    *    Тест 4 содержит 3 точки на границе и один в контуре, я принимаю, что считаются только внутри контура, тогда ответ 1.
    **/

    var checkField = function (options) {

        var x               = options[0],
            y               = options[1],
            rectangle_x     = [ options[2],  options[4], options[6], options[8] ],
            rectangle_y     = [ options[3],  options[5], options[7], options[9] ],
            ans = false;

        // луч направлен влево
        for(var i = 0; i < 4; i++) {
            for(var j = 1; j < 4; j++) {
                if ( ( ( ( rectangle_y[i] <= y ) && ( y < rectangle_y[j] ) ) ||
                       ( ( rectangle_y[j] <= y ) && ( y < rectangle_y[i] ) ) ) &&
              ( x > (y - rectangle_y[i]) * (rectangle_x[j] - rectangle_x[i])  / ( rectangle_y[j] - rectangle_y[i] ) + rectangle_x[i] ) ) {
                ans = !ans
               }
            }

        }

        return ans
    }

    var countSuccessFlyers = function(options) {
        var N = parseInt(options[0]),
            count = 0;

        for(var i = 0; i < N; i++) {
            if( checkField( options[i + 1].split(' ').map(function(el){
                return parseInt(el); // прежде чем отправить массив символов спарсим их
            }))) {
                count++;
            }
        }
        return count;
    }

    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(countSuccessFlyers(test));
        }
    };



}());