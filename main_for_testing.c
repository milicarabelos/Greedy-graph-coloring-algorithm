#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "APIparte2.h"
#include "EstructuraGrafo23.h"

int main() {
    FILE* fp;
    // cambiar el primer parametro para probar otros casos, probar my_grafo_papi.txt no deberia andar
    fp = fopen("Grafos/pqsc.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }
    Grafo my_graph = ConstruirGrafo(fp);
    // Aca tengo que llamar a Construir Grafo mandandole el fp

    u32 n = NumeroDeVertices(my_graph);
    u32* Orden = calloc(n, sizeof(u32));
    u32* Color = calloc(n, sizeof(u32));

    printf("antes de greedy\n");
    // OrdenAleatorio(n, Orden);
    OrdenWelshPowell(n, Orden, my_graph);
    // OrdenNaturalReverse(n, Orden);
    // OrdenNatural(n, Orden);
    u32 color_greedy = Greedy(my_graph, Orden, Color);
    u32 minimo_coloreo = color_greedy;
    printf("coloreo inicial con %d colores\n", color_greedy);

    for (u32 i = 0; i < 500; i++) {
        char result = OrdenImparPar(n, Orden, Color);

        if (result == 1) {
            printf("error en OrdenImparPar\n");
            break;
        } else {
            color_greedy = Greedy(my_graph, Orden, Color);

            if (minimo_coloreo > color_greedy) {
                minimo_coloreo = color_greedy;
            }

            // printf("coloreo numero %d con %d colores\n", i + 1, color_greedy);
        }
    }

    printf("minimo coloreo ImparPar: %d\n", minimo_coloreo);

    for (u32 i = 0; i < 1; i++) {
        char result = OrdenJedi(my_graph, Orden, Color);

        if (result == 1) {
            printf("error en OrdenImparPar\n");
            break;
        } else {
            color_greedy = Greedy(my_graph, Orden, Color);

            if (minimo_coloreo > color_greedy) {
                minimo_coloreo = color_greedy;
            }

            // printf("coloreo numero %d con %d colores\n", i + 1, color_greedy);
        }
    }

    printf("minimo coloreo Jedi: %d\n", minimo_coloreo);

    free(Orden);
    free(Color);
    Orden = NULL;
    Color = NULL;

    DestruirGrafo(my_graph);
    fclose(fp);

    return 0;
}
