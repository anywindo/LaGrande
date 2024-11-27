#include "header.h"

void showMenu(char *picker, string user) {
    printf("\n [User: %s]\n", user);
    logoASCII();
    printf("\n\t\t---[ La Grande Restaurant POS System ]---\n");
    printf("\n\t[]. ");
    printf("\n\t[]. ");
    printf("\n\t[]. ");
    printf("\n\t[]. ");
    printf("\n\t[]. \n");
    printf("\n\t[0]. Logout dari %s", user);
    printf("\n\t[Q]. Keluar aplikasi\n");
    printf("\n\t>> "); *picker = getchar();
}

void printNota(AddressParent nota) {

}

void printAllNota(Multilist L) {

}

void logoASCII() {
    printf("       .-.                  .-.                       .      \n");
    printf("      / (_)          .--.`-'                         /       \n");
    printf("     /      .-.     /  (_;    ).--..-.  .  .-.  .-../   .-.  \n");
    printf("    /      (  |    /         /    (  |   )/   )(   /  ./.-'_ \n");
    printf(" .-/.    .-.`-'-' (     --;-/      `-'-''/   (  `-'-..(__.'  \n");
    printf("(_/ `-._.          `.___.'                    `-              \n");
}