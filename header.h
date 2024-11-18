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
typedef char string[50];

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
void createEmpty(Multilist *L);
bool isEmpty(Multilist L);
void showMenu(int *picker);

// DEKLARASI FUNGSI PARENT (NOTA)
DataParent makeDataParent(int nomor, string tanggal, int meja);
AddressParent alokasiParent(DataParent data);
AddressParent findParent(Multilist L, int nomorNota);

void insertFirstParent(Multilist *L, DataParent data);
void insertLastParent(Multilist *L, DataParent data);
void deleteParent(Multilist *L, int nomorNota);

// DEKLARASI FUNGSI CHILD (ITEM PESANAN)
DataChild makeDataChild(string nama, int jumlah, float harga);
AddressChild alokasiChild(DataChild data);

void insertFirstChild(Multilist L, int nomorNota, DataChild data);
void insertLastChild(Multilist L, int nomorNota, DataChild data);
void deleteChild(Multilist *L, int nomorNota, string namaItem);

// FUNGSI OPERASI NOTA
void mergeNota(Multilist *L, int notaSumber, int notaTujuan);
void splitNota(Multilist *L, int nomorNota, int jumlahSplit);
bool prosesPayment(Multilist *L, int nomorNota, float jumlahBayar);

// FUNGSI LAPORAN
void hitungOmzet(Multilist L, float *totalOmzet);
void cariItemTerlaris(Multilist L);
void printNota(AddressParent nota);
void printAllNota(Multilist L);

// FUNGSI BONUS (FILE HANDLING)
void saveToFile(Multilist L, string filename);
void loadFromFile(Multilist *L, string filename);

// FUNGSI HELPER
void updateTotalPembelian(AddressParent nota);
bool isNotaLunas(AddressParent nota);
AddressChild findChild(AddressParent nota, string namaItem);
void moveAllItems(AddressParent source, AddressParent destination);

#endif //LAGRANDE_HEADER_H