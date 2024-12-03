#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STATIC_FILE "statis.bin"
#define JUMLAH_MEJA 20

typedef struct{
	float omset;
	// STATISTIK LOAD DARI FILE
} Statis;

// ADT UTAMA ---------------------------------------------------------------------------------------------------

// DATA TYPES
typedef char string[100];

typedef struct Child* AddressChild;
typedef struct Parent* AddressParent;

// DATA STRUKTUR UNTUK ITEM PESANAN (CHILD)
typedef struct DataChild {
    string namaItem;
    int jumlah;
    float harga;
    float subtotal;
} DataChild;

// DATA STRUKTUR UNTUK NOTA (PARENT)
typedef struct DataParent {
    int nomorNota;
    string tanggal;
    int nomorMeja;
    float totalPembelian;
    bool status;
} DataParent;

// STRUKTUR NODE CHILD (ITEM PESANAN)
typedef struct Child {
    DataChild dataChild;
    AddressChild next;
} NodeChild;

// STRUKTUR NODE PARENT (NOTA)
typedef struct Parent {
    DataParent dataParent;
    AddressParent next;
    AddressChild firstChild;
    AddressParent merged;  // Pointer untuk nota yang digabungkan
} NodeParent;

// STRUKTUR MULTILIST
typedef struct {
    AddressParent firstParent;
} Multilist;

// DEKLARASI FUNGSI UTAMA
void createEmpty(Multilist *L); // SOURCE.C
bool isEmpty(Multilist L); // SOURCE.C

// DEKLARASI FUNGSI PARENT (NOTA)
DataParent makeDataParent(int nomor, string tanggal, int meja); // SOURCE.C
AddressParent alokasiParent(DataParent data); // SOURCE.C
AddressParent findParent(Multilist L, int nomorNota); // SOURCE.C

void insertFirstParent(Multilist *L, DataParent data); // SOURCE.C
void insertLastParent(Multilist *L, DataParent data); // SOURCE.C
void deleteParent(Multilist *L, int nomorNota); // SOURCE.C

// DEKLARASI FUNGSI CHILD (ITEM PESANAN)
DataChild makeDataChild(string nama, int jumlah, float harga); // SOURCE.C
AddressChild alokasiChild(DataChild data); // SOURCE.C

void insertFirstChild(Multilist L, int nomorNota, DataChild data); // SOURCE.C
void insertLastChild(Multilist L, int nomorNota, DataChild data); // SOURCE.C
void deleteChild(Multilist *L, int nomorNota, string namaItem); // SOURCE.C

// FUNGSI OPERASI NOTA
void mergeNota(Multilist *L, int notaSumber, int notaTujuan); // NOTA.C
void splitNota(Multilist *L, int nomorNota, int jumlahSplit); // NOTA.C
bool prosesPayment(Multilist *L, int nomorNota, float jumlahBayar); // NOTA.C
void updateTotalPembelian(AddressParent nota); // NOTA.C
bool isNotaLunas(AddressParent nota); // NOTA.C
AddressChild findChild(AddressParent nota, string namaItem); // NOTA.C
void moveAllItems(AddressParent source, AddressParent destination); // NOTA.C
void updateNota(Multilist *Kasir, Multilist *Dapur); // NOTA.C

// FUNGSI LAPORAN
void hitungOmzet(Multilist L, float *totalOmzet); // NOTA.C
void cariItemTerlaris(Multilist L); // NOTA.C
void printNota(AddressParent nota); // GENERAL.C
void printAllNota(Multilist L); // GENERAL.C

// FUNGSI BONUS (FILE HANDLING)
void saveToFile(Multilist L); // FILEHANDLER.C
void loadFromFile(Multilist *L, string filename); // FILEHANDLER.C
void saveStatis(Statis *data); // FILEHANDLER.C
void loadStatis(Statis *data); // FILE HANDLER.C

// FUNGSI UI
void logoASCII(); // GENERAL.C
void getLocalTime(int *day, int *month, int *year); // GENERAL.C
void showMenu(char *picker, string user); // GENERAL.C
void showTools(char *picker, string user); // GENERAL.C

// END OF ADT UTAMA ---------------------------------------------------------------------------------------------


// ADT MENU --------------------------------------------------------------------------------------------------
#define FILENAME "nomor_nota.txt"

typedef struct{
    int id;
    string nama;
    float harga;
} Menu;

#define MENU_PESANAN { \
    {1, "Grilled Sandwich", 40900}, \
    {2, "Granola", 36800}, \
    {3, "Croissant", 30100}, \
    {4, "Caesar Salad", 25900}, \
    {5, "Carbonara", 35800}, \
    {6, "Chicken Wings", 40800}, \
    {7, "Signature Fried Rice", 45900}, \
    {8, "Mineral Water", 10500}, \
    {9, "Signature Tea", 30900}, \
    {10, "Oolong Rain Tea", 25900}, \
    {11, "Me-Espresso", 37800}, \
    {12, "Mochalatte", 36900}, \
    {13, "Lattearth", 37900}, \
    {14, "Koomboocha", 32900} \
}

// DECLARASI
int getNomorNota(); // MENU.C
void saveCounter(int counter); // MENU.C
int readCounter(); // MENU.C
void tampilkanMenu(); // MENU.C
void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal); // MENU.C
// END ADT MENU ------------------------------------------------------------------------------------------------

