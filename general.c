#include "header.h"

void showMenu(char *picker, string user) {
    printf("\n [User: %s]\n", user);
    printf("\n >> "); *picker = getchar();
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