#include "header.h"

void createEmpty(Multilist *L){
    L->firstParent = NULL;
}

bool isEmpty(Multilist L){
    return L.firstParent == NULL;
}

// PARENT
DataParent makeDataParent(int nomor, string tanggal, int meja) {
    DataParent newData;
    newData.nomorNota = nomor;
    strcpy(newData.tanggal, tanggal);
    newData.nomorMeja = meja;
    newData.totalPembelian = 0;
    newData.status = true;
    return newData;
}

AddressParent alokasiParent(DataParent data) {
    AddressParent P = (AddressParent)malloc(sizeof(NodeParent));
    if(P != NULL)
    {
        P->dataParent = data;
        P->next = NULL;
        P->firstChild = NULL;
        P->merged = NULL;
    }
    return P;
}

AddressParent findParent(Multilist L, int nomorNota) {
    AddressParent P = L.firstParent;
    while(P != NULL)
    {
        if(P->dataParent.nomorNota == nomorNota)
            return P;

        P = P->next;
    }
    return NULL;
}

void insertFirstParent(Multilist *L, DataParent data) {
    AddressParent P = alokasiParent(data);
    if(P != NULL)
    {
        if(isEmpty(*L))
            L->firstParent = P;
        else
        {
            P->next = L->firstParent;
            L->firstParent = P;
        }
    }
}

void insertLastParent(Multilist *L, DataParent data) {
    if(isEmpty(*L))
        insertFirstParent(L, data);
    else
    {
        AddressParent P = alokasiParent(data);
        if(P != NULL)
        {
            AddressParent last = L->firstParent;
            while(last->next != NULL)
                last = last->next;

            last->next = P;
        }
    }
}

void deleteParent(Multilist *L, int nomorNota) {
    if(!isEmpty(*L))
    {
        AddressParent P = L->firstParent;
        AddressParent prev = NULL;

        while(P != NULL && P->dataParent.nomorNota != nomorNota)
        {
            prev = P;
            P = P->next;
        }

        if(P != NULL)
        {
            AddressChild currentChild = P->firstChild;
            while(currentChild != NULL) {
                AddressChild temp = currentChild;
                currentChild = currentChild->next;
                free(temp);
            }

            if(prev == NULL)
                L->firstParent = P->next;
            else
                prev->next = P->next;
            
			MEJA[P->dataParent.nomorMeja-1] = 0;
			free(P);
        }
    }
}

// CHILD
DataChild makeDataChild(string nama, int jumlah, float harga) {
    DataChild newData;
    strcpy(newData.namaItem, nama);
    newData.jumlah = jumlah;
    newData.harga = harga;
    newData.subtotal = jumlah * harga;
    return newData;
}

AddressChild alokasiChild(DataChild data) {
    AddressChild C = (AddressChild)malloc(sizeof(NodeChild));
    if(C != NULL)
    {
        C->dataChild = data;
        C->next = NULL;
    }
    return C;
}

void insertFirstChild(Multilist L, int nomorNota, DataChild data) {
    AddressParent P = findParent(L, nomorNota);
    if(P != NULL)
    {
        AddressChild C = alokasiChild(data);
        if(C != NULL)
        {
            C->next = P->firstChild;
            P->firstChild = C;
            P->dataParent.totalPembelian += data.subtotal;
        }
    }
}

void insertLastChild(Multilist L, int nomorNota, DataChild data) {
    AddressParent P = findParent(L, nomorNota);
    if(P != NULL)
    {
        if(P->firstChild == NULL)
            insertFirstChild(L, nomorNota, data);
        else
        {
            AddressChild C = alokasiChild(data);
            if(C != NULL)
            {
                AddressChild last = P->firstChild;
                while(last->next != NULL) {
                    last = last->next;
                }
                last->next = C;
                P->dataParent.totalPembelian += data.subtotal;
            }
        }
    }
}

void deleteChild(Multilist *L, int nomorNota, string namaItem) {
    AddressParent P = findParent(*L, nomorNota);
    if(P != NULL && P->firstChild != NULL)
    {
        AddressChild C = P->firstChild;
        AddressChild prev = NULL;

        while(C != NULL && strcmp(C->dataChild.namaItem, namaItem) != 0)
        {
            prev = C;
            C = C->next;
        }

        if(C != NULL)
        {
            P->dataParent.totalPembelian -= C->dataChild.subtotal;

            // Hapus node
            if(prev == NULL)
                P->firstChild = C->next;
            else
                prev->next = C->next;

            free(C);
        }
    }
}
