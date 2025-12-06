public class Main {

    // Función auxiliar para imprimir arreglos
    private static void printArray(int[] arr) {
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if (i < arr.length - 1) System.out.print(", ");
        }
        System.out.println("]");
    }

    public static void main(String[] args) {

        int[] ejemplo1 = {4, 10, 3, 5, 1};
        int[] ejemplo2 = {1, 2, 98, 4, 5};
        int[] ejemplo3 = {5, 4, 3, 2, 1};
        int[] ejemplo4 = {2, 2, 2, 1, 3, 3, 0, 5, 5};

        System.out.println("===== Ejemplo 1 =====");
        printArray(ejemplo1);
        HeapSort.heapSort(ejemplo1);
        printArray(ejemplo1);

        System.out.println("\n===== Ejemplo 2 =====");
        printArray(ejemplo2);
        HeapSort.heapSort(ejemplo2);
        printArray(ejemplo2);

        System.out.println("\n===== Ejemplo 3 =====");
        printArray(ejemplo3);
        HeapSort.heapSort(ejemplo3);
        printArray(ejemplo3);

        System.out.println("\n===== Ejemplo 4 =====");
        printArray(ejemplo4);
        HeapSort.heapSort(ejemplo4);
        printArray(ejemplo4);
    }
}

