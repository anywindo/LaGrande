#include "header.h"
#include "login.h"

Statis Stat = {0.0, {0}};

int main(void) {
    // VARS
    Multilist Dapur, Kasir;
	
    // TEMP VARS
    char menu, confirm;
    int day, month, year;

    int nomorNota;
    string tanggal;

    // INIT
    srand(time(NULL));
    getLocalTime(&day, &month, &year);
    sprintf(tanggal, "%02d-%02d-%04d", day, month, year);
    createEmpty(&Dapur);
    createEmpty(&Kasir);
        
    // MAIN PROG
    preBoot();
    
    login:
    loginUser(); // LOGIN
	
	loadStatis(&Stat);
    loadFromFile(&Kasir);
        
    // OUTER LOOP
    do{
    	mainMenu:
    	system("cls");
    	system("color 0F");
        printf("\n [Date: %02d-%02d-%04d]", day,month,year);
        showMenu(&menu, userLogged);
        
        switch (menu) {
        	// POS SYSTEM
        	
            case '1': // PESANAN BARU
                inputPesanan(&Kasir, &Dapur, tanggal);
            break;

			case '2': // UPDATE
            	if(isEmpty(Kasir)){
            		printf("\n\t[!] Nota Kosong");
            		break;
				}
				
				updateNota(&Kasir, &Dapur);
			break;
			
			case '3': // PEMBAYARAN - SELESAI
            	if(isEmpty(Kasir)){
            		printf("\n\t[!] Nota Kosong");
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
				        	if(isEmpty(Kasir)){
			            		printf("\n\t[!] Nota Kosong");
			            		break;
							}
				        	printPilih(Kasir);
				        break;
				        
				        case '2': // PRINT ALL
				        	if(isEmpty(Kasir)){
			            		printf("\n\t[!] Nota Kosong");
			            		break;
							}
				        	printAllNota(Kasir);
				        break;
				        
				        case '3': // GABUNG NOTA
				        	if(isEmpty(Kasir)){
			            		printf("\n\t[!] Nota Kosong");
			            		break;
							}
				        	mergeNota(&Kasir, &Dapur);
				        break;
				        
				        case '4': // SPLIT NOTA
				        	if(isEmpty(Kasir)){
			            		printf("\n\t[!] Nota Kosong");
			            		break;
							}
							
				        break;
					}
					getch();
				} while (menu != '0');
			break;
			
			// MANAGEMENT
			
			case '5': // ANALYSIS
				menuTerjual();
			break;


            // NAVIGATION
        
            default: // IF NOT IN SWITCH
                printf("\n\t[!] Menu tidak tersedia!");
            break;
                
            case '0': // LOGOUT
                printf("\n\t[>] Konfirmasi logout (y/n): "); scanf(" %c", &confirm);
                
                if(confirm == 'y') goto login; // LOGOUT
                else
                    printf("\n\t[*] Batal logout");
            break;
                
            case 'Q': // QUIT
                printf("\n\t[>] Konfirmasi keluar aplikasi (y/n): "); scanf(" %c", &confirm);
                
                if(confirm == 'y'){
                	saveToFile(Kasir);
                	saveToFile(Dapur);
                	saveStatis(&Stat);
					ShutdownMessage();
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
