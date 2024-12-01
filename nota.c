#include "header.h"

void mergeNota(Multilist *L, int notaSumber, int notaTujuan) {

}

void splitNota(Multilist *L, int nomorNota, int jumlahSplit) {

}

bool prosesPayment(Multilist *L, int nomorNota, float jumlahBayar) {

}

void updateTotalPembelian(AddressParent nota) {

}

bool isNotaLunas(AddressParent nota) {

}

AddressChild findChild(AddressParent nota, string namaItem) { // Pesanan

}

void moveAllItems(AddressParent source, AddressParent destination) {

}

void updateNota(Multilist *Kasir, Multilist *Dapur){ // NATAN
	Menu menuMakanan[] = MENU_MAKANAN;
	Menu menuMinuman[] = MENU_MINUMAN;
	float subtotal;
	
    system("cls");
    int nomorNota;
    int ID, jumlah;
    AddressParent alamatUpdate;

    printf("\n\t\t---[ Update Nota ]---\n");
    printf("\n\tNomor Nota yang Diupdate : \n"); scanf("%d", &nomorNota);
    findParent(*Kasir, nomorNota);
    
	if(alamatUpdate == NULL){
		printf("\n Nota Tidak Ditemukan");
		return;
	}
    
    tampilkanMenu(menuMakanan, menuMinuman);
    
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
		
//		insertLastChild((*Kasir), nomorNota, makeDataChild(menuMakanan[ID-1].nama, jumlah, menuMakanan[ID-1].harga * jumlah));
//		insertLastChild((*Dapur), nomorNota, makeDataChild(menuMakanan[ID-1].nama, jumlah, menuMakanan[ID-1].harga * jumlah));
		
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
//		insertLastChild((*Kasir), nomorNota, makeDataChild(menuMinuman[ID-1].nama, jumlah, menuMinuman[ID-1].harga * jumlah));
//		insertLastChild((*Dapur), nomorNota, makeDataChild(menuMinuman[ID-1].nama, jumlah, menuMinuman[ID-1].harga * jumlah));
	
		subtotal += menuMakanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuMinuman[ID-1].nama, jumlah, menuMinuman[ID-1].harga * jumlah);
	} while (1);
	
    // LANJUTAN
}

