#include "APIparte2.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int cmp_ascendente(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_descendente(const void *a, const void *b) {
    int num1 = *((int *)a);
    int num2 = *((int *)b);
    return num2 - num1;
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
        qsort(vecinos_colores, grado_vertice, sizeof(u32), cmp_ascendente);

        if (vecinos_colores[0] == n + 2) {
            Color[vertice] = min_col;
        } else {

            for (u32 j = 0; j < grado_vertice; j++) {
                // empiezo a recorrer desde el color minimo de los vecinos si no es el min_col
                // resulta que el color es mayor que el min_col, entonces puedo usarlo y hago break
                if (min_col = vecinos_colores[i]) {
                    min_col++;
                } else {
                    break;
                }
            }

            Color[vertice] = min_col;
        }

        free(vecinos_colores);
        vecinos_colores = NULL;
    }
}

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {

    u32 *pares = calloc(n, sizeof(u32));
    if (pares == NULL) {
        return (char)1;
    }

    u32 *impares = calloc(n, sizeof(u32));
    if (impares == NULL) {
        free(pares);
        return (char)1;
    }

    qsort(Color, n, sizeof(u32), cmp_ascendente);

    u32 last_charged = Color[0];
    u32 ind_impar = 0;

    for (u32 ind_col = 0; ind_col < n; ind_col++) {
        u32 ind_par = 0;

        if (Color[ind_col] % 2 == 0 && (Color[ind_col] != last_charged || ind_col == 0)) {
            pares[ind_par] = Color[ind_col];
            last_charged = Color[ind_col];
            ind_par++;
        }
        // siempre mi color empieza en 0 asi que no necesito chequear i!=0
        else if (Color[ind_col] % 2 != 0 && Color[ind_col] != last_charged){
            impares[ind_impar] = Color[ind_col];
            last_charged = Color[ind_col];
            ind_impar++;
        }
    }

    u32 i = 0;
    for (u32 ind = ind_impar - 1; ind >= 0; ind--) {

            Orden[i] = impares[ind];
            i++;
    }

    i=0;
    for (u32 ind = i + 1; ind < n; ind++) {

        Orden[i] = pares[ind];
        i++;
    }

    free(pares);
    pares = NULL;
    free(impares);
    impares = NULL;

    return (char)0;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
}