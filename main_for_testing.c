#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "APIParte2.h"
// #include "EstructuraGrafo23.h"

///////////////////////funciones de orden iniciales///////////////////////////
void OrdenNatural(u32 n, u32 *Orden) {
    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }
}

void OrdenNaturalReverse(u32 n, u32 *Orden) {
    for (u32 i = 0; i < n; i++) {
        Orden[i] = n - 1 - i;
    }
}

void OrdenAleatorio(u32 n, u32 *Orden) {
    unsigned int randomID = 0;
    bool used[n];                           
    memset(used, false, n * sizeof(bool));

    for (u32 indCol = 0; indCol < n; indCol++) {
        while (used[randomID]) {
            randomID = rand() % n;
        }

        Orden[indCol] = randomID;
        used[randomID] = true;
    }
}

struct dataGrades {
    u32 indice;
    u32 grade;
};

// grados de mayor a menor
int compareGrades(const void *a, const void *b) {
    const struct dataGrades *dataA = (const struct dataGrades *)a;
    const struct dataGrades *dataB = (const struct dataGrades *)b;

    if (dataA->grade < dataB->grade) {
        return 1;
    } else if (dataA->grade > dataB->grade) {
        return -1;
    } else {
        return 0;
    }
}

void OrdenWelshPowell(u32 n, u32 *Orden, Grafo myGraph) {
    struct dataGrades grados[n];
    for (u32 i = 0; i < n; i++) {
        grados[i].indice = i;
        grados[i].grade = Grado(i, myGraph);
    }

    qsort(grados, n, sizeof(struct dataGrades), compareGrades);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = grados[i].indice;
    }
}
//////////////////////////////////////////////////////////////////////////////////////


void swapArrays(u32 **arr1, u32 **arr2) {
    u32 *temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}

int main() {
    Grafo myGraph = ConstruirGrafo();
    u32 n = NumeroDeVertices(myGraph);
    u32 *Orden = calloc(n, sizeof(u32));
    u32 *Color = calloc(n, sizeof(u32));
    u32 *Color_2 = calloc(n, sizeof(u32));
    u32 elegir = 0;
    u32 minNumCrom = n + 2;

    OrdenNatural(n, Orden);
    u32 numCrom1 = Greedy(myGraph, Orden, Color);

    OrdenWelshPowell(n, Orden, myGraph);
    u32 numCrom2 = Greedy(myGraph, Orden, Color);

    if (numCrom1 < numCrom2) {
        minNumCrom = numCrom1;
        elegir = 1;
    } else {
        minNumCrom = numCrom2;
        elegir = 2;
    }

    OrdenAleatorio(n, Orden);
    u32 numCrom3 = Greedy(myGraph, Orden, Color);

    if (minNumCrom > numCrom3) {
        minNumCrom = numCrom3;
        elegir = 3;
    }

    OrdenNaturalReverse(n, Orden);
    u32 numCrom4 = Greedy(myGraph, Orden, Color);

    if (minNumCrom > numCrom4) {
        minNumCrom = numCrom4;
        elegir = 4;
    }

    // esto lo hago para que el array de colores me quede de la mejor manera para volver a correr
    // greedy en los ordenes por colores
    switch (elegir) {
        case 1:
            OrdenNatural(n, Orden);
            printf("elegi natural\n");
            break;
        case 2:
            OrdenWelshPowell(n, Orden, myGraph);
            printf("elegi welsh\n");
            break;
        case 3:
            OrdenAleatorio(n, Orden);
            printf("elegi aleatorio\n");
            break;
        case 4:
            OrdenNaturalReverse(n, Orden);
            printf("elegi natural reverse\n");
            break;
        default:
            break;
    }

    printf("coloreo orden inicial inicial con %d colores\n", minNumCrom);
    u32 colorGreedy, colorGreedy2;

    for (u32 i = 0; i < 500; i++) {
        //// [1]
        char char_1 = OrdenImparPar(n, Orden, Color);
        colorGreedy = Greedy(myGraph, Orden, Color);
        //// [2]
        char char_2 = OrdenJedi(myGraph, Orden, Color_2);
        colorGreedy2 = Greedy(myGraph, Orden, Color_2);

        if (colorGreedy < colorGreedy2) {
            if (minNumCrom > colorGreedy) {
                minNumCrom = colorGreedy;
            }
        } else {
            if (minNumCrom > colorGreedy2) {
                minNumCrom = colorGreedy2;
            }
        }

        if (i % 16 == 0) {
            swapArrays(&Color, &Color_2);
        }

        if (char_1 == 1 || char_2 == 1) {
            printf("error en OrdenImparPar o OrdenJedi\n");
            break;
        }
    }

    printf("minimo coloreo despues de Jedy y ImparPar: %d\n", minNumCrom);

    free(Orden);
    free(Color);
    free(Color_2);
    Orden = NULL;
    Color = NULL;
    Color_2 = NULL;

    DestruirGrafo(myGraph);
    return 0;
}
