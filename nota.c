#include "header.h"
Menu menuPesanan[] = MENU_PESANAN;

void mergeNota(Multilist *L, Multilist *L2) {
    if (L == NULL || isEmpty(*L)) {
        printf("\n[!] Tidak ada nota untuk digabungkan.\n");
        return;
    }
	
	system("cls");
	printf("\n\t\t---[ Gabung Nota ]---\n");
    int notaSumber, notaTujuan;
	printNotaAktif(*L);
    printf("\n\t[>] Masukkan nomor nota sumber: "); scanf("%d", &notaSumber);
    printf("\t[>] Masukkan nomor nota tujuan: "); scanf("%d", &notaTujuan);

    if (notaSumber == notaTujuan) {
        printf("\n\t[!] Nota sumber dan tujuan tidak boleh sama.\n");
        return;
    }

    AddressParent source = findParent(*L, notaSumber);
    AddressParent destination = findParent(*L, notaTujuan);

    if (source == NULL || destination == NULL) {
        printf("\n\t[!] Salah satu atau kedua nota tidak ditemukan.\n");
        return;
    }

    moveAllItems(source, destination);

    source->dataParent.status = false;
    source->merged = destination;

	source = findParent(*L2, notaSumber);  
    destination = findParent(*L2, notaTujuan); 
   
    moveAllItems(source, destination);

	deleteParent(&(*L), notaSumber);
	deleteParent(&(*L2), notaSumber);
    
    printf("\n\t[+] Nota %d berhasil digabungkan ke Nota %d.\n", notaSumber, notaTujuan);
}

void splitNota(Multilist *L, Multilist *L2) {//NATAN
	int nomorNota, id, count=0, jmlItem;
	AddressParent alamatNotaKasir,alamatNotaDapur, alamatNotaPisah, cetak, temp;
	AddressChild item, itemPisah;
	string namaItem;
	
	if (L == NULL || isEmpty(*L)) {
        printf("\n[!] Tidak ada nota untuk dipisah.\n");
        return;
	}
	printNotaAktif(*L);
    printf("\n\t Input Nomor Nota yang Akan Dipisah : "); scanf("%d", &nomorNota);
    alamatNotaPisah = findParent(*L, nomorNota);
    alamatNotaKasir = findParent(*L, nomorNota);
    
    // eror hendling klo null
    if (alamatNotaPisah == NULL  ) {
    printf("\n [!] Nomor nota yang hendak dipisah tidak ditemukan.\n");
    return;
	}
    
    
		int noNota = getNomorNota();
//insertLastParent(&(*L),makeDataParent(noNota,alamatNotaPisah->dataParent.tanggal,alamatNotaPisah->dataParent.nomorMeja));
		insertLastParent(&(*L),makeDataParent(noNota,alamatNotaPisah->dataParent.tanggal,alamatNotaPisah->dataParent.nomorMeja));
		insertLastParent(&(*L2),makeDataParent(noNota,alamatNotaPisah->dataParent.tanggal,alamatNotaPisah->dataParent.nomorMeja));
		
	do{	
		// ini cek jmlh anak di parent, jadi klo 1 doang menu dan makannya g bs split
		count=0;
	    AddressChild currentChild = alamatNotaPisah->firstChild;
	    while (currentChild != NULL) {
	        count++;  
	        currentChild = currentChild->next;  
	    }
		system("cls");
		printf("\n\t\t---[ Pisah Nota ]---\n");
		printNota(alamatNotaPisah);
		printf("\n\t[Exit = 0]");	
	
		input:
	    printf("\n\tInput nama item yang hendak dipisah		: ");fflush(stdin);gets(namaItem); // input nama item
	    if(strcmpi (namaItem,"0")==0) {
	    	printf("\n\tKeluar...");
	    	break;
		}
		
	    item = findChild( alamatNotaPisah, namaItem);
	    if (item == NULL){
	    	printf("\n\t\t[!] Item Tidak Ditemukan");
	    	goto input;
		}
		if (count == 1 && item->dataChild.jumlah == 1 ) {
		    printf("\n\t\t[!] Nomor nota yang hendak dipisah hanya memiliki 1 jumlah item.");
		    printf("\n\t\t[!] Silahkan tekan 0 untuk keluar.\n");
		    goto input;
		}
	    printf("\tJumlah '%s' yang hendak dipindah	: ", item->dataChild.namaItem);scanf("%d", &jmlItem); // input jumlah dari item
	    
	    if(count ==1 && jmlItem>= item->dataChild.jumlah){
	    	printf("\n\t\t[!] Jumlah item di nota original tidak boleh kosong.\n");   	
		    goto input;
		}
		if(jmlItem< 1){
	    	printf("\n\t\t[!] Jumlah yang ingin dipindah tidak boleh 0.\n");
		    goto input;
		}
		if(item->dataChild.jumlah - jmlItem <0){
	    	printf("\n\t\t[!] Jumlah yang ingin dipindah melebihi jumlah item.\n");
		    goto input;
		}
	

		// jadi initu biar ga duplikat atau multiple child untuk menu makanan yang sama
		temp = findParent(*L, noNota); 
		currentChild = temp->firstChild;
		
		int found = 0; //klo ketemu nanti jd 1
		while (currentChild != NULL) {
		    if (strcmpi(currentChild->dataChild.namaItem, namaItem) == 0) {
		        currentChild->dataChild.jumlah += jmlItem;
		        found = 1;
		        break;
		    }
		    currentChild = currentChild->next;
		}
	
		if (found==0) { //Klo masi 0 brati antara ga ketemu, atau emg blm punya child, jadi kita bikin child
		    insertFirstChild(*L, noNota, makeDataChild(namaItem, jmlItem, item->dataChild.harga));
		}


//insertFirstChild(*L2, noNota, makeDataChild(item->dataChild.namaItem,jmlItem,item->dataChild.harga));

		// ini bagian kurangi jumlah item, dan klo item nya ilang brati delete dullu sblm tulis data ke nota
		item = findChild( alamatNotaKasir, namaItem); //cari item yg dipisah didalam nota kasir asli
	
//itemPisah = findChild( alamatNotaKasir, namaItem); //cari item yg dipisah didalam nota kasir asli
		item->dataChild.jumlah -= jmlItem;// kurangin jmlh nya
	
//itemPisah->dataChild.jumlah -= jmlItem;// kurangin jmlh nya
		if(alamatNotaPisah->firstChild->dataChild.jumlah <= 0){
			deleteChild(&(*L), alamatNotaKasir->dataParent.nomorNota, namaItem);// klo 0 brati apus child nya
		}
		
//item = findChild( alamatNotaDapur, namaItem);
//item->dataChild.jumlah -= jmlItem;//cari item yg dipisah didalam nota dapur asli
//if(item->dataChild.jumlah==0) deleteChild(&(*L2), nomorNota, namaItem);

		//mengubah variabel alamat nota kasir dan dapur untuk megang address dari nota split yg dibuat
		alamatNotaKasir = findParent(*L, alamatNotaPisah->dataParent.nomorNota);
		
//alamatNotaDapur = findParent(*L2, alamatNotaPisah->dataParent.nomorNota);

		//mengisi data child nota asli kasir dan dapur dengan data alamat nota pisah
		alamatNotaKasir->firstChild->dataChild = alamatNotaPisah->firstChild->dataChild;
		
//alamatNotaDapur->firstChild->dataChild = alamatNotaPisah->firstChild->dataChild;

		
		updateTotalPembelian( alamatNotaKasir);
		cetak = findParent(*L, noNota);
//updateTotalPembelian( alamatNotaDapur);
		
	    printf("\n\t\t [+] Nota Berhasil dipisah");fflush(stdin);gets(namaItem);// input nama item ini biar ga lgsg ilang aja
		
		
	}while(1);
	printf("\n\t[!] Berikut adalah nota baru anda : ");
	printNota(cetak);
	return;
}

void prosesPayment(Multilist *Kasir, Multilist *Dapur) {
    AddressParent alamatNotaKasir,alamatNotaDapur;
    int nomorNota;
    float nominalBayar, kembalian;
    
    system("cls");
	printf("\n\t\t---[ Bayar Nota ]---\n");
	printNotaAktif(*Kasir);
	printf("\n\t[>] Nomor Nota yang Dibayar : "); scanf("%d", &nomorNota);
    alamatNotaKasir = findParent(*Kasir, nomorNota);
    alamatNotaDapur = findParent(*Dapur, nomorNota);
    
	if(alamatNotaKasir == NULL){
		printf("\n\t[!] Nota Tidak Ditemukan");
		return;
	}else if(alamatNotaKasir->dataParent.status == false){
		printf("\n\t[*] Nota Sudah Dibayar");
		return;
	}else{
		printNota(alamatNotaKasir);
		printf("\n\n\t[+] Grand Total Nota %d: %.2f", nomorNota, alamatNotaKasir->dataParent.totalPembelian);
		printf("\n\n\t[>] Masukan Nominal Pembayaran : "); scanf("%f", &nominalBayar);
		
		kembalian = nominalBayar - alamatNotaKasir->dataParent.totalPembelian;
		
		if(kembalian <0){
			printf("\n\t[!] Uang Anda Tidak Cukup");
		}else{
			if(kembalian == 0)
				printf("\n\t[+] Terimakasih Telah Membayar Dengan Uang Pas" );
			else	
				printf("\n\t[+] Terimakasih, Kembalian anda adalah : Rp. %.2f", kembalian );
	 		
			Statis stat;
			loadStatis(&stat);
			stat.omset += alamatNotaKasir->dataParent.totalPembelian;
			saveStatis(&stat);
			
			MEJA[alamatNotaKasir->dataParent.nomorMeja-1] = 0;
			alamatNotaKasir->dataParent.status = false;
//			alamatNotaDapur->dataParent.status = false;
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

    printf("\n\t\t---[ Update Nota ]---\n");
    printNotaAktif(*Kasir);
    printf("\n\t[>] Nomor Nota yang Diupdate : "); scanf("%d", &nomorNota);
    alamatNotaKasir = findParent(*Kasir, nomorNota);
    alamatNotaDapur = findParent(*Dapur, nomorNota);
    
	if(alamatNotaKasir == NULL || alamatNotaKasir->dataParent.status == false){
		printf("\n\t[!] Nota Tidak Ditemukan");
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
			printf(" [!] Jumlah harus lebih dari 0.\n");
			goto inputPesanan;
		}
		
		Stat.ID[ID-1] += jumlah;
		saveStatis(&Stat);
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		
		subtotal += menuPesanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah);
	} while (1);
	updateTotalPembelian( alamatNotaKasir);
	updateTotalPembelian( alamatNotaDapur);
	
    printf("\n [*] Subtotal                  \t: Rp%.2f", subtotal);
	printf("\n [*] Grand Total untuk Nota %d \t: Rp%.2f\n", alamatNotaKasir->dataParent.nomorNota, alamatNotaKasir->dataParent.totalPembelian);
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
		
		Stat.ID[ID-1] += jumlah;
		saveStatis(&Stat);
		insertLastChild((*Kasir), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		insertLastChild((*Dapur), nomorNota, makeDataChild(menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga));
		
		subtotal += menuPesanan[ID-1].harga * jumlah;
		printf(" [*] Selected '%s' * %d = Rp%.2f\n", menuPesanan[ID-1].nama, jumlah, menuPesanan[ID-1].harga * jumlah);
	} while (1);
	
	if(subtotal == 0)
	{
		deleteParent(&(*Kasir), nomorNota);
		deleteParent(&(*Dapur), nomorNota);
		MEJA[nomorMeja-1] = 0;
		printf("\n [!] Membatalkan pesanan.");
		return;
	}
	
	printf("\n [*] Subtotal : Rp%.2f", subtotal);
	printf("\n [+] Nota %d sudah dimasukkan untuk diproses di dapur.\n", nomorNota);
	
	updateTotalPembelian( alamatNotaKasir);
	updateTotalPembelian( alamatNotaDapur);
}
