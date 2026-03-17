#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

struct Produk {
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

Produk katalog[100];
int jumlahProduk = 0;

void loadData() {
    FILE *file = fopen("shopeaseFile.txt", "r");
    if (file == NULL) {
        cout << "File tidak bisa ditemukan. Mulai lagi dengan data kosong:(\n";
        return;
    }
    
    jumlahProduk = 0;
    while (fscanf(file, "%[^|]|%[^|]|%lf|%d|%f\n", katalog[jumlahProduk].name, katalog[jumlahProduk].category, &katalog[jumlahProduk].price, &katalog[jumlahProduk].stock, &katalog[jumlahProduk].rating) != EOF) {
        jumlahProduk++;
    }
    
    fclose(file);
    cout << "Data dimuat. Total produk: " << jumlahProduk << endl;
}

void saveData() {
    FILE *file = fopen("shopeaseFile.txt", "w");
    if (file == NULL) {
        cout << "Gagal simpan file!\n";
        return;
    }
    
    for (int i = 0; i < jumlahProduk; i++) {
        fprintf(file, "%s|%s|%.0lf|%d|%.1f\n", katalog[i].name, katalog[i].category, katalog[i].price, katalog[i].stock, katalog[i].rating);
    }
    
    fclose(file);
    cout << "Data tersimpan!\n";
}

void tambahProduk() {
    cout << "\n=== TAMBAH PRODUK ===\n";
    
    if (jumlahProduk >= 100) {
        cout << "Katalog penuh!\n";
        return;
    }
    
    cout << "Nama produk: ";
    cin.ignore();
    cin.getline(katalog[jumlahProduk].name, 60);
    
    cout << "Kategori: ";
    cin.getline(katalog[jumlahProduk].category, 30);
    
    cout << "Harga: Rp ";
    cin >> katalog[jumlahProduk].price;
    
    cout << "Stok: ";
    cin >> katalog[jumlahProduk].stock;
    
    cout << "Rating (0-5): ";
    cin >> katalog[jumlahProduk].rating;
    
    jumlahProduk++;
    saveData();
    
    cout << "\nProduk Berhasil Ditambahkan!\n";
}

void bubbleSortByName() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (strcmp(katalog[j].name, katalog[j + 1].name) > 0) {
                Produk temp = katalog[j];
                katalog[j] = katalog[j + 1];
                katalog[j + 1] = temp;
            }
        }
    }
}

int partition(Produk arr[], int low, int high) {
    float pivot = arr[high].rating;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].rating > pivot) {
            i++;
            Produk temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    Produk temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(Produk arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void tampilkanProduk() {
    if (jumlahProduk == 0) {
        cout << "\nBelum ada produk.\n";
        return;
    }
    
    cout << "\n=== PILIH URUTAN ===\n";
    cout << "1. Urutan Nama (A-Z) - Bubble Sort\n";
    cout << "2. Urutan Rating Tertinggi - Quick Sort\n";
    cout << "Pilih: ";
    
    int mode;
    cin >> mode;
    
    if (mode == 1) {
        bubbleSortByName();
        cout << "\n=== URUTAN NAMA DARI A-Z ===\n";
    } else if (mode == 2) {
        quickSort(katalog, 0, jumlahProduk - 1);
        cout << "\n=== URUTAN DENGAN RATING TERTINGGI ===\n";
    } else {
        cout << "Pilihan salah!\n";
        return;
    }
    
    cout << "========================================================\n";
    cout << "No Nama                    Kategori  Harga  Stok Rating\n";
    cout << "========================================================\n";
    
    for (int i = 0; i < jumlahProduk; i++) {
        printf("%-2d %-24s %-10s Rp%.0lf %-4d %.1f\n", 
               i+1, katalog[i].name, katalog[i].category, 
               katalog[i].price, katalog[i].stock, katalog[i].rating);
    }
}

void cariProduk() {
    if (jumlahProduk == 0) {
        cout << "\nBelum ada produk.\n";
        return;
    }
    
    cout << "\n=== CARI PRODUK ===\n";
    cout << "Nama Produk: ";
    
    char cari[60];
    cin.ignore();
    cin.getline(cari, 60);
    
    for (int i = 0; i < jumlahProduk; i++) {
        if (strcmp(katalog[i].name, cari) == 0) {
            cout << "\nPRODUK DITEMUKAN!\n";
            cout << "Nama     : " << katalog[i].name << endl;
            cout << "Kategori : " << katalog[i].category << endl;
            cout << "Harga    : Rp " << katalog[i].price << endl;
            cout << "Stok     : " << katalog[i].stock << endl;
            cout << "Rating   : " << katalog[i].rating << endl;
            return;
        }
    }
    
    cout << "\nProduk tidak ditemukan!\n";
}

int main() {
    loadData();
    
    int pilihan;
    
    do {
        cout << "\n========================\n";
        cout << "   *SHOPEASE CATALOG*     \n";
        cout << "========================\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Lihat Produk\n";
        cout << "3. Cari Produk\n";
        cout << "4. Keluar\n";
        cout << "========================\n";
        cout << "Pilih (1-4): ";
        cin >> pilihan;
        
        if (pilihan == 1) {
            tambahProduk();
        } else if (pilihan == 2) {
            tampilkanProduk();
        } else if (pilihan == 3) {
            cariProduk();
        } else if (pilihan == 4) {
            saveData();
            cout << "\nTerima kasih, sudah menggunakkan ShopEase :)\n";
        } else {
            cout << "\nPilihan salah! Coba lagi yaa...\n";
        }
        
    } while (pilihan != 4);
    
    return 0;
}
