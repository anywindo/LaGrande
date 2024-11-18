# 🍽️ Sistem Manajemen Restoran La Grande

![Manajemen Restoran](https://img.shields.io/badge/Manajemen-Restoran-orange)
![Versi](https://img.shields.io/badge/Versi-1.0-blue)
![Lisensi](https://img.shields.io/badge/Lisensi-MIT-green)

## 📋 Daftar Isi
- [Ringkasan](#ringkasan)
- [Fitur](#fitur)
- [Kebutuhan Sistem](#kebutuhan-sistem)
- [Struktur Data](#struktur-data)
- [Penggunaan](#penggunaan)
- [Tangkapan Layar](#tangkapan-layar)
- [Kontribusi](#kontribusi)
- [Lisensi](#lisensi)

## 🎯 Ringkasan
Sistem Manajemen Restoran La Grande adalah solusi lengkap yang dirancang untuk mengoptimalkan operasional restoran, mulai dari manajemen pesanan hingga pelaporan keuangan. Dibangun menggunakan struktur data multilist, sistem ini mampu menangani beberapa pesanan secara bersamaan sambil menjaga integritas data.

## ⭐ Fitur

### 🧾 Manajemen Pesanan
- Membuat pesanan baru dengan penugasan meja
- Menambah/mengubah item menu dalam pesanan
- Pelacakan pesanan secara langsung
- Mencetak struk pesanan

### 💳 Pemrosesan Pembayaran
- **Gabung Nota**: Menggabungkan beberapa nota untuk pembayaran kelompok
- **Pisah Nota**: Membagi satu nota menjadi beberapa tagihan
- Validasi pembayaran yang aman
- Perhitungan kembalian

### 📊 Pelaporan
- Pelacakan pendapatan harian
- Analisis item menu terpopuler
- Visualisasi tren penjualan
- Laporan periode kustom

### 💾 Penyimpanan Data
- Fungsi simpan otomatis
- Backup dan pemulihan data
- Ekspor laporan ke file

## 🖥️ Kebutuhan Sistem
- Kompiler C (Disarankan GCC)
- Minimum RAM 2GB
- Ruang disk kosong 100MB
- Terminal/Command Prompt

## 🏗️ Struktur Data

### Komponen Utama
```
Multilist
└── Nota (Parent)
    ├── Detail Nota
    │   ├── Nomor Nota
    │   ├── Tanggal
    │   ├── Nomor Meja
    │   └── Total Pembelian
    │
    └── Item Menu (Child)
        ├── Nama Item
        ├── Jumlah
        ├── Harga
        └── Subtotal
```

### Hubungan Utama
| Entitas | Hubungan | Entitas |
|---------|----------|---------|
| Nota | 1:N | Item Menu |
| Nota | 1:1 | Nota Gabungan |

## 🎮 Penggunaan

### Membuat Nota Baru
```c
DataParent dataNota = makeDataParent(1, "18-03-2024", 5);
insertFirstParent(&sistemRestoran, dataNota);
```

### Menambah Item Menu
```c
DataChild dataItem = makeDataChild("Pasta Carbonara", 2, 15.99);
insertLastChild(sistemRestoran, 1, dataItem);
```

### Memproses Pembayaran
```c
prosesPayment(&sistemRestoran, nomorNota, jumlahBayar);
```

## 📸 Tangkapan Layar

<details>
<summary>Klik untuk melihat tangkapan layar</summary>

### Menu Utama
```
===== Restoran La Grande =====
1. Buat Nota Baru
2. Tambah Item Menu
3. Proses Pembayaran
4. Lihat Laporan
5. Keluar
```

### Manajemen Nota
```
Nota #1234
Meja: 5
Item:
- 2x Pasta Carbonara   Rp159.900
- 1x Caesar Salad      Rp129.900
Total: Rp289.800
```
</details>

## 🤝 Kontribusi
Kami menyambut kontribusi! Silakan ikuti langkah-langkah berikut:

1. Fork repositori
2. Buat branch fitur Anda
3. Commit perubahan Anda
4. Push ke branch
5. Buat Pull Request

## 📄 Lisensi
Proyek ini dilisensikan di bawah Lisensi MIT - lihat file [LISENSI](LISENSI) untuk detail.

---

<div align="center">

Dibuat dengan ❤️ oleh La Grenade team

📧 Kontak: coder@lagrande.com

</div>

---

### 📚 Dokumentasi Tambahan

#### Struktur Tabel Data

1. Data Item Menu (DataChild)
| Variabel   | Tipe Data |
|------------|-----------|
| namaItem   | string    |
| jumlah     | int       |
| harga      | float     |
| subtotal   | float     |

2. Data Nota (DataParent)
| Variabel        | Tipe Data |
|-----------------|-----------|
| nomorNota       | int       |
| tanggal         | string    |
| nomorMeja       | int       |
| totalPembelian  | float     |

3. Node Item Menu (NodeChild)
| Variabel    | Tipe Data    |
|-------------|--------------|
| dataChild   | DataChild    |
| next        | AddressChild |

4. Node Nota (NodeParent)
| Variabel     | Tipe Data     |
|--------------|---------------|
| dataParent   | DataParent    |
| next         | AddressParent |
| firstChild   | AddressChild  |
| merged       | AddressParent |

5. Multilist
| Variabel     | Tipe Data     |
|--------------|---------------|
| firstParent  | AddressParent |

#### Definisi Tipe
| Definisi Tipe  | Tipe Dasar |
|----------------|------------|
| string         | char[50]   |
| AddressChild   | NodeChild* |
| AddressParent  | NodeParent*|
