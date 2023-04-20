#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "APIparte2.h"
#include "EstructuraGrafo23.h"

int main() {
    FILE* fp;
    // cambiar el primer parametro para probar otros casos, probar my_grafo_papi.txt no deberia andar
    fp = fopen("Grafos/pQ5Q5.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }
    Grafo my_graph = ConstruirGrafo(fp);
    // Aca tengo que llamar a Construir Grafo mandandole el fp

    u32 n = NumeroDeVertices(my_graph);
    u32* Orden = calloc(n, sizeof(u32));
    u32* Color = calloc(n, sizeof(u32));

    // Orden = my_graph->list_vertices->indice;

    printf("antes de greedy\n");

    for (u32 i = 0; i < n; i++) {
        Orden[i] = Nombre(i, my_graph);

        // printf("Orden[%d] = %d\n", i, Orden[i]);
    }

    /*     for (u32 i = 0; i < NumeroDeLados(my_graph); i++)
        {
            printf("Lado %d: %d - %d\n", i, my_graph->list_lados[i].x, my_graph->list_lados[i].y);
        } */

    u32 colores = Greedy(my_graph, Orden, Color);

    printf("coloreo con %d colores\n", colores);

    DestruirGrafo(my_graph);
    fclose(fp);
    return 0;
}
