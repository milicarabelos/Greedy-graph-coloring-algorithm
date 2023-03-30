
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
static Grafo init_grafo(unsigned int n, unsigned int m) {

    Grafo new_grafo = calloc(1, sizeof(struct GrafoSt));

    if (new_grafo == NULL) {
        printf("Error no se pudo pedir la memoria para la estructura grafo");
        return NULL;
    }

    // guardaste memoria para M*2 tuplas
    new_grafo->list_lados = (Tupla *)calloc((2 * m), sizeof(Tupla));
    if (new_grafo->list_lados == NULL) {
        printf("Error no se pudo pedir la memoria para la lista de lados");
        return NULL;
    }
    // guaradste memoria para una lista con N vertices
    // estos vertices fijate van a vivr en esos espacios de memoria
    new_grafo->list_vertices = calloc(n, sizeof(vertice));
    if (new_grafo->list_vertices == NULL) {
        printf("Error no se pudo pedir la memoria para la lista de vertices");
        return NULL;
    }
    new_grafo->cant_vertices = n;
    new_grafo->cant_lados = m;
    new_grafo->mayor_grado = 0;
    new_grafo->menor_grado = 0;

    return new_grafo;
}

// revisar
static void cargar_lado(Tupla *lista_lados, int i, unsigned int primero, unsigned int segundo) {
    lista_lados[i].x = primero;
    lista_lados[i].y = segundo;
    lista_lados[i + 1].x = segundo;
    lista_lados[i + 1].y = primero;
}

// ordenar de menor a mayor primero respecto de la primera componente (x) y luego de la segunda (y)
static int cmp_tuples(const void *a, const void *b) {
    Tupla *tupla_a = (Tupla *)a;
    Tupla *tupla_b = (Tupla *)b;
    // vertice a y vertice b
    //  (1, 3)
    //  (1, 4)
    //  (2, 1)
    //  (3, 4)
    //  (4, 1)
    //  (4, 5)
    //  (5, 6)
    //  (5, 9)
    //  (9, 5)
    // a = 1 mientras se repita cargo los b
    // last_charged = 1
    // x < last_charged por orden ya se que lo cargue
    // 2 < 1 no bueno lo agrego
    //
    //[1,3,4,2] list vert [1,2,3,4] orden natural

    /*formas que no van:
           cargar todos los a y despues todos los b
           cargar y reordenar
       */
    if (tupla_a->x < tupla_b->x) {
        return -1;
    } else if (tupla_a->x > tupla_b->x) {
        return 1;
    } else {
        if (tupla_a->y < tupla_b->y) {
            return -1;
        } else if (tupla_a->y > tupla_b->y) {
            return 1;
        } else {
            return 0;
        }
    }
}

static void cargar_vertices(Grafo G) {
    unsigned int last_charged;
    unsigned int grado = 0;
    unsigned int indice_vert = 0;

    last_charged = G->list_lados[indice_vert].x;
    G->list_vertices[indice_vert].nombre = last_charged;
    G->list_vertices[indice_vert].indice = indice_vert;
    for (unsigned int i = 0; i < G->cant_lados * 2; i++) {
        if (G->list_lados[i].x == last_charged) {
            grado++;
            G->list_vertices[indice_vert].grado = grado;
        } else {
            indice_vert++;
            last_charged = G->list_lados[i].x;
            G->list_vertices[indice_vert].nombre = last_charged;
            G->list_vertices[indice_vert].indice = indice_vert;
            grado = 1;
        }
    }
}

static Grafo destroy_grafo(Grafo grafo) {
    /*    for (unsigned int i = 0; i < grafo->cant_lados; i++) {
           free(grafo->list_vertices[i]->indice_vecinos);
           grafo->list_vertices[i]->indice_vecinos = NULL;
       } */

    free(grafo->list_vertices);
    grafo->list_vertices = NULL;
    free(grafo->list_lados);
    grafo->list_lados = NULL;

    return NULL;
}

static void cargar_ordenado(){};
////////////////////////////////////////////////////////////////////////////////////////

// construcci'on/destrucci'on
/*debe leer desde stdin
Debo calcular el Delta
*/
Grafo ConstruirGrafo(FILE *f_input) {
    char line[1024];
    unsigned int n, m, x, y;
    Grafo my_grafo;

    while (fgets(line, sizeof(line), f_input)) {
        if (line[0] == 'c') {
            // hago skip a esta linea y continuo a la siguiente
            continue;
        } else if (line[0] == 'p') {
            sscanf(line, "p edge %u %u", &n, &m);
            printf("n = %u, m = %u\n", n, m);
            my_grafo = init_grafo(n, m);

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
    for (unsigned int i = 0; i < m * 2; i = i + 2) {
        fgets(line, sizeof(line), f_input);
        if (line[0] != 'e') {
            // ERROR en formato
            return NULL;
        } else {
            // revisar
            // aca entiendo deberiamos cargar desp ordenar y desp cargar los vertices pero pa eso deberiamos recorrer los vertices y eso esta raro
            sscanf(line, "e %u %u", &x, &y);
            cargar_lado(my_grafo->list_lados, i, x, y);
        }
    }

    // ordeno los lados de menor a mayor por primera y segunda componente
    // ERROR: aca funciona para R22_93_15 pero tira malloc corrupted para el resto SE CLAVA ACAAAA
    // printf("antes del sort");
    qsort(my_grafo->list_lados, my_grafo->cant_lados * 2, sizeof(Tupla), cmp_tuples);
    printf("\nlados\n");
    for (unsigned int i = 0; i < my_grafo->cant_lados * 2; i++) {
        printf("%u lado = (%u,%u)\n", (i + 1), my_grafo->list_lados[i].x, my_grafo->list_lados[i].y);
    }

    // ete aqui la señora
    cargar_vertices(my_grafo);

    printf("\n");
    printf("vertices: \n");
    for (unsigned int i = 0; i < my_grafo->cant_vertices; i++) {
        printf("i:%u vert:%u\n", i, my_grafo->list_vertices[i].nombre);
    }

    return my_grafo;
}

void DestruirGrafo(Grafo G) {
    G = destroy_grafo(G);
}

// funciones para extraer datos del grafo. unsigned int debe estar definida en el .h de arriba

unsigned int NumeroDeVertices(Grafo G) {
    return G->cant_vertices;
}
unsigned int NumeroDeLados(Grafo G) {
    return G->cant_lados;
}
unsigned int Delta(Grafo G) {
    return G->mayor_grado;
}
// funciones de extraccion de informacion de vertices

unsigned int Nombre(unsigned int i, Grafo G) {
    return G->list_vertices[i].nombre;
}
unsigned int Grado(unsigned int i, Grafo G) {
    return G->list_vertices[i].grado;
}

// vertice i y  buscar el j-esimo vecino de i

unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G) {
    if (i >= G->cant_vertices || j >= G->list_vertices[i].grado) {
        return (2 ^ 32) - 1;
        // caso de error
    }

    return G->list_vertices[i].indice_vecinos[j];
}
