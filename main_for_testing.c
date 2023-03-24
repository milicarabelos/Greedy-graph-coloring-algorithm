#include <stdio.h>
#include <string.h>

#include "APIG23.h"
#include "EstructuraGrafo23.h"

int main() {
    FILE *fp;

    fp = fopen("R22_93_15.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }
    // Aca tengo que llamar a Construir Grafo mandandole el fp
    fclose(fp);
    return 0;
}
