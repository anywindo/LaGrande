#include "header.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

void saveToFile(Multilist L) {
    AddressParent nota;
    string fileName;

    #ifdef _WIN32
    if (CreateDirectory("nota", NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {}
    #else
        mkdir("nota", 0755);
    #endif

    snprintf(fileName, sizeof(fileName), "nota/Nota_Meja%.2d.txt", nota->dataParent.nomorNota);

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("[!] ERROR: Unable to open file.");
        return;
    }

    fprintf(file, "ISI DISINI");
    // SETERUSNYA

    fclose(file);
}

void loadFromFile(Multilist *L, string filename){

}