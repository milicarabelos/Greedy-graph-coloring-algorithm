
#include <APIG23.h>
#include <EstructuraGrafo23.h>

/*Crea un nuevo grafo con la cantidad de vertices
y la cantidad de lados
*/
Grafo init_grafo(unsigned int n, unsigned int m)
{
    Grafo new_grafo = calloc(1, sizeof(struct GrafoSt));
    new_grafo->list_lados = (Tupla *)calloc(m, sizeof(unsigned int));
    new_grafo->list_vertices = (vertice *)calloc(n, sizeof(vertice));
    new_grafo->cant_vertices = n;
    new_grafo->cant_lados = m;
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
    return new_vertice;
}
// revisar
void cargar_lado(Tupla *lista_lados, int i, unsigned int primero, unsigned int segundo)
{
    lista_lados[i].x = primero;
    lista_lados[i].y = segundo;
}

Grafo destroy_grafo(Grafo grafo)
{
    for (unsigned int i = 0; i < grafo->cant_lados; i++)
    {
        free(grafo->list_vertices[i]->indice_vecinos);
        grafo->list_vertices[i]->indice_vecinos = NULL;
    }

    free(grafo->list_vertices);
    grafo->list_vertices = NULL;
    free(grafo->list_lados);
    grafo->list_lados = NULL;

    return NULL;
}