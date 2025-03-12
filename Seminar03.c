#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr Usi: %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume Sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
    for (int i = 0; i < nrMasini; i++) {
        afisareMasina(masini[i]);
    }
}

void adaugaMasinaInVector(Masina** masini, int *nrMasini, Masina masinaNoua) {
    Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
    for (int i = 0; i < *nrMasini; i++) {
        aux[i] = (*masini)[i];
    }
    aux[*nrMasini] = masinaNoua;
    *nrMasini = *nrMasini + 1;
    free(*masini);
    *masini = aux;
}

Masina citireMasinaFisier(FILE* file) {
    char buffer[100];
    fgets(buffer, 100, file);
    Masina masina;
    const char sep[3] = ",\n";
    char *aux;
    masina.id = atoi(strtok(buffer, sep));
    masina.nrUsi = atoi(strtok(NULL, sep));
    masina.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    masina.model = malloc(strlen(aux) + 1);
    strcpy(masina.model, aux);
    aux = strtok(NULL, sep);
    masina.numeSofer = malloc(strlen(aux) + 1);
    strcpy(masina.numeSofer, aux);
    masina.serie = *(strtok(NULL, sep));
    return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
    FILE* file = fopen(numeFisier, "r");
    Masina* masini = NULL;
    do {
        adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
    } while (!feof(file));
    fclose(file);
    return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
    for (int i = 0; i < *nrMasini; i++) {
        free((*vector)[i].model);
        free((*vector)[i].numeSofer);
    }
    free(*vector);
    *vector = NULL;
    *nrMasini = 0;
}

float pretMediuDupaUsi(Masina* vector, int nrMasini, int nrUsi) {
    float suma = 0;
    int index = 0;
    for (int i = 0; i < nrMasini; i++) {
        if (vector[i].nrUsi == nrUsi) {
            suma += vector[i].pret;
            index++;
        }
    }
    if (index > 0) {
        return suma / index;
    }

    return 0;
}

int main() {

    Masina* masini = NULL;
    int nrMasini = 0;
    masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
    afisareVectorMasini(masini, nrMasini);
    dezalocareVectorMasini(&masini, &nrMasini);

    return 0;
}
