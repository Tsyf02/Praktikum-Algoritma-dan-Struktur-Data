#include <iostream>  
using namespace std;

void bubblesort_ascending(string arr[], int n) 
{
    string temp; 

    for (int i = 0; i < n - 1; i++) 
    {
		
        for (int j = 0; j < n - 1 - i; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                temp       = arr[j];      // nyimpan arr[j] ke variabel temp
                arr[j]     = arr[j + 1]; // pindahin arr[j+1] ke posisi arr[j]
                arr[j + 1] = temp;       // Isi arr[j+1] dengan nilai temp (asli arr[j])
            }
        }
    }
}

void quicksort_descending(string arr[], int awal, int akhir) 
{
    int low  = awal;  // Indeks kiri = awal
    int high = akhir; // Indeks kanan = dimulai akhir

    // Pilih pivot dari elemen tengah array
    string pivot = arr[(awal + akhir) / 2]; // rumusnya emang gini //

   
    do 
    {
        while (arr[low] > pivot)
            low++;

        while (arr[high] < pivot)
            high--;

        // Jika low masih di kiri atau sama dengan high, swap elemennya
        if (low <= high) 
        {
            swap(arr[low], arr[high]); // Tukar posisi arr[low] dan arr[high]
            low++;                     // Geser low ke kanan
            high--;                    // Geser high ke kiri
        }

    } while (low <= high); // Ulangi selama low itu belum melewati high

    // Rekursif: urutkan bagian kiri (dari awal-> high)
    if (awal < high)
        quicksort_descending(arr, awal, high);

    // Rekursif: urutkan bagian kanan (dari low -> akhir)
    if (low < akhir)
        quicksort_descending(arr, low, akhir);
}

//void =nampilin array
void tampilArray(string arr[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        cout << i + 1 << ". " << arr[i] << endl; // nampil-> nomor urut + nama
    }
}

int main() {
    int n; //VAR jmlh mahasswa

    cout << "============================================" << endl;
    cout << "    PROGRAM MENGURUTKAN NAMA MAHASISWA      " << endl;
    cout << "============================================" << endl;

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    cin.ignore();

    // Deklarasi array string = nyimpan nama mahasiswa
    string nama[n];

    // Perulangan = membaca nama mahasiswa 
    cout << "\nMasukkan nama-nama mahasiswa:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Mahasiswa ke-" << i + 1 << ": ";
        getline(cin, nama[i]); //  getline = input nama dengan spasi
    }

    // Buat salinan array untuk Quick Sort descending
    // agar array asli tidak berubah saat dipakai Bubble Sort
    string nama_qs[n];
    for (int i = 0; i < n; i++) {
        nama_qs[i] = nama[i];
    }
    
//bublle
    bubblesort_ascending(nama, n); //manggil yang secara ascending
    
    cout << "\n============================================" << endl;
    cout << " Hasil Bubble Sort_Ascending  			     " << endl;
    cout << "============================================" << endl;
    tampilArray(nama, n); 
//quick
    quicksort_descending(nama_qs, 0, n - 1); // Panggil fungsi quick sort descending

    cout << "\n============================================" << endl;
    cout << " Hasil Quick Sort_Descending   			 " << endl;
    cout << "============================================" << endl;
    tampilArray(nama_qs, n); 

    cout << "\n============================================" << endl;
    cout << "NAMA MAHASISWA TELAH DITAMPILKAN:)  	 	 " << endl;
    cout << "============================================" << endl;

    return 0; 
}

