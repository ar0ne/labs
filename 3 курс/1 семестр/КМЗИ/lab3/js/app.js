/**
variant 9
**/

(function () {

    var LinearCongruentialGenerator = function (options) {

        var that = {};

        options.a = options.a || 5;
        options.c = options.c || 3;
        options.N = options.N || Math.pow(2,31);
        options.x_last = options.x_last || 1;

        that.getA = function () {
            return options.a;
        }
        that.setA = function (a) {
            if (a) {
                options.a = a;
            }
        }

        that.getC = function () {
            return options.c;
        }
        that.setC = function (c) {
            if (c) {
                options.c = c;
            }
        }

        that.getLastX = function () {
            return options.x_last;
        }
        that.setLastX = function (x_last) {
            if (x_last) {
                options.x_last = x_last;
            }
        }

        that.getN = function () {
            return options.N;
        }
        that.setN = function (N) {
            if (N) {
                options.N = N;
            }
        }

        that.generate = function () {
            var a = that.getA(),
                c = that.getC(),
                x_last = that.getLastX(),
                N = that.getN();

            that.setLastX (( a * x_last + c ) % N) ;    
            return parseFloat( '0.' + that.getLastX());      
        }

        return that;
    }


    var LaggedGibonacciGenerator = function (options) {

        var that = {};

        that.getA = function () {
            return options.a;
        }
        that.setA = function (a) {
            if (a) {
                options.a = a;
            }
        }

        options.a = options.a || 4;
        options.b = options.b || 1;
        options.k = options.k || (function () { 
            var out = [];
            for (var i=0; i < that.getA(); i++) {
                out.push( Math.random() );
            }
            return out;
        }())
     
       
        that.getB = function () {
            return options.b;
        }
        that.setB = function (b) {
            if (b) {
                options.b = b;
            }
        }

        that.getK = function () {
            return options.k;
        }
        that.setk = function (GPN) {
            for (var i = 0; i < that.getA(); i++ ) {
                that.addToK ( GPN() );
            }
        }

        that.addToK = function (element) {
            if (element) {
                options.k.push(element);
            }
        }

        that.generate = function () {
            var k = that.getK(),
                a = that.getA(),
                b = that.getB(),
                i = that.getK().length;

                if (k[i-a] && k[i-b]) {

                    if (k[i-a] > k[i-b]) {
                        that.addToK(k[i-a] - k[i-b]);
                        return k[i-a] - k[i-b];
                    } else {
                        that.addToK(k[i-a] - k[i-b] + 1);
                        return k[i-a] - k[i-b] + 1;
                    }

                } else {
                    throw new Error('Выход за пределы массива K[]!');
                }

            return false;            
        }

        /**
        *   T=(2^max{a,b}−1)⋅2^L, 
        *   где L - число битов в мантиссе вещественного числа
        */
        that.period = function () {
            console.log('Период зацикливания ГСЧ: ' + ( Math.pow( 2, Math.max( that.getA() ,that.getB() ) ) - 1 ) * Math.pow( 2, 16 ) );
        }
    
        return that;
    }


    // magic numbers
    var a = 55, 
        b = 24,
        gen = LaggedGibonacciGenerator({

            a:  a,
            b:  b,

            k:  (function () {

                    var k_array_of_linear_congr_gen = [],
                        gen_linear_congr = LinearCongruentialGenerator({
                            // options a,c,N and x_0 for linear generator
                        }),
                        i;

                    for (i=0; i < a; i++) {
                        k_array_of_linear_congr_gen.push(gen_linear_congr.generate());
                    }

                    return k_array_of_linear_congr_gen;
                }())
    })

    gen.period();

/////////////////////////////////////////////////////////////////
/////////       Гистограмма относительных частот        /////////
///////////////////////////////////////////////////////////////// 

    window.onload = function () {

        // var N = 70; // размер выборок
        // console.log('Размер выборки: ' + N);

        // var values = (function () {
        //     var out = [];
        //     var a = 0.89, b = 1.11;
        //     for(var i = 0; i < N; i++) {
        //         out.push (a + (b-a)* gen.generate());
        //        // document.write(out[i]+"<br />");
        //     }            
        //     return out;
        // }());

        var values = [11.013028656308077, 17.41740622236544, 8.2329308507487, 9.019622093964346, 9.144631381921613, 10.506426539401614, 17.561057126673802, 15.37226944001769, 11.135944784855411, 14.755178708498562, 8.67382636156196, 9.074874847894991, 9.417531426987804, 17.19389007793559, 13.368848280135662, 11.675910748866974, 9.613855943010194, 13.77256409272495, 12.297046916588668, 9.579111219428345, 13.35383137696807, 9.10537410993518, 8.38357913955563, 17.454023052245834, 8.989724962903036, 9.861563392343994, 11.020917516978619, 9.033631736761471, 15.610685439910965, 8.045015240313727, 15.040498557021527, 8.752272995614181, 8.853389005866493, 12.208207802048625, 14.521248019698906, 17.486125308211243, 8.599007997769693, 18.840532158988832, 13.071697929773013, 15.610386478484715, 16.807876979678625, 11.554408716993311, 9.652712153971725, 11.002478043658742, 16.289580273847022, 9.61698069686856, 8.436484985556772, 14.884143700120598, 10.016712768368016, 16.267173229148824, 11.21678142032914, 11.298736392765653, 8.719812097505597, 12.415955835980654, 9.839950546983388, 11.407332066320969, 16.84476050514494, 19.09863297903256, 11.012523550841964, 13.34332365911921, 8.855524960050374, 11.811167490774597, 18.339186121494382, 8.127839614310927, 16.04350782092024, 10.873318350029795, 14.428483227578264, 8.849430643153505, 13.087692996981556, 11.570472631574116, 10.479557433868486, 13.464643118722211, 11.766661261070611, 10.293421337168727, 10.41477155130615, 12.658134284110032, 11.884974540700174, 18.174762904094457, 16.86964995609211, 13.467863284719273, 8.31839384103295, 8.018085849895746, 8.727054626176589, 11.93085498474689, 12.795109933136285, 9.068029775149608, 8.65566952023729, 13.297194665245488, 11.292884366505517, 19.12536846426882, 18.410152025904374, 8.396547981894393, 14.990923306492892, 9.07449239870008, 9.036861792954157, 9.152849638623357, 12.459583137195027, 10.00739120639324, 18.941465761551953, 10.29419908965215, 18.541972353261524, 10.77279815063533, 10.264795220142819, 11.960184929993613, 16.382709486624073, 16.02220949096624, 14.485384104012617, 8.677932499690074, 11.004203630513386, 10.178600336735691, 8.597518404986134, 10.39197383251482, 10.265097436231017, 8.862466844824954, 13.275684881789259, 9.085398514265353, 11.931693987230394, 10.179932081357464, 9.502320496352723, 12.130115135563704, 10.068583173372785, 16.196167166723548, 9.188131203526773, 11.925750870493232, 8.984239146092182, 12.636534446546737, 10.160003890490815, 9.670403920396195, 12.20916197436351, 12.290256413864977, 9.177358310532536, 8.723717085481061, 9.368692398914071, 11.449100964851946, 11.626784732712833, 11.46914548559529, 9.093855135294328, 15.86388836845097, 10.39247323112716, 15.859115083088913, 11.321049376924627, 11.134404716150259, 9.042921426369027, 13.699170989605328, 8.449932058370692, 18.43806352754558, 8.614162836150557, 18.196357652476998, 9.10578964104517, 8.772715944596214, 13.154276299422074, 8.65429366029105, 10.05273026006838, 8.42869477605583, 14.395911094535688, 19.392635528947356, 13.277925181669511, 9.095531955720528, 12.134973614997676, 8.169684262544836, 11.423856692514928, 10.698911682927129, 8.29170341386679, 15.912281515008656, 16.175382605742517, 13.609285851856784, 11.180066646342683, 10.882157593578123, 14.965507308994264, 8.233972049371733, 15.28014488682746, 8.645309920107465, 15.397134566536563, 8.517554641961713, 9.21395582304978, 9.137524226100297, 10.533075839806553, 15.508694087615261, 9.646998462465548, 15.075878136798368, 8.826535062854502, 16.84502764989049, 10.153140653250174, 9.385598540706045, 14.432590251319494, 10.122799330104739, 16.59236087130118, 13.967735500932374, 12.412594169100801, 10.741407060920407, 11.191941861833756, 8.707633024559088, 10.961609043793787, 11.623847509226032, 14.590495818362967, 10.972329299165322, 9.110570529201292, 12.674304873708033, 9.39477614600073, 12.810035460397613, 12.999966893233129, 10.715145873632048, 9.350571818806047, 10.91960935207917, 8.196727218948594, 8.338816903777344, 9.723046930455695, 18.049627456852797, 10.56864338476228, 9.08934877533809, 8.446889253868964, 8.295648945543418, 15.236473555139684, 16.174310864253272, 9.063275026408975, 8.72569118082451, 11.837252807813005, 8.180296547866462, 9.09435421010728, 11.184274634879785, 8.233872216180869, 11.990028988315219, 8.891468322646556, 9.393495830156423, 8.479494926593308, 11.253171088251946, 10.455922163502676, 8.433765389762327, 13.750270817022784, 12.76707299956265, 12.301892773381097, 15.941568970526708, 17.431797174243528, 8.15561656165724, 11.991782451476759, 15.736666553809862, 13.257550060040394, 12.271728736086986, 14.45361847357947, 13.005398115270774, 10.399697093544166, 14.483102333467464, 8.67558223848774, 19.55751861696476, 10.271678143172368, 8.676287617258634, 8.129504045305163, 16.480057017913538, 9.184729362570792, 8.341225746261108, 9.429329657988646, 8.223681573829523, 8.124534352565947, 8.477531401692204, 11.327446471278442, 14.11730703529806, 8.559797930098675, 9.528988640519207, 8.882945912506926, 10.433073947354151, 12.08928935091878, 8.859088675025676, 19.00209998603591, 10.652595507689783, 9.030265178925193, 11.192702643383438, 8.884639632726271, 9.65398548630773, 15.553629127904633, 9.739663313949192, 9.389120459491533, 11.373088173061165, 8.408906051575586, 8.74335231085267, 13.558430958533906, 19.87023651913742, 11.050905582523523, 9.931772363686163, 11.754173432442517, 8.812895478273369, 9.714211915621807, 19.38386714549871, 10.270150351657058, 14.762318600855586, 11.484169976426498, 8.953037408324489, 11.431399711977745, 9.560906475716893, 8.150181386080222, 9.28025055392354, 10.630839351817913, 10.560727217489983, 10.43338929456877, 9.510137109949964, 14.54246473553732, 9.384123805199046, 12.993342477459938, 8.136861811759875, 13.84930344874189, 14.978412117607638]

        // A formatter for counts.
        var formatCount = d3.format(",.0f");

        var margin = {top: 10, right: 30, bottom: 30, left: 30},
            width = 960 - margin.left - margin.right,
            height = 500 - margin.top - margin.bottom;

        var x = d3.scale.linear()
            .domain([0, 1])
            .range([0, width]);

        // Generate a histogram using twenty uniformly-spaced bins.
        var data = d3.layout.histogram()
            .bins(x.ticks(20))
            (values);

        var y = d3.scale.linear()
            .domain([0, d3.max(data, function(d) { return d.y; })])
            .range([height, 0]);

        var xAxis = d3.svg.axis()
            .scale(x)
            .orient("bottom");

        var svg = d3.select("body").append("svg")
            .attr("width", width + margin.left + margin.right)
            .attr("height", height + margin.top + margin.bottom)
          .append("g")
            .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

        var bar = svg.selectAll(".bar")
            .data(data)
          .enter().append("g")
            .attr("class", "bar")
            .attr("transform", function(d) { return "translate(" + x(d.x) + "," + y(d.y) + ")"; });

        bar.append("rect")
            .attr("x", 1)
            .attr("width", x(data[0].dx) - 1)
            .attr("height", function(d) { return height - y(d.y); });

        bar.append("text")
            .attr("dy", ".75em")
            .attr("y", 6)
            .attr("x", x(data[0].dx) / 2)
            .attr("text-anchor", "middle")
            .text(function(d) { return formatCount(d.y); });

        svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + height + ")")
        .call(xAxis);

    }

}())