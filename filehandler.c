#include "header.h"

void saveToFile(Multilist L) {
	
}

void loadFromFile(Multilist *L) {
	
}

void saveStatis(Statis *data) {
    FILE *file = fopen(STATIC_FILE, "wb");
    if (file == NULL) {
        printf("\n [!] ERROR: Unable to open file.");
        return;
    }
    fwrite(data, sizeof(Statis), 1, file);
    fclose(file);
}

void loadStatis(Statis *data) {
    FILE *file = fopen(STATIC_FILE, "rb");
    if (file == NULL) {
        printf("\n [!] Tidak ada data tersimpan. Mulai dari awal.\n");
        data->omset = 0.0f;
        return;
    }
    fread(data, sizeof(Statis), 1, file);
    fclose(file);
}

int readCounter()
{
    FILE *file = fopen(FILENAME, "r");
    int counter = 0;

    if (file == NULL)
    {
        counter = 0;
    }
    else
    {
        fscanf(file, "%d", &counter);
        fclose(file);
    }

    return counter;
}

void saveCounter(int counter)
{
    FILE *file = fopen(FILENAME, "w");

    if (file == NULL)
    {
        printf("\n [!] Error: Unable to open file for writing.\n");
        exit(1);
    }

    fprintf(file, "%d", counter);
    fclose(file);
}

int getNomorNota()
{
    int counter = readCounter();
    counter++;
    saveCounter(counter);
    return counter;
}
