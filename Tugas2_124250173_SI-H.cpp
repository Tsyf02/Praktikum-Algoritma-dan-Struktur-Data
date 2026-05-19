#include <iostream>
#include <string>
using namespace std;

struct Kendaraan {
    string nopol;
    string nama;
    string status;
    Kendaraan* kiri;
    Kendaraan* kanan;
};

struct StackNode {
    string nopol;
    string aksi;
    StackNode* next;
};

struct QueueNode {
    string nopol;
    QueueNode* next;
};

int kapasitas = 5;
int jumlahParkir = 0;


// pada fungsi ini buat bikin node baru
Kendaraan* buatNode(string nopol, string nama) {
    Kendaraan* baru = new Kendaraan();
    baru->nopol = nopol;
    baru->nama = nama;
    baru->status = "Di Luar Parkiran";
    baru->kiri = NULL;
    baru->kanan = NULL;
    return baru;
}

// FUNGSI NYA dibuat buat nambahin kendaraan ke BST .
Kendaraan* tambah(Kendaraan* root, string nopol, string nama) {
    if (root == NULL) return buatNode(nopol, nama);
    if (nopol < root->nopol)
        root->kiri = tambah(root->kiri, nopol, nama);
    else if (nopol > root->nopol)
        root->kanan = tambah(root->kanan, nopol, nama);
    return root;
}
//kITA nyari kendaraan di BST .
Kendaraan* cari(Kendaraan* root, string nopol) {
    if (root == NULL || root->nopol == nopol) return root;
    if (nopol < root->nopol) return cari(root->kiri, nopol);
    return cari(root->kanan, nopol);
}
// show all vehicle
void tampil(Kendaraan* root) {
    if (root == NULL) return;
    tampil(root->kiri);
    cout << root->nopol << " | " << root->nama << " | " << root->status << endl;
    tampil(root->kanan);
}

Kendaraan* cariMin(Kendaraan* root) {
    while (root->kiri != NULL) root = root->kiri;
    return root;
}

// fungsi buat hapus node
Kendaraan* hapus(Kendaraan* root, string nopol, bool& ketemu) {
    if (root == NULL) {
        ketemu = false;
        return NULL;
    }
    if (nopol < root->nopol) {
        root->kiri = hapus(root->kiri, nopol, ketemu);
    } else if (nopol > root->nopol) {
        root->kanan = hapus(root->kanan, nopol, ketemu);
    } else {
        ketemu = true;
        if (root->kiri == NULL) {
            Kendaraan* temp = root->kanan;
            delete root;
            return temp;
        } else if (root->kanan == NULL) {
            Kendaraan* temp = root->kiri;
            delete root;
            return temp;
        }
        Kendaraan* temp = cariMin(root->kanan);
        root->nopol = temp->nopol;
        root->nama = temp->nama;
        root->status = temp->status;
        root->kanan = hapus(root->kanan, temp->nopol, ketemu);
    }
    return root;
}

void push(StackNode*& top, string nopol, string aksi) {
    StackNode* baru = new StackNode();
    baru->nopol = nopol;
    baru->aksi = aksi;
    baru->next = top;
    top = baru;
}

void pop(StackNode*& top, string& nopol, string& aksi) {
    StackNode* temp = top;
    nopol = temp->nopol;
    aksi = temp->aksi;
    top = top->next;
    delete temp;
}

void enqueue(QueueNode*& front, QueueNode*& rear, string nopol) {
    QueueNode* baru = new QueueNode();
    baru->nopol = nopol;
    baru->next = NULL;
    if (rear == NULL) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }
}

string dequeue(QueueNode*& front, QueueNode*& rear) {
    QueueNode* temp = front;
    string nopol = temp->nopol;
    front = front->next;
    if (front == NULL) rear = NULL;
    delete temp;
    return nopol;
}

void tampilAntrian(QueueNode* front) {
    if (front == NULL) {
        cout << "Antrian kosong" << endl;
        return;
    }
    QueueNode* curr = front;
    while (curr != NULL) {
        cout << curr->nopol << " menunggu giliran masuk parkiran" << endl;
        curr = curr->next;
    }
}

int main() {
    Kendaraan* root = NULL;
    StackNode* top = NULL;
    QueueNode* front = NULL;
    QueueNode* rear = NULL;

    int pilihan;
    string nopol, nama;

    do {
        cout << "\n=== SISTEM PARKIR BANDARA GSA ===" << endl;
        cout << "1. Tambah Kendaraan" << endl;
        cout << "2. Tampil Kendaraan" << endl;
        cout << "3. Kendaraan Masuk" << endl;
        cout << "4. Kendaraan Keluar" << endl;
        cout << "5. Hapus Kendaraan" << endl;
        cout << "6. Undo" << endl;
        cout << "7. Tampil Antrian" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            cout << "Nama Pemilik: ";
            getline(cin, nama);
            root = tambah(root, nopol, nama);
            cout << "Data kendaraan berhasil ditambahkan" << endl;

        } else if (pilihan == 2) {
            cout << "\n--- Daftar Kendaraan ---" << endl;
            cout << "Nopol | Nama | Status" << endl;
            tampil(root);

        } else if (pilihan == 3) {
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            Kendaraan* k = cari(root, nopol);
            if (k == NULL) {
                cout << "Kendaraan tidak ditemukan!" << endl;
            } else if (k->status == "Di Luar Parkiran") {
                if (jumlahParkir < kapasitas) {
                    k->status = "Di Parkiran";
                    jumlahParkir++;
                    push(top, nopol, "masuk");
                    cout << "Kendaraan berhasil masuk" << endl;
                } else {
                    enqueue(front, rear, nopol);
                    cout << "Parkiran penuh, kendaraan masuk ke dalam antrian" << endl;
                }
            }

        } else if (pilihan == 4) {
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            Kendaraan* k = cari(root, nopol);
            if (k == NULL) {
                cout << "Kendaraan tidak ditemukan!" << endl;
            } else if (k->status == "Di Parkiran") {
                k->status = "Di Luar Parkiran";
                jumlahParkir--;
                push(top, nopol, "keluar");
                cout << "Kendaraan berhasil keluar" << endl;
                if (front != NULL) {
                    string nopolAntrian = dequeue(front, rear);
                    Kendaraan* ka = cari(root, nopolAntrian);
                    if (ka != NULL) {
                        ka->status = "Di Parkiran";
                        jumlahParkir++;
                    }
                    cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian" << endl;
                }
            }

        } else if (pilihan == 5) {
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            bool ketemu = true;
            root = hapus(root, nopol, ketemu);
            if (ketemu)
                cout << "Data kendaraan berhasil dihapus" << endl;
            else
                cout << "Kendaraan tidak ditemukan!" << endl;

        } else if (pilihan == 6) {
            if (top == NULL) {
                cout << "Tidak ada aksi untuk di-undo" << endl;
            } else {
                string nopolUndo, aksi;
                pop(top, nopolUndo, aksi);
                Kendaraan* k = cari(root, nopolUndo);
                if (aksi == "masuk") {
                    k->status = "Di Luar Parkiran";
                    jumlahParkir--;
                    cout << "Undo: Kendaraan keluar dari parkiran" << endl;
                } else {
                    k->status = "Di Parkiran";
                    jumlahParkir++;
                    cout << "Undo: Kendaraan masuk kembali ke parkiran" << endl;
                }
            }

        } else if (pilihan == 7) {
            tampilAntrian(front);
        }

    } while (pilihan != 0);

    return 0;
}
