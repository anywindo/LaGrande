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
void trimNewline(char *str);
// END ADT LOGIN -----------------------------------------------------------------------------------------------

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void registerUser() {
    printf("\n [PAGE: Registrasi User]\n");
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("\n [>] Enter username: ");
    fflush(stdin); gets(username);
    trimNewline(username);

    printf(" [>] Enter password: ");
    fflush(stdin); gets(password);
    trimNewline(password);

    FILE *file = fopen(DATA_FILE, "a");
    if (file == NULL) {
        printf("\n\t[!] Error opening file!");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("\n\t[+] Sukses menambahkan user!\n");
}

void loginUser() {
    int attempts = 5;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    while (attempts > 0) {
        system("cls");
        printf("\n [PAGE: Login User] - [Attempt: %d]\n", attempts);
        logoASCII();
        printf("\n [>] Masukkan username: "); fflush(stdin); gets(username);
        trimNewline(username);

        printf(" [>] Masukkan password: "); fflush(stdin); gets(password);
        trimNewline(password);

        if (validateCredentials(username, password) && strcmp(username, "admin") == 0) {
            strcpy(userLogged, username);
            adminManagement();
            if(adminAsUser)
                return;
        } else if (validateCredentials(username, password)) {
            strcpy(userLogged, username);
            printf("\n\t[*] Login berhasil! Selamat datang, %s.\n", username);
            return;
        } else {
            printf("\n\t[!] Username atau password salah!\n");
            attempts--;
        }
        getch();
    }

    printf("\n\t[!] Anda telah mencoba login sebanyak 5 kali. Program akan keluar.\n");
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
        printf("\n [PAGE: Admin Management] - [User: admin]\n");
        printf("\n\t--- POS Management ---\n");
        printf("\n [1]. Tampilkan semua user");
        printf("\n [2]. Tambahkan user baru");
        printf("\n [3]. Hapus user\n");
        printf("\n [4]. Admin sebagai kasir");
        printf("\n [0]. Logout\n");
        printf("\n >> "); scanf("%d", &menu);

        switch(menu){
            case 1:
                viewUsers();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                deleteUser();
                break;
            case 4:
                adminAsUser = true;
                return;
            case 0:
                printf("\n\t[*] Exiting admin session...\n");
                break;
            default:
                printf("\n\t[!] Menu tidak ada!");
                break;
        }
        getch();
    } while (menu != 0);
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

    printf("\n [*] Username untuk dihapus: ");
    fflush(stdin); gets(username);
    trimNewline(username);

    FILE *file = fopen(DATA_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("\n\t[!] Error processing request!");
        return;
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
