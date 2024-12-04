#include "header.h"
Menu menuPesanan[] = MENU_PESANAN;

void mergeNota(Multilist *L, Multilist *L2) {
    if (L == NULL || isEmpty(*L)) {
        printf("\n[!] Tidak ada nota untuk digabungkan.\n");
        return;
    }

    int notaSumber, notaTujuan;

    printf("\n [>] Masukkan nomor nota sumber: "); scanf("%d", &notaSumber);
    printf(" [>] Masukkan nomor nota tujuan: "); scanf("%d", &notaTujuan);

    if (notaSumber == notaTujuan) {
        printf("\n [!] Nota sumber dan tujuan tidak boleh sama.\n");
        return;
    }

    AddressParent source = findParent(*L, notaSumber);
    AddressParent destination = findParent(*L, notaTujuan);

    if (source == NULL || destination == NULL) {
        printf("\n [!] Salah satu atau kedua nota tidak ditemukan.\n");
        return;
    }

    moveAllItems(source, destination);

    source->dataParent.status = false;
    source->merged = destination;

	source = findParent(*L2, notaSumber);  
    destination = findParent(*L2, notaTujuan); 
    
    moveAllItems(source, destination);
    
    source->dataParent.status = false;
    source->merged = destination;
    
    printf("\n [+] Nota %d berhasil digabungkan ke Nota %d.\n", notaSumber, notaTujuan);
}


void splitNota(Multilist *L, int nomorNota, int jumlahSplit) {
	
}


void prosesPayment(Multilist *Kasir, Multilist *Dapur) {
    AddressParent alamatNotaKasir,alamatNotaDapur;
    int nomorNota;
    float nominalBayar, kembalian;
    
    system("cls");
	printf("\n\t\t---[ Bayar Nota ]---\n");
	printNotaAktif(*Kasir);
	printf("\n [>] Nomor Nota yang Dibayar : "); scanf("%d", &nomorNota);
    alamatNotaKasir = findParent(*Kasir, nomorNota);
    alamatNotaDapur = findParent(*Dapur, nomorNota);
    
	if(alamatNotaKasir == NULL){
		printf("\n [!] Nota Tidak Ditemukan");
		return;
	}else if(alamatNotaKasir->dataParent.status == false){
		printf("\n [*] Nota Sudah Dibayar");
		return;
	}else{
		printNota(alamatNotaKasir);
		printf("\n\n [+] Grand Total Nota %d: %.2f", nomorNota, alamatNotaKasir->dataParent.totalPembelian);
		printf("\n\n [>] Masukan Nominal Pembayaran : "); scanf("%f", &nominalBayar);
		
		kembalian = nominalBayar - alamatNotaKasir->dataParent.totalPembelian;
		
		if(kembalian <0){
			printf("\n [!] Uang Anda Tidak Cukup");
		}else{
			if(kembalian == 0)
				printf("\n [+] Terimakasih Telah Membayar Dengan Uang Pas" );
			else	
				printf("\n [+] Terimakasih, Kembalian anda adalah : Rp. %.2f", kembalian );
	 		
			Statis stat;
			loadStatis(&stat);
			stat.omset += alamatNotaKasir->dataParent.totalPembelian;
			saveStatis(&stat);
			
			MEJA[alamatNotaKasir->dataParent.nomorMeja-1] = 0;
			alamatNotaKasir->dataParent.status = false;
			alamatNotaDapur->dataParent.status = false;
		}
		
	}
}

void updateTotalPembelian(AddressParent nota) { //natan
	if (nota == NULL) {
        return;
    }

    nota->dataParent.totalPembelian = 0.0f;

    AddressChild currentChild = nota->firstChild;
    
    while (currentChild != NULL) {
        nota->dataParent.totalPembelian += currentChild->dataChild.subtotal;  
        currentChild = currentChild->next;  
    }
}

AddressChild findChild(AddressParent nota, string namaItem) { // Pesanan
	if(nota == NULL)
		return NULL;
	
	AddressChild temp = nota->firstChild;
	
	while(temp != NULL)
	{
		if(strcmpi(temp->dataChild.namaItem, namaItem) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

void moveAllItems(AddressParent source, AddressParent destination) { // ALEX
	if(source == NULL || destination == NULL)
		return;
		
	if(destination->firstChild == NULL)
		destination->firstChild = source->firstChild;
	else
	{
		AddressChild lastChild = destination->firstChild;
		while(lastChild->next != NULL)
			lastChild = lastChild->next;
		lastChild->next = source->firstChild;
	}
	
	source->firstChild = NULL;
	
	updateTotalPembelian(source);
	updateTotalPembelian(destination);
}

void updateNota(Multilist *Kasir, Multilist *Dapur){ // NATAN
	
	Menu menuPesanan[] = MENU_PESANAN;
	float subtotal;
	
    system("cls");
    int nomorNota;
    int ID, jumlah;
    AddressParent alamatNotaKasir,alamatNotaDapur;

    printf("\n\t---[ Update Nota ]---\n");
    printNotaAktif(*Kasir);
    printf("\n [>] Nomor Nota yang Diupdate : "); scanf("%d", &nomorNota);
    alamatNotaKasir = findParent(*Kasir, nomorNota);
    alamatNotaDapur = findParent(*Dapur, nomorNota);
    
	if(alamatNotaKasir == NULL || alamatNotaKasir->dataParent.status == false){
		printf("\n [!] Nota Tidak Ditemukan");
		return;
	}
	
    tampilkanMenu();
    
    printf("\n\n [>>]-[ Order ]--- [0 untuk lanjut]\n");
    do{
		inputPesanan:
		printf("\n [>] Pilih ID: "); scanf("%d", &ID);
		
		if(ID > 14 || ID < 1)
		{
			if(ID == 0) break;
			
			printf(" [!] ID tidak tersedia\n");
			getch();
			goto inputPesanan;
		}
		
		printf(" [>] Jumlah: "); scanf("%d", &jumlah);
		if(jumlah < 1) 
		{
			printf(" [!] Jumlah harus lebih dari 0.");
			goto inputPesanan;
		}
		
		Stat.ID[ID-1] += 1;
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		
		subtotal += menuPesanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah);
	} while (1);
	updateTotalPembelian( alamatNotaKasir);
	updateTotalPembelian( alamatNotaDapur);
	
    printf("\n [*] Subtotal: Rp%.2f", subtotal);
	printf("\n [*] Grand Total untuk Nota %d: Rp%.2f\n", alamatNotaKasir->dataParent.nomorNota, alamatNotaKasir->dataParent.totalPembelian);
	printf("\n [+] Nota %d sudah diupdate.", nomorNota);
	
}



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
    
    if(isMEJAFull(MEJA)){
    	printf("\n\t[!] Meja penuh.");
    	return;
	}
	
    int nomorMeja = rand() % JUMLAH_MEJA;
    
	while(!isMEJAEmpty(MEJA[nomorMeja])){
    	nomorMeja = (rand() % JUMLAH_MEJA);
	}
	
	MEJA[nomorMeja] = 1;
	nomorMeja += 1;
    
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
		if(jumlah < 1) 
		{
			printf(" [!] Jumlah harus lebih dari 0.\n");
			goto inputPesanan;
		}
		
		Stat.ID[ID-1] += 1;
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		
		subtotal += menuPesanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah);
	} while (1);
	
	printf("\n [*] Subtotal: Rp%.2f", subtotal);
	printf("\n [+] Nota %d sudah dimasukkan untuk diproses di dapur.\n", nomorNota);
	
	updateTotalPembelian( alamatNotaKasir);
	updateTotalPembelian( alamatNotaDapur);
}
