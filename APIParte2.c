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
    printf("n = %d\n", n);
    u32 cant_col = 1; //cantidad de colores que uso
    u32 ultimo_col = 0; //el mayot que use

    // inicializo el color de todos los vertices en n+2
    // este color no se usaria nunca en un coloreo propio
    for (u32 i = 0; i < n; i++) {
        Color[i] = n + 2;
    }

    printf("greedy inicializado\n");
    //  Asigno el primer color a primer vertice
    //Color[Orden[0]] = 0;

    for (u32 i = 0; i < n; i++) {

        u32 min_col = 0;
        u32 vertice = Orden[i];
        u32 grado_vertice = Grado(vertice, G);
        u32 *vecinos_colores = calloc(grado_vertice, sizeof(u32));

        //printf("greedy iteracion 1 i=%d\n", i);

        for (unsigned j = 0; j < grado_vertice; j++) {
            vecinos_colores[j] = Color[IndiceVecino(j, vertice, G)];
            //printf("greedy iteracion 2 j =%d\n", j);
        }

        // Ordeno los colores de los vecinos
        qsort(vecinos_colores, grado_vertice, sizeof(u32), cmp_ascendente);

        if (vecinos_colores[0] == n + 2) {
            Color[vertice] = 0;
        } 
        else {

            for (u32 j = 0; j < grado_vertice; j++) {
                // empiezo a recorrer desde el color minimo de los vecinos si no es el min_col
                // resulta que el color es mayor que el min_col, entonces puedo usarlo y hago break
                u32 color_repetido = n+2;

                if (min_col == vecinos_colores[j] && vecinos_colores[j] != color_repetido) {
                    //QUE PASA SI LOS COLORES SE REPITEN??
                    color_repetido = vecinos_colores[j];
                    min_col++;
                    if (min_col > ultimo_col) {
                        ultimo_col = min_col;
                        cant_col++;
                    }
                } else {
                    break;
                }
                //printf("colores iteracion %d\n", j);
            }

            Color[vertice] = min_col;
        }

        free(vecinos_colores);
        vecinos_colores = NULL;
    }

    return cant_col;
}

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {

    u32 *pares = calloc(n, sizeof(u32));
    if (pares == NULL) {
        return (char)1;
    }

    qsort(Color, n, sizeof(u32), cmp_ascendente);

    
    u32 last_charged = Color[0]; //== 0
    u32 ind_impar = 0;
    u32 ind_par = 0;

    for (u32 ind_col = 0; ind_col < n; ind_col++) {

        if (Color[ind_col] % 2 == 0 && (Color[ind_col] != last_charged || ind_col == 0)) {
            pares[ind_par] = Color[ind_col];
            last_charged = Color[ind_col];
            ind_par++;
        }
        // siempre mi color empieza en 0 asi que no necesito chequear i==0
        else if (Color[ind_col] % 2 != 0 && Color[ind_col] != last_charged){
            Orden[ind_impar] = Color[ind_col];
            last_charged = Color[ind_col];
            ind_impar++;
        }
    }

    for (u32 ind = 0 ; ind < ind_par; ind++) {

        Orden[ind_impar] = pares[ind];
        ind_impar++;
    }

    free(pares);
    pares = NULL;
    return (char)0;
}

/* char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {

} */