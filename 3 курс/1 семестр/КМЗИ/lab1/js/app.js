/////////////////////////////////////////////////////////

$(function(){
	
	// значения по умолчанию
	$('#input_text_diff_replace').val("BLABLA");
	$('#input_key_diff_replace').val('SIX');
	$('#input_key_hill').val("[[ 6, 24,  1],[13, 16, 10],[20, 17,  15]]");

	/**
	* onclick events for buttons
	*/
	$('#crypt_diff_replace').click(function(){

		var input 	= $('#input_text_diff_replace').val().toUpperCase().replace(/\s/g, ""),
			key   	= $('#input_key_diff_replace').val().toUpperCase().replace(/\s/g, ""),
			result 	= $('#result_diff_replace');

		if(!input) return;

		var diffReplace = new DifficultReplace(input, key);	
		var cryptText = diffReplace.crypt();

		result .val(cryptText);
	});

	$('#encrypt_diff_replace').click(function(){

		var	key   	= $('#input_key_diff_replace').val().toUpperCase(),
			input 	= $('#input_text_diff_replace'),
			result 	= $('#result_diff_replace');

		input.val(result.val().toUpperCase());

		var diffReplace = new DifficultReplace;	
		var encryptText = diffReplace.encrypt(input.val().toUpperCase() , key);

		result.val(encryptText);
	});

	$('#copy_to_next_diff_replace').click(function(){

		var result 	= $('#result_diff_replace').val().toUpperCase(),
			next 	= $('#input_text_hill');

		next.val(result);
	})

	$('#crypt_hill').click(function(){
		var	input 	= $('#input_text_hill'),
			result 	= $('#result_hill');

		if(!input.val()) return;

		var hill = new CryptSystemHill(input.val().toUpperCase());

		var cryptText = hill.crypt();
		result.val(cryptText);

	})

	$('#encrypt_hill').click(function(){
		var	input 	= $('#input_text_hill'),
			result 	= $('#result_hill');

		input.val(result.val().toUpperCase());

		var hill = new CryptSystemHill(input.val());

		var encryptText = hill.encrypt(input.val());
		result.val(encryptText);

	})

	$('#copy_to_next_hill').click(function(){

		var result 	= $('#result_hill').val().toUpperCase(),
			next 	= $('#input_text_lzw');

		next.val(result);
	})

	$('#crypt_lzw').click(function(){
		var	input 	= $('#input_text_lzw'),
			result 	= $('#result_lzw');

		if(!input.val()) return;

		var lzw = new Lzw;

		var compText = lzw.compress(input.val());
		result.val(compText);

	})

	$('#encrypt_lzw').click(function(){
		var	input 	= $('#input_text_lzw'),
			result 	= $('#result_lzw');

		input.val(result.val());

		var lzw = new Lzw;

		var decompText = lzw.decompress(input.val());
		result.val(decompText);
	})

	/////////////////////////////////////////////////////////////////////////
	/*
	 Пример работы приложения только в консоли без интерфейса
	 */
	 
	// на текст накладываются в виде одноязычия и только заглавных букв(необходимо для корректной работы) + длина кратна 3
	var text = "Введите свой текст сюда";
	var key  = "Ключик";

	var cryptText = "";
	var temp = text;

	var diffReplace = new DifficultReplace(text.toUpperCase().replace(/\s/g, ""), key.toUpperCase());	
	cryptText = diffReplace.crypt();
	console.log("Метод сложной замены\nИсходный текст: " + temp + "\nЗашифрованный: " + cryptText);

	var hill = new CryptSystemHill(cryptText);
	temp = cryptText;
	cryptText = hill.crypt();
	console.log("Криптосистема Хилла\nИсходный текст: " + temp + "\nЗашифрованный: " + cryptText);
	//console.log("encryptText HILLA = " + hill.encrypt(cryptText));

	var lzw = new Lzw(cryptText);
	temp = cryptText;
	cryptText = lzw.compress();
	console.log("Метод сжатия LZW\nИсходный текст: " + temp + "\nЗашифрованный: " + cryptText);

	console.log("Проверим целостность (обратные операции)");

	if(temp != lzw.decompress(cryptText)){
		throw new Error("Ошибка в алгоритме разжатия LZW!");
	}
	temp = lzw.decompress(cryptText);

	console.log("Метод разжатия LZW\nИсходный текст: " +  cryptText + "\nРасшифрованный: " + temp);

	cryptText = temp;
	temp = hill.encrypt(cryptText)

	console.log("Метод расшифровки Хилла\nИсходный текст: " +  cryptText + "\nРасшифрованный: " + temp);

	cryptText = temp;
	temp = diffReplace.encrypt(cryptText);

	console.log("Метод расшифровки Сложной замены\nИсходный текст: " +  cryptText + "\nРасшифрованный: " + temp);

}); // END 



/*
	Input:
		ЗАЩИТАИНФОРМАЦИИ
		МОРЕ

		  | А Б В Г Д Е Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я
		-------------------------------------------------------------------
		М | М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я А Б В Г Д Е Ж З И Й К Л
		О | О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я А Б В Г Д Е Ж З И Й К Л М Н
		Р | Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я А Б В Г Д Е Ж З И Й К Л М Н О П
		Е | Е Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я А Б В Г Д

	Output:
		УОЙНЮОШТАЬАСМДШН
*/

/**
* Конструктор класса DifficultReplace 
* Реализует метод сложной замены для строки text заданным ключом key.
* При этом на входной текст накладывается ограничения в виде алфавита символов,
* в данном случае это кириллица или латиница, без каких-либо дополнительных символов(пробел, запятых и т.д.)
* Примечание: Так как даже в Unicode буква Ё находится не в основной последовательности, поэтому в нашем алфавите всего 32 буквы.
*/
function DifficultReplace(text, key){
	this.text = text || "ПРОСТОТЕКСТ";
	this.key  = key  || "КЛЮЧ";
}

/**
* Возвращаем зашифрованную строку text ключом key
*/
DifficultReplace.prototype.crypt = function(text, key){
	key  =  key  || this.key;
	text = (text || this.text).toUpperCase();

	if(text.length < key.length){
		console.log("Текст для зашифровывания должен быть длиннее чем ключ!\nПоэтому мы укоротим ключ.\nkey_old = " + key);
		key = this.key = key.slice(0, text.length);
		console.log("key = " + key);
	}

	var alphabet_size = text[0].charCodeAt(0) <= 'Z'.charCodeAt(0) ?  26 : 32;
	var first_letter = alphabet_size == 26 ? 'ABC'.charCodeAt(0) : "АБВ".charCodeAt(0);
	var last_letter  = alphabet_size == 26 ? "XWZ".charCodeAt(2) : "ЭЮЯ".charCodeAt(2);

	var out = '';
	for(var i=0, j=0; i < text.length; i++, j++){

		if(j == key.length) {
			j = 0;
		}

		chCode = text[i].charCodeAt(0) - first_letter + key[j].charCodeAt(0) ;

		if(chCode > last_letter ){
			chCode -= alphabet_size;
		}else if(chCode < first_letter){
			chCode += alphabet_size;
		}
		
		out += String.fromCharCode( chCode );
	}
	return out;
}

/**
* Возвращаем расшифрованную строку text ключом key
*/
DifficultReplace.prototype.encrypt = function(text, key){
	text = (text || this.text).toUpperCase();
	key  =   key || this.key;

	var out = '';
	for(var i=0, j=0; i < text.length; i++, j++){

		if(j == key.length) {
			j = 0;
		}

		var alphabet_size = text[0].charCodeAt(0) <= 'Z'.charCodeAt(0) ?  26 : 32;
		var first_letter = alphabet_size == 26 ? 'ABC'.charCodeAt(0) : "АБВ".charCodeAt(0);
	
		chCode = text[i].charCodeAt(0) - key[j].charCodeAt(0);
		if(chCode > alphabet_size ){
			chCode -= alphabet_size;
		}else if(chCode < 0){
			chCode += alphabet_size;
		}

		out += String.fromCharCode( first_letter + chCode); 
	}
	return out;
}

/////////////////////////////////////////////////////////////////////////////////

/**
* Конструктор класса CryptSystemHill 
* text - поле хранящее строку для зашифровывания
* key  - матрица 3х3 для зашифровывания исходного текста
* mod  - размер алфавита (26,32)
*/
function CryptSystemHill (text, key){
	this.text = (text || "Хилл лучший").toUpperCase();
	this.key  = key   || getDefaultKey();

	this.mod  = this.text[0].charCodeAt(0) <= 'Z'.charCodeAt(0) ?  26 : 32;

	function getDefaultKey(){ 	// ключ по умолчанию
		return [[ 6, 24,  1],
				[13, 16, 10],
				[20, 17,  15]];
	}
}

/**
* Метод crypt возвращает строку зашифрованную ключом key
*/
CryptSystemHill.prototype.crypt = function(text,key){
	text = (text || this.text).toUpperCase();
	key  =  key  || this.key;
	var mod = (text[0].charCodeAt(0) <= 'Z'.charCodeAt(0) ?  26 : 32) || this.mod;

	var cryptText = [];

	// массив должен быть кратен 3 иначе дополняем его какой-то буквой
	while(text.length % 3 != 0){
		text += 
			mod == 26 ? 'X' : 'Ж';
	}

	var temp = "";

	for(var i=0, j=0; j < text.length / 3; i += 3, j++){
		temp = text[i] + text[i+1] + text[i+2];
		cryptText.push( this.multiplyMatrix( this.makeArrayFromString(temp)));
	}
	return this.makeStringFromArray(cryptText);
}


/**
* Метод для перемножения матрицы MxN и Nx1 по модулю mod
* @param 	matrix 	Array	-	матрица размерностью Nx1 на которую умножают (3x1)
* @param 	key 	Array	-	матрица размерностью MxN (3x3)
* @return 	out 	Array	-	Массив перемноженных матриц по модулю mod
*/
CryptSystemHill.prototype.multiplyMatrix = function(matrix, key){
	key = key || this.key;

	var out = [];
	var temp = 0;
	for(var i=0; i < key.length; i++){
		for(var j=0; j < matrix.length; j++){
			temp += key[i][j] * matrix[j];
		}
		temp %= this.mod;
		out.push(temp);
		temp = 0;
	}
	return out;
}

/**
* Метод возвращает массив из цифр соответствующего алфавита, в зависимости от mod
* @param 	text String	-  Строка текста в соответствующем алфавите
* @return 	out  Array 	- 	Массив чисел соответсвующие буквам алфавита 
*/ 
CryptSystemHill.prototype.makeArrayFromString = function(text){
	var out = []; // 
	for (var i = 0; i < text.length; i++) {
		// в зависимости от языка
		out.push (
			this.mod == 26 ? text[i].charCodeAt(0) - 'ABC'.charCodeAt(0) : text[i].charCodeAt(0) - 'АБВ'.charCodeAt(0)
		);
	};
	return out;
}

/**
* Метод возвращает Строку символов в зависимости от алфавита
* @param 	matrix 	Array 	- 	Массив из чисел 
* @return 	str 	String  -   Строка из символов соответсвующего алфавита
*/ 	
CryptSystemHill.prototype.makeStringFromArray = function(matrix){
	var str = '';
	for(var i=0; i<matrix.length; i++){
		for(var j=0; j<matrix[i].length; j++){
			matrix[i][j] += ( matrix[i][j] < 0 ? this.mod : 0);
			str += 
				this.mod == 26 ? String.fromCharCode('ABC'.charCodeAt(0) + matrix[i][j]) :  String.fromCharCode('АБВ'.charCodeAt(0) + matrix[i][j]);
		}
	}
	return str;
}

/**
* Метод производит расшифровку строки cryptText при этом генерирует для ключа key ключ расшифровки,
* если таков существует!
* @param 	cryptText 	String  - 	строка зашифрованного текста
* @param 	key 		Array 	- 	Массив числовой 3х3
* return Строку расшифрованного текста
*/
CryptSystemHill.prototype.encrypt = function(cryptText, key){
	key = key || this.key;

	var encryptText = [];
	var temp = '';	

	for(var i = 0, j = 0; j < cryptText.length/3 ; i+=3, j++){
		temp = cryptText[i] + cryptText[i+1] + cryptText[i+2];
		encryptText.push( this.multiplyMatrix( this.makeArrayFromString(temp) , this.makeEncryptKey(key)));
	}
	return this.makeStringFromArray(encryptText);
}


/**
* Метод производит новую матрицу являющуюся обратной key по модулю mod
* 
*
*/

CryptSystemHill.prototype.makeEncryptKey = function(key, mod){
	key = key || this.key;
	mod = mod || this.mod;

	// найдем определить матрицы
	var det  = getDeterminantSquareMatrix3x3(key, mod);
	// присоединенная матрица 
 	var connectedMatrix = makeCoonectedMatrix(key, mod);
	// транспонированная матрица
	var transMatrix = makeTranspanentMatrix(connectedMatrix);
	// обратная матрица по модулю mod
	var invertMatrix = makeInvertMatrix(transMatrix, det, mod);

	return invertMatrix;

	/**
	* Функция возвращает определитель квадратной матрицы размерностю 2х2
	* @param matrix  	-		Матрица 2х2
	* @return Int 		- 		Определитель матрицы
	*/ 
	function getDeterminantSquareMatrix2x2 (matrix, mod){
		return  ( matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] ) % mod;
	}

	/**
	* Функция возвращает определитель квадратной матрицы размерностю 3х3
	* @param matrix  	-		Матрица 3х3
	* @return Int 		- 		Определитель матрицы
	*/ 
	function getDeterminantSquareMatrix3x3 (matrix, mod){
		return  ((
				matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) - 
				matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
				matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])
				) % mod + mod ) % mod;
	}

	/**
	* Функция возвращает присоединенную матрицу размерностью 3х3
	* @param matrix  - 	Матрица 3 x 3 (K)
	* @return 		 - 	Присоединенную матрицу 3х3 (К*)	
	*/
	function makeCoonectedMatrix (matrix, mod){
		return  [
				 [
				  getDeterminantSquareMatrix2x2([ [ matrix[1][1], matrix[1][2] ], [ matrix[2][1], matrix[2][2] ] ], mod),
				  getDeterminantSquareMatrix2x2([ [ matrix[1][0], matrix[1][2] ], [ matrix[2][0], matrix[2][2] ] ], mod),
				  getDeterminantSquareMatrix2x2([ [ matrix[1][0], matrix[1][1] ], [ matrix[2][0], matrix[2][1] ] ], mod)
				 ],
				 [
				  getDeterminantSquareMatrix2x2([ [ matrix[0][1], matrix[0][2] ], [ matrix[2][1], matrix[2][2] ] ], mod),
				  getDeterminantSquareMatrix2x2([ [ matrix[0][0], matrix[0][2] ], [ matrix[2][0], matrix[2][2] ] ], mod),
				  getDeterminantSquareMatrix2x2([ [ matrix[0][0], matrix[0][1] ], [ matrix[2][0], matrix[2][1] ] ], mod)
				 ],
				 [
				  getDeterminantSquareMatrix2x2([ [ matrix[0][1], matrix[0][2] ], [ matrix[1][1], matrix[1][2] ] ], mod),
				  getDeterminantSquareMatrix2x2([ [ matrix[0][0], matrix[0][2] ], [ matrix[1][0], matrix[1][2] ] ], mod),
				  getDeterminantSquareMatrix2x2([ [ matrix[0][0], matrix[0][1] ], [ matrix[1][0], matrix[1][1] ] ], mod)
				 ]
				];
	}

	/**
	* Функция возвращает транспонированную матрицу размерностью 3х3 
	* @param matrix 	-		присоединенная матрица (К*) 
	* @return array		-		массив 3х3 (K^T)
	*/
	function makeTranspanentMatrix(matrix){
		return 	[
				 [   matrix[0][0], - matrix[1][0],   matrix[2][0]
				 ],
				 [ - matrix[0][1],   matrix[1][1], - matrix[2][1]
				 ],
				 [   matrix[0][2], - matrix[1][2],   matrix[2][2]
				 ]
				];
	}

	/**
	* @param 	matrix 	Array 	-	транспанированная матрица (K^T)
	* @param 	det 	Int 	- 	детерминант матрицы (|K|)
	* @return 	out 	Array 	- 	инверсная матрица K^(-1) = K^T / |K| 
	*/
	function makeInvertMatrix(matrix, det, mod){

		var di = 0;
		for(var i = 0; i<mod; i++){
			if(det * i % mod == 1) {
				di = i;
			}
		}
		if(di == 0 ){
			throw new Error("Не возможно подобрать обратную матрицу. Попробуйте другой ключ!");
		}

		for(var i = 0; i<matrix.length; i++){
			for(var j=0; j<matrix[i].length; j++){
				matrix[i][j] *= di;
				matrix[i][j] %= mod;
			}
		}
		return matrix;
	}


} // END makeEncryptKey

//////////////////////////////////////////////////////////

/** 
* Конструктор класса Lzw 
* text - текст для сжатия
* size - размер словаря
* dict - словарь ( ASCII + cirillic)
*/
function Lzw (text) {
	this.text = text || "Lzw не плохо сжимает, но большие последовательности";
	this.size = 0;
	this.dict = {};
}

/**
* Метод создает словарь 
* Словарь представляет собой объект с числовыми индексами и соответсвующие им уникальные строки
* Словарь первоначально состоит из 321 элемента, для примера:
* {	0: 'A',
*	1: 'B',
*	...
*	320: 'ю',
*	321: 'я' }
*/
Lzw.prototype.createDictionary = function(){
	var dict = {};
	for(var i = 0; i <= 256; i++){ // ASCII
		dict [this.size++] = String.fromCharCode(i);  
	}
	for(var i = 1040; i <= 1103; i++){ // кириллица
		dict [this.size++] = String.fromCharCode(i);
	}
	return dict;
}

/**
* Метод для сжатия входного текста text
* @param 	text 	String  	- 	Текст для сжатия
* return String из чисел соответсвующие индексам словаря 
*/
Lzw.prototype.compress = function(text){
	text = text || this.text; 

	if(!text){
		throw new Error("compress: Нечего сжимать!");
	}

	// возвращает индекс существующего значения value
	function getIndex(obj, value){
		for(val in obj){
			if(obj[val] == value){
				return val;
			}
		}
		throw new Error("Не содержит данный индекс в словаре - " + value);
	}

	// проверяем содержится ли данное значение value в obj 
	function isConsist(obj, value){
		for(val in obj){
			if(obj[val] == value){
				return true;
			}
		}
		return false;
	}
	
	// делаем словарь первоначальным
	this.size = 0;
	this.dict = this.createDictionary();

	var out = "",   // выходная строка
		s = "",		// temp variables
		c = "";		 

	for(var i = 0; i < text.length; i++){
		c = text[i];

		if(isConsist(this.dict, s + c)){ // если словарь содержит s + c 
			s += c;	// тогда наращиваем s
		}else{	// иначе выведем s и добавим s + c в словарь
			out += getIndex(this.dict, s) + " ";
			this.dict[++this.size] = s + c;
			s = c;
		}
	}

	out += getIndex(this.dict, s);

	return out;
}


/**
* Метод для разжатия текста text 
* @param 	text 	String 	-	строка индексов словаря
* return String  первоначальная строка до сжатия
*/
Lzw.prototype.decompress = function(text){
	if (!text){
		throw new Error("decompress: Нечего декомпрессировать!");
	}

	// делаем словарь первоначальным
	this.size = 0;
	this.dict = this.createDictionary();
	
	text = text.split(" ");

	var out = "";
		cur = text[0],
		prev = "",
		s = "";

	out += this.dict[cur];

	for(var i = 1; i < text.length; i++){
		prev = cur;
		cur = text[i];
		
		if(this.dict[cur]){
			s = this.dict[cur];
			out += s;
			this.dict[++this.size] = this.dict[prev] + s[0];
		}else{
			s = this.dict[prev] + this.dict[prev][0];
			out += s;
			this.dict[++this.size] = s;
		}
	}

	return out;
}

