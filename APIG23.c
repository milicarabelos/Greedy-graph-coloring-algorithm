
#include "APIG23.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EstructuraGrafo23.h"

//////////////////////////////////////////////////////////////////////////////////////////
///////////////FUNCIONES ESTATICAS PARA MEJORAR LA MODULARIZACION DEL CODIGO//////////////

/*Crea un nuevo grafo con la cantidad de vertices
y la cantidad de lados
*/
/* static print_graph(Grafo G) {
    printf("Vertices: %u\n", G->cantVertices);
    printf("Lados: %u\n", G->cantLados);
    printf("Mayor grado: %u\n", G->mayor_grado);
         for (u32 i = 0; i < G->cantVertices; i++) {
            printf("Vertice %u: ", G->listVertices[i].nombre);
            printf("Grado %u: ", G->listVertices[i].grado);
            for (u32 j = 0; j < G->listVertices[i].grado; j++) {
                printf("%u ", G->listVertices[i].indiceVecinos[j]);
            }
            printf("\n");
        }
} */

static Grafo initGrafo(u32 n, u32 m) {
    Grafo newGrafo = calloc(1, sizeof(GrafoSt));

    if (newGrafo == NULL) {
        printf("Error no se pudo pedir la memoria para la estructura grafo");
        return NULL;
    }

    // guardaste memoria para M*2 tuplas
    newGrafo->listLados = (Tupla *)calloc((2 * m), sizeof(Tupla));
    if (newGrafo->listLados == NULL) {
        printf("Error no se pudo pedir la memoria para la lista de lados");
        free(newGrafo);
        return NULL;
    }
    // guaradste memoria para una lista con N vertices
    // estos vertices fijate van a vivr en esos espacios de memoria
    newGrafo->listVertices = calloc(n, sizeof(vertice));
    if (newGrafo->listVertices == NULL) {
        printf("Error no se pudo pedir la memoria para la lista de vertices");
        free(newGrafo->listLados);
        free(newGrafo);
        return NULL;
    }
    newGrafo->cantVertices = n;
    newGrafo->cantLados = m;
    newGrafo->mayorGrado = 0;

    return newGrafo;
}

static void cargar_lado(Tupla *listaLados, int i, u32 primero, u32 segundo) {
    listaLados[i].x = primero;
    listaLados[i].y = segundo;
    listaLados[i + 1].x = segundo;
    listaLados[i + 1].y = primero;
}

static int cmpTuples(const void *a, const void *b) {
    // ordena de menor a mayor primero respecto de
    // la primera componente (x) y luego de la segunda (y)

    Tupla *tuplaA = (Tupla *)a;
    Tupla *tuplaB = (Tupla *)b;
    if (tuplaA->x < tuplaB->x) {
        return -1;
    } else if (tuplaA->x > tuplaB->x) {
        return 1;
    } else {
        if (tuplaA->y < tuplaB->y) {
            return -1;
        } else if (tuplaA->y > tuplaB->y) {
            return 1;
        } else {
            return 0;
        }
    }
}

static int binarySearch(Grafo G, u32 target_name) {
    u32 left = 0;
    u32 right = G->cantVertices - 1;
    u32 pivot;
    u32 vecino;
    while (left <= right) {
        pivot = (left + right) / 2;
        vecino = G->listVertices[pivot].nombre;

        if (vecino == target_name) {
            return pivot;
        } else if (vecino < target_name) {
            left = pivot + 1;
        } else {
            right = pivot - 1;
        }
    }
    return -1;
}

static void cargarVecinos(Grafo G) {
    u32 indice;
    u32 maxGrade = 0;
    // printf("Cargando vecinos.\n");
    for (u32 i = 0; i < G->cantVertices; i++) {
        if (G->listVertices[i].grado > maxGrade) {
            maxGrade = G->listVertices[i].grado;
        }
        for (u32 j = 0; j < G->listVertices[i].grado; j++) {
            // printf("Cargando vecino %u del vertice %u\n", j, G->listVertices[i].nombre);
            indice = binarySearch(G, G->listVertices[i].indiceVecinos[j]);
            if (indice != -1) {
                // printf("Nombre del vertice: %u ", G->listVertices[i].nombre);
                // printf("Nombre del vecino antes: %u", G->listVertices[i].indiceVecinos[j]);
                ////    printf(" GRADO %u", G->listVertices[i].grado);
                // printf("\nNombre del vecino buscado con indice obtenido: %u\n\n", G->listVertices[indice].nombre);

                G->listVertices[i].indiceVecinos[j] = indice;
            }
        }
    }
    G->mayorGrado = maxGrade;
    // printf("Vecinos Cargados :).\n");
}

static void cargarVertices(Grafo G) {
    u32 lastCharged = 0;
    u32 grado = 0;
    u32 indiceVert = 0;
    u32 **generalVecinos = calloc(G->cantVertices, sizeof(u32 *));

    // cargo el primer vertice y su indice
    G->listVertices[indiceVert].nombre = G->listLados[indiceVert].x;
    lastCharged = G->listVertices[indiceVert].nombre;
    G->listVertices[indiceVert].indice = indiceVert;

    for (u32 i = 0; i < G->cantLados * 2; i++) {
        if (G->listLados[i].x == lastCharged) {
            grado++;
            G->listVertices[indiceVert].grado = grado;
        } else {
            indiceVert++;
            grado = 1;
            lastCharged = G->listLados[i].x;
            G->listVertices[indiceVert].nombre = lastCharged;
            G->listVertices[indiceVert].indice = indiceVert;
            G->listVertices[indiceVert].grado = grado;
        }

        generalVecinos[indiceVert] = realloc(generalVecinos[indiceVert], grado * sizeof(u32));
        // printf("%u \n", generalVecinos[indiceVert]);
        generalVecinos[indiceVert][grado - 1] = G->listLados[i].y;
    }

    // update the vertex arrays with the neighbor lists
    for (u32 i = 0; i < G->cantVertices; i++) {
        G->listVertices[i].indiceVecinos = calloc(G->listVertices[i].grado, sizeof(u32));
        // printf("list_vecinos de %u\n", G->listVertices[i].nombre);

        // printf("[");
        for (u32 j = 0; j < G->listVertices[i].grado; j++) {
            G->listVertices[i].indiceVecinos[j] = generalVecinos[i][j];
            // printf("%u,", G->listVertices[i].indiceVecinos[j]);
        }
        // printf("] \n");
        free(generalVecinos[i]);
    }
    free(generalVecinos);
}

static Grafo destroyGrafo(Grafo grafo) {
    for (u32 i = 0; i < grafo->cantVertices; i++) {
        free(grafo->listVertices[i].indiceVecinos);
        grafo->listVertices[i].indiceVecinos = NULL;
    }

    free(grafo->listVertices);
    grafo->listVertices = NULL;
    free(grafo->listLados);
    grafo->listLados = NULL;

    free(grafo);
    return NULL;
}

// construcci'on/destrucci'on
/*debe leer desde stdin
Debo calcular el Delta
*/
Grafo ConstruirGrafo() {
    FILE *fInput = stdin;
    char line[1024];
    u32 n, m, x, y;
    Grafo myGraph;

    while (fgets(line, sizeof(line), fInput)) {
        if (line[0] == 'c') {
            // hago skip a esta linea y continuo a la siguiente
            continue;
        } else if (line[0] == 'p') {
            sscanf(line, "p edge %u %u", &n, &m);
            // printf("n = %u, m = %u\n", n, m);
            myGraph = initGrafo(n, m);

            break;
        } else {
            // En caso de error devuelvo NULL
            return NULL;
        }
    }

    /* Tengo que sacar las ultimas dos guardas, luego de encontrar la linea con p tengo m lineas de formato e num num donde cargo los lados,
   si tengo una linea con otro formato deberia dar error,  despues de m lineas puede haber una cantidad arbitraria de lineas sin formato
   por lo que no tengo que seguir leyendo
    */
    for (u32 i = 0; i < m * 2; i = i + 2) {
        fgets(line, sizeof(line), fInput);
        if (line[0] != 'e') {
            // ERROR en formato
            return NULL;
        } else {
            // aca entiendo deberiamos cargar desp ordenar y desp cargar los vertices pero pa eso deberiamos recorrer los vertices y eso esta raro
            sscanf(line, "e %u %u", &x, &y);
            cargar_lado(myGraph->listLados, i, x, y);
        }
    }

    // ordeno los lados de menor a mayor por primera y segunda componente
    // ERROR: aca funciona para R22_93_15 pero tira malloc corrupted para el resto SE CLAVA ACAAAA
    // printf("antes del sort");
    qsort(myGraph->listLados, myGraph->cantLados * 2, sizeof(Tupla), cmpTuples);

    // carga de vertices
    cargarVertices(myGraph);

    // carga de vecinos
    cargarVecinos(myGraph);

    // print_graph(myGraph);

    return myGraph;
}

void DestruirGrafo(Grafo G) {
    G = destroyGrafo(G);
}

// funciones para extraer datos del grafo. u32 debe estar definida en el .h de arriba

u32 NumeroDeVertices(Grafo G) {
    return G->cantVertices;
}
u32 NumeroDeLados(Grafo G) {
    return G->cantLados;
}
u32 Delta(Grafo G) {
    return G->mayorGrado;
}
// funciones de extraccion de informacion de vertices

u32 Nombre(u32 i, Grafo G) {
    return G->listVertices[i].nombre;
}
u32 Grado(u32 i, Grafo G) {
    return G->listVertices[i].grado;
}

// vertice i y  buscar el j-esimo vecino de i

u32 IndiceVecino(u32 j, u32 i, Grafo G) {
    if (i >= G->cantVertices || j >= G->listVertices[i].grado) {
        return (2 ^ 32) - 1;
        // caso de error
    }

    return G->listVertices[i].indiceVecinos[j];
}
