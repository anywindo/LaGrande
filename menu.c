#include "header.h"

Menu menuPesanan[] = MENU_PESANAN;

void tampilkanMenu() { // ALEX
    int i;
    Menu menuPesanan[] = MENU_PESANAN;
    
    printf("\n =======================================================================================\n");
    printf("| %-3s | %-20s | %-8s |    \t| %-3s | %-20s | %-8s |\n", 
           "ID", "Nama Makanan", "Harga", "ID", "Nama Minuman", "Harga");
    printf(" ---------------------------------------------------------------------------------------\n");
    for (i = 0; i < 7; i++) {
        printf("| %-3d | %-20s | Rp%.0f |    \t| %-3d | %-20s | Rp%.0f |\n", 
               menuPesanan[i].id, menuPesanan[i].nama, menuPesanan[i].harga, 
               menuPesanan[i+7].id, menuPesanan[i+7].nama, menuPesanan[i+7].harga);
    }
    printf(" =======================================================================================\n\n");
}

void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal){ // ALEX
	int ID, jumlah;
	float subtotal = 0;
    int nomorNota = getNomorNota();
    
    bool meja[JUMLAH_MEJA] = {false};
    int nomorMeja = (rand() % JUMLAH_MEJA) + 1;
    
	AddressParent alamatNotaKasir,alamatNotaDapur;
    alamatNotaKasir = findParent(*Kasir, nomorNota);
    alamatNotaDapur = findParent(*Dapur, nomorNota);
    
    system("cls");
    printf("\n [Date: %s]\n", tanggal);
    tampilkanMenu();
    
    printf("\n\t\t---[ Pesanan Baru ]---\n");
    
    printf("\n [Nomor : %03d]", nomorNota);
    printf("\n [Meja  : %03d]\n", nomorMeja);
    
    insertLastParent(&(*Kasir), makeDataParent(nomorNota, tanggal, nomorMeja));
    insertLastParent(&(*Dapur), makeDataParent(nomorNota, tanggal, nomorMeja));
	
	printf("\n\n [>>]-[ Order ]--- [0 untuk lanjut]\n");
	do{
		inputPesanan:
		printf("\n [*] Pilih ID: "); scanf("%d", &ID);
		
		if(ID > 14 || ID < 1)
		{
			if(ID == 0) break;
			
			printf(" [!] ID tidak tersedia\n");
			getch();
			goto inputPesanan;
		}
		
		printf(" [*] Jumlah: "); scanf("%d", &jumlah);
		
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah));
		
		subtotal += menuPesanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah);
	} while (1);
    
	
	printf("\n [*] Subtotal: Rp%.2f", subtotal);
	printf("\n [+] Nota %d sudah dimasukkan untuk diproses di dapur.\n", nomorNota);
	
	updateTotalPembelian( alamatNotaKasir);
	updateTotalPembelian( alamatNotaDapur);
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

