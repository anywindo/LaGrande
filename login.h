#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ADT LOGIN ---------------------------------------------------------------------------------------------------
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define DATA_FILE "userdata.txt"

char userLogged[MAX_USERNAME];
bool adminAsUser = false;

void registerUser();
void loginUser();
void adminManagement();
void viewUsers();
void deleteUser();
int validateCredentials(char *username, char *password);
void console();
void firstBoot();
bool isEmptyUserdata();

// END ADT LOGIN -----------------------------------------------------------------------------------------------
void registerUser() {
    printf("\n [PAGE: Registrasi User]\n");
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME];
    char filePassword[MAX_PASSWORD];

    printf("\n [>] Enter username: ");
    fflush(stdin);
    gets(username);

    printf(" [>] Enter password: ");
    fflush(stdin);
    gets(password);

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("\n\t[!] Error opening file for checking!\n");
        return;
    }

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            fclose(file);
            printf("\n\t[!] Username '%s' sudah terdaftar. Tidak dapat menambahkan user yang sama.\n", username);
            return;
        }
    }
    fclose(file);

    file = fopen(DATA_FILE, "a");
    if (file == NULL) {
        printf("\n\t[!] Error opening file for writing!\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("\n\t[+] Sukses menambahkan user!\n");
}


void loginUser() {
	system("cls"); firstBoot();
    int attempts = 5;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
	
    while (attempts > 0) {
        system("cls"); system("color 0F");
        printf("\n\t [PAGE: Login User] - [Attempt: %d]\n", attempts);
        logoASCII();
        gotoxy(0,3);
        printf("\n\t ---[ System Login ]---\n");
        printf("\n\t [>] Masukkan username: "); fflush(stdin); gets(username);

        printf("\t [>] Masukkan password: "); fflush(stdin); gets(password);

        if (validateCredentials(username, password) && strcmp(username, "admin") == 0) {
            strcpy(userLogged, username);
            adminManagement();
            if(adminAsUser)
                return;
        } else if (validateCredentials(username, password)) {
            strcpy(userLogged, username);
            system("color 20");
            printf("\n\t [*] Login berhasil! Selamat datang, %s.\n", username);
            Sleep(500);
            return;
        } else {
        	system("color 4F");
            printf("\n\t [!] Username atau password salah!\n");
            attempts--;
        }
        getch();
    }

	system("color 4F");
    printf("\n\t [!] Anda telah mencoba login sebanyak 5 kali. Program akan keluar.\n");
    system("color 0F");
    ShutdownMessage();
    exit(0);
}

int validateCredentials(char *username, char *password) {
    char fileUsername[MAX_USERNAME];
    char filePassword[MAX_PASSWORD];

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("\n\t[!] Error opening file!\n");
        return 0;
    }
		
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void adminManagement(){
    int menu;

    do {
        system("cls");
        system("color 1F");
        printf("\n [PAGE: Admin Management] - [User: admin]\n");
        printf("\n\t--- POS Management ---\n");
        printf("\n [1]. Tampilkan semua user");
        printf("\n [2]. Tambahkan user baru");
        printf("\n [3]. Hapus user");
        printf("\n [4]. Hapus data tersimpan\n");
        printf("\n [5]. Admin sebagai kasir");
        printf("\n [6]. System Console\n");
        printf("\n [0]. Logout\n");
        printf("\n >> "); scanf("%d", &menu);

        switch(menu){
            case 1:
            	if(isEmptyUserdata()){
            		printf("\n [!] Tidak ada data di userdata! lakukan first boot terlebih dahulu!");
            		break;
				}
                viewUsers();
                break;
            case 2:
            	if(isEmptyUserdata()){
            		printf("\n [!] Tidak ada data di userdata! lakukan first boot terlebih dahulu!");
            		break;
				}
                registerUser();
                break;
            case 3:
            	if(isEmptyUserdata()){
            		printf("\n [!] Tidak ada data di userdata! lakukan first boot terlebih dahulu!");
            		break;
				}
                deleteUser();
                break;
            case 4:
            	if(isEmptyUserdata()){
            		printf("\n [!] Tidak ada data di userdata! lakukan first boot terlebih dahulu!");
            		break;
				}
            	printf("\n\t[?] Apakah Anda ingin menghapus data tersimpan?\n\t[*] Data ini meliputi nota.bin dan statis.bin\n\n\t[>] Konfirmasi (y/n): ");
            	char confirm; scanf(" %c", &confirm);
				
				if(confirm == 'y' || confirm == 'Y')
				{
					resetNota();
					resetStatis();
				}
				else
					printf("\n\t[*] Tidak jadi delete data.");
            	break;
            case 5:
            	if(isEmptyUserdata()){
            		printf("\n [!] Tidak ada data di userdata! lakukan first boot terlebih dahulu!");
            		break;
				}
                adminAsUser = true;
                return;
            case 6:
            	if(isEmptyUserdata()){
            		printf("\n [!] Tidak ada data di userdata! lakukan first boot terlebih dahulu!");
            		break;
				}
            	console();
            	break;
            case 0:
            	if(isEmptyUserdata())
            	{
			        printf("\n\t[!] No users found in userdata.txt.");
			        printf("\n\t[*] Exiting admin session...");
			        exit(1);
			    }
                printf("\n\t[*] Exiting admin session..."); Sleep(50);
				printf("\n\t[>] Press again to exit as admin.");
                break;
            default:
                printf("\n\t[!] Menu tidak ada!");
                break;
        }
        if(menu != 0) getch();
    } while (menu != 0);
    return;
}

void viewUsers() {
    printf("\n [PAGE: Tampil User]\n");
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("\n\t[!] User tidak ditemukan");
        return;
    }

    while (fscanf(file, "%s %s", username, password) != EOF)
        printf("\n- Username: %s", username);

    fclose(file);
}

void deleteUser() {
    printf("\n [PAGE: Delete User]\n");
    char username[MAX_USERNAME];
    char fileUsername[MAX_USERNAME];
    char filePassword[MAX_PASSWORD];
    int found = 0;

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("\n\t[!] Error opening user data file!\n");
        return;
    }

    printf("\n- Daftar User:\n");
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        printf("- %s\n", fileUsername);
    }
    fclose(file);

    printf("\n [*] Username untuk dihapus: ");
    fflush(stdin);
    gets(username);

    file = fopen(DATA_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("\n\t[!] Error processing request!\n");
        return;
    }

    if (strcmpi(username, "admin") == 0) {
        char confirmation;
        printf("\n [*] Anda memilih untuk menghapus semua data pengguna. Apakah Anda yakin? (y/n): ");
        fflush(stdin);
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') 
        {
            fclose(file);
            fclose(tempFile);

            tempFile = fopen(DATA_FILE, "w");
            if (tempFile != NULL) {
                fclose(tempFile);
            }
            resetNota();
            resetStatis();
            printf("\n\t[-] Semua user dan data telah dihapus. \n\t[*] Konfigurasi first boot akan dijalankan di sesi selanjutnya.\n");
            return;
        } 
        else 
        {
            fclose(file);
            fclose(tempFile);
            printf("\n\t[!] Operasi dibatalkan.\n");
            return;
        }
    }

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
            found = 1;
        else
            fprintf(tempFile, "%s %s\n", fileUsername, filePassword);
    }

    fclose(file);
    fclose(tempFile);

    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    if (found)
        printf("\n\t[-] User '%s' telah dihapus.\n", username);
    else
        printf("\n\t[!] User '%s' tidak ditemukan!", username);
}

void console(){
	char input[200];
	system("cls");
	system("color 0F");
	
	con:
	printf("\n\t[#] System Console - [type 'exit' to end session]\n");
	do{
		printf("\nadmin@LaGrande > ");
		fflush(stdin); gets(input);
		
		if(strcmpi(input, "exit") == 0)
		break;
		
		system(input);
		
		if(strcmpi(input, "cls") == 0)
		goto con;
	} while (1);
	printf("\nadmin@LaGrande > Press again to exit console session.");
}

void firstBoot() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL || fgetc(file) == EOF) {
        fclose(file);
        char adminPassword[MAX_PASSWORD];
		
        printf("\n [!] No users found in the system. Creating default 'admin' user.");
        printf("\n [>] Enter password for 'admin': ");
        fflush(stdin); gets(adminPassword);

        file = fopen(DATA_FILE, "w");
        if (file == NULL) {
            printf("\n [!] Error creating user data file.");
            exit(1);
        }

        fprintf(file, "admin %s\n", adminPassword);
        fclose(file);

        printf("\n [*] Default 'admin' user created successfully.\n");
    } else {
        fclose(file);
    }
}

bool isEmptyUserdata()
{
    FILE *file = fopen("userdata.txt", "r");
    if(file == NULL)
    {
        printf("\n\t[!] Error: Could not open userdata.txt.");
        exit(2);
    }

    string buffer;
    if(fscanf(file, "%s", buffer) == EOF)
    {
        fclose(file);
        return true;
    }

    fclose(file);
    return false;
}
