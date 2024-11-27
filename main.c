#include "header.h"
#include "login.h"

int main(void) {
    // VARS
    Multilist L;

    // TEMP VARS
    char menu, confirm;

    // MAIN PROG
    login:
    loginUser();

    do{
        showMenu(&menu, userLogged);

        switch (menu) {
            default:
                printf("\n\t[!] Menu tidak tersedia!");
                break;

            case '0':
                printf("\n [>] Konfirmasi logout (y/n): "); getchar(); confirm = getchar();
                if(confirm == 'y')
                    goto login;
                else
                    printf("\n\t[*] Batal logout");
                break;
        }
        getchar();
    } while (1);
    return 0;
}