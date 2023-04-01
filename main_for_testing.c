#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "EstructuraGrafo23.h"

int main() {
    FILE* fp;
    // cambiar el primer parametro para probar otros casos, probar my_grafo_papi.txt no deberia andar
    fp = fopen("R10.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }
    Grafo my_graph = ConstruirGrafo(fp);
    // Aca tengo que llamar a Construir Grafo mandandole el fp
    DestruirGrafo(my_graph);
    fclose(fp);
    return 0;
}
