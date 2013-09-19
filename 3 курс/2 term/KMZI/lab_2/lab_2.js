"use strict";

var LFSR = require('./lfsr');
var sha_256 = require('./sha_256');


var args = process.argv.slice(2);

var error_message = "\
Usage:\n\n\  $node lab_2 [ sha256 <hello_world> | geffe [repeat] | lcg [repeat] | qcg [repeat] ]\n\n\
-----------------------------------------------------------------\n\
Для вызова справки ключи -h или --help\n\n\
Ключ: sha256 вычислит хэш от строки, например от 'hello_world'\n\
Ключ: geffe - вернёт псевдорандомное число, согласно алгоритму Геффе\n\
Ключ: lcg - вернёт псевдорандомное число, согласно алгоритму линейного конгруэнтного генератора\n\
Ключ: qcg - вернёт псевдорандомное число, согласно алгоритму линейного квадратичного конгруэнтного генератора\n\
Без ключей: Вычислит хэш sha256 от псевдослучайного числа от генераторов qcg и geffe.\n\
\nДля генераторов geffe, lcg, qcg доступен многократный вызов ( генератор [количество] )\n\
-----------------------------------------------------------------\n\
Примеры:\n\n\
  $ node lab_2 sha256 abc\n\
  ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\n\
\n\
  $ node lab_2 geffe 3\n\
    246403\n\
    319910\n\
    81302\n\n\
  $ node lab_2 lcg\n\
    22155\n\n\
  $ node lab_2 qcg\n\
    18432\n";

if(args.length > 2 || 
   args.length >= 1 && (args[0] == "-h" || args[0] == "--help") ) {
	console.log(error_message);
	process.exit(0);
}

var geffeGenerator = {
	bitLength: 10,
    initialState: parseInt('1010101010', 2), // seed
    lfsr: new LFSR(this.bitLength, this.initialState),
    rand: function(){
    	var lfsr1 = this.lfsr.seq(10),
	    	lfsr2 = this.lfsr.seq(10),
	    	lfsr3 = this.lfsr.seq(10);
		return lfsr3 * lfsr1 ^ (1 ^ lfsr3) * lfsr2;
	}
};

var linearCongruentialGenerator = {
	next: 9883,
	rand: function(){
		this.next = (this.next * 1103515245 + 12345) % (Math.pow(2, 31) - 1);
		return Math.floor(this.next / 65536);
	}
};

var quadCongruentialGenerator = {
	next: 9883,
	rand:  function(){
		this.next = (this.next * this.next * 13445  +  9883 * this.next + 92147 ) % (Math.pow(2, 31) - 1);
		return Math.floor(this.next / 65536);
	}
};


if(args.length > 0 	  && 
  (args[0] == "geffe" ||
   args[0] == "lcg"   ||
   args[0] == "qcg" )) {

	var repeat = args.length == 2 ? args[1] : 1;

	switch(args[0]){

		case "geffe":

			for(var i = 0; i < repeat; i++){
				console.log(geffeGenerator.rand());
			}

			break; 
		case "lcg":

			for(var i = 0; i < repeat; i++){
				console.log(linearCongruentialGenerator.rand())
			}

			break; 
		case "qcg":

			for(var i = 0; i < repeat; i++){
				console.log(quadCongruentialGenerator.rand());
			}
			break; 
	}


} else if( args.length > 0 &&
		   args[0] == "sha256" ) {

	var key = args[1] || "";

	console.log(sha_256.hash(key));

} else if(args.length == 0) {
	// по умолчанию: создаю случайное число в qcg и geffe и вывожу их хэши sha256 

	var tmp = geffeGenerator.rand();
	console.log("SHA256: " + tmp);
	console.log(sha_256.hash(new String(tmp)));


	tmp = quadCongruentialGenerator.rand();
	console.log("SHA256: " + tmp);
	console.log(sha_256.hash(new String(tmp)));

}


