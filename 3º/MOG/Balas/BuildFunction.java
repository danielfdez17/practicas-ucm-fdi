public class BuildFunction {
    private final int[] funcionObject;
    private final int[][] matrizRestricciones;
    private final TypeProblem type;
    private final int[] indicesCoeficientes;
    private final int sumaFunctionObject;
    public BuildFunction(final int[]funcion, final int[][] mRestricciones, TypeProblem t) {
        this.funcionObject = funcion;
        this.matrizRestricciones = mRestricciones;
        this.type = t;
        this.sumaFunctionObject = 0;
        this.indicesCoeficientes = null;
    }
    public BuildFunction(final int[]funcion, final int[][] mRestricciones, TypeProblem t,
                         final int[]index, final int sumFunctObj) {
        this.funcionObject = funcion;
        this.matrizRestricciones = mRestricciones;
        this.type = t;
        this.sumaFunctionObject = sumFunctObj;
        this.indicesCoeficientes = index;
    }
    public int[] getFObjetivo() { return this.funcionObject; }
    public int[][] getMRestricciones(){ return this.matrizRestricciones; }
    public TypeProblem getType(){ return this.type; }
    public int[] getIndexCoef(){ return this.indicesCoeficientes; }
    public int getSumFunction(){ return this.sumaFunctionObject; }
}
