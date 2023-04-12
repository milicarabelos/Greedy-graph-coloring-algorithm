#include "APIparte2.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

u32 Greedy(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);

    // inicializo el color de todos los vertices en n+2
    // este color no se usaria nunca en un coloreo propio
    for (u32 i = 0; i < n; i++) {
        Color[i] = n + 2;
    }

    //  Asigno el primer color a primer vertice
    Color[Orden[0]] = 0;

    for (u32 i = 1; i < n; i++) {
        
        u32 min_col = 0;
        u32 vertice = Orden[i];
        u32 grado_vertice = Grado(vertice, G);
        u32 *vecinos_colores = calloc(grado_vertice, sizeof(u32));

        for (unsigned j = 0; j < grado_vertice; i++) {
            vecinos_colores[j] = Color[IndiceVecino(j, vertice, G)];
        }

        // Ordeno los colores de los vecinos
        qsort(vecinos_colores, grado_vertice, sizeof(u32), cmpfunc);

        if (vecinos_colores[0] == n + 2) {
            Color[vertice] = min_col;
        } else {

            for (j = 0; j < grado_vertice; j++) {
                // empiezo a recorrer desde el color minimo de los vecinos si no es el min_col
                // resulta que el color es mayor que el min_col, entonces puedo usarlo y hago break
                if (min_col = vecinos_colores[i]) {
                    min_col++;
                }
                else{
                    break;
                }
            }

            Color[vertice] = min_col;
        }

        free(vecinos_colores);
    }
}

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
}