#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STATIC_FILE "statis.bin"
//#define NOTA_FILE "nota.bin"
#define JUMLAH_MEJA 20
#define FILENAME "nomor_nota.txt"

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

typedef char string[100];

extern int MEJA[20];

typedef struct{
	float omset;
	int ID[14];
} Statis;

typedef struct{
    int id;
    string nama;
    float harga;
} Menu;

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
    AddressParent merged;
} NodeParent;

// STRUKTUR MULTILIST
typedef struct {
    AddressParent firstParent;
} Multilist;

// SOURCE.C
void createEmpty(Multilist *L); 
bool isEmpty(Multilist L); 
DataParent makeDataParent(int nomor, string tanggal, int meja); 
AddressParent alokasiParent(DataParent data); 
AddressParent findParent(Multilist L, int nomorNota); 
void insertFirstParent(Multilist *L, DataParent data); 
void insertLastParent(Multilist *L, DataParent data); 
void deleteParent(Multilist *L, int nomorNota); 
DataChild makeDataChild(string nama, int jumlah, float harga); 
AddressChild alokasiChild(DataChild data); 
void insertFirstChild(Multilist L, int nomorNota, DataChild data); 
void insertLastChild(Multilist L, int nomorNota, DataChild data); 
void deleteChild(Multilist *L, int nomorNota, string namaItem); 

// NOTA.C
void mergeNota(Multilist *L, Multilist *L2); 
void splitNota(Multilist *L, int nomorNota, int jumlahSplit); 
void prosesPayment(Multilist *Kasir, Multilist *Dapur); 
void updateTotalPembelian(AddressParent nota); 
AddressChild findChild(AddressParent nota, string namaItem); 
void moveAllItems(AddressParent source, AddressParent destination); 
void updateNota(Multilist *Kasir, Multilist *Dapur); 

// FUNGSI LAPORAN
void cariItemTerlaris(Multilist L); 

// GENERAL.C
void printNota(AddressParent nota);
void printAllNota(Multilist L); 
void printNotaAktif(Multilist Nota); 
void printPilih(Multilist Nota);
void logoASCII(); 
void getLocalTime(int *day, int *month, int *year); 
void showMenu(char *picker, string user); 
void showTools(char *picker, string user); 
void color(string cname); 
void printMEJA(); 
bool isMEJAFull(int MEJA[]); 
bool isMEJAEmpty(int MEJA); 
int getNomorNota(); 
void saveCounter(int counter); 
int readCounter(); 
void tampilkanMenu(); 
void inputPesanan(Multilist *Kasir, Multilist *Dapur, string tanggal);
void preBoot();
void drawProgressBar(int current, int total, int width);

// FILEHANDLER.C
void saveToFile(Multilist L);
void loadFromFile(Multilist *L); 
void saveStatis(Statis *data);
void loadStatis(Statis *data);

