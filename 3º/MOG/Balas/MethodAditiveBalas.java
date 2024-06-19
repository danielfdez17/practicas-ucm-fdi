import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;




public class MethodAditiveBalas  {
    private final int V;
    private final int R;
    private final int[][] matrizTablero;
    private final int[][] matrizRestriccion;
    private final int[] functionObject;
    private final int[] indexCoef;
    private final int sumFunctionObject;
    private final List<Integer> actualValuesZ;
    private int x;
    public MethodAditiveBalas(final int[] functionObject,
                         final int[][] mRestriccion,
                         final int variables,
                         final int restricciones,
                         final int sumaFuncionObject,
                         final int[] indexCoeficientes) {
        this.functionObject = functionObject;
        this.V = variables;
        this.R = restricciones;
        this.matrizRestriccion = mRestriccion;  
        this.sumFunctionObject = sumaFuncionObject;
        this.indexCoef = indexCoeficientes;
        this.matrizTablero = new int[this.V][this.V];
        this.actualValuesZ = new ArrayList<Integer>();
    }
   
   
    public void run() {
        System.out.println("...METODO ADITIVO DE EGON BALAS...");
        int[] valoresVariables = new int[this.V];
        int infactibilidad = 0; //Se declara la variable donde se guardan las infactibilidades
        int index = 0;  //Variable donde se guardará el numero de iteraciones
        System.out.println("Iteracion ");
        this.printTable();
       
        for (int i = 0; i < this.V; i++) //La 1º solucion candidata seran todas cero
            valoresVariables[i] = 0;
       
        infactibilidad = this.calculateInfactibilite(valoresVariables); //Calculamos la factibilidad de la primera solucion
        if (infactibilidad == 0) { //Si la primera solucion es una solucion optima se detiene el proceso
             System.out.println("La solucion optima esta dada por:");
             System.out.println("Z = 0, X1,...,XN = 0");        
        }
        int[] arrayInfactibilidades = new int[this.V];
        //Si no es optima, declaramos un array donde se guardaran las infactibilidades de cada tablero
       
       
        ++index; //Subimos a uno la solucion optima
        while (infactibilidad != 0) {
            //Se limpia la lista donde se guarda la columna Z de las iteraciones
            this.actualValuesZ.clear();
            System.out.println("Iteracion: " + index);
            this.printTable();
            arrayInfactibilidades = this.calculateInfactibilites(valoresVariables);
            //Se busca si hay un cero en la infactibilidad registrada.
            int positionInfactiblite = searchInfactibilite(arrayInfactibilidades, 0);
            //Si no encontramos una infactibilidad de cero
            if (positionInfactiblite == -1) {
                //Se busca el menor valor de infactibilidad
                int minorInfactibilite = searchMinor(arrayInfactibilidades);
                //Se coloca en la posicion donde se encuentra dicho valor
                positionInfactiblite = searchInfactibilite(arrayInfactibilidades, minorInfactibilite);
                //Cambiamos el valor de las variables a 1 en esa posicion
                valoresVariables[positionInfactiblite] = 1;
            } else {
                //Notificamos que hay solucion optima
                System.out.println("");
                System.out.println("Se encontraron una o varias soluciones optimas en este tablero...");
                List<Integer> indexFactibilityCorrect = new ArrayList<Integer>(); //Es decir indices de factibilidad 0
                List<Integer> finalSolution = new ArrayList<Integer>();
                Map<Integer, Integer> indexKey = new HashMap<Integer, Integer>(); //Mapa para indices y sus valores
               
                //Se añaden las infactibilidades al array
                for (int i = 0; i < arrayInfactibilidades.length ; i++)
                    if(arrayInfactibilidades[i] == 0)
                        indexFactibilityCorrect.add(i);
               
                //Se realiza una busqueda de los valores finales que sean posibles candidatos
                for (int i = 0; i < indexFactibilityCorrect.size(); i++){
                    finalSolution.add(this.actualValuesZ.get(indexFactibilityCorrect.get(i)));
                    indexKey.put(finalSolution.get(i), indexFactibilityCorrect.get(i));
                }
               
                //Se ordena la lista en orden ascendente
                Collections.sort(finalSolution);
               
                //Se busca cual es la fila donde esta el valor solucion menor
                int positionFinal = indexKey.get(finalSolution.get(0));
                int[] solutionOne = new int[this.V];
               
                System.out.print("Valores Solucion: "); //Noficamos
                for (int i = 0; i < this.V; i ++){
                    System.out.print("X" + (i + 1) + "=" + matrizTablero[positionFinal][i] + ", ");
                    solutionOne[i] = matrizTablero[positionFinal][i];
                }
                System.out.println("Z = " + this.actualValuesZ.get(positionFinal));
                System.out.println("");
               
                //Si el problema no era de maximizacion, se realiza el siguiente proceso para mostrar la informacion
                if (this.sumFunctionObject != 0){
                    System.out.println("Valores solucion al problema original...");
                    System.out.println("Valores solucion: ");
                    System.out.print(" Z = " + ((actualValuesZ.get(positionFinal)+this.sumFunctionObject)*-1) + ", ");
                    for (int i = 0; i < this.V; i++){
                        byte next = (byte) (i + 1);
                        if (this.indexCoef[i] != 0)
                            System.out.print("X" + next + "=" + (1 - solutionOne[i] )+ " ,");
                        else
                            System.out.print("X" + next + "=" + (solutionOne[i]) + " ,");
                       
                    }
                    System.out.println("");                    
                }
                infactibilidad = arrayInfactibilidades[positionInfactiblite];
            }
            index++;
            System.out.println("");
        }
       
    }
   
   
    private int calculateInfactibilite(final int[] valoresVariables) {
        int[] valuesRestricction = new int[this.R]; //Valores que tomara las restricciones
        int infactibilidad = 0; //Inicializacion de infactibilidad de cero
        int z = 0; //Funcion objetivo de cero
        for(int i = 0; i < this.R; i++) //Array unidimensional de valores para el resultado
            for(int j = 0; j < this.V; j++)
                valuesRestricction[i] =
                        valuesRestricction[i] + (valoresVariables[j]* this.matrizRestriccion[i][j]);
           
        //Se le suma o resta (depende el caso) el valor que esta a la derecha del signo.
        for(int i = 0; i < this.R; i++)
            valuesRestricction[i] += (this.matrizRestriccion[i][this.V + 1] * (-1));
       
        //Calculamos infactibilidad
        for(int i = 0; i < this.R; i++)
            if (valuesRestricction[i] > 0)
                infactibilidad +=  valuesRestricction[i];
           
        //Calculamos el valor de Z con los valores de las variables
        for(int i = 0; i < this.V; i++)
            z = z + (valoresVariables[i] * this.functionObject[i]);
       
        //Se añaden los valores a la matriz del tablero
        for (int i = 0; i < this.V ; i++)
            matrizTablero[this.x][i] = valoresVariables[i];
       
        //Se imprimen los resultados
        for (int i = 0; i < this.V ; i++)
            System.out.printf("%-7s", valoresVariables[i]);
       
        for (int i = 0; i < this.R; i++)
            System.out.printf("%-7s",valuesRestricction[i] + "<=0");
       
        System.out.printf("%-7s", infactibilidad);
        System.out.printf("%9s", z);
        System.out.println("");
        this.actualValuesZ.add(z); //Añadimos a los valores de Z
        return infactibilidad;
    }
   
    private int[] calculateInfactibilites(final int[] arrayOfValues) {
        int[] createArrayInfactibility = new int[this.V];
        int[] valuesCopyAuxiliarity = new int [this.V];
       
        System.arraycopy(arrayOfValues, 0, valuesCopyAuxiliarity, 0, this.V);
        for (int i = 0; i < this.V; i++) {
            arrayOfValues[i] = 1;
            createArrayInfactibility[i] = this.calculateInfactibilite(arrayOfValues);
            this.x++;
            System.arraycopy(valuesCopyAuxiliarity, 0, arrayOfValues, 0, this.V);
        }
        this.x = 0;
        return createArrayInfactibility;
    }
   
    private int searchInfactibilite(final int[] arrayInfactibilite, final int minor) {
        int position = -1;
        for (int i = 0; i < arrayInfactibilite.length; i++) {
            if (arrayInfactibilite[i] == minor) {
                position = i;
                break;
            }
        }
        return position;
    }
   
    private int searchMinor(final int[]arrayInfactibilite) {
        int minor = arrayInfactibilite[0];
        for (int i = 0; i < arrayInfactibilite.length; i++) {
            if (minor > arrayInfactibilite[i]) {
                minor = arrayInfactibilite[i];
            }
        }
        return minor;
    }
   
    private void printTable() {
        for(int i = 0; i < this.V; i++){
            System.out.printf("%-7s","X" + (i + 1));
        }
       
        for(int i = 0; i < this.R; i++){
            System.out.printf("%-7s", "R" + (i + 1));
        }
        System.out.printf("%-7s", "Infact.");
        System.out.printf("%9s", "Z");
        System.out.println("");    
    }
       
}
