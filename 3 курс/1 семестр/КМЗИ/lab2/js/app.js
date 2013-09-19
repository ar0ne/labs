/**
Variant 2. 
  A       |   B     |   C       |         D   |
Скремблер |   OFB   | 3 байта   | Сдвиг влево |
**/

/**
Лабораторная работа «Блочные шифры»
       Задание:
  1.   Изучить блочные алгоритмы шифрования: алгоритм перестановки,
       алгоритм скремблеров, алгоритм замены по таблице, матричный метод
       преобразования и алгоритм Винжера.
  2.   Изучить режимы использования блочных шифров (ECB, CBC, CFB и
       OFB).
  3.   Изучить способы объединения блочных шифров (многократное
       шифрование, сеть Фейстела).
  4.   Реализовать систему в соответствии с вариантами, указанными в таблице
       2 и заданием:

Изучить принцип работы алгоритма, который указан в варианте
(Таблица 2, Поле А) на приведенном примере. Разработать собственный
алгоритм (или модифицировать пример), который реализует указанный
в варианте:
• режим использования блочного шифра (Таблица 2, Поле В);
• работает с указанной длиной блока (Таблица 2, Поле С);
• позволяет оценивать скорость шифрования/дешифрования.
озволяет оценивать скорость шифрования/дешифрования.

         Дополнительные требования:
  1.    Функции шифрования/дешифрования + вспомогательные функции,
        необходимые для осуществления процесса кодирования/декодирования,
        помещаются в отдельную библиотеку .
  2.    Пароль в зашифрованном виде записывается в закодированный файл.
        При попытке расшифровать его с другим паролем выводится сообщение
        об ошибке.
  3.    В процессе кодирования осуществляется подсчет контрольной суммы.
        При декодировании осуществляется проверка контрольной суммы. При
        несовпадении выдается сообщение об ошибке. Для четных вариантов
        контрольная сумма считается по открытому тексту, для нечетных
        вариантов по шифрованному тексту.
  4.    Должна иметься возможность отключения режима использования
        блочного шифра и работа программы в режиме простого ECB.
  5.    Паролем может быть ЛЮБАЯ последовательность символов (русских и
        английских, цифр, знаков препинания и т. д.).
  6.    Программа должна быть оформлена в виде удобной утилиты,
        позволяющей работать с любыми файлами.
  7.    Программа должна обеспечивать шифрование файлов произвольной
        длины.


8.   Текст программы оформляется согласно общепринятым правилам
     (удобочитаемо,     с описанием ВСЕХ функций, переменных и
     критических мест).
9. В процессе работы программа ОБЯЗАТЕЛЬНО выдает информацию
     о состоянии процесса кодирования/декодирования.
10. После завершения работы программы выдает информацию о скорости
     шифрования / дешифрования (символ /сек)
11. Интерфейс программы может быть произвольным, но удобным и
     понятным 
12. Среда разработки и язык программирования могут быть произвольными.
   Требования для сдачи лабораторной работы:
5. Демонстрация работы реализованной вами системы.
6. АВТОРСТВО.
7. Теория (ориентирование по алгоритму и теоретическим аспектам методов
   гаммирования и перестановок).
**/



var MYAPP = MYAPP || function() {};

MYAPP.Cipher = function(key, IV, sizeBlock){
  this.sizeBlock = sizeBlock || 3;
  this.key = key || "secret key";
  this.IV = IV || 0;
  this.alphabet = this.createAlphabet();
  return this;
}

/**
*  Encrypt mode Output Feedback
*
*  @param   {string}    message     открытый текст
*  @param   {string}    _IV         вектор инициализации
*  @param   {string}    _key        ключ
*
*  @return  {string}                зашифрованный текст
*/
MYAPP.Cipher.prototype.encryptOFB = function (message, _IV, _key){
    if (typeof message === "string"){
        message = this.toBytes(message);
    }

    var out  = [],
        _key = _key || this.key;

    if(_IV) {
        _key = _IV;
        this.IV = 0;
    }
    _key = this.Ek( this.toBytes( _key ) );

    // каждый подблок размером sizeBlock ключ проходит через Ek затем (+) c message
    for(var i = 0; i < message.length; i++){
        if( i % this.sizeBlock  === 0){
            _key = this.Ek( _key );
        }
        out[i] = message[i] ^ _key[i % _key.length - 1];
    }

    return this.toString(out);
}   

/**
*  Decrypt message 
*/
MYAPP.Cipher.prototype.decryptOFB = MYAPP.Cipher.prototype.encryptOFB;


/*
*  Encrypt ECB mode
*  @param           message
*  @return   
*/
MYAPP.Cipher.prototype.encryptECB = function (message) {
    if(typeof message === 'string'){
        message = this.toBytes(message);
    }else if(typeof message === "object"){ //UInt8Array
        var tmp_array = [];
        for(var i = 0; i<message.length; i++){
            tmp_array[i] = message[i];
        }
        message = tmp_array;
    }

    if (message.length / this.sizeBlock) {
        var len = message.length ;
        var kp = Math.floor(len / this.sizeBlock); //   кратность открытого текста размеру блока

        for(var i = 0; i < (kp + 1) * this.sizeBlock - len; i++) {
            message .push(0);
        }
    }

    var out = [];
    for(var i = 0; i < message.length ; i += this.sizeBlock){
        var tmp_sl = [];
        for(var j=0; j<this.sizeBlock; j++){
            tmp_sl[j] = message[i + j];
        }
        out.push(this.Ek(tmp_sl));
    }

    var tmp_out = [];
    for(var i = 0; i < out.length; i++){
        for(var j = 0; j < this.sizeBlock; j++){
            tmp_out.push(out[i][j]);
        }
    }

    return tmp_out;
}

/*
*  @param       {string|array}        message   
*  @return      {string}
*/
MYAPP.Cipher.prototype.decryptECB = function (message){
    if(typeof message === 'string'){
        message = this.toBytes(message);
    }

    var out = [];
    for(var i = 0; i < message.length ; i += this.sizeBlock){
        var tmp_sl = [];
        for(var j=0; j<this.sizeBlock; j++){
            tmp_sl[j] = message[i + j];
        }
        out.push(this.Dk(tmp_sl));
    }

    var tmp_out = [];
    for(var i = 0; i < out.length; i++){
        for(var j = 0; j < this.sizeBlock; j++){
            tmp_out.push(out[i][j]);
        }
    }

    return tmp_out;
}

/**
* Scrambler method
* Зацикливание входного блока block со сдвигов влево на n бит
* @param  block    {array integer}    (3 bytes)
* @param  n        {integer}          на сколько бит сдвигать
* return           {array of indexes}
*/
MYAPP.Cipher.prototype.Ek = function ( block, n){
    n = n || 3;

    var shiftedBlock = '';

    for (var i in block){
      // adding zero's : 101   =>  0000 0101
        for(var j = 0; j < 8 - block[i].toString(2).length; j++){
          shiftedBlock += '0';
        }
        shiftedBlock += block[i].toString(2);
    }
    // left shift on n bits 
    shiftedBlock = shiftedBlock.substr(n) + shiftedBlock.substr(0, n);
    //console.log(shiftedBlock);

    var out = [];
    for(var i = 0; i < shiftedBlock.length ; i += 8){
     out. push( parseInt( shiftedBlock.substr(i, 8), 2) );
    }

    return out;
}

/**
* Decrypt scrambler cipher
* @param block    {array of integer(indexes)}  (3 numbers)
* @param n        {integer}                     на сколько бит сдвигать
* return          {array of indexes}
*/
MYAPP.Cipher.prototype.Dk = function( block, n){
    n = n || 3;

    var message = '';
    for (var i in block){
        for(var j = 0; j < 8 - block[i].toString(2).length; j++){
            message += '0';
        }
        message += block[i].toString(2);
    }

    message = message.substr(-n) + message.substr(0, message.length - n);

    var out = [];
    for(var i = 0; i < message.length ; i += 8){
        out. push( parseInt( message.substr(i, 8), 2) );
    }

    return out;
}

/**
* Create Array of integer (from 0 to 256) of letter index from 'alphabet'
* @param text       {string}      
* return outArray   {array} 
*/
MYAPP.Cipher.prototype.toBytes = function (text){
    if(typeof text !== "string"){
        throw new Error("toBytes: неправильный тип аргумента - ");
    }
    text = text.split("");

    var outArray = [];
    for (var letter in text){
        if(!this.alphabet.hasOwnProperty( text[ letter ] )) 
            throw new Error("В алфавите нет данного символа! - " + letter);
        outArray.push ( this.alphabet[ text[letter]  ]);
    }

    return outArray;
}

/**
* Create String from array of alphabet indexes 
*/
MYAPP.Cipher.prototype.toString = function (arrayIndexes){
  var outString = "";

  // возвращает индекс существующего значения value
  function getIndex(obj, value){
      for(var val in obj){
          if(obj[val] == value){
              return val;
          }
      }
      throw new Error("Не содержит данный индекс в словаре - " + value);
  }

  for(var index in arrayIndexes){
      outString +=  getIndex( this.alphabet,  arrayIndexes[index]) ;
  }
  return outString;
}

/**
*  Create Object alphabet of letter english and from 193 russian,
*  in output you have object like this
*   alpabet = {
*       'z'  : 123,
*        ...
*       'ж' :  204,   
*   }
*/
MYAPP.Cipher.prototype.createAlphabet = function () {

    var alphabet = {};

    for(var i = 0; i < 192; i++){
        alphabet[String.fromCharCode(i)] = i;
    }
    for(var i=192, j = "АБВ".charCodeAt(0); i < 192 + 32*2 ; i++, j++ ){
        alphabet[String.fromCharCode(j)] = i;
    }
    return alphabet;
}

//////////////////////////////////////////////////////////////////////////
////////////       TESTS                    ///////////////////////////////
///////////////////////////////////////////////////////////////////////////

// Test's
MYAPP.Tests = function(){
    console.log('Запущены тесты:');
    for(var test in MYAPP.Tests){
        MYAPP.Tests[test]();
    }
}

MYAPP.Tests.testEk = function(){
    var myApp = new MYAPP.Cipher;

    if( JSON.stringify( [8, 16, 24]) !== JSON.stringify ( myApp.Ek( [1,2,3] , 3) ) ){
        throw new Error("Test Ek didn't accept!");
    }
    console.log('testEk....OK');
}

MYAPP.Tests.testDk = function(){
    var myApp = new MYAPP.Cipher;

    if( JSON.stringify( [1,2,3]) !== JSON.stringify ( myApp.Dk( [8,16,24] , 3) ) ){
        throw new Error("TestDk didn't accept!");
    }
    console.log('testDk....OK');
}

MYAPP.Tests.testEncryptECB = function(){
    var myApp = new MYAPP.Cipher;

    if( JSON.stringify( [67, 43, 99, 99, 121, 139, 145, 152, 1] ) !== JSON.stringify ( myApp.encryptECB("hello123") )) {
       throw new Error("1: testEncryptECB didn't accept!:1");
    }

    if( JSON.stringify(  "C+ccy" ) !== JSON.stringify ( myApp.toString( myApp.encryptECB( "hello123" )))) {
       throw new Error("2: testEncryptECB didn't accept!:2");
    }
    console.log('testEncryptECB....OK');
}


/* 
@TODO: остальные тесты
*/

var myTests = new MYAPP.Tests;      // тесты
    myApp   = new MYAPP.Cipher;     // главный объект

///////////////////////////////////////////////////////////////////////////////////
/////////////////           EVENTS          ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

/**
* Onchange event for input.
* Load image and create 2 output images: crypted and decrypted
*/

var openFile = function(event) {
    var input = event.target;

    var reader = new FileReader();

    reader.onload = function(){

        var arrayBuffer = reader.result,
            bytes = new Uint8Array(arrayBuffer),
            ofb_blob,
            ecb_blob,
            time,
            tmp;

        var image_base = document.getElementById('base_img'),
            image_crypted_ofb = document.getElementById('encrypted_img_ofb'),
            image_decrypted_ofb = document.getElementById('decrypted_img_ofb'),
            image_crypted_ecb = document.getElementById('encrypted_img_ecb'),
            image_decrypted_ecb = document.getElementById('decrypted_img_ecb');

        // оригинал
        image_base.src = 'data:image/png;base64,' + encode(bytes);

        // зашифрованная картинка OFB mode
        time = new Date;
        ofb_blob = myApp.toBytes( myApp.encryptOFB(bytes) );
        tmp = new Date - time;
        console.log('Время encrypt OFB: ' + tmp + "mc");
        console.log('Скорость(символов/сек):' + bytes.length / (tmp / 1000));
        image_crypted_ofb.src = 'data:image/png;base64,'+ encode(ofb_blob);

        // расшифрованная картинка OFB mode
        time = new Date;
        ofb_blob = myApp.toBytes( myApp.decryptOFB(ofb_blob) );
        tmp = new Date - time;
        console.log('Время decrypt OFB: ' + tmp + "mc");
        console.log('Скорость(символов/сек): ' + bytes.length / (tmp / 1000));
        image_decrypted_ofb.src = 'data:image/png;base64,'+ encode(ofb_blob);

        // зашифрованная картинка ECB mode
        time = new Date;
        ecb_blob = myApp.encryptECB( bytes );
        tmp = new Date - time;
        console.log('Время encrypt ECB: ' + tmp + "mc");
        console.log('Скорость(символов/сек):' + bytes.length / (tmp / 1000));
        image_crypted_ecb.src = 'data:image/png;base64,'+ encode(ecb_blob);


        // расшифрованная картинка ECB mode
        time = new Date;
        ecb_blob = myApp.decryptECB(ecb_blob);
        tmp = new Date - time;
        console.log('Время decrypt ECB:' + tmp + "mc");
        console.log('Скорость(символов/сек):' + bytes.length / (tmp / 1000));
        image_decrypted_ecb.src = 'data:image/png;base64,'+ encode(ecb_blob);
    };

    reader.readAsArrayBuffer(input.files[0]);
}   

/**
*  Encode array of bytes to base64
* @param    {array}     input 
* @return   {string}   
*/
function encode (input) {
    var keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    var output = "";
    var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
    var i = 0;

    while (i < input.length) {
        chr1 = input[i++];
        chr2 = i < input.length ? input[i++] : Number.NaN; // Not sure if the index 
        chr3 = i < input.length ? input[i++] : Number.NaN; // checks are needed here

        enc1 = chr1 >> 2;
        enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
        enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
        enc4 = chr3 & 63;

        if (isNaN(chr2)) {
            enc3 = enc4 = 64;
        } else if (isNaN(chr3)) {
            enc4 = 64;
        }
        output += keyStr.charAt(enc1) + keyStr.charAt(enc2) +
                  keyStr.charAt(enc3) + keyStr.charAt(enc4);
    }
    return output;
}