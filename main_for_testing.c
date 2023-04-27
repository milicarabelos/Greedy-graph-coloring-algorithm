#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "APIparte2.h"
#include "EstructuraGrafo23.h"

void swap_arrays(u32** arr1, u32** arr2) {
    u32* temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}

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
    u32* Color_2 = calloc(n, sizeof(u32));
    u32 elegir = 0;
    u32 min_num_crom = n + 2;

    printf("antes de greedy\n");

    OrdenNatural(n, Orden);
    u32 num_crom_1 = Greedy(my_graph, Orden, Color);

    OrdenWelshPowell(n, Orden, my_graph);
    u32 num_crom_2 = Greedy(my_graph, Orden, Color);

    if (num_crom_1 < num_crom_2) {
        min_num_crom = num_crom_1;
        elegir = 1;
    } else {
        min_num_crom = num_crom_2;
        elegir = 2;
    }

    OrdenAleatorio(n, Orden);
    u32 num_crom_3 = Greedy(my_graph, Orden, Color);

    if (min_num_crom > num_crom_3) {
        min_num_crom = num_crom_3;
        elegir = 3;
    }

    OrdenNaturalReverse(n, Orden);
    u32 num_crom_4 = Greedy(my_graph, Orden, Color);

    if (min_num_crom > num_crom_4) {
        min_num_crom = num_crom_4;
        elegir = 4;
    }

    // esto lo hago para que el array de colores me quede de la mejor manera para volver a correr
    // greedy en los ordenes por colores
    switch (elegir) {
        case 1:
            OrdenNatural(n, Orden);
            printf("elegi natural\n");
            break;
        case 2:
            OrdenWelshPowell(n, Orden, my_graph);
            printf("elegi welsh\n");
            break;
        case 3:
            OrdenAleatorio(n, Orden);
            printf("elegi aleatorio\n");
            break;
        case 4:
            OrdenNaturalReverse(n, Orden);
            printf("elegi natural reverse\n");
            break;
        default:
            break;
    }

    printf("coloreo inicial con %d colores\n", min_num_crom);
    u32 color_greedy, color_greedy_2;

    for (u32 i = 0; i < 500; i++) {
        //// [1]
        char char_1 = OrdenImparPar(n, Orden, Color);
        color_greedy = Greedy(my_graph, Orden, Color);
        //// [2]
        char char_2 = OrdenJedi(n, Orden, Color_2);
        color_greedy_2 = Greedy(my_graph, Orden, Color_2);

        if (color_greedy < color_greedy_2) {
            if (min_num_crom > color_greedy) {
                min_num_crom = color_greedy;
            }
        } else {
            if (min_num_crom > color_greedy_2) {
                min_num_crom = color_greedy_2;
            }
        }

        if (i % 16 == 0) {
            swap_arrays(&Color, &Color_2);
        }

        if (char_1 == 1 || char_2 == 1) {
            printf("error en OrdenImparPar o OrdenJedi\n");
            break;
        }
    }

    printf("minimo coloreo despues de Jedy y ImparPar: %d\n", min_num_crom);

    //////////////////////////////////////////////////////////////////////////////////////
    /*     u32 color_greedy = 0;

        for (u32 i = 0; i < 1; i++) {
            char result = OrdenImparPar(n, Orden, Color);

            if (result == 1) {
                printf("error en OrdenImparPar\n");
                break;
            } else {
                color_greedy = Greedy(my_graph, Orden, Color);

                if (min_num_crom > color_greedy) {
                    min_num_crom = color_greedy;
                }
            }
        }

        printf("minimo coloreo ImparPar: %d\n", min_num_crom);

        for (u32 i = 0; i < 1; i++) {
            char result = OrdenJedi(my_graph, Orden, Color);

            if (result == 1) {
                printf("error en OrdenImparPar\n");
                break;
            } else {
                color_greedy = Greedy(my_graph, Orden, Color);

                if (min_num_crom > color_greedy) {
                    min_num_crom = color_greedy;
                }

                // printf("coloreo numero %d con %d colores\n", i + 1, color_greedy);
            }
        }

        printf("minimo coloreo Jedi: %d\n", min_num_crom);*/
    ////////////////////////////////////////////////////////

    free(Orden);
    free(Color);
    free(Color_2);
    Orden = NULL;
    Color = NULL;

    DestruirGrafo(my_graph);
    fclose(fp);

    return 0;
}
