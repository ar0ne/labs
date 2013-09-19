;(function() {
    "use strict"

    var fs = require('fs');

    if (process.argv.length !== 3) {
        console.error('Ошибка: Вы забыли указать имя файла с тестами!');
        console.error('Пример: $ node analize.js test.pas');
        process.exit(1);
    }
    // считываю имя Теста для задачи
    var input_file = process.argv[2];
    // открываю для чтения и запускаю main
    fs.readFile(input_file, 'utf-8', function (err, text) {
        if (err) throw err;
        main(text);
    });

    var KEYS = {
        "begin" : "Ключевое слово",
        "end"   : "Ключевое слово",
        "do"    : "Ключевое слово",
        "to"    : "Ключевое слово",
        "array" : "Ключевое слово",
        "of"    : "Ключевое слово",
        "integer": "Ключевое слово",
        "byte"  : "Ключевое слово",
        "char"  : "Ключевое слово",
        "word"  : "Ключевое слово",
        "real"  : "Ключевое слово",
        "var"   : "Ключевое слово",
        "["     : "Знак левой скобки",
        "]"     : "Знак правой скобки",
        ":"     : "Знак двоеточия",
        ".."    : "Знак промежутка",
        ";"     : "Ключевое слово",

    };

    var count = -5;


    var analize = function(str, result) {

        var bracket = /\;$/,
            var_init = /^[var]?\s*[a-zA-Z]+\:?/,
            count_init = /[a-zA-Z]+:?array?\[I\.{2}[X+|V+|L+|I+|M]+\]\sof\s[integer|real|byte|word|char]+/;

        var m = bracket.exec(str);
        if ( m == null ) {
            console.error('Error: not found bracket!');
        }

        m = var_init.exec(str);
        if ( m == null ) {
            console.error('Error: init block must to start with var or from variable name!');
        }

        m = count_init.exec(str);
        if( m == null) {
            console.error('Error: something wrong with strings!');
        }

        // all checks done
        var variables = /[a-zA-Z](?=\:)/;
        
        m = variables.exec(str);
        if(m != null) {
            result.push({
                "Лексема"           :   m[0],
                "Тип лексемы"       :   "Идентификатор",
                "Значение"          :   m[0] + " : array",
            })
        }

        var all = /[a-zA-Z]+(:?)(array?)(\[)(I)(\.{2})([X+|V+|L+|I+|M]+)(\])\s(of)\s([integer|real|byte|word|char]+)(\;){1}/;

        m = all.exec(str);
        if(m != null) {
            for(var i = 0; i < m.length; i++) {
                var tmp = m[i];
                if(KEYS.hasOwnProperty(tmp)) {
                    switch (tmp){
                        case ":":
                            // двоеточие
                            result.push({
                                "Тип лексемы" :     KEYS[":"],
                                "Лексема"     :     ":",
                                "Значение"    :     "Y" + count++,
                            });
                            break;
                        case "array":
                            // //array
                            result.push({
                                "Тип лексемы" :     KEYS["array"],
                                "Лексема"     :     "array",
                                "Значение"    :     "Y" + count++,
                            });
                            break;
                        case "[":
                            result.push({
                                "Тип лексемы" :     KEYS["["],
                                "Лексема"     :     "[",
                                "Значение"    :     "Y" + count++,
                            });
                            break;
                       case "..":
                            result.push({
                                "Тип лексемы" :     KEYS[".."],
                                "Лексема"     :     "..",
                                "Значение"    :     "Y" + count++,
                            })
                            break;
                        case "]":
                            result.push({
                                "Тип лексемы" :     KEYS["]"],
                                "Лексема"     :     "]",
                                "Значение"    :     "Y" + count++,
                            });
                            break;     
                        case ";":
                            result.push({
                                "Тип лексемы" :     KEYS[";"],
                                "Лексема"     :     ";",
                                "Значение"    :     "Y" + count++,
                            });
                            break;                   
                    }
                } else {
                    var rome_numbers = /^(M{0,3})(D?C{0,3}|C[DM])(L?X{0,3}|X[LC])(V?I{0,3}|I[VX])$/;
                    var r = rome_numbers.exec(tmp);
                    if(r != null) {
                        // if that numbers
                        result.push({
                            "Тип лексемы" :     "Константное значение",
                            "Лексема"     :     tmp,
                            "Значение"    :     tmp,
                        });
                    }
                    
                }
            }
        }
        

    }

    var show = function(obj) {
        console.log("  Лексема  |  Тип лексемы          |  Значение");
        console.log(' ===========================================================');
        for(var o in obj) {
            console.log(" ", obj[o]["Лексема"],"        | ", obj[o]["Тип лексемы"],"        | ", obj[o]["Значение"]);
        }
    }

    var main = function(options) {

        var result = [];

        analize(options, result);
        
        options = options.split('\n');

        var result = [];

        for(var i = 0; i < options.length; i++) {
         analize(options[i] , result) ;
        }
        
        show(result);

        //console.log(result);
    }



}());