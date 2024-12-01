#include "header.h"

void showMenu(char *picker, string user) { // ALEX
    printf("\n [User: %s]\n", user);
    logoASCII();
    printf("\n\t\t---[ La Grande Restaurant POS System ]---\n");
    printf("\n\t[1]. Pesanan Baru");
    printf("\n\t[2]. Update Nota");
    printf("\n\t[3]. Pembayaran Nota");
    printf("\n\t[4]. Tools Nota\n");
    printf("\n\t\t---[ La Grande Management Tools ]---\n");
    printf("\n\t[5]. Penghasilan");
    printf("\n\t[6]. Data Analyst\n");
    printf("\n\t\t---[ System ]---\n");
    printf("\n\t[0]. Logout dari %s", user);
    printf("\n\t[Q]. Keluar aplikasi\n");
    printf("\n\t>> "); scanf(" %c", picker);
}

void printNota(AddressParent nota) {
	
}

void printAllNota(Multilist L) {

}

void logoASCII() { // ALEX
    printf("       .-.                  .-.                       .      \n");
    printf("      / (_)          .--.`-'                         /       \n");
    printf("     /      .-.     /  (_;    ).--..-.  .  .-.  .-../   .-.  \n");
    printf("    /      (  |    /         /    (  |   )/   )(   /  ./.-'_ \n");
    printf(" .-/.    .-.`-'-' (     --;-/      `-'-''/   (  `-'-..(__.'  \n");
    printf("(_/ `-._.          `.___.'                    `-              \n");
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
