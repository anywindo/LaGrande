#include "header.h"
#define TABLE_COUNT 20

void showMenu(char *picker, string user) { // ALEX
	int activeTables[TABLE_COUNT] = {0};
	int i,j;
	
    printf("\n [User: %s]\n", user);
    logoASCII();
    
    printf("\n\t\t\t\t---[ Meja La Grande ]---\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            int tableIndex = i * 5 + j; 
            printf("\t");
            printf("+---------+  ");
        }
        printf("\n");
        for (j = 0; j < 5; j++) {
            int tableIndex = i * 5 + j;
            printf("\t");
            printf("| Meja %02d |  ", tableIndex + 1);
        }
        printf("\n");
        for (j = 0; j < 5; j++) {
            printf("\t");
            printf("+---------+  ");
        }
        printf("\n\n");
    }

    printf("\n\t\t---[ La Grande Restaurant POS System ]---\n");
    printf("\n\t[1]. Pesanan Baru");
    printf("\n\t[2]. Update Nota");
    printf("\n\t[3]. Pembayaran Nota");
    printf("\n\t[4]. Tools Nota\n");
    printf("\n\t\t---[ La Grande Management Tools ]---\n");
    printf("\n\t[5]. Penghasilan");
    printf("\n\t[6]. Data Analyst\n");
    printf("\n\t\t---[ System ]---\n");
    printf("\n\t[0]. Logout dari %s", user);
    printf("\n\t[Q]. Keluar aplikasi\n");
    printf("\n\t>> "); scanf(" %c", picker);
}

void showTools(char *picker, string user) { // ALEX
	printf("\n [User: %s]\n", user);
	logoASCII();
	
	printf("\n\t\t---[ Tools ]---\n");
	printf("\n\t[1]. Cari Nota");
    printf("\n\t[2]. Lihat Semua Nota");
    printf("\n\t[3]. Gabung Nota");
    printf("\n\t[4]. Split Nota");
    printf("\n\t[0]. Kembali\n");
    printf("\n\t>> "); scanf(" %c", picker);
}

void printNota(AddressParent nota) {
    if (nota != NULL) {
        printf("\n\tNomor Nota: %03d", nota->dataParent.nomorNota);
        printf("\n\tTanggal: %s", nota->dataParent.tanggal);
        printf("\n\tNomor Meja: %d", nota->dataParent.nomorMeja);
        printf("\n\tTotal Pembelian: Rp%.2f\n", nota->dataParent.totalPembelian);
        
        AddressChild currentChild = nota->firstChild;
        while (currentChild != NULL) {
            printf("\n\t\tNama Item: %s", currentChild->dataChild.namaItem);
            printf("\n\t\tJumlah: %d", currentChild->dataChild.jumlah);
            printf("\n\t\tHarga: Rp%.2f", currentChild->dataChild.harga);
            printf("\n\t\tSubtotal: Rp%.2f\n", currentChild->dataChild.subtotal);
            currentChild = currentChild->next;
        }
    } else {
        printf("\n\tNota tidak ditemukan!\n");
    }
}

void printAllNota(Multilist L) {
    AddressParent current = L.firstParent;
    if (current == NULL) {
        printf("\n [!] Tidak ada nota yang tersedia.\n");
        return;
    }

    while (current != NULL) {
//    	if(current->dataParent.status)
    	{
	        printNota(current);
        }

        current = current->next;
    }
}

void logoASCII() { // ALEX
    printf("       .-.                  .-.                       .      \n");
    printf("      / (_)          .--.`-'                         /       \n");
    printf("     /      .-.     /  (_;    ).--..-.  .  .-.  .-../   .-.  \n");
    printf("    /      (  |    /         /    (  |   )/   )(   /  ./.-'_ \n");
    printf(" .-/.    .-.`-'-' (     --;-/      `-'-''/   (  `-'-..(__.'  \n");
    printf("(_/ `-._.          `.___.'                    `-              \n");
}

void getLocalTime(int *day, int *month, int *year){ // ALEX
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    *day = localTime->tm_mday;
    *month = localTime->tm_mon + 1;
    *year = localTime->tm_year + 1900;
}
