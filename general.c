#include "header.h"
#define TABLE_COUNT 20

void showMenu(char *picker, string user) { // ALEX	
    printf("\n [User: %s]\n", user);
    logoASCII();
	
	printf("\n\t\t---[ Meja Tersedia ]---\n");
	printMEJA();
	
    printf("\n\t\t---[ Point-of-Sales ]---\n");
    printf("\n\t[1]. Pesanan Baru");
    printf("\n\t[2]. Update Nota");
    printf("\n\t[3]. Pembayaran Nota");
    printf("\n\t[4]. Tools Nota\n");
    printf("\n\t\t---[ Management Tools ]---\n");
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
        printf("\n\t-------------------------------------------------------\n");
        printf("\tNo.%03d        *** Nota Pembelian ***      %s\n", nota->dataParent.nomorNota, nota->dataParent.status ? "        Aktif" : "Sudah Dibayar");
        printf("\t-------------------------------------------------------\n");
        printf("\n\tTanggal          : %s", nota->dataParent.tanggal);
        printf("\n\tStatus           : %s", nota->dataParent.status ? "Aktif" : "Sudah Dibayar");
        printf("\n\tNomor Nota       : %03d", nota->dataParent.nomorNota);
        printf("\n\tNomor Meja       : %d", nota->dataParent.nomorMeja);
        printf("\n\n\t\t      -- Rincian Pembelian --\n");

        AddressChild currentChild = nota->firstChild;
        while (currentChild != NULL) {
            printf("\n\tNama Item        : %s", currentChild->dataChild.namaItem);
            printf("\n\tJumlah           : %d", currentChild->dataChild.jumlah);
            printf("\n\tHarga            : Rp%.2f", currentChild->dataChild.harga);
            printf("\n\tSubtotal         : Rp%.2f\n", currentChild->dataChild.subtotal);
            currentChild = currentChild->next;
        }

        printf("\n\n\tTotal Pembelian  : Rp%-10.2f", nota->dataParent.totalPembelian);
        
        printf("\n\t-------------------------------------------------------\n");

    } else {
        printf("\n [!] Tidak ada nota yang tersedia.\n");
    }
}

void printAllNota(Multilist L) {
    AddressParent current = L.firstParent;
    if (current == NULL) {
        printf("\n [!] Tidak ada nota yang tersedia.\n");
        return;
    }

    while (current != NULL) {
	    printNota(current);
        current = current->next;
    }
}

void printNotaAktif(Multilist Nota){
	AddressParent current = Nota.firstParent;
    
	printf("\n\t [*] Nota Aktif: ");   
	 
    if (current == NULL){
		printf("Tidak ada nota.");
        return;
	}
        
    while (current != NULL) {
	    if(current->dataParent.status)
			printf("[%03d] ", current->dataParent.nomorNota);
        current = current->next;
    }
    printf("\n");
}

void printPilih(Multilist Nota){
	int nomorNota;
	
	printNotaAktif(Nota);
	
	printf("\n\t[>] Nomor Nota: "); scanf("%d", &nomorNota);
	AddressParent parent = findParent(Nota, nomorNota);
	
	if(parent == NULL){
		printf("\n\t[!] Nota tidak ditemukan.");
		return;
	}
	
	printNota(parent);
}

void logoASCII() { // ALEX
	printf("\n");
    printf("\t\t\t\t       .-.                  .-.                       .      \n");
    printf("\t\t\t\t      / (_)          .--.`-'                         /       \n");
    printf("\t\t\t\t     /      .-.     /  (_;    ).--..-.  .  .-.  .-../   .-.  \n");
    printf("\t\t\t\t    /      (  |    /         /    (  |   )/   )(   /  ./.-'_ \n");
    printf("\t\t\t\t .-/.    .-.`-'-' (     --;-/      `-'-''/   (  `-'-..(__.'  \n");
    printf("\t\t\t\t(_/ `-._.          `.___.'                    `-              \n\n");
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

void color(string cname){
	if (strcmpi(cname, "black") == 0) {
	        printf("\033[0;30m");  // Black text
    }
    else if (strcmpi(cname, "red") == 0) {
        printf("\033[0;31m");  // Red text
    }
    else if (strcmpi(cname, "green") == 0) {
        printf("\033[0;32m");  // Green text
    }
    else if (strcmpi(cname, "yellow") == 0) {
        printf("\033[0;33m");  // Yellow text
    }
    else if (strcmpi(cname, "blue") == 0) {
        printf("\033[0;34m");  // Blue text
    }
    else if (strcmpi(cname, "magenta") == 0) {
        printf("\033[0;35m");  // Magenta text
    }
    else if (strcmpi(cname, "cyan") == 0) {
        printf("\033[0;36m");  // Cyan text
    }
    else if (strcmpi(cname, "white") == 0) {
        printf("\033[0;37m");  // White text
    }
    else if (strcmpi(cname, "bblack") == 0) {
        printf("\033[1;30m");  // Bright black (gray)
    }
    else if (strcmpi(cname, "brightred") == 0) {
        printf("\033[1;31m");  // Bright red text
    }
    else if (strcmpi(cname, "bgreen") == 0) {
        printf("\033[1;32m");  // Bright green text
    }
    else if (strcmpi(cname, "byellow") == 0) {
        printf("\033[1;33m");  // Bright yellow text
    }
    else if (strcmpi(cname, "bblue") == 0) {
        printf("\033[1;34m");  // Bright blue text
    }
    else if (strcmpi(cname, "bmagenta") == 0) {
        printf("\033[1;35m");  // Bright magenta text
    }
    else if (strcmpi(cname, "bcyan") == 0) {
        printf("\033[1;36m");  // Bright cyan text
    }
    else if (strcmpi(cname, "bwhite") == 0) {
        printf("\033[1;37m");  // Bright white text
    }
    else {
        printf("\033[0m");
    }
}

int MEJA[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool isMEJAEmpty(int MEJA){
	return MEJA == 0;
}

bool isMEJAFull(int MEJA[]){
	int i;
	
	for(i = 0; i < JUMLAH_MEJA; i++)
	{
		MEJA[i] == 0;
		return false;
	}
	return true;
}

void printMEJA() {
    int i, j;
	
	printf("\n\t");
    for(i = 0; i < 4; i++) 
	{    
        for(j = 0; j < 5; j++) 
		{
            int index = i * 5 + j;
            
            if(MEJA[index] == 0)
            {
            	color("green");
                printf("[ %02d ]\t", index + 1); 
            	color("reset");
			}
            else
            {            	
            	color("red");
                printf("[ XX ]\t"); 
            	color("reset");
			}
        }
        printf("\n\t");
    }
    printf("\n");
}

void drawProgressBar(int current, int total, int width) {
    printf("\033[48;5;4m");
    printf("\033[38;5;15m");
    int i, progress = (current * width) / total;

    printf("\033[38;5;15m[");
    for (i = 0; i < width; i++) {
        if (i < progress) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("]");
    fflush(stdout);
}

void preBoot() {
    system("cls");
    printf("\033[48;5;4m");
    printf("\033[38;5;15m");

    int width = 120;
    int height = 30;
    int progressBarWidth = 50;
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("#");
            } else if (i >= height / 2 - 6 && i <= height / 2 + 5 &&
                       j >= width / 4 && j <= 3 * width / 4) {
                if (i == height / 2 - 6 || i == height / 2 + 5 ||
                    j == width / 4 || j == 3 * width / 4) {
                    printf("*");
                } else if (i == height / 2 - 4 && j == (width - strlen("La Grande PreBoot Requirements")) / 2) {
                    printf("\033[38;5;15mLa Grande PreBoot Requirements");
                    j += strlen("La Grande PreBoot Requirements") - 1;
                } else if (i == height / 2 - 2 && j == (width - strlen("Pastikan berkas berikut untuk penyimpanan berkas")) / 2) {
                    printf("Pastikan berkas berikut untuk penyimpanan berkas");
                    j += strlen("Pastikan berkas berikut untuk penyimpanan berkas") - 1;
                } else if (i == height / 2 - 1 && j == (width - strlen("terdapat tepat dalam satu direktori dari executable!")) / 2) {
                    printf("terdapat tepat dalam satu direktori dari executable!");
                    j += strlen("terdapat tepat dalam satu direktori dari executable!") - 1;
                } else if (i == height / 2 + 1 && j == (width - strlen("[File: userdata.txt, nomor_nota.txt, dan statis.bin]")) / 2) {
                    printf("[File: userdata.txt, nomor_nota.txt, dan statis.bin]");
                    j += strlen("[File: userdata.txt, nomor_nota.txt, dan statis.bin]") - 1;
                } else if (i == height / 2 + 3 && j == (width - strlen("Copyright La Grande")) / 2) {
                    printf("Copyright La Grande");
                    j += strlen("Copyright La Grande") - 1;
                } else if (i == height / 2 + 4 && j == (width - strlen("ISD C - 230712: 423 - 428 - 440 - 555")) / 2) {
                    printf("ISD C - 230712: 423 - 428 - 440 - 555");
                    j += strlen("ISD C - 230712: 423 - 428 - 440 - 555") - 1;
                } else if (i == height / 2 + 6 && j == (width - progressBarWidth) / 2) {
                    printf("\033[38;5;15m");
                    drawProgressBar(0, 100, progressBarWidth);
                    j += progressBarWidth - 1;
                } else {
                    printf(" ");
                }
            } else {
                printf(" ");
            }
        }
    }


    for (i = 0; i <= 100; i += 5) {
        printf("\033[%d;%dH", height / 2 + 7, (width - progressBarWidth) / 2);
        drawProgressBar(i, 100, progressBarWidth);
        Sleep(100);
    }

    printf("\033[0m");
}

void ShutdownMessage() {
    printf("\033[38;5;15m");

    string messages[] = {
        "\n[  OK      ] Initializing system components and verifying core modules to ensure a stable shutdown process...",
        "[  OK      ] Loading essential drivers and checking module dependencies for optimal system operation...",
        "[  OK      ] Verifying hardware configurations and performing a pre-shutdown diagnostic check...",
        "[  OK      ] Checking disk integrity and performing a quick scan to detect potential file system issues...",
        "[  OK      ] Mounting essential file systems and synchronizing data to ensure no data loss...",
        "[  WARNING ] /dev/sr1 is write-protected, mounting read-only to avoid accidental data modification...",
        "[  OK      ] Mounted file systems successfully. All required directories are now accessible...",
        "[  INFO    ] Initiating safe shutdown sequence to minimize system impact and ensure power-down...",
        "[  INFO    ] Running final checks on the memory and active processes to avoid potential issues...",
        "[  OK      ] Deleting unnecessary system files to optimize shutdown process...",
        "[  WARNING ] Deleting system32...",
        "[  ERROR   ] Unable to delete system32 due to lack of permissions. File protection mechanisms in place...",
        "[  OK      ] Proceeding with shutdown sequence. Powering down hardware components...",
        "[  INFO    ] Closing active connections and preparing network interfaces for system shutdown...",
        "[  OK      ] Preparing for final power-off. All services are now safely stopped and unregistered...",
        "[  OK      ] Powering down system. No further operations will be possible after this point. Goodbye!"
    };

    int numMessages = sizeof(messages) / sizeof(messages[0]);
	int i;
    for (i = 0; i < numMessages; i++) {
        int delay = 50 + (rand() % 200); 
        if (i == 5) {
            printf("\033[38;5;11m%s\n", messages[i]); 
        } else if (i == 10) {
            printf("\033[38;5;9m%s\n", messages[i]); 
        } else if (i == 11) {
            printf("\033[38;5;15m%s\n", messages[i]);
        } else {
            printf("\033[38;5;10m%s\n", messages[i]); 
        }
        Sleep(delay); 
    }

    printf("\033[0m");
}
