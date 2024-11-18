//
// Created by Arwindo Pratama on 18/11/24.
//

#ifndef LAGRANDE_HEADER_H
#define LAGRANDE_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void createEmpty(Multilist *L); // MODIFICATION.C
bool isEmpty(Multilist L); // MODIFICATION.C
void showMenu(int *picker); // GENERAL.C

// DEKLARASI FUNGSI PARENT (NOTA)
DataParent makeDataParent(int nomor, string tanggal, int meja); // MODIFICATION.C
AddressParent alokasiParent(DataParent data); // MODIFICATION.C
AddressParent findParent(Multilist L, int nomorNota); // MODIFICATION.C

void insertFirstParent(Multilist *L, DataParent data); // MODIFICATION.C
void insertLastParent(Multilist *L, DataParent data); // MODIFICATION.C
void deleteParent(Multilist *L, int nomorNota); // MODIFICATION.C

// DEKLARASI FUNGSI CHILD (ITEM PESANAN)
DataChild makeDataChild(string nama, int jumlah, float harga); // MODIFICATION.C
AddressChild alokasiChild(DataChild data); // MODIFICATION.C

void insertFirstChild(Multilist L, int nomorNota, DataChild data); // MODIFICATION.C
void insertLastChild(Multilist L, int nomorNota, DataChild data); // MODIFICATION.C
void deleteChild(Multilist *L, int nomorNota, string namaItem); // MODIFICATION.C

// FUNGSI OPERASI NOTA
void mergeNota(Multilist *L, int notaSumber, int notaTujuan); // NOTA.C
void splitNota(Multilist *L, int nomorNota, int jumlahSplit); // NOTA.C
bool prosesPayment(Multilist *L, int nomorNota, float jumlahBayar); // NOTA.C

// FUNGSI LAPORAN
void hitungOmzet(Multilist L, float *totalOmzet); // HELPER.C
void cariItemTerlaris(Multilist L); // HELPER.C
void printNota(AddressParent nota); // GENERAL.C
void printAllNota(Multilist L); // GENERAL.C

// FUNGSI BONUS (FILE HANDLING)
void saveToFile(Multilist L, string filename); // FILEHANDLER.C
void loadFromFile(Multilist *L, string filename); // FILEHANDLER.C

// FUNGSI HELPER
void updateTotalPembelian(AddressParent nota); // HELPER.C
bool isNotaLunas(AddressParent nota); // HELPER.C
AddressChild findChild(AddressParent nota, string namaItem); // HELPER.C
void moveAllItems(AddressParent source, AddressParent destination); // HELPER.C

#endif //LAGRANDE_HEADER_H