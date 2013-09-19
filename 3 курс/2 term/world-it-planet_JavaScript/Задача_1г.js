;(function() {
	"use strict"

	/**
		Для открытия тестов из файла, использовал Node.JS(не нашёл условия, можно или нет использовать, так что исходим из того, что можем).
		Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

		Запуск из терминала:

		$ node Задача_1г.txt Тесты_1г.txt

		Копия тестов Тесты_1г.txt:
		10 3 2 1
		---
		100 0 0 0
		---
		15 5 5 5
		---
		60 20 0 15
		---
		2 1 0 0 
		---
		4 2 0 0

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
	- в пароле должно быть хотя бы «a «заглавных букв
	- в пароле должно быть хотя бы «b» строчных букв
	- в пароле должно быть хотя бы «с» цифр
	- в пароле не должно быть двух одинаковых идущих подряд символов
	*/

	var generatePassword = function (options) {
		var n = parseInt(options[0]),
			a = parseInt(options[1]),
			b = parseInt(options[2]),
			c = parseInt(options[3]);

			var pass = "",
				ch = '';

			for(var i = 0, ch = 'A' ; i < a; i++) {
				if(i && i % 26 == 0) {
					ch = 'A'
				}
				pass += ch;
				ch = String.fromCharCode( ch.charCodeAt(0) + 1 );
			}
			for(var i = 0, ch = 'a' ; i < b; i++) {
				if(i && i % 26 == 0) {
					ch = 'a' 
				}
				pass += ch;
				ch = String.fromCharCode( ch.charCodeAt(0) + 1 );
			}
			for(var i = 0, ch = '0' ; i < c; i++) {
				if(i && i % 10 == 0) {
					ch = '0'
				}
				pass += ch;
				ch = String.fromCharCode( ch.charCodeAt(0) + 1 );
			}

			// сколько осталось заполним зацикленными ABC...
			var foo = n - (a + b + c);

			// check what the last char was (test 5)

			ch = ( pass [ pass.length - 1 ] == 'A' ? 'B' : 'A'); 

			for(var i = 0 ; i < foo; i++) {
				if(i && i % 26 == 0) {
					ch = 'A'
				}
				pass += ch;
				ch = String.fromCharCode( ch.charCodeAt(0) + 1 );
			}

			return pass;
	}
	

	var main = function(options) {
		// между тестами нужно вставлять "---"
		var tests = options.split('---\n');

		for(var i = 0; i < tests.length; i++) {
			var test = tests[i].split('\n');
			console.log(generatePassword(test[0].split(' ')));
		}
	};



}());