#include <stdio.h>
#include <stdlib.h>

#ifndef API_PARTE2_H
#define API_PARTE2_H

#include "APIG23.h"

// se asume que Orden y Color tienen alocadas las cantidades correctas de memoria

/*corre Greedy en el orden dado por Orden, cargando el coloreo en Color y devolviendo el numero de colores usado */
u32 Greedy(Grafo G, u32* Orden, u32* Color);

/*ordena indices poniendo primero los indices  de color el mayor impar,
luego los indices de color el segundo mayor impar, etc hasta terminar con los impares,
y luego pone los indices de color el mayor par, luego el segundo mayor par, etc.
Aca no es necesaria la estructura de G, solo n.*/
char OrdenImparPar(u32 n, u32* Orden, u32* Color);

// ordena indices en la forma especial dada en las especificaciones
// char OrdenJedi(Grafo G, u32* Orden, u32* Color);


/*ordena los indices de manera natural*/
void OrdenNatural(u32 n, u32* Orden, Grafo my_graph);

/*ordena los indices de manera antural a la inversa*/
void OrdenNaturalReverse(u32 n, u32* Orden, Grafo my_graph);

/*ordena los indices de manera aleatoria*/
void OrdenAleatorio(u32 n, u32* Orden, Grafo my_graph);

void OrdenWelshPowell(u32 n, u32* Orden, Grafo my_graph);
#endif
