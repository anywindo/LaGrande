#include "header.h"

Menu menuMakanan[] = MENU_MAKANAN;
Menu menuMinuman[] = MENU_MINUMAN;

void tampilkanMenu() { // ALEX
    int i;
    Menu menuMakanan[] = MENU_MAKANAN;
	Menu menuMinuman[] = MENU_MINUMAN;
    
    printf("\n =======================================================================================\n");
    printf("| %-3s | %-20s | %-8s |    \t| %-3s | %-20s | %-8s |\n", 
           "ID", "Nama menuMakanan", "Harga", "ID", "Nama menuMinuman", "Harga");
    printf(" ---------------------------------------------------------------------------------------\n");
    for (i = 0; i < 7; i++) {
        printf("| %-3d | %-20s | Rp%.0f |    \t| %-3d | %-20s | Rp%.0f |\n", 
               menuMakanan[i].id, menuMakanan[i].nama, menuMakanan[i].harga, 
               menuMinuman[i].id, menuMinuman[i].nama, menuMinuman[i].harga);
    }
    printf(" =======================================================================================\n\n");
}

void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal){ // ALEX
	int ID, jumlah;
	float subtotal = 0;
    int nomorNota = getNomorNota();
    int nomorMeja = rand() % 50; // BELOM NUNGGU PUTRI BUAT MEJA
	
    system("cls");
    printf("\n [Date: %s]\n", tanggal);
    tampilkanMenu(menuMakanan, menuMinuman);
    
    printf("\n\t\t---[ Pesanan Baru ]---\n");
    
    printf("\n [Nomor : %03d]", nomorNota);
    printf("\n [Meja  : %03d]\n", nomorMeja);
    
    insertLastParent(&(*Kasir), makeDataParent(nomorNota, tanggal, nomorMeja));
    insertLastParent(&(*Dapur), makeDataParent(nomorNota, tanggal, nomorMeja));
	
	printf("\n\n [#A]-[ menuMakanan ]--- [0 untuk lanjut]\n");
	do{
		inputmenuMakanan:
		printf("\n [*] Pilih ID: "); scanf("%d", &ID);
		
		if(ID > 7 || ID < 1)
		{
			if(ID == 0) break;
			
			printf(" [!] ID tidak tersedia\n");
			getch();
			goto inputmenuMakanan;
		}
		
		printf(" [*] Jumlah: "); scanf("%d", &jumlah);
		
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuMakanan[ID-1].nama, jumlah, menuMakanan[ID-1].harga * jumlah));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuMakanan[ID-1].nama, jumlah, menuMakanan[ID-1].harga * jumlah));
		
		subtotal += menuMakanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuMakanan[ID-1].nama, jumlah, menuMakanan[ID-1].harga * jumlah);
	} while (1);
    
    printf("\n\n [#B]-[ menuMinuman ]--- [0 untuk lanjut]\n");
	do{
		inputmenuMinuman:
		printf("\n [*] Pilih ID: "); scanf("%d", &ID);
		
		if(ID > 7 || ID < 1)
		{
			if(ID == 0) break;
			
			printf(" [!] ID tidak tersedia\n");
			getch();
			goto inputmenuMinuman;
		}
		
		printf(" [*] Jumlah: "); scanf("%d", &jumlah);
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuMinuman[ID-1].nama, jumlah, menuMinuman[ID-1].harga * jumlah));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuMinuman[ID-1].nama, jumlah, menuMinuman[ID-1].harga * jumlah));
	
		subtotal += menuMakanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuMinuman[ID-1].nama, jumlah, menuMinuman[ID-1].harga * jumlah);
	} while (1);
	
	printf("\n [*] Subtotal: Rp%.2f", subtotal);
	printf("\n [+] Nota %d sudah dimasukkan untuk diproses di dapur.", nomorNota);
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

