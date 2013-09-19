;(function() {
    "use strict"

    /**
        Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
        Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

        Запуск из терминала:

        $ node Задача_1в.txt Тесты_1в.txt

        Копия файла тестов Тесты_1в.txt:
        10 3
        1234531230
        ---
        15 5
        010124132113211
        ---
        10 1
        0123456789
        ---
        20 2
        12345678909876543210
        ---
        11 3
        12090345090

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


    var findChiper = function(options) {

        var n = parseInt(options[0].split(' ')[0]),
            k = parseInt(options[0].split(' ')[1]),
            str = options[1];

        for(var i = 0; i < n - k; i++) {
            var mask = str.substr(i, k);
            for(var j = i + k; j < n; j++ ) {
                var tmpstr = str.substr(j);
                if(tmpstr.indexOf( mask ) + 1) {
                    return "Да";
                }
            }
        }
        return "Нет";
    }

   

    var main = function(options) {
        // между тестами нужно вставлять "---"
        var tests = options.split('---\n');

        for(var i = 0; i < tests.length; i++) {
            var test = tests[i].split('\n');
            console.log(findChiper(test));
        }
    };



}());