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
