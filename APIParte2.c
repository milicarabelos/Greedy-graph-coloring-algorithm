#include "APIparte2.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct set_vetices {
    u32 *vertices;
    u32 len_vertices;
    u32 color;
    u32 fun_grado;
} set_vertices;

int cmp_fun_grado(const void *a, const void *b) {
    set_vertices *x = (const set_vertices *)a;
    set_vertices *y = (const set_vertices *)b;

    if (x->fun_grado < y->fun_grado) {
        return 1;
    } else if (x->fun_grado > y->fun_grado) {
        return -1;
    } else {
        return 0;
    }
}

int cmp_ascendente(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_desc(const void *a, const void *b) {
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
        // ese color ya que lo tiene un vecino de mi vertice
        if (min_col == vecinos_colores[i]) {
            ultimo_color_chequeado = vecinos_colores[i];
            min_col++;
        } else {  // si no es igual quiere decir que min_col es menor por el orden ascendente uso este min_col
            free(vecinos_colores);
            vecinos_colores = NULL;
            return min_col;
        }
    }

    free(vecinos_colores);
    vecinos_colores = NULL;

    return min_col;
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

struct data_colores {
    u32 cantidad;
    u32 *indices;
};

// encuentra el maximo valor de un array
u32 find_max(u32 arr[], u32 n) {
    unsigned int max_val = 0;

    for (u32 i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {
    u32 cantcol = find_max(Color, n) + 1;

    // pido memoria para el array por colores
    struct data_colores *colores = calloc(cantcol, sizeof(struct data_colores));
    if (colores == NULL) {
        return 1;
    }
    // pido memoria para cada array interno
    for (u32 i = 0; i < cantcol; i++) {
        colores[i].indices = calloc(n, sizeof(u32));
        // si hay error al pedir memoria
        if (colores[i].indices == NULL) {
            for (u32 j = 0; j < i; j++) {
                free(colores[j].indices);
                colores[j].indices = NULL;
            }

            free(colores);
            colores = NULL;

            return 1;
        }
        colores[i].cantidad = 0;
    }

    // pedi toda la memora ahora recorro

    for (u32 i = 0; i < n; i++) {
        u32 color_a_cargar = Color[i];
        u32 index = colores[color_a_cargar].cantidad;

        colores[color_a_cargar].indices[index] = i;
        colores[color_a_cargar].cantidad++;
    }

    // ahora recorro los colores y cargo Orden
    // cargar colores impares
    u32 iterar_color = 1;

    // mientras el color sea valido en mi coloreo
    u32 i = 0;
    while (iterar_color < cantcol && i < n) {
        u32 counter = 0;
        // cargo todos los vertices del color iterar_color
        while (counter < colores[iterar_color].cantidad) {
            Orden[i] = colores[iterar_color].indices[counter];
            counter++;
            i++;
        }
        // itero el siguiente color impar
        iterar_color += 2;
    }

    // cargar colores pares
    iterar_color = 0;

    // mientras el color sea valido en mi coloreo
    while (iterar_color < cantcol) {
        u32 counter = 0;
        // cargo todos los vertices del color iterar_color
        while (counter < colores[iterar_color].cantidad) {
            Orden[i] = colores[iterar_color].indices[counter];
            counter++;
            i++;
        }
        // itero el siguiente color impar
        iterar_color += 2;
    }

    assert(i == n);

    // libero la memoria pedida
    for (u32 i = 0; i < cantcol; i++) {
        free(colores[i].indices);
        colores[i].indices = NULL;
    }

    free(colores);
    colores = NULL;

    return 0;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    set_vertices *aux_struct;
    u32 acum = 0;
    u32 r = 0;
    u32 index_vertex = 0;

    for (u32 i = 0; i < n; i++) {
        if (Color[i] > r) {
            r = Color[i];
        }
    }
    r++;

    aux_struct = calloc(r, sizeof(set_vertices));

    for (u32 i = 0; i < r; i++) {
        aux_struct[i].color = i;
        aux_struct[i].vertices = calloc(Delta(G), sizeof(u32));
        aux_struct[i].len_vertices = 0;
        // sumatoria de grado de los vertices de color i
        for (u32 j = 0; j < n; j++) {
            if (Color[j] == aux_struct[i].color) {
                acum += Grado(j, G);
                if (aux_struct[i].len_vertices < index_vertex) {
                    aux_struct[i].len_vertices = (aux_struct[i].vertices, sizeof(u32) * (aux_struct[i].len_vertices) * 2);
                }
                aux_struct[i].vertices[index_vertex] = j;
                index_vertex++;
            }
        }
        acum = acum * i;
        aux_struct[i].fun_grado = acum;
        aux_struct[i].len_vertices = index_vertex;
        acum = 0;
        index_vertex = 0;
    }
    qsort(aux_struct, r, sizeof(set_vertices), cmp_fun_grado);

    index_vertex = 0;  // para reordenar Orden
    int i = 0;         // iterador de r ergo colores
    while ((index_vertex < n) && (i < r)) {

        // j es el que recorre adentro de cada arreicito de vertices de mismo color
        for (u32 j = 0; j < aux_struct[i].len_vertices; j++) {
            Orden[index_vertex] = aux_struct[i].vertices[j];
            index_vertex++;
        }
        i++;
    }

    free(aux_struct);

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

    return 0;
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
    return 0;
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
    return 0;
}
