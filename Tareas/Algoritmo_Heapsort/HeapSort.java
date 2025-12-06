public class HeapSort {

    // Método público para ordenar un arreglo usando HeapSort
    public static void heapSort(int[] arr) {
        int n = arr.length;

        // 1) Construir un max-heap
        buildMaxHeap(arr, n);

        // 2) Extraer el máximo y colocarlo al final
        for (int i = n - 1; i > 0; i--) {
            swap(arr, 0, i);      // mover la raíz al final
            heapify(arr, 0, i);   // restaurar la propiedad del heap
        }
    }

    // Construye un max-heap desde un arreglo desordenado
    private static void buildMaxHeap(int[] arr, int heapSize) {
        // El último nodo interno está en heapSize / 2 - 1
        for (int i = heapSize / 2 - 1; i >= 0; i--) {
            heapify(arr, i, heapSize);
        }
    }

    // Mantiene la propiedad de max-heap en el nodo i
    private static void heapify(int[] arr, int i, int heapSize) {
        int largest = i;
        int left = 2 * i + 1;   // hijo izquierdo
        int right = 2 * i + 2;  // hijo derecho

        // Verificar hijo izquierdo
        if (left < heapSize && arr[left] > arr[largest]) {
            largest = left;
        }

        // Verificar hijo derecho
        if (right < heapSize && arr[right] > arr[largest]) {
            largest = right;
        }

        // Si el mayor no era el nodo raíz, intercambiamos
        if (largest != i) {
            swap(arr, i, largest);
            heapify(arr, largest, heapSize);  // recursividad
        }
    }

    // Función auxiliar para intercambiar dos elementos
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
