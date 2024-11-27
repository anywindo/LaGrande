#include "header.h"
#include "login.h"

int main(void) {
    // VARS
    Multilist L;

    // TEMP VARS
    char menu, confirm;

    // MAIN PROG
    login:
    loginUser(); // LOGIN

    // OUTER LOOP
    do{
        showMenu(&menu, userLogged);

        switch (menu) {
            default: // IF NOT IN SWITCH
                printf("\n\t[!] Menu tidak tersedia!");
                break;
            case '0': // LOGOUT
                printf("\n\t[>] Konfirmasi logout (y/n): "); getchar(); confirm = getchar();
                if(confirm == 'y') goto login; // LOGOUT
                else
                    printf("\n\t[*] Batal logout");
                break;
            case 'Q': // QUIT
                printf("\n\t[>] Konfirmasi keluar aplikasi (y/n): "); getchar(); confirm = getchar();
                if(confirm == 'y') exit(1);
                else
                    printf("\n\t[*] Batal logout");
                break;
        }
        getchar();
    } while (1);
    return 0;
}