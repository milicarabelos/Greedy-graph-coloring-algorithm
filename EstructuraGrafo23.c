
#include <EstructuraGrafo23.h>
#include <APIG23.h>

Grafo init_grafo(unsigned int n, unsigned int m)
{
    Grafo new_grafo = calloc(1, sizeof(struct GrafoSt));
    new_grafo->list_lados = (Tupla *)calloc(n, sizeof(unsigned int));
    new_grafo->list_vertices = (vertice *)calloc(m, sizeof(vertice));
    new_grafo->n = n;
    new_grafo->m = m;
    new_grafo->mayor_grado = 0;
    new_grafo->menor_grado = 0;

    return new_grafo;
}

vertice init_vertice(unsigned int nombre)
{
    vertice new_vertice = calloc(1, sizeof(struct _s_vertice));
    new_vertice->nombre = nombre;
    new_vertice->grado = 0;
    new_vertice->indice_vecinos = (unsigned int *)calloc(1, sizeof(vertice));
    // VER ACA COMO PEDIR BIEN LA MEMORIA DE LOS VECINOS PODEMOS PONER NULL ACA Y DESPUES CADA QUE
    // AGREGEMOS UN VECINO VAMOS HACIENDO REALLOC ME PARECE BUENA IDEA TOTAL DIFERENCIAMOS LOS CASOS
    //  CUANDO EL GRADO ES 1 QUE USAMOS CALLOC ELSE REALOCC
}