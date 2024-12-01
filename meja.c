#include "header.h"

void initMeja(bool meja[JUMLAH_MEJA]) {
	int i;
    for (i = 0; i < JUMLAH_MEJA; i++) {
        meja[i] = false; 
    }
}

void tampilMeja(bool meja[JUMLAH_MEJA]) {
	int i;
    for (i = 0; i < JUMLAH_MEJA; i++) {
        if (i % 5 == 0 && i != 0) {
            printf("\n");
        }
        printf("Meja %2d: %s\t", i + 1, meja[i] ? "Aktif" : "Nonaktif");
    }
    printf("\n");
}

bool isMejaEmpty(bool meja[JUMLAH_MEJA]) {
	int i;
    for (i = 0; i < JUMLAH_MEJA; i++) {
        if (meja[i]) {
            return false;
        }
    }
    return true; 
}

int cekMejaAktif(bool meja[JUMLAH_MEJA], int nomorMeja) {
    if (nomorMeja < 1 || nomorMeja > JUMLAH_MEJA) {
        return -1; 
    }
    return meja[nomorMeja - 1] ? -1 : nomorMeja;
}

bool isFull(bool meja[JUMLAH_MEJA]) {
	int i;
    for (i = 0; i < JUMLAH_MEJA; i++) {
        if (!meja[i]) {
            return false; 
        }
    }
    return true;
}

void merubahMeja(bool meja[JUMLAH_MEJA], int nomorMeja) {
    if (nomorMeja < 1 || nomorMeja > JUMLAH_MEJA) {
        printf("Nomor meja tidak valid!\n");
        return;
    }
    meja[nomorMeja - 1] = !meja[nomorMeja - 1]; 
    printf("Meja %d sekarang %s.\n", nomorMeja, meja[nomorMeja - 1] ? "Aktif" : "Nonaktif");
}
