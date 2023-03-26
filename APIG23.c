
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

    printf("entre a init");

    Grafo new_grafo = calloc(1, sizeof(struct GrafoSt));

    if (new_grafo == NULL) {
        printf("Error no se pudo pedir la memoria para la estructura grafo");
        return NULL;
    }

    printf("antes de los lados");
    new_grafo->list_lados = (Tupla *)calloc(m, sizeof(unsigned int));
    if (new_grafo->list_lados == NULL) {
        printf("Error no se pudo pedir la memoria para la lista de lados");
        return NULL;
    }
    printf("desp de los lados");
    new_grafo->list_vertices = (vertice *)calloc(n, sizeof(vertice));
    if (new_grafo->list_vertices == NULL) {
        printf("Error no se pudo pedir la memoria para la lista de vertices");
        return NULL;
    }
    new_grafo->cant_vertices = n;
    new_grafo->cant_lados    = m;
    new_grafo->mayor_grado   = 0;
    new_grafo->menor_grado   = 0;

    return new_grafo;
}

static vertice init_vertice(unsigned int nombre) {
    vertice new_vertice = calloc(1, sizeof(struct _s_vertice));
    if (new_vertice == NULL) {
        printf("Error pidiendo memoria para el vertice");
        return NULL;
    }
    new_vertice->nombre         = nombre;
    new_vertice->grado          = 0;
    new_vertice->indice_vecinos = (unsigned int *)calloc(1, sizeof(vertice));
    // VER ACA COMO PEDIR BIEN LA MEMORIA DE LOS VECINOS PODEMOS PONER NULL ACA Y DESPUES CADA QUE
    // AGREGEMOS UN VECINO VAMOS HACIENDO REALLOC ME PARECE BUENA IDEA TOTAL DIFERENCIAMOS LOS CASOS
    //  CUANDO EL GRADO ES 1 QUE USAMOS CALLOC ELSE REALOCC
    return new_vertice;
}
// revisar
static void cargar_lado(Tupla *lista_lados, int i, unsigned int primero, unsigned int segundo) {
    lista_lados[i].x = primero;
    lista_lados[i].y = segundo;
}

static int cmp_tuples(const void *a, const void *b) {
    Tupla *tupla_a = (Tupla *)a;
    Tupla *tupla_b = (Tupla *)b;

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

static Grafo destroy_grafo(Grafo grafo) {
    for (unsigned int i = 0; i < grafo->cant_lados; i++) {
        free(grafo->list_vertices[i]->indice_vecinos);
        grafo->list_vertices[i]->indice_vecinos = NULL;
    }

    free(grafo->list_vertices);
    grafo->list_vertices = NULL;
    free(grafo->list_lados);
    grafo->list_lados = NULL;

    return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////

// construcci'on/destrucci'on
/*debe leer desde stdin
Debo calcular el Delta
*/
Grafo ConstruirGrafo(FILE *f_input) {
    char         line[256];
    unsigned int n, m, x, y;
    Grafo        my_grafo;

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
    for (size_t i = 0; i < m; i++) {
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
    qsort(my_grafo->list_lados, my_grafo->cant_lados, sizeof(Tupla), cmp_tuples);

    for (unsigned int i = 0; i < my_grafo->cant_lados; i++) {
        printf("%u lado = (%u,%u)\n", i, my_grafo->list_lados[i].x, my_grafo->list_lados[i].y);
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
    return G->list_vertices[i]->nombre;
}
unsigned int Grado(unsigned int i, Grafo G) {
    return G->list_vertices[i]->grado;
}

unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G) {
    if (i >= G->cant_vertices || j >= G->list_vertices[i]->grado) {
        return (2 ^ 32) - 1;
        // caso de error
    }

    return G->list_vertices[i]->indice_vecinos[j];
}
