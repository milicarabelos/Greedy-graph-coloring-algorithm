#include "APIParte2.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct setVertices {
    u32 *vertices;
    u32 lenVertices;
    u32 color;
    u32 funGrados;
} setVertices;

static int cmpFunGrados(const void *a, const void *b) {
    setVertices *x = (setVertices *)a;
    setVertices *y = (setVertices *)b;

    if (x->funGrados < y->funGrados) {
        return 1;
    } else if (x->funGrados > y->funGrados) {
        return -1;
    } else {
        return 0;
    }
}

static int cmpAscendente(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// esta funcion devuelve el primer color disponible para un vertice de acuerdo a los colores de sus vecinos
static u32 primerColorDisponible(u32 i, Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 minCol = 0;
    u32 vertice = Orden[i];
    u32 gradoVertice = Grado(vertice, G);
    u32 ultimoColorChequeado = n + 2;  // inicializacion en un color que no se usa nunca en greedy
    u32 *vecinosColores = calloc(gradoVertice, sizeof(u32));

    for (u32 i = 0; i < gradoVertice; i++) {
        vecinosColores[i] = Color[IndiceVecino(i, vertice, G)];
    }

    qsort(vecinosColores, gradoVertice, sizeof(u32), cmpAscendente);

    // como el array esta ordenado de menor a mayor si mi color es menor que el minimo
    // puedo usarlo
    if (minCol < vecinosColores[0]) {
        free(vecinosColores);
        vecinosColores = NULL;
        return minCol;
    }

    for (u32 i = 0; i < gradoVertice; i++) {
        // si llego a un vertice que aun no fue coloreado no lo miro ni a los siguientes
        if (vecinosColores[i] == n + 2) {
            free(vecinosColores);
            vecinosColores = NULL;
            return minCol;
        }

        // si el color esta repetido no lo miro
        while (vecinosColores[i] == ultimoColorChequeado) {
            i++;
        }

        // si el color es igual al minimo que quiero usar aumento mi minimo pues no puedo usar
        // ese color ya que lo tiene un vecino de mi vertice
        if (minCol == vecinosColores[i]) {
            ultimoColorChequeado = vecinosColores[i];
            minCol++;
        } else {
            // si no es igual quiere decir que minCol es menor por el orden ascendente uso este minCol
            free(vecinosColores);
            vecinosColores = NULL;
            return minCol;
        }
    }

    free(vecinosColores);
    vecinosColores = NULL;

    return minCol;
}

static u32 asignarColor(u32 i, Grafo G, u32 *Orden, u32 *Color, u32 maxColorUsed) {
    // asigna el minimo color posible a un vertice i y actualiza el maximo color usado
    //  ya que maxColorUsed + 1 es la cant de colores que use para greedy en total
    u32 color = primerColorDisponible(i, G, Orden, Color);

    if (maxColorUsed < color) {
        maxColorUsed = color;
    }

    Color[Orden[i]] = color;
    return maxColorUsed;
}

u32 Greedy(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    u32 maxColorUsed = 0;

    // inicializo el color de todos los vertices en n+2 este color no se usaria nunca en un coloreo propio
    for (u32 i = 0; i < n; i++) {
        Color[i] = n + 2;
    }

    // asignar el primer color al primer vertice
    Color[Orden[0]] = 0;

    // asignar el minimo color posible a los demas vertices
    for (u32 i = 1; i < n; i++) {
        maxColorUsed = asignarColor(i, G, Orden, Color, maxColorUsed);
    }

    // el maximo color usado + 1 es la cantidad de colores usados
    return maxColorUsed + 1;
}

struct data_colores {
    u32 cantidad;
    u32 *indices;
};

u32 maxElemArray(u32 arr[], u32 n) {
    // encuentra el maximo valor de un array
    unsigned int max_val = 0;

    for (u32 i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

char OrdenImparPar(u32 n, u32 *Orden, u32 *Color) {
    u32 cantCol = maxElemArray(Color, n) + 1;
    struct data_colores *colores = calloc(cantCol, sizeof(struct data_colores));
    if (colores == NULL) {
        return 1;
    }

    for (u32 i = 0; i < cantCol; i++) {
        colores[i].indices = calloc(n, sizeof(u32));
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
    for (u32 i = 0; i < n; i++) {
        u32 colorACargar = Color[i];
        u32 index = colores[colorACargar].cantidad;

        colores[colorACargar].indices[index] = i;
        colores[colorACargar].cantidad++;
    }

    // ahora recorro los colores y cargo Orden
    // cargar colores impares
    u32 mayorImpar;
    u32 mayorPar;

    if ((cantCol - 1) % 2 == 0) {
        mayorPar = cantCol - 1;
        mayorImpar = cantCol - 2;
    } else {
        mayorPar = cantCol - 2;
        mayorImpar = cantCol - 1;
    }

    u32 iterarColor = mayorImpar;
    u32 i = 0;
    while (iterarColor < cantCol && iterarColor > 0 && i < n) {
        // mientras el color sea valido en mi coloreo
        u32 counter = 0;
        while (counter < colores[iterarColor].cantidad) {
            // cargo todos los vertices del color iterarColor
            Orden[i] = colores[iterarColor].indices[counter];
            counter++;
            i++;
        }
        iterarColor -= 2;
    }

    iterarColor = mayorPar;
    while (iterarColor < cantCol && iterarColor >= 0 && i <= n) {
        // mientras el color sea valido en mi coloreo
        u32 counter = 0;
        while (counter < colores[iterarColor].cantidad) {
            // cargo todos los vertices del color iterarColor
            Orden[i] = colores[iterarColor].indices[counter];
            counter++;
            i++;
        }
        iterarColor -= 2;
    }

    assert(i == n);

    for (u32 i = 0; i < cantCol; i++) {
        free(colores[i].indices);
        colores[i].indices = NULL;
    }

    free(colores);
    colores = NULL;

    return 0;
}

static char cargarVerticesMismoColor(Grafo G, setVertices *auxStruct, u32 *Color, u32 n, u32 r) {
    u32 acum, indiceVertices;
    for (u32 i = 0; i < r; i++) {
        // me voy fijando en cada color y agrego espacio para los vertices,
        // la cantidad inicial de vertices con ese color es 0
        indiceVertices = 0;
        acum = 0;
        auxStruct[i].color = i;
        auxStruct[i].vertices = calloc(n, sizeof(u32));

        if (auxStruct[i].vertices == NULL) {
            for (u32 k = 0; k < i; k++) {
                free(auxStruct[k].vertices);
                auxStruct[k].vertices = NULL;
            }
            free(auxStruct);
            auxStruct = NULL;
            return '1';
        }

        auxStruct[i].lenVertices = 0;
        auxStruct[i].funGrados = 0;
    }

    // Comparo el color de todos los vertices con el color i
    for (u32 j = 0; j < n; j++) {
        // voy sumando el grado de los vertices de mismo color
        u32 index = auxStruct[Color[j]].lenVertices;
        auxStruct[Color[j]].vertices[index] = j;
        auxStruct[Color[j]].lenVertices++;
        auxStruct[Color[j]].funGrados += Grado(j, G) * Color[j];
    }
    return 0;
}

static void destroy_same_color(setVertices *auxStruct, u32 r) {
    for (u32 i = 0; i < r; i++) {
        free(auxStruct[i].vertices);
        auxStruct[i].vertices = NULL;
    }
    free(auxStruct);
    auxStruct = NULL;
}

char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
    u32 n = NumeroDeVertices(G);
    setVertices *verticeMismoColor;
    u32 r = 0;
    u32 indiceVertices = 0;
    char error;

    r = maxElemArray(Color, n) + 1;

    verticeMismoColor = calloc(r, sizeof(setVertices));
    if (verticeMismoColor == NULL) {
        return 1;
    }
    // itero en el struct de tamaño colores
    error = cargarVerticesMismoColor(G, verticeMismoColor, Color, n, r);
    if (error == '1') {
        return 1;
    }
    qsort(verticeMismoColor, r, sizeof(setVertices), cmpFunGrados);
    // iterador de r ergo colores
    for (u32 i = 0; (i < r); i++) {
        for (u32 j = 0; j < verticeMismoColor[i].lenVertices; j++) {
            Orden[indiceVertices] = verticeMismoColor[i].vertices[j];
            indiceVertices++;
        }
    }
    destroy_same_color(verticeMismoColor, r);
    return 0;
}
