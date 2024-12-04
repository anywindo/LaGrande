#include "header.h"

void saveToFile(Multilist list)
{
    FILE* file = fopen(NOTA_FILE, "wb");
    if (!file) {
        printf("Error membuka file untuk menulis (biner).\n");
        return;
    }

    fwrite(MEJA, sizeof(int), 20, file);

    AddressParent parent = list.firstParent;
    while (parent != NULL) {
        fwrite(&parent->dataParent, sizeof(DataParent), 1, file);

        AddressChild child = parent->firstChild;
        int childCount = 0;
        while (child != NULL) {
            childCount++;
            child = child->next;
        }

        fwrite(&childCount, sizeof(int), 1, file);

        child = parent->firstChild;
        while (child != NULL) {
            fwrite(&child->dataChild, sizeof(DataChild), 1, file);
            child = child->next;
        }

        parent = parent->next;
    }

    fclose(file);
    printf("\n[*] Data berhasil disimpan ke file %s.\n", NOTA_FILE);
}

void loadFromFile(Multilist* list)
{
    FILE* file = fopen(NOTA_FILE, "rb");
    if (!file) {
        printf("\n [!] Error membuka file %s untuk membaca (biner).\n", NOTA_FILE);
        return;
    }

    // Muat data array MEJA
    fread(MEJA, sizeof(int), 20, file);

    // Muat data multilist
    list->firstParent = NULL;
    AddressParent lastParent = NULL;

    while (1) {
        // Baca data parent
        AddressParent newParent = (AddressParent)malloc(sizeof(NodeParent));
        if (fread(&newParent->dataParent, sizeof(DataParent), 1, file) != 1) {
            free(newParent);
            break; // End of file
        }

        newParent->firstChild = NULL;
        newParent->next = NULL;

        if (list->firstParent == NULL) {
            list->firstParent = newParent;
        } else {
            lastParent->next = newParent;
        }
        lastParent = newParent;

        // Baca jumlah child
        int childCount;
        fread(&childCount, sizeof(int), 1, file);

        // Baca data child
        int i;
        AddressChild lastChild = NULL;
        for (i = 0; i < childCount; i++) {
            AddressChild newChild = (AddressChild)malloc(sizeof(NodeChild));
            fread(&newChild->dataChild, sizeof(DataChild), 1, file);
            newChild->next = NULL;

            if (lastChild == NULL) {
                newParent->firstChild = newChild;
            } else {
                lastChild->next = newChild;
            }
            lastChild = newChild;
        }
    }

    fclose(file);
    printf("Data berhasil dimuat dari file biner %s.\n", NOTA_FILE);
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
