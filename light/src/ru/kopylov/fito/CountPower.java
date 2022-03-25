package ru.kopylov.fito;

public class CountPower {
    //drv, r1, r2, b, w, f1, f2, f2
//    private  static String str = "1,255,0,127,127,  1,  0,  0,";
    private  static String[] strs = {

            "1,255,0,  0,  0,  0,  0,  0,",
            "1,255,255,255,0,  0,  0,  0,",
            "1,0,0,0,255,  0,  0,  0,",
            "1,255,255,0,0,  0,  1,  0,",
            "1,255,255,  0, 0,  0,  0,  1"};
//    |10% - 25 |20% - 51 |30% - 76 |40% - 102 |50% - 127 |60% - 153
//    |70% - 178 |80% - 204 |90% - 229 |100% - 255 |


    private static int[] nominals ={0, 30, 30, 20, 40, 20, 40, 40};
    private static int calc255(int rate, int watts){
        double res = ((double) rate/255.)*watts;
        return (int) res;
    }
    private static int[] str2ints(String str){
        String[] sArr = str.split(",");
        int [] arr = new int[8];
        for(int i=0; i<8; i++){
            arr[i]=Integer.parseInt(sArr[i].trim());
        }
        return arr;
    }
    private static int calculate(String str ){

        int [] arr = str2ints(str);
        int red =  calc255(arr[1], nominals[1]) + calc255(arr[2], nominals[2]);
        int blue = calc255(arr[3], nominals[3]);
        int white = calc255(arr[4], nominals[4]);
        int full = arr[5]*nominals[5] +arr[6]*nominals[6] +arr[7]*nominals[7];
        int res = red+blue+white+full;
        System.out.println(str + " // "+String.format("r: %d; b: %d; w: %d; f: %d; total: %d", red, blue, white, full, res));


        return res;
    }

    public static void main(String[] args) {
        for (String str : strs) {
            calculate(str);
        }

    }

    public static void printPercents(){
        for(int i = 0; i<=100; i+=10){
            double res = (i/100.)*255;
            System.out.print(i+"% - "+(int)res+" |");
        }
    }
}
