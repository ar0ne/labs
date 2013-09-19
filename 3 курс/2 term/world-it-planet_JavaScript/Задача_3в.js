;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_3в.txt Тесты_3в.txt

        Копия тестов Тесты_3в.txt:
        3 4
        ---
        2 8
        ---
        2 6
        ---
        2 4
        ---
        7 10

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


    var steps,
        nRoutes,
        k = 0;


    var countRabbitJumps = function (options) {
        options = options[0].split(' ').map(function(el) {
            return parseInt(el);
        });

        var k = options[0],
            n = options[1],
            steps = [],
            nRoutes = 0;

        var jump = function(n) {
            var i = 1;
            while ( i <= k) {
                if( i < n ) {
                    steps[steps.length] = i;
                    jump(n - i);
                } else {
                    steps[steps.length] = i;
                    //console.log(steps);
                    delete steps[steps.length];
                    if(steps.length > 1) {
                        delete steps[steps.length];
                    }
                    nRoutes += 1;
                    return;
                }
                i += 1;
            }
            return "";
        }

        jump(n);
        return nRoutes;
        
    }



   



    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(countRabbitJumps(test));
        }
    };



}());