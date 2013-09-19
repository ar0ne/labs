package itod_lab_1;

import java.util.Random;

class ManyLayerNeuroNetwork {
    private final double a;
    private final double b;
    private final double c;
    private final double d;
    private final int COUNT_INPUT;
    private final int COUNT_HIDDEN_LAYER;
    private final double Em;
    
    private double w_ki[][]; // between input  and hidden layers
    private double w_ij[];   // between hidden and output layers 
    
    private double T_i[];
    private double T_j;
    
    private double ethalons[];
    
    private double Y_i[];
    private double Y_j[];
    
   
    ManyLayerNeuroNetwork(double a, double b, double c, double d, 
                          int count_input, int count_hidden, double Em) {
        
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
        COUNT_INPUT = count_input;
        COUNT_HIDDEN_LAYER = count_hidden;
        this.Em = Em;
        Y_i = new double[COUNT_HIDDEN_LAYER];
        
        init();
    }
        
    public void learn(int size) {
        
        double Es = 1.0d;
        
        double alpha = 0.1d; // 0.1 or 0.2
        
        double gamma_j = 0.0d;
        double gamma_i[] = new double[COUNT_HIDDEN_LAYER];
        Y_j = new double[size - COUNT_INPUT];
        
        ethalons = new double[size];
        for(int i = 0; i < ethalons.length; i++) {
            ethalons[i] = getEthalon(0.1d * i);
        }
        
        int iter = 0;
        
        while( Es > Em ) {
            Es = 0.0d;
            
            for(int pos = 0; pos < size - COUNT_INPUT; pos++) {
                
                // прямое распространение ошибки
                // скрытый слой
                for( int i = 0; i < COUNT_HIDDEN_LAYER; i++ ) {
                    double S_i = 0;
                    for( int k = 0; k < COUNT_INPUT; k++ ) {
                        S_i += w_ki[k][i] * ethalons[i + pos] ;
                    }
                    S_i -= T_i[i];
                    Y_i[i] = getY_i(S_i);
                } 
                
                // выходной слой
                double S_j = 0.0d;
                for(int i = 0; i < COUNT_HIDDEN_LAYER; i++) {
                    S_j += w_ij[i] * Y_i[i];
                }
                S_j -= T_j;
                Y_j[pos] = getY_j(S_j);
                
                // фаза обратного распространения сигнала
                // вычисляем ошибки нейронных элементов выходного слоя
                gamma_j = Y_j[pos] - ethalons[COUNT_INPUT + pos];
                
                // вычисляем ошибки нейронных элементов скрытого слоя
                for(int i = 0; i < COUNT_HIDDEN_LAYER; i++) {
                    gamma_i[i] = gamma_j * 2 * (1 - Y_j[pos]) * Y_j[pos] * w_ij[i];
                }
                
                // модифицируем коэффициенты
                // для выходного слоя
                for(int i = 0; i < COUNT_HIDDEN_LAYER; i++) {
                    w_ij[i] = w_ij[i] - alpha * gamma_j * (1 - Math.pow(Y_j[pos], 2)) * Y_i[i];
                }
                T_j = T_j + alpha * gamma_j * (1 - Math.pow(Y_j[pos], 2));

                // для скрытого слоя
                for(int i = 0; i < COUNT_HIDDEN_LAYER; i++) {
                    for(int k = 0; k < COUNT_INPUT; k++) {
                        w_ki[k][i] = w_ki[k][i] - alpha * gamma_j * 2 * (1 - Y_j[pos]) * Y_j[pos] * ethalons[k + pos];
                    }
                    T_i[i] = T_i[i] + alpha * Y_j[pos] * 2 * (1 - Y_j[pos]) * Y_i[i];
                }
                
                // для выходного слоя
                for(int i = 0; i < COUNT_HIDDEN_LAYER; i++ ){
                    w_ij[i] = w_ij[i] - alpha * gamma_j * (1 - Math.pow(Y_j[pos], 2)) * Y_i[i];
                }
                T_j = T_j + alpha * gamma_j * (1 - Math.pow(Y_j[pos], 2));
                
                Es = Es + Math.pow(Y_j[pos] - ethalons[pos + COUNT_INPUT], 2);
            }
            Es *= 0.5;
            
            iter++;
        }

        System.out.println("Learning Many Layers Neural Network\nIterations: " + iter);
        System.out.println("#\tResult\t\t\t\tEthalon\t\t\t\tDelta");
        for(int i = 0; i < size - COUNT_INPUT; i++ ) {
            System.out.println((i+1) + "\t" + Y_j[i] + "\t\t" + ethalons[i + COUNT_INPUT] + "\t\t" + Math.abs(Y_j[i] - ethalons[i + COUNT_INPUT]));
        }
    }
    /**
     * Прогноз НС на size элемент
     * @param size 
     */
    public void forecast(int size) {
        
        int learn_size = ethalons.length;
        
        int offset = learn_size - COUNT_INPUT;
        
        ethalons = new double[ethalons.length + size];
        
        for(int i = 0; i < ethalons.length; i++) {
            ethalons[i] = getEthalon(0.1d * i);
            //System.out.println(ethalons[i]);
        }
        
        double X_k[] = new double[COUNT_INPUT];
        
        for(int i = 0; i < COUNT_INPUT; i++) {
            X_k[i] = ethalons[i + offset];
        }
               
        double result [] = new double [size - COUNT_INPUT];
        
        for(int pos = 0; pos < size - COUNT_INPUT; pos++) {
            
            for (int i = 0; i < COUNT_HIDDEN_LAYER; i++) {
                double S_i = 0;
                for (int k = 0; k < COUNT_INPUT; k++) {
                    S_i += w_ki[k][i] * X_k[i];
                }
                S_i -= T_i[i];
                Y_i[i] = getY_i(S_i);
            }

            // выходной слой
            double S_j = 0.0d;
            for (int i = 0; i < COUNT_HIDDEN_LAYER; i++) {
                S_j += w_ij[i] * Y_i[i];
            }
            S_j -= T_j;
            result[pos] = getY_j(S_j);
            
            // сдвигаем входные образы на 1 вправо
            for(int i = 0; i < COUNT_INPUT - 1; i++) {
                X_k[i] = X_k[i+1];
            }
            // и подставляем результат в качестве последнего элемента
            X_k[COUNT_INPUT - 1] = result[pos];
            
        }
              
        System.out.println("\nForecasting");
        System.out.println("#\tResult\t\t\t\tEthalon\t\t\t\tDelta");
        for(int i = 0; i < size - COUNT_INPUT; i++) {
            System.out.println((i+21) + "\t" + result[i] + "\t\t" + ethalons[i + COUNT_INPUT + offset ] + "\t\t" + Math.abs( ethalons[i + COUNT_INPUT + offset] - result[i]));
        }
        
    }  
    
    /**
     * init parametrs w and T
     */
    private void init() {
        Random rand = new Random();
        
        w_ki = new double[COUNT_INPUT][];
        w_ij = new double[COUNT_HIDDEN_LAYER];
        T_i  = new double[COUNT_HIDDEN_LAYER];
        
        for(int i = 0; i < COUNT_INPUT; i++) {
            w_ki[i] = new double[COUNT_HIDDEN_LAYER];
            for(int j = 0; j < COUNT_HIDDEN_LAYER; j++){
                w_ki[i][j] = rand.nextDouble();
            }
        }
        
        for(int i = 0; i < COUNT_HIDDEN_LAYER; i++){
            w_ij[i] = rand.nextDouble();
            T_i[i] = rand.nextDouble();
        }
        
        T_j = rand.nextDouble();
    }
        
    /**
     * Прямое распространение: выходное значение нейрона скрытого слоя i
     * @param S_i
     * @return Выходное значение i-го нейрона, биполярной сигмоидной функции
     */
    private double getY_i(double S_i) {
        return ( 2. / ( 1 + Math.exp(-S_i) ) - 1);
    }
    
    /**
     * Прямое распространение: выходное значение нейрона выходного слоя j
     * @param S_j
     * @return Выходное значение последнего слоя, гиперболический тангенс
     */
    private double getY_j(double S_j) {
        return  (( Math.exp(S_j) - Math.exp(-S_j)) / ( Math.exp(S_j) + Math.exp(-S_j)) );
    }
    
    /**
     * Функция F(x) заданная по варианту
     * @param x
     * @return значение y = f(x)
     */
    public double getEthalon(double x) {
        return (a * Math.cos(b * x) + c * Math.sin(d * x));
    }
    
}
