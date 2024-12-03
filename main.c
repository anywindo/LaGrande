#include "header.h"
#include "login.h"

int main(void) {
    // VARS
    Multilist Dapur, Kasir;
    Statis Stat;
	
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
    loadFromFile(&Kasir);
    loadStatis(&Stat);
    
    // MAIN PROG
    login:
    loginUser(); // LOGIN

    // OUTER LOOP
    do{
    	mainMenu:
    	system("cls");
        printf("\n [Date: %02d-%02d-%04d]", day,month,year);
        showMenu(&menu, userLogged);
        
        switch (menu) {
        	// POS SYSTEM
        	
            case '1': // PESANAN BARU
                inputPesanan(&Kasir, &Dapur, tanggal);
            break;

			case '2': // UPDATE
            	if(isEmpty(Kasir)){
            		printf("\n [!] Nota Kosong");
            		break;
				}
				
				updateNota(&Kasir, &Dapur);
			break;
			
			case '3': // PEMBAYARAN - SELESAI
            	if(isEmpty(Kasir)){
            		printf("\n [!] Nota Kosong");
            		break;
				}
				
				prosesPayment(&Kasir, &Dapur);
			break;

			case '4': // TOOLS - SHOW MERGE SPLIT ETC
				do{
	            	system("cls");
	            	printf("\n [Date: %02d-%02d-%04d]", day,month,year);
	            	showTools(&menu, userLogged);
	            	
	            	switch (menu) {
				    	default:
				            printf("\n\t[!] Menu tidak tersedia!");
				        break;
				        
				        case '0':
				        	goto mainMenu;
				        break;
				        
				        case '1': // PRINT ONE
				        	
				        break;
				        
				        case '2': // PRINT ALL
				        	printAllNota(Kasir);
				        break;
				        
				        case '3': // GABUNG NOTA
				        	saveToFile(Kasir);
				        break;
				        
				        case '4': // SPLIT NOTA
				        	saveToFile(Kasir);
				        break;
					}
					getch();
				} while (menu != '0');
			break;
			
			// MANAGEMENT
			
			case '5': // PENGHASILAN
				loadStatis(&Stat);
				printf("\n\t[*] Pengahasilan: Rp%.2f", Stat.omset);
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
                
                if(confirm == 'y'){
                	saveToFile(Kasir);
                	exit(0);
				}
                else
                    printf("\n\t[*] Batal keluar");
            break;
        }
    	getch();
    } while (1);
    return 0;
}
