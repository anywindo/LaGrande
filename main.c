#include "header.h"
#include "login.h"
#include "input.h"

int main(void) {
    // VARS
    Multilist Dapur, Kasir;

    // TEMP VARS
    char menu, confirm;
    int day, month, year;

    int nomorNota;
    string tanggal;

    // INIT
    getLocalTime(&day, &month, &year);
    sprintf(tanggal, "%02d-%02d-%04d", day, month, year);
    createEmpty(&Dapur);
    createEmpty(&Kasir);

    // MAIN PROG
    login:
    loginUser(); // LOGIN

    // OUTER LOOP
    do{
    	system("cls");
        printf("\n [Date: %02d-%02d-%04d]", day,month,year);
        showMenu(&menu, userLogged);
        
        switch (menu) {
        	// POS SYSTEM
        	
            case '1': // PESANAN BARU
                inputPesanan(&Kasir, &Dapur, tanggal); // masih belom jadi;
            break;

			case '2': // UPDATE
            
			break;

			case '3': // PEMBAYARAN - SELESAI
            
			break;

			case '4': // TOOLS - MERGE SPLIT
            
			break;
			
			// MANAGEMENT
			
			case '5': // PENGHASILAN
				
			break;
			
			case '6': // ANALYSIS
				
			break;

            // NAVIGATION
        
            default: // IF NOT IN SWITCH
                printf("\n\t[!] Menu tidak tersedia!");
            break;
                
            case '0': // LOGOUT
                printf("\n\t[>] Konfirmasi logout (y/n): "); confirm = getch();
                
                if(confirm == 'y') goto login; // LOGOUT
                else
                    printf("\n\t[*] Batal logout");
            break;
                
            case 'Q': // QUIT
                printf("\n\t[>] Konfirmasi keluar aplikasi (y/n): "); confirm = getch();
                
                if(confirm == 'y') exit(1);
                else
                    printf("\n\t[*] Batal keluar");
            break;
        }
    	getch();
    } while (1);
    return 0;
}
