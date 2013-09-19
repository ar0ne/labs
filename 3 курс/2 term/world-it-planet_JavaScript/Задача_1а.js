;(function() {
	"use strict"

/**
	Для написания использовал Node.JS(не нашёл условия, можно или нет использовать).
	Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

	Запуск из терминала:

	$ node Задача_1а.txt Тесты_1а.txt

	Копия файла Тесты_1а.txt
	3
	0 1 1
	1 0 1
	1 1 0
	---
	5 
	0 0 0 0 0
	0 0 0 0 0
	0 0 1 0 0 
	0 0 0 0 0
	0 0 0 0 0
	---
	0
	---
	10
	0 1 0 0 1 0 0 0 1 0
	1 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	1 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	1 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	---
	6
	1 1 1 1 1 1
	1 1 1 1 1 1
	1 1 1 1 1 1
	1 1 1 1 1 1
	1 1 1 1 1 1
	1 1 1 1 1 1


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

	// исходим из того что дорога из одного города в другой всегда имеет такую же дорогу из 2го в 1ый
	// чего не указано в задании, к сожалению
	var countOfTheRoad = function (map) {
		var N 		= map[0],
			arr 	= [],
			count 	= 0;

		for(var i = 0; i < N; i++){
			arr[i] = map[1 + i].split(' ');
		}

		for(var i = 0; i < N; i++) {
			for(var j = 0; j < N; j++) {
				if(parseInt(arr[i][j]) === 1 && i != j) {
					count++;
				}
			}
		}

		return (count % 2 === 0  ? count : count - 1) / 2;
	}


	var main = function(options) {
		// между тестами нужно вставлять ---
		var tests = options.split('---\n');

		for(var i = 0; i < tests.length; i++) {
			// Output count of roads between citys
			console.log(countOfTheRoad(tests[i].split('\n')));
		}
	};



}());