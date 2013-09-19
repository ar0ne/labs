;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_2д.txt Тесты_2д.txt

        Копия тестов Тесты_2д.txt:
        2 10 4 8
        ---
        2 3 6 12
        ---
        4 20 6 12
        ---
        1 50 40 90
        ---
        1 10 4 10

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


    var countRooms = function(options) {
        options = options[0].split(' ').map(function(el) {
            return parseInt(el);
        });

        var a = options[0],
            b = options[1],
            c = options[2],
            d = options[3];

        var count = 0,
            min_y,
            max_y;


        for(var x = 1; x < (d >> 1); x++) {
            if(x * x > b) {
                break;
            }

            min_y = x;

            if ( min_y <= (( c + 1 ) >> 1 ) - x ) {
                min_y = (( c + 1 ) >> 1 );
            } 
            if( min_y > max_y * max_y >> d) {
                min_y = min_y * 2 >> 1;
            }
            if ( parseInt((a + x - 1) / x ) > min_y) {
                min_y = parseInt((a + x - 1) / x);
            }
            // if( max_y - min_y >= (d - c )* 2) {

                //}

            max_y = (d >> 1) - x;

            if(max_y >= parseInt(b / x) ) {
                max_y = parseInt(b / x);
            }

            if(max_y >= min_y) {
                count += (max_y - min_y + 1);
            }

        }

        return count;
        // return count / 2
    }



    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(countRooms(test));
        }
    };



}());