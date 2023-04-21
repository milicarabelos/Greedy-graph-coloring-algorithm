#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "APIparte2.h"
#include "EstructuraGrafo23.h"

int main() {
    FILE* fp;
    // cambiar el primer parametro para probar otros casos, probar my_grafo_papi.txt no deberia andar
<<<<<<< HEAD
    fp = fopen("Grafos/pdsc.txt", "r");
=======
    fp = fopen("R22_93_15.txt", "r");
>>>>>>> 44458ae ( fix my part)
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }
    Grafo my_graph = ConstruirGrafo(fp);
    // Aca tengo que llamar a Construir Grafo mandandole el fp

    u32 n = NumeroDeVertices(my_graph);
    u32* Orden = calloc(n, sizeof(u32));
    u32* Color = calloc(n, sizeof(u32));

    for (u32 i = 0; i < n; i++) {
        Orden[i] = my_graph->list_vertices[i].indice;

<<<<<<< HEAD
        assert(Orden[i] < n);
    }
=======
    printf("antes de greedy\n");
    OrdenNatural(n, Orden, my_graph);
>>>>>>> 44458ae ( fix my part)

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

    printf("minimo coloreo: %d\n", minimo_coloreo);

    free(Orden);
    free(Color);
    Orden = NULL;
    Color = NULL;

    DestruirGrafo(my_graph);
    fclose(fp);

    return 0;
}
