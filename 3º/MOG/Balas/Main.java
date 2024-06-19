import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.IntStream;


public class Main {


    public static void main(String[] args) throws InterruptedException {
       
        try(BufferedReader br = new BufferedReader(new FileReader("src/datos.txt"))) {
            String line = br.readLine();
            while (line != null && !line.trim().equalsIgnoreCase("")) {
                String[] parts = line.trim().split(" ");
                final TypeProblem type = TypeProblem.getType(parts[0]);
                final int V = Integer.parseInt(parts[1]);
                final int R = Integer.parseInt(parts[2]);
                List<Integer> listVariables = new ArrayList<Integer>(V);
                List<List<String>> matrizRestricciones = new ArrayList<List<String>>(R);
                String lineOfVariables = br.readLine();


                IntStream
                    .range(0, lineOfVariables.split(" ").length)
                    .forEach(i -> listVariables.add(i, Integer.parseInt(lineOfVariables.split(" ")[i])));
                for (int i = 0; i < R; i++) {
                    String lineOfRestriccition = br.readLine();
                    matrizRestricciones.add(i, Arrays.asList(lineOfRestriccition.split(" ")));
                }
                Main.problemAditiveBalas(type, V, R, listVariables, matrizRestricciones);
                line = br.readLine();
            }
        } catch (Exception e) {
            System.out.println("Fichero no encontrado");
            System.out.println(e.getMessage());
        }
       
       
    }
   
    private static void problemAditiveBalas(final TypeProblem t,
                                            final int V,
                                            final int R,
                                            final List<Integer> listVariables,
                                            final List<List<String>> matrizRestriccion) {
        System.out.println("*************PROBLEMA ADITIVO DE BALAS*************");
        final TypeProblem type = t;
        final int variablesDecision = V;
        final int restricciones = R;


        System.out.println("Seleccionado -> " + type.name());
        BuildFunction builder = Main.build(type, variablesDecision, restricciones, listVariables, matrizRestriccion);
        Main.printConsole(type,
                          variablesDecision,
                          restricciones,
                          builder.getFObjetivo(),
                          builder.getMRestricciones());
       
        BuildFunction buildAlgorithm = Main.buildAlgorithm(
                                            builder.getType(),
                                            variablesDecision,
                                            restricciones,
                                            builder.getFObjetivo(),
                                            builder.getMRestricciones());
        Main.printConsoleAlgorithm(buildAlgorithm.getType(),
                                    variablesDecision,
                                    restricciones,
                                    buildAlgorithm.getSumFunction(),
                                    buildAlgorithm.getFObjetivo(),
                                    buildAlgorithm.getMRestricciones());
        MethodAditiveBalas algorithmBalas = new MethodAditiveBalas(
                  buildAlgorithm.getFObjetivo(),
                  buildAlgorithm.getMRestricciones(),
                  variablesDecision,  
                  restricciones,
                  buildAlgorithm.getSumFunction(),
                  buildAlgorithm.getIndexCoef());
        algorithmBalas.run();
    }


    private static synchronized BuildFunction build(final TypeProblem type,
            final int V,
            final int R,
            final List<Integer> listVariables,
            final List<List<String>> matrizDynamic) {
       
        final int[] functionObject = new int[V];
        final int[][] matrixRestricction = new int[R][V + 2];
        Map<String, Byte> mapDesiguality = new HashMap<String, Byte>(2);
        mapDesiguality.put("<=", (byte) -1);
        mapDesiguality.put(">=", (byte) 1);
        for (int i = 0; i < V; i++)
            functionObject[i] = listVariables.get(i);
       
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < V; j++)
                matrixRestricction[i][j] = Integer.parseInt(matrizDynamic.get(i).get(j));
           
            matrixRestricction[i][V] = mapDesiguality.get(matrizDynamic.get(i).get(V));
            matrixRestricction[i][V + 1] = Integer.parseInt(matrizDynamic.get(i).get(V + 1));
        }
       
        return new BuildFunction(functionObject, matrixRestricction, type);
    }


    private static synchronized void printConsole(
            final TypeProblem type,
            final int variables,
            final int restricciones,
            final int[] functionObject,
            final int[][] matrixRestricction) {
        System.out.println("El problema es de la forma");
        System.out.print(type.name() + " Z = ");
        for (int i = 0; i < variables; i++) {
            if (functionObject[i] >= 0 && i > 0) {
                System.out.print("+");
            }
            System.out.print(functionObject[i] + "X" + (i + 1));
        }


        System.out.println("");
        System.out.println("Sujeto a: ");
        for (int i = 0; i < restricciones; i++) {
            for (int j = 0; j < variables + 2; j++) {
                if (j == variables) {
                    final int dataMatriz = matrixRestricction[i][j];
                    if (dataMatriz == -1)
                        System.out.print("<=" + " ");
                    else if (dataMatriz == 1)
                        System.out.print(">=" + " ");
                } else if (j == (variables + 1)) {
                    System.out.print(matrixRestricction[i][j]);
                } else {
                    if (matrixRestricction[i][j] >= 0 && j > 0) {
                        System.out.print("+");
                    }
                    System.out.print(matrixRestricction[i][j] + "X" + (j + 1) + " ");
                }
            }
            System.out.println(" ");
        }
        System.out.println(" ");
       
    }
   
    private static synchronized BuildFunction buildAlgorithm(
            final TypeProblem type,
            final int variables,
            final int restricciones,
            final int[] functionObject,
            final int[][] matrixRestricction) {
        TypeProblem typeActual = type;
        if (typeActual.name().equals(TypeProblem.MAXIMIZAR.name())) {
            System.out.println("");
            System.out.println("Se detectó un problema de Maximizacion...");
           
            System.out.print("Funcion Objetivo Original: ");
            for (int i = 0; i < variables; i++)
                System.out.print(functionObject[i] + ", ");
           
            System.out.println("");
            for (int i = 0; i < variables; i++)
                functionObject[i] *= -1;
           
            System.out.print("Nueva Funcion Objetivo: ");
            for (int i = 0; i < variables; i++)
                System.out.print(functionObject[i] + ", ");
           
            typeActual = TypeProblem.MINIMIZAR;
            System.out.println("");
        }
       
        //Comprobacion de Menor o Igual en las restricciones...
        System.out.println("");
        System.out.println("Comprobacion de las restricciones");
        for (int i = 0; i < restricciones; i++) {
            for (int j = 0; j < variables + 2; j++) {
                if (j == variables) {
                    final int data = matrixRestricction[i][j];
                    if (data == -1)
                        System.out.println("La restriccion es valida...");
                    else if (data == 1) {
                         System.out.println("La restriccion NO es valida...");
                         
                         System.out.print("Restriccion original: ");
                         for (int k = 0; k < matrixRestricction[i].length ; k++) {
                             System.out.print(matrixRestricction[i][k] + ", ");
                         }
                         System.out.println("");
                         System.out.print("Restriccion invertida: ");
                         for (int k = 0; k < matrixRestricction[i].length; k++) {
                             matrixRestricction[i][k] *= -1;
                             System.out.print(matrixRestricction[i][k] + ", ");
                         }
                         System.out.println("");
                    }
                }
            }
        }
       
        //Comprobacion de coeficientes en la F.O
        System.out.println("");
        System.out.println("Comprobacion de los coeficientes en la Funcion Objetivo");
        final int[] indexCoeficNew = new int[variables];
        int sumatoryFunctionObject = 0;
        int[] auxiliarityRestricctionNew = new int[restricciones];
        for (int i = 0; i < variables; i++) {
            indexCoeficNew[i] = 0;


            for (int j = 0; j < auxiliarityRestricctionNew.length; j++) {
                auxiliarityRestricctionNew[j] = 0;
            }


            if (functionObject[i] < 0) {
                System.out.println("Se ha detectado un coeficiente negativo en la funcion objetivo...");
                System.out.println("Coeficiente: " + functionObject[i] + "X" + (i + 1));


                System.out.println("Añadiendo a lista de indices no validos... Indice: " + i);
                indexCoeficNew[i] = 1;


                sumatoryFunctionObject = sumatoryFunctionObject + functionObject[i];
                System.out.println("Sumando a la lista de holgura de la F.O... Suma: " + sumatoryFunctionObject);


                System.out.println("Reemplazando coeficiente no validos...");
                functionObject[i] = functionObject[i] * -1;


                for (int j = 0; j < restricciones; j++) {
                    System.out.println("Ajustando... la restriccion " + j);
                    System.out.println("Sumando a la holgura de la restriccion");
                    auxiliarityRestricctionNew[j] = auxiliarityRestricctionNew[j] + matrixRestricction[j][i];
                    System.out.println("Suma de la restriccion " + j + " Acomulada: " + auxiliarityRestricctionNew[j]);
                    System.out.println("Invirtiendo los signos de la restriccion en la posicion " + (i + 1));
                    matrixRestricction[j][i] = matrixRestricction[j][i] * -1;
                }


                final byte variableNext = (byte) (variables + 1);
                for (int j = 0; j < restricciones; j++) {
                    System.out.println("Sumando/Restando la desigualdad " + j);
                    System.out.println("Valor ORIGINAL en la casilla restriccion:" + j + ", " + (variableNext)
                            + " :" + matrixRestricction[j][variableNext]);
                    matrixRestricction[j][variableNext] = matrixRestricction[j][variableNext] - auxiliarityRestricctionNew[j];
                }
                System.out.println("");
            }
        }
        return new BuildFunction(functionObject, matrixRestricction, typeActual,
                                 indexCoeficNew, sumatoryFunctionObject);
    }
   
    private static synchronized void printConsoleAlgorithm(
            final TypeProblem type,
            final int variables,
            final int restricciones,
            final int sumFunctionObject,
            final int[] functionObject,
            final int[][] matrixRestricction) {
         //Imprimiendo el problema final en consola
        final String SPACE_BLANK = " ";
        System.out.println("Imprimiendo el problema final...");
        System.out.print(type.name() + " Z = ");
        for (int i = 0; i < variables; i++) {
            if (functionObject[i] >= 0 && i > 0)
                System.out.print("+");
           
            System.out.print(functionObject[i] + "X" + (i + 1) + " ");
        }
        if (sumFunctionObject >= 0)
            System.out.println(" + " + sumFunctionObject);
        else
            System.out.println(sumFunctionObject);
       


        System.out.println("Sujeto a: ");
        for (int i = 0; i < restricciones; i++) {
            for (int j = 0; j < variables + 2; j++) {
                if (j == variables) {
                    final int data = matrixRestricction[i][j];
                    if (data == -1) System.out.print("<=" + " ");
                        else if (data == 1) System.out.print(">=" + " ");
                } else if (j == (variables + 1))
                    System.out.print(matrixRestricction[i][j]);
                 else {
                    if (matrixRestricction[i][j] >= 0 && j > 0)
                        System.out.print("+");
                    System.out.print(matrixRestricction[i][j] + "X" + (j + 1) + " ");
                }
            }
            System.out.println(SPACE_BLANK);
        }
        System.out.println(SPACE_BLANK);
    }
}
