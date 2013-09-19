;(function() {
	"use strict"

	/**
		Для открытия тестов из файла использовал Node.JS(не нашёл условия, можно или нет использовать, 
		так что исходим из того, что можем).
		Тесты лежат в отдельных файлах для каждого задания соответсвенно Тесты_Х.txt

		Запуск из терминала:

		$ node Задача_1б.txt Тесты_1б.txt

		Копия файла Тесты_1б.txt
		D 1 D 3 E 5
		---
		H 2 C 8 A 2
		---
		F 7 G 3 B 5
		---
		A 1 B 1 C 1
		---
		H 5 H 6 H 7

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


	var countOfEmptyFields = function (coord) {

		var queen = [ 8 - parseInt(coord[1]), coord[0].charCodeAt(0) - "A".charCodeAt(0) ];
		var tower = [ 8 - parseInt(coord[3]), coord[2].charCodeAt(0) - "A".charCodeAt(0) ];
		var horse = [ 8 - parseInt(coord[5]), coord[4].charCodeAt(0) - "A".charCodeAt(0) ];

		var map = [],
			N = 8;

		for(var i = 0; i < N; i++) {
			map[i] = [];
			for(var j = 0; j < N; j++) {
				map[i][j] = 0;
			}
		}

		map[queen[0]][queen[1]] = 1;
		map[tower[0]][tower[1]] = 1;
		map[horse[0]][horse[1]] = 1;

		for(var i = 0; i < N; i++) {
			// horizontal queen
			map [ queen[0] ][i] = (map [ queen[0] ][i] === 0  ? 2 : map [ queen[0] ][i]);
			// vertical queen
			map [ i ][queen[1]] = (map [ i ][queen[1]] === 0  ? 2 : map [ i ][queen[1]]);

			// horizontal tower
			map [ tower[0] ][i] = (map [ tower[0] ][i] === 0  ? 2 : map [ tower[0] ][i]);
			// vertical tower
			map [ i ][tower[1]] = (map [ i ][tower[1]] === 0  ? 2 : map [ i ][tower[1]]);

			// перекрестные направления queen
			if( i == 0 ) continue; // не имеет смысла
			if( map [ queen[0] + i ] &&
				map [ queen[0] + i ][ queen[1] + i] !== undefined  && 
				map [ queen[0] + i ][ queen[1] + i] === 0 ) {
				map [ queen[0] + i ][ queen[1] + i] = 2;
			}
			if( map [ queen[0] + i ] &&
				map [ queen[0] + i ][ queen[1] - i] !== undefined  && 
				map [ queen[0] + i ][ queen[1] - i] === 0 ) {
				map [ queen[0] + i ][ queen[1] - i] = 2;
			}
			if( map [ queen[0] - i ] &&
				map [ queen[0] - i ][ queen[1] + i] !== undefined  &&   
				map [ queen[0] - i ][ queen[1] + i] === 0 ) {
				map [ queen[0] - i ][ queen[1] + i] = 2;
			}
			if( map [ queen[0] - i ] && 
				map [ queen[0] - i ][ queen[1] - i] !== undefined  && 
				map [ queen[0] - i ][ queen[1] - i] === 0 ) {
				map [ queen[0] - i ][ queen[1] - i] = 2;
			}
		}

		// horse: all 8 possible variants
		if( map [ horse[0] - 2 ] && 
			map [ horse[0] - 2 ] [ horse[1] - 1 ] !== undefined &&
		 	map [ horse[0] - 2 ] [ horse[1] - 1 ] === 0 ) {
			map [ horse[0] - 2 ] [ horse[1] - 1 ] = 2;
		}

		if( map [ horse[0] + 2 ] && 
			map [ horse[0] + 2 ] [ horse[1] - 1 ] !== undefined &&
		 	map [ horse[0] + 2 ] [ horse[1] - 1 ] === 0 ) {
			map [ horse[0] + 2 ] [ horse[1] - 1 ] = 2;
		}

		if( map [ horse[0] - 2 ] && 
			map [ horse[0] - 2 ] [ horse[1] + 1 ] !== undefined &&
		 	map [ horse[0] - 2 ] [ horse[1] + 1 ] === 0 ) {
			map [ horse[0] - 2 ] [ horse[1] + 1 ] = 2;
		}

		if( map [ horse[0] + 2 ] && 
			map [ horse[0] + 2 ] [ horse[1] + 1 ] !== undefined &&
		 	map [ horse[0] + 2 ] [ horse[1] + 1 ] === 0 ) {
			map [ horse[0] + 2 ] [ horse[1] + 1 ] = 2;
		}

		if( map [ horse[0] - 1 ] && 
			map [ horse[0] - 1 ] [ horse[1] - 2 ] !== undefined &&
		 	map [ horse[0] - 1 ] [ horse[1] - 2 ] === 0 ) {
			map [ horse[0] - 1 ] [ horse[1] - 2 ] = 2;
		}

		if( map [ horse[0] + 1 ] && 
			map [ horse[0] + 1 ] [ horse[1] - 2 ] !== undefined &&
		 	map [ horse[0] + 1 ] [ horse[1] - 2 ] === 0 ) {
			map [ horse[0] + 1 ] [ horse[1] - 2 ] = 2;
		}

		if( map [ horse[0] - 1 ] && 
			map [ horse[0] - 1 ] [ horse[1] + 2 ] !== undefined &&
		 	map [ horse[0] - 1 ] [ horse[1] + 2 ] === 0 ) {
			map [ horse[0] - 1 ] [ horse[1] + 2 ] = 2;
		}

		if( map [ horse[0] + 1 ] && 
			map [ horse[0] + 1 ] [ horse[1] + 2 ] !== undefined &&
		 	map [ horse[0] + 1 ] [ horse[1] + 2 ] === 0 ) {
			map [ horse[0] + 1 ] [ horse[1] + 2 ] = 2;
		}

		// uncomment if you want to see map
		//console.warn(map);

		// calculate how many empty field exist
		var count = 0;

		for(var i = 0; i < N; i++ ) {
			for(var j = 0; j < N; j++) {
				if(map[i][j] === 2) {
					count++;
				}
			}
		}

		return count;
	}

	/*
		Из условия видно что последовательность входной строки: ферзь, ладья и конь
		координата состоит из A-H и 1-8
		Пример: D 1 D 3 E 5
	*/

	var main = function(options) {
		// между тестами нужно вставлять "---"
		var tests = options.split('---\n');

		for(var i = 0; i < tests.length; i++) {
			var test = tests[i].split('\n');
			console.log(countOfEmptyFields(test[0].split(' ')));
		}
	};



}());