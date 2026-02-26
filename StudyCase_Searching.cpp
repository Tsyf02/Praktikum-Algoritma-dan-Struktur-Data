#include <iostream>
using namespace std;

struct Buku {
    char nama[50];
    int harga;
}; // struct, definisikan tipe data bukunya

// FUNGSI BANTU = Bandingkan 2 string (char array)
// Return  (0 jika kalau sama, <0 jika a<b, >0 jika a>b)

int bandingkanString(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

// FUNGSI BANTU = Nampilkan seluruh data bukunya
void tampilkanData(Buku daftar[], int n) {
    cout << "=======================================================" << endl;
    cout << "        	DAFTAR BUKU DI TOKO KAMI         " << endl;
    cout << "=======================================================" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << daftar[i].nama
             << " - Rp" << daftar[i].harga << endl;
    }
    cout << "=======================================================" << endl;
}

			// FUNGSI - SEQUENTIAL SEARCH //
// Cara kerja 	: Bandingkan data satu per satu
//              dari indeks pertama sampai akhir
// TIPE			: Data acak / terurut
// Return    	: indeks jika ditemukan, -1 jika tidak
int sequentialSearch(Buku daftar[], int n, char target[]) {
    bool ketemu = false;
    int i = 0;

    while ((i < n) & (!ketemu)) {
        if (bandingkanString(daftar[i].nama, target) == 0)
            ketemu = true;
        else
            i = i + 1;
    }

    if (ketemu) return i;
    else return -1;
}

			// FUNGSI - Binary Search //
// Cara kerja : Bandingkan nilai target dengan
//              elemen di indeks tengah, lalu area pencarian ke kiri atau kanan (dipersempit)
// TIPE       : Data HARUS udah terurut
// Rumus      : indeksTengah = (kiri + kanan) / 2  *
// Return     : indeks jika ditemukan, -1 jika tidak

int binarySearch(Buku daftar[], int n, char target[]) {
    int kiri = 0;
    int kanan = n - 1;
    bool ketemu = false;
    int mid;

    while ((!ketemu) & (kiri <= kanan)) {
        mid = (kiri + kanan) / 2;   // Rumus dari indeks tengah tadi *penting*

        if (bandingkanString(daftar[mid].nama, target) == 0) {
            ketemu = true;          // 	Indeks mid, DATA ditemukan
        } else {
            if (bandingkanString(target, daftar[mid].nama) < 0)
                kanan = mid - 1;    // Target < tengah [cari DARI kiri] *rumus*
            else
                kiri = mid + 1;     // Target > tengah [cari DARI kanan] *rumus*
        }
    }

    if (ketemu) return mid;
    else return -1;
}

// MAIN program nya
int main() {
    // Data buku disediakan dari awal, saya urutkan ini berdasarkan alphabet
    Buku tokoBuku[] = {
        {"Algoritma Pemrograman dan Struktur Data", 140000},
        {"Bahasa Indonesia"						  ,  65000},
        {"Bahasa Inggris"						  ,  85000},
        {"Manajemen dan Organisasi"				  ,  95000},
        {"Olahraga"								  ,  60000},
        {"Pemrograman Web"						  ,  80000},
        {"Pendidikan Pancasila"					  ,  70000},
        {"Pengantar Bisnis"						  ,  90000},
        {"Pengantar Metode Statistika"			  , 115000}
    };
    int n = sizeof(tokoBuku) / sizeof(tokoBuku[0]);

    char cariNama[50];
    int pilihanMetode;
    
    // Judul PROGRAM nya //
    cout << endl;
    cout << "=======================================================" << endl;
    cout << " 	 - SISTEM PENCARIAN BUKU 'TOKO BUKU' - 				" << endl;
    cout << " 	 Praktikum Algoritma & Struktur Data   	 			" << endl;
    cout << "	Study Case - Pencarian Data (Searching) 			" << endl;
    cout << "=======================================================" << endl;
    cout << endl;

    // Tampilkan semua data di toko buku
    tampilkanData(tokoBuku, n);

    // Input nama buku, apa yang mau kita cari?
    cout << endl;
    cout << "Masukkan nama buku : ";
    cin.getline(cariNama, 50);

    cout << endl;
    cout << "Pilih Metode Pencarian:" << endl;
    cout << "1. Sequential Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "3. Keduanya" << endl;
    cout << "Pilihan (1/2/3) : ";
    cin >> pilihanMetode;
    cout << endl;

    // metode - SEQUENTIAL SEARCH
    if (pilihanMetode == 1 || pilihanMetode == 3) {
        cout << "-----------------------------------------" << endl;
        cout << "  Sequential Search              " << endl;
        cout << "-----------------------------------------" << endl;

        int hasilSeq = sequentialSearch(tokoBuku, n, cariNama);

        if (hasilSeq != -1) {
            cout << "Status  : Ditemukan di indeks ke-" << hasilSeq << endl;
            cout << "Nama    : " << tokoBuku[hasilSeq].nama << endl;
            cout << "Harga   : Rp" << tokoBuku[hasilSeq].harga << endl;
        } else {
            cout << "Status  : Buku \"" << cariNama << "\" tidak ditemukan." << endl;
        }
        cout << endl;
    }

    // metode - BINARY SEARCH
    if (pilihanMetode == 2 || pilihanMetode == 3) {
        cout << "-----------------------------------------" << endl;
        cout << "   Binary Search                  " << endl;
        cout << "-----------------------------------------" << endl;

        int hasilBin = binarySearch(tokoBuku, n, cariNama);

        if (hasilBin != -1) {
            cout << "Status  : Ditemukan di indeks ke-" << hasilBin << endl;
            cout << "Nama    : " << tokoBuku[hasilBin].nama << endl;
            cout << "Harga   : Rp" << tokoBuku[hasilBin].harga << endl;
        } else {
            cout << "Status  : Buku \"" << cariNama << "\" tidak ditemukan." << endl;
        }
        cout << endl;
    }

		//PENUTUP//
    cout << "=======================================================" << endl;
    cout << "    	  Terima kasih, atas kunjungannya :)  	 " << endl;
    cout << "=======================================================" << endl;

    return 0;
}
