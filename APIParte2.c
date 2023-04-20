#include "APIparte2.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int cmp_ascendente(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_descendente(const void *a, const void *b) {
    int num1 = *((int *)a);
    int num2 = *((int *)b);
    return num2 - num1;
}

// esta funcion devuelve el primer color disponible para un vertice de acuerdo a los colores de sus vecinos
static u32 primer_color_disponible(u32 i, Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 min_col = 0;
    u32 vertice = Orden[i];
    u32 grado_vertice = Grado(vertice, G);
    u32 ultimo_color_chequeado = n + 2;  // inicializacion en un color que no se usa nunca en greedy
    u32 *vecinos_colores = calloc(grado_vertice, sizeof(u32));

    for (u32 i = 0; i < grado_vertice; i++) {
        vecinos_colores[i] = Color[IndiceVecino(i, vertice, G)];
    }

    qsort(vecinos_colores, grado_vertice, sizeof(u32), cmp_ascendente);

    // como el array esta ordenado de menor a mayor si mi color es menor que el minimo
    // puedo usarlo
    if (min_col < vecinos_colores[0]) {
        free(vecinos_colores);
        vecinos_colores = NULL;
        return min_col;
    }

    for (u32 i = 0; i < grado_vertice; i++) {
        // si llego a un vertice que aun no fue coloreado no lo miro ni a los siguientes
        if (vecinos_colores[i] == n + 2) {
            free(vecinos_colores);
            vecinos_colores = NULL;
            return min_col;
        }

        // si el color esta repetido no lo miro
        while (vecinos_colores[i] == ultimo_color_chequeado) {
            i++;
        }

        // si el color es igual al minimo que quiero usar aumento mi minimo pues no puedo usar
        //  ese color
        if (min_col == vecinos_colores[i]) {
            ultimo_color_chequeado = vecinos_colores[i];
            min_col++;
        } else {  // si no es igual quiere decir que min_col es menor por el orden ascendente uso este min_col
            free(vecinos_colores);
            vecinos_colores = NULL;
            return min_col;
        }
    }

    return n + 2;
}

// funcion encargada de asignar el minimo color posible a un vertice i y actualizar el maximo color usado
//  ya que max_color_used + 1 es la cant de colores que use para greedy en total
static u32 asignar_color(u32 i, Grafo G, u32 *Orden, u32 *Color, u32 max_color_used) {
    u32 color = primer_color_disponible(i, G, Orden, Color);

    if (max_color_used < color) {
        max_color_used = color;
    }

    Color[Orden[i]] = color;
    return max_color_used;
}

u32 Greedy(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 max_color_used = 0;

    // inicializo el color de todos los vertices en n+2 este color no se usaria nunca en un coloreo propio
    for (u32 i = 0; i < n; i++) {
        Color[i] = n + 2;
    }

    // asignar el primer color al primer vertice
    Color[Orden[0]] = 0;

    // asignar el minimo color posible a los demas vertices
    for (u32 i = 1; i < n; i++) {
        max_color_used = asignar_color(i, G, Orden, Color, max_color_used);
    }

    // el maximo color usado + 1 es la cantidad de colores usados
    return max_color_used + 1;
}

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {
    u32 *pares = calloc(n, sizeof(u32));
    if (pares == NULL) {
        return (char)1;
    }

    qsort(Color, n, sizeof(u32), cmp_ascendente);

    u32 last_charged = Color[0];  //== 0
    u32 ind_impar = 0;
    u32 ind_par = 0;

    for (u32 ind_col = 0; ind_col < n; ind_col++) {
        if (Color[ind_col] % 2 == 0 && (Color[ind_col] != last_charged || ind_col == 0)) {
            pares[ind_par] = Color[ind_col];
            last_charged = Color[ind_col];
            ind_par++;
        }
        // siempre mi color empieza en 0 asi que no necesito chequear i==0
        else if (Color[ind_col] % 2 != 0 && Color[ind_col] != last_charged) {
            Orden[ind_impar] = Color[ind_col];
            last_charged = Color[ind_col];
            ind_impar++;
        }
    }

    for (u32 ind = 0; ind < ind_par; ind++) {
        Orden[ind_impar] = pares[ind];
        ind_impar++;
    }

    free(pares);
    pares = NULL;
    return (char)0;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
    u32 acum = 0;
    u32 n = NumeroDeVertices(G);
    u32 r = 0;
    // cantidad de colores
    for (u32 i = 0; Color[i] != NULL; i++) {
        r += 1;
    }
    for (u32 i = 0; i < r; i++) {
        // sumatoria de grado de los vertices de color i
        for (u32 j = 0; j < n; j++) {
            if (Color[j] == i) {
                acum += Grado(j, G);
            }
        }
        acum = acum * i;
        Orden[i] = acum;
        acum = 0;
    }
    qsort(Orden, r, sizeof(u32), cmp_descendente);
    for (u32 i = 1; Orden[i] != NULL; i++) {
        if (Orden[i] > Orden[i - 1]) {
            return '1';
        }
    }
    return '0';
    // Ver cuando retorna '1'
}
char OrdenNaturalReverse(u32 n, u32 *Orden, u32 *Color) {
    u32 last_charged = Color[n - 1];  //== 0

    qsort(Color, n, sizeof(u32), cmp_ascendente);

    for (u32 ind_col = 0; ind_col < n; ind_col++) {
        if ((Color[ind_col] != last_charged)) {
            last_charged = Color[n - ind_col - 1];
        }
        Orden[ind_col] = last_charged;
    }
}

char OrdenNatural(u32 n, u32 *Orden, u32 *Color) {
    u32 last_charged = Color[0];  //== 0

    qsort(Color, n, sizeof(u32), cmp_ascendente);

    for (u32 ind_col = 0; ind_col < n; ind_col++) {
        if ((Color[ind_col] != last_charged)) {
            last_charged = Color[ind_col];
        }
        Orden[ind_col] = last_charged;
    }
}

char OrdenAleatorio(u32 n, u32 *Orden, u32 *Color) {
    unsigned int random_id = 0;
    u32 last_charged = Color[random_id];  //== 0
    qsort(Color, n, sizeof(u32), cmp_ascendente);

    for (u32 ind_col = 0; ind_col < n; ind_col++) {
        while ((Color[random_id] == last_charged)) {
            random_id = rand() % n;
            last_charged = Color[random_id];
        }
        Orden[ind_col] = last_charged;
    }
}
