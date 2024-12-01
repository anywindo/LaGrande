#ifndef LAGRANDE_INPUT_H
#define LAGRANDE_INPUT_H
#include "header.h"
#define FILENAME "nomor_nota.txt"

typedef struct{
    int id;
    string nama;
    float harga;
} Menu;

Menu makanan[] = {
        {1, "Grilled Sandwich", 40900},
        {2, "Granola", 36800},
        {3, "Croissant", 30100},
        {4, "Caesar Salad", 25900},
        {5, "Carbonara", 35800},
        {6, "Chicken Wings", 40800},
        {7, "Signature Fried Rice", 45900}
};

Menu minuman[] = {
        {1, "Mineral Water", 10500},
        {2, "Signature Tea", 30900},
        {3, "Oolong Rain Tea", 25900},
        {4, "Me-Espresso", 37800},
        {5, "Mochalatte", 36900},
        {6, "Lattearth", 37900},
        {7, "Koomboocha", 32900}
};

// DECLARE
int getNomorNota();
void saveCounter(int counter);
int readCounter();
void tampilkanMenu(Menu menu[], Menu minuman[]);
void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal);

void tampilkanMenu(Menu makanan[], Menu minuman[]) {
    int i;
    
    printf("\n =======================================================================================\n");
    printf("| %-3s | %-20s | %-8s |    \t| %-3s | %-20s | %-8s |\n", 
           "ID", "Nama Makanan", "Harga", "ID", "Nama Minuman", "Harga");
    printf(" ---------------------------------------------------------------------------------------\n");
    for (i = 0; i < 7; i++) {
        printf("| %-3d | %-20s | Rp%-6d |    \t| %-3d | %-20s | Rp%-6d |\n", 
               makanan[i].id, makanan[i].nama, makanan[i].harga, 
               minuman[i].id, minuman[i].nama, minuman[i].harga);
    }
    printf(" =======================================================================================\n\n");
}


void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal){
	int ID, jumlah;
    int nomorNota = getNomorNota();
    int nomorMeja = rand() % 50; // BELOM NUNGGU PUTRI BUAT MEJA
	
    system("cls");
    printf("\n [Date: %s]\n", tanggal);
    tampilkanMenu(makanan, minuman);
    
    printf("\n\t\t---[ Pesanan Baru ]---\n");
    
    printf("\n [Nomor:\t %03d]", nomorNota);
    printf("\n [Meja:\t %03d]", nomorMeja);
    
    insertLastParent(&(*Kasir), makeDataParent(nomorNota, tanggal, nomorMeja));
    insertLastParent(&(*Dapur), makeDataParent(nomorNota, tanggal, nomorMeja));
	
	printf("\n\t\t---[ Makanan ]--- [0 untuk lanjut minuman]\n");
	do{
		printf("\n [*] Pilih ID: "); scanf("%d", &ID);
		if(ID == 0) break;
		printf(" [*] Jumlah: "); scanf("%d", &jumlah);
		insertLastChild((*Kasir), nomorNota, makeDataChild(makanan[ID-1].nama, jumlah, makanan[ID-1].harga));
		insertLastChild((*Dapur), nomorNota, makeDataChild(makanan[ID-1].nama, jumlah, makanan[ID-1].harga));
	} while (1);
    
    printf("\n\t\t[][ Minuman ]--- [0 untuk keluar lanjut]\n");
	do{
		printf("\n [*] Pilih ID: "); scanf("%d", &ID);
		if(ID == 0) break;
		printf(" [*] Jumlah: "); scanf("%d", &jumlah);
		insertLastChild((*Kasir), nomorNota, makeDataChild(minuman[ID-1].nama, jumlah, minuman[ID-1].harga));
		insertLastChild((*Dapur), nomorNota, makeDataChild(minuman[ID-1].nama, jumlah, minuman[ID-1].harga));
	} while (1);
	
	printf("\n[+] Nota %d sudah dimasukkan untuk diproses di dapur.", nomorNota);
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
