var TAPS = {
    2: [2, 1], // 3
    3: [3, 2], // 7
    4: [4, 3], // 15
    5: [5, 3], // 31
    6: [6, 5], // 63
    7: [7, 6], // 127
    8: [8, 6, 5, 4], // 255
    9: [9, 5], // 511
    10: [10, 7], // 1023
    11: [11, 9], // 2027
    12: [12, 11, 10, 4], // 4095
    13: [13, 12, 11, 8], // 8191
    14: [14, 13, 12, 2], // 16383
    15: [15, 14], // 32767
    16: [16, 14, 13, 11], // 65535
    17: [17, 14], // 131071
    18: [18, 11], // 262143
    19: [19, 18, 17, 14], // 524287
    20: [20, 17],
    21: [21, 19],
    22: [22, 21],
    23: [23, 18],
    24: [24, 23, 22, 17],
    25: [25, 22],
    26: [26, 6, 2, 1],
    27: [27, 5, 2, 1],
    28: [28, 25],
    29: [29, 27],
    30: [30, 6, 4, 1],
    31: [31, 28]
};

/**
 * @param {Number} [n] число бит в регистре
 * @param {Number} [seed] начальная позиция
 */
var LFSR = function (n, seed) {
    this.n = n || this.DEFAULT_LENGTH;
    this.taps = TAPS[this.n];
    seed || (seed = this._defaultSeed(this.n));

    var mask = parseInt(Array(this.n + 1).join('1'), 2);
    this.register = (seed & mask);
}

LFSR.prototype = {
    TAPS: TAPS,
    DEFAULT_LENGTH: 31,
    shift: function() {
        var tapsNum = this.taps.length,
            i,
            bit = this.register >> (this.n - this.taps[0]);
        for (i = 1; i < tapsNum; i++) {
            bit = bit ^ (this.register >> (this.n - this.taps[i]));
        }
        bit = bit & 1;
        this.register = (this.register >> 1) | (bit << (this.n - 1));
        return bit & 1;
    },
    /**
        Возвращает число-последовательность следующих сдвинутых n бит
     */
    seq: function(n) {
        var seq = 0;
        for (var i = 0; i < n; i++) {
            seq = (seq << 1) | this.shift();
        }
        return seq;
    },
    /**
     * Возвращает строку ввиде бинарной последовательности n бит
     */
    seqString: function(n) {
        var seq = '';
        for (var i = 0; i < n; i++) {
            seq += this.shift();
        }
        return seq;
    },
    /**
     * Возвращает число сдвигов до первоначального состояния(позиции)
     */
    maxSeqLen: function() {
        var initialState = this.register,
            counter = 0;
        do {
            this.shift();
            counter++;
        } while (initialState != this.register);
        return counter;
    },
    /**
     * Возвращает число-последовательность из 1 и 0
     */
    _defaultSeed: function(n) {
        if (!n) throw new Error('n is required');
        var lfsr = new LFSR(8, 92914);
        return lfsr.seq(n);
    }
};

module.exports = LFSR;
