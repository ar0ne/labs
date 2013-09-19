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

	/**
		9. Входной язык содержит последовательность описаний массивов в соответствии со спецификацией языка Паскаль, 
		разделенных символом ;(точка с запятой). Считать, что массивы могут содержать только элементы скалярных типов integer, real, byte, word и char. 
		10. См. вариант №9, но размер массива должен указываться с помощью римских чисел. 

		1 		I 	
		5 		V 	
		10 		X 	
		50 		L 	
		100  	C 	
		500 	D 	
		1000 	M 	

	**/


	var KEYS = {
		"begin" : "Ключевое слово",
		"end" 	: "Ключевое слово",
		"do"	: "Ключевое слово",
		"to"	: "Ключевое слово",
		"array"	: "Ключевое слово",
		"of"	: "Ключевое слово",
		"integer": "Ключевое слово",
		"byte"	: "Ключевое слово",
		"char"	: "Ключевое слово",
		"word"	: "Ключевое слово",
		"real"	: "Ключевое слово",
		"var"	: "Ключевое слово",
		"["		: "Знак левой скобки",
		"]"		: "Знак правой скобки",
		":"		: "Знак двоеточия",
		".."	: "Знак промежутка",



	};

	var count = 1;


	var analize = function(str, result) {

		var lecs = str.replace(";", "").split(" ");

		for(var i = 0; i < lecs.length; i++) {
			
			if(KEYS.hasOwnProperty( lecs[i]) ) {
				var lecsema = lecs[i];
				result.push({
					"Тип лексемы" :  	KEYS[lecsema],
					"Лексема" 	  :		lecs[i],
					"Значение"	  : 	"Y" + count++,
				});
			}else if(lecs[i].indexOf(":") + 1) {

				if(lecs[i].indexOf("[") + 1 && lecs[i].indexOf("]") + 1  ) {

					var tmp = lecs[i].split(":").map(function(el) {
						return el.replace("]", "").split("[").map(function(e) {
							return e.split("..");
						});
					});

					// имя массива
					result.push( {
						"Тип лексемы" : 	"Идентификатор",
						"Лексема"	  :  	tmp[0][0][0],
						"Значение"	  : 	tmp[0][0][0] + " : array",
					});
					// // двоеточие
					result.push({
						"Тип лексемы" : 	KEYS[":"],
						"Лексема"	  :  	":",
						"Значение"	  : 	"Y" + count++,
					});
					// //array
					result.push({
						"Тип лексемы" : 	KEYS["array"],
						"Лексема"	  :  	"array",
						"Значение"	  : 	"Y" + count++,
					});
					result.push({
						"Тип лексемы" : 	KEYS["["],
						"Лексема"	  :  	"[",
						"Значение"	  : 	"Y" + count++,
					});
					// // from X (array size)
					result.push({
						"Тип лексемы" : 	"Константное значение",
						"Лексема"	  :  	tmp[1][1][0],
						"Значение"	  : 	tmp[1][1][0],
					});
					result.push({
						"Тип лексемы" : 	KEYS[".."],
						"Лексема"	  :  	"..",
						"Значение"	  : 	"Y" + count++,
					})
					// // to X (array size)
					result.push({
						"Тип лексемы" : 	"Константное значение",
						"Лексема"	  :  	tmp[1][1][1],
						"Значение"	  : 	tmp[1][1][1],
					});
					result.push({
						"Тип лексемы" : 	KEYS["]"],
						"Лексема"	  :  	"]",
						"Значение"	  : 	"Y" + count++,
					})

				}

			//console.log(tmp);

			}
		}

	}

	var show = function(obj) {
		console.log("  Лексема 	|  Тип лексемы 			|  Значение");
		console.log(' ===========================================================');
		for(var o in obj) {
			console.log(" ", obj[o]["Лексема"]," 		| ", obj[o]["Тип лексемы"]," 		| ", obj[o]["Значение"]);
		}
	}



	var main = function(options) {
		
		options = options.split('\n').map(function(el) {
			return el.trim();
		});

		var result = [];

		for(var i = 0; i < options.length; i++) {
			analize(options[i] , result) ;
		}
		
		// show(result);

	 	console.log(result);
	}



}());