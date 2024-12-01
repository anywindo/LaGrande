//
// Created by Arwindo Pratama on 27/11/24.
//

#ifndef LAGRANDE_INPUT_H
#define LAGRANDE_INPUT_H
#include "header.h"
#define FILENAME "nomor_nota.txt"

typedef struct{
    int id;
    string nama;
    int harga;
} Menu;

// Daftar menu makanan
Menu makanan[] = {
        {1, "Grilled Sandwich", 40900},
        {2, "Granola", 36800},
        {3, "Croissant", 30100},
        {4, "Caesar Salad", 25900},
        {5, "Carbonara", 35800},
        {6, "Chicken Wings", 40800},
        {7, "Signature Fried Rice", 45900}
};

// Daftar menu minuman
Menu minuman[] = {
        {1, "Mineral Water", 10500},
        {2, "Signature Tea", 30900},
        {3, "Oolong Rain Tea", 25900},
        {4, "Me-Espresso", 37800},
        {5, "Mochalatte", 36900},
        {6, "Lattearth", 37900}
};

// DECLARE
int getNomorNota();
void saveCounter(int counter);
int readCounter();
void tampilkanMenu(Menu menu[], char *kategori, int n);
void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal);

void tampilkanMenu(Menu menu[], char *kategori, int n)
{
	int i;
	
    printf("\n\t=========================================\n");
    printf("\t           Menu %-10s          \n", kategori);
    printf("\t=========================================\n");
    printf("\t| %-3s | %-20s | %-8s |\n", "ID", "Nama", "Harga");
    printf("\t-----------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("\t| %-3d | %-20s | Rp%-6d |\n", menu[i].id, menu[i].nama, menu[i].harga);
    }
    printf("\t=========================================\n\n");
}

void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal){
    system("cls");
    printf("\n [Date: %s]\n", tanggal);
    printf("\n\t\t---[ Pesanan Baru ]---\n");
    int nomorNota = getNomorNota();
    int nomorMeja = rand() % 50; // BELOM
    printf("\n [No. %03d]", nomorNota);
    printf("\n [Meja %02d]", nomorMeja);

    
    insertLastParent(&(*Kasir), makeDataParent(nomorNota, tanggal, nomorMeja));
    insertLastParent(&(*Dapur), makeDataParent(nomorNota, tanggal, nomorMeja));
    // CAPEK
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
        printf("Error: Unable to open file for writing.\n");
        exit(1);
    }

    fprintf(file, "%d", counter); // Save the updated counter value
    fclose(file);
}

int getNomorNota()
{
    int counter = readCounter();
    counter++;
    saveCounter(counter);
    return counter;
}
#endif //LAGRANDE_INPUT_H
