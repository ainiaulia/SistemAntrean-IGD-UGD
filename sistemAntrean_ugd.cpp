#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Datapasien{      
    int noPasien;
    char nama[50];
    int umur;
    char keluhan[100];
    int prioritas;
    char status[20];
};

struct Node{        
    Datapasien data;
    Node *next;
};

Node *head = NULL;

void tambahLinkedList(Datapasien pasien) {    
    Node *newNode = new Node;
    newNode->data = pasien;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    }else {
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void hapusLinkedList() {    
    Node *current = head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}

void simpanFile(Datapasien pasien) {   
    FILE *file = fopen("data_pasien.txt", "a");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    fprintf(file, "%d,%s,%d,%s,%d,%s\n", pasien.noPasien, pasien.nama, pasien.umur, pasien.keluhan, pasien.prioritas, pasien.status);
    fclose(file);
}

void simpanSemuaKeFile() {
    FILE *file = fopen("data_pasien.txt", "w");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    Node *temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%d,%s,%d,%s\n", temp->data.noPasien, temp->data.nama, 
                temp->data.umur, temp->data.keluhan, temp->data.prioritas, temp->data.status);
        temp = temp->next;
    }
    fclose(file);
}

bool hanyaHuruf(const char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z')||(str[i] >= 'a' && str[i] <= 'z')|| str[i] == ' ')) {
            return false;
        }
    }
    return true;
}

int validasiAngka(string pesan) {
    int angka;

    while (true) {
        cout << pesan;
        cin >> angka;

        if (cin.fail()) {
            cout << "Data harus berupa angka! Silakan coba lagi.\n" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        } else {
            cin.ignore(100, '\n');
            return angka;
        }
    }
}

void validasiString(char hasil[], int panjang, string pesan) {
    while (true) {
        cout << pesan;
        cin.getline(hasil, panjang);

        if (hasil[0] == '\0') {
            cout << "Data tidak boleh kosong! Silakan coba lagi.\n" << endl;
        } else if (!hanyaHuruf(hasil)) {
            cout << "Data hanya boleh berisi huruf! Silakan coba lagi.\n" << endl;
        } else {
            break;
        }
    }
} 

// ==================== MENU 1: INPUT DATA PASIEN ====================
void inputPasien() {    
    Datapasien pasien;
    int jmlInput;

    cout << "========== INPUT DATA PASIEN ==========\n" << endl;
    cout << "Jumlah Pasien yang akan diinput : ";
    cin >> jmlInput;
    cin.ignore(); 

    for (int i = 0; i < jmlInput; i++) {
        cout << "\nData Pasien ke-" << (i + 1) << ":\n";

        pasien.noPasien = validasiAngka("Masukkan No Pasien : ");
        validasiString(pasien.nama, 50, "Masukkan Nama Pasien : ");
        pasien.umur = validasiAngka("Masukkan Umur Pasien : ");
        validasiString(pasien.keluhan, 100, "Masukkan Keluhan : ");

        // Validasi prioritas (harus 1, 2, atau 3)
        while (true) {
            cout << "Masukkan Prioritas (1-3) : ";
            cout << "\n(1 = Gawat Darurat, 2 = Sedang, 3 = Ringan)" << endl;
            cout << "Pilih: ";
            cin >> pasien.prioritas;

            if(cin.fail()) {
                cout << "Data harus berupa angka! Silakan coba lagi.\n" << endl;
                cin.clear();
                cin.ignore(100, '\n');
            } else if(pasien.prioritas < 1 || pasien.prioritas > 3) {
                cout << "Prioritas harus antara 1-3! Silakan coba lagi.\n" << endl;
                cin.ignore(100, '\n');
            } else {
                cin.ignore(100, '\n');
                break;
            }
        }

        validasiString(pasien.status, 20, "Masukkan Status : ");
        simpanFile(pasien);  // Simpan ke file
    }

    cout << "\nData pasien berhasil disimpan!\n" << endl;
}

void bacaDataDariFile() {
    FILE *file = fopen("data_pasien.txt", "r");
    if (file == NULL) {
        return;
    }

    hapusLinkedList();
    Datapasien pasien;
    
    while (fscanf(file, "%d,%[^,],%d,%[^,],%d,%[^\n]", &pasien.noPasien, pasien.nama, &pasien.umur, pasien.keluhan, &pasien.prioritas, pasien.status) != EOF) {
        tambahLinkedList(pasien);
    }
    fclose(file);
}

// ==================== MENU 2: TAMPILKAN SEMUA DATA PASIEN ====================
void tampilData() {   
    bacaDataDariFile();  // Baca data dari file ke linked list
    
    if (head == NULL) {
        cout << "\nBelum ada data pasien!\n" << endl;
        return;
    }

    cout << "\n========== DATA PASIEN ==========\n" << endl;
    Node *temp = head;
    while (temp != NULL) {
        cout << "No Pasien : " << temp->data.noPasien << endl;
        cout << "Nama      : " << temp->data.nama << endl;
        cout << "Umur      : " << temp->data.umur << endl;
        cout << "Keluhan   : " << temp->data.keluhan << endl;
        
        // Tampilkan prioritas dengan keterangan
        cout << "Prioritas : " << temp->data.prioritas;
        if (temp->data.prioritas == 1) cout << " (Gawat Darurat)";
        else if (temp->data.prioritas == 2) cout << " (Sedang)";
        else if (temp->data.prioritas == 3) cout << " (Ringan)";
        cout << endl;
        
        cout << "Status    : " << temp->data.status << endl; 
        cout << "---------------------------------\n" << endl;
        temp = temp->next;
    }
}

void tampilPasien(Node *temp) {
    cout << "\n--- Data Pasien ---" << endl;
    cout << "No Pasien : " << temp->data.noPasien << endl;
    cout << "Nama      : " << temp->data.nama << endl;
    cout << "Umur      : " << temp->data.umur << endl;
    cout << "Keluhan   : " << temp->data.keluhan << endl;
    cout << "Prioritas : " << temp->data.prioritas;
    if (temp->data.prioritas == 1) cout << " (Gawat Darurat)";
    else if (temp->data.prioritas == 2) cout << " (Sedang)";
    else if (temp->data.prioritas == 3) cout << " (Ringan)";
    cout << endl;
    cout << "Status    : " << temp->data.status << endl;
    cout << "---------------------------------" << endl;
}

// ==================== SORTING ====================
void tukarData(Node *a, Node *b) {
    Datapasien temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// ==================== MENU 4: SORTING DATA PASIEN ====================
void sortingData() {
    bacaDataDariFile();
    
    if (head == NULL) {
        cout << "\nBelum ada data pasien!\n" << endl;
        return;
    }
    
    int pilihSort;
    cout << "\n========== SORTING DATA PASIEN ==========" << endl;
    cout << "1. Urutkan berdasarkan No Pasien (Ascending)" << endl;
    cout << "2. Urutkan berdasarkan Prioritas (Ascending)" << endl;
    cout << "Pilih: ";
    cin >> pilihSort;
    
    if (pilihSort != 1 && pilihSort != 2) {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }
    
    if (head == NULL || head->next == NULL) {
        cout << "\nData sudah terurut atau hanya 1 data!" << endl;
        return;
    }
    
    // Bubble sort 
    bool swapped;
    Node *ptr1;
    Node *lptr = NULL;
    
    do {
        swapped = false;
        ptr1 = head;
        
        while (ptr1->next != lptr) {
            bool perluTukar = false;
            
            if (pilihSort == 1) {
                if (ptr1->data.noPasien > ptr1->next->data.noPasien)
                    perluTukar = true;
            } else if (pilihSort == 2) {
                if (ptr1->data.prioritas > ptr1->next->data.prioritas)
                    perluTukar = true;
            }
            
            if (perluTukar) {
                tukarData(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    simpanSemuaKeFile();  // Simpan hasil sorting ke file
    cout << "\nData berhasil diurutkan dan disimpan!" << endl;
    
    cout << "\nHasil setelah sorting:" << endl;
    tampilData();
}

// ==================== MENU 5: TAMPILAN ANTRIAN BY URGENSI ====================
void tampilAntrianByUrgensi() {
    bacaDataDariFile();
    
    if (head == NULL) {
        cout << "\nBelum ada data pasien!\n" << endl;
        return;
    }
    
    
    Node *sortedHead = NULL;
    Node *temp = head;
    while (temp != NULL) {
        Node *newNode = new Node;
        newNode->data = temp->data;
        newNode->next = NULL;
        
        if (sortedHead == NULL) {
            sortedHead = newNode;
        } else {
            Node *last = sortedHead;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
        }
        temp = temp->next;
    }
    
    // Sorting berdasarkan prioritas (ascending)
    if (sortedHead != NULL && sortedHead->next != NULL) {
        bool swapped;
        Node *ptr1;
        Node *lptr = NULL;
        
        do {
            swapped = false;
            ptr1 = sortedHead;
            
            while (ptr1->next != lptr) {
                if (ptr1->data.prioritas > ptr1->next->data.prioritas) {
                    Datapasien tempData = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = tempData;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }
    
    // Tampilkan antrian berdasarkan urgensi
    cout << "\n========== ANTRIAN PASIEN BERDASARKAN URGENSI ==========\n" << endl;
    cout << "Urutan prioritas: Gawat Darurat (1) -> Sedang (2) -> Ringan (3)\n" << endl;
    
    int urutan = 1;
    Node *current = sortedHead;
    while (current != NULL) {
        cout << "Antrian ke-" << urutan << ":" << endl;
        cout << "   No Pasien : " << current->data.noPasien << endl;
        cout << "   Nama      : " << current->data.nama << endl;
        cout << "   Umur      : " << current->data.umur << endl;
        cout << "   Keluhan   : " << current->data.keluhan << endl;
        cout << "   Prioritas : " << current->data.prioritas;
        if (current->data.prioritas == 1) cout << " (Gawat Darurat)";
        else if (current->data.prioritas == 2) cout << " (Sedang)";
        else if (current->data.prioritas == 3) cout << " (Ringan)";
        cout << endl;
        cout << "   Status    : " << current->data.status << endl;
        cout << "   ---------------------------------\n" << endl;
        
        urutan++;
        current = current->next;
    }
    
    // Hapus linked list copy untuk menghindari memory leak
    current = sortedHead;
    while (current != NULL) {
        Node *hapus = current;
        current = current->next;
        delete hapus;
    }
}

// ==================== MENU 3: EDIT DATA (berdasarkan No Pasien) ====================
void editDataPasien() {
    int editNo;
    cout << "\nMasukkan No Pasien yang akan diedit: ";
    cin >> editNo;
    
    Node *temp = head;
    bool ditemukan = false;
    
    // Cari pasien berdasarkan no Pasien
    while (temp != NULL) {
        if (temp->data.noPasien == editNo) {
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }
    
    if (!ditemukan) {
        cout << "\nPasien dengan No " << editNo << " tidak ditemukan!" << endl;
        return;
    }
    
    // Tampilkan data lama
    cout << "\nData lama:" << endl;
    tampilPasien(temp);
    
    // Input data baru
    cout << "\nMasukkan data baru:" << endl;
    cin.ignore();
    
    validasiString(temp->data.nama, 50, "Masukkan Nama Baru : ");
    temp->data.umur = validasiAngka("Masukkan Umur Baru : ");
    validasiString(temp->data.keluhan, 100, "Masukkan Keluhan Baru : ");
    
    // Validasi prioritas baru
    while (true) {
        cout << "Masukkan Prioritas Baru (1-3) : ";
        cout << "\n(1 = Gawat Darurat, 2 = Sedang, 3 = Ringan)" << endl;
        cout << "Pilih: ";
        cin >> temp->data.prioritas;
        if(cin.fail()) {
            cout << "Data harus berupa angka! Silakan coba lagi.\n" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        } else if(temp->data.prioritas < 1 || temp->data.prioritas > 3) {
            cout << "Prioritas harus antara 1-3! Silakan coba lagi.\n" << endl;
            cin.ignore(100, '\n');
        } else {
            cin.ignore(100, '\n');
            break;
        }
    }
    
    validasiString(temp->data.status, 20, "Masukkan Status Baru : ");	
    
    simpanSemuaKeFile();  // Simpan perubahan ke file
    cout << "\nData pasien dengan No " << editNo << " berhasil diupdate!" << endl;
}

// ==================== MENU 3: HAPUS DATA (berdasarkan No Pasien) ====================
void hapusDataPasien() {
    int hapusNo;
    cout << "\nMasukkan No Pasien yang akan dihapus: ";
    cin >> hapusNo;
    
    Node *temp = head;
    Node *prev = NULL;
    bool ditemukan = false;
    
    // Cari pasien yang akan dihapus
    while (temp != NULL) {
        if (temp->data.noPasien == hapusNo) {
            ditemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    
    if (!ditemukan) {
        cout << "\nPasien dengan No " << hapusNo << " tidak ditemukan!" << endl;
        return;
    }
    
    // Tampilkan data yang akan dihapus
    cout << "\nData yang akan dihapus:" << endl;
    tampilPasien(temp);
    
    // Konfirmasi penghapusan
    char konfirmasi;
    cout << "\nApakah Anda yakin ingin menghapus data ini? (y/n): ";
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Hapus node dari linked list
        if (prev == NULL) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        
        simpanSemuaKeFile();  // Simpan perubahan ke file
        cout << "\nData pasien dengan No " << hapusNo << " berhasil dihapus!" << endl;
    } else {
        cout << "\nPenghapusan dibatalkan!" << endl;
    }
}

// ==================== MENU 3: SEARCHING + EDIT + HAPUS ====================
void searchingpasien() {   
    bacaDataDariFile();
    
    if (head == NULL) {
        cout << "\nData pasien kosong!" << endl;
        return;
    }

    int pilihCari;
    cout << endl;
    cout << "========== MENU SEARCHING PASIEN ==========" << endl;
    cout << "1. Cari berdasarkan No Pasien" << endl;
    cout << "2. Cari berdasarkan Nama" << endl;
    cout << "3. Cari berdasarkan Prioritas" << endl;
    cout << "Pilih: ";
    cin >> pilihCari;

    Node *hasil[100];  // Array untuk menyimpan hasil pencarian
    int jmlHasil = 0;
    
    switch(pilihCari) {
        case 1: {  // Pencarian berdasarkan No Pasien
            int cariNo;
            cout << "Masukkan No Pasien yang dicari: ";
            while (!(cin >> cariNo)) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Input tidak valid! Masukkan angka: ";
            }
            
            Node *temp = head;
            while (temp != NULL) {
                if (temp->data.noPasien == cariNo) {
                    hasil[jmlHasil++] = temp;
                    break;  // No Pasien, langsung berhenti
                }
                temp = temp->next;
            }
            break;
        }
        case 2: {  // Pencarian berdasarkan Nama
            char cariNama[50];
            cout << "Masukkan Nama Pasien yang dicari: ";
            cin.ignore();
            cin.getline(cariNama, 50);

            Node *temp = head;
            while (temp != NULL) {
                if (strstr(temp->data.nama, cariNama) != NULL) {
                    hasil[jmlHasil++] = temp;
                }
                temp = temp->next;
            }
            break;
        }
        case 3: {  // Pencarian berdasarkan prioritas
            int cariPrioritas;
            cout << "Masukkan Prioritas yang dicari (1-3): ";
            while (!(cin >> cariPrioritas) || cariPrioritas < 1 || cariPrioritas > 3) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Input tidak valid! Masukkan angka (1-3): ";
            }

            Node *temp = head;
            while (temp != NULL) {
                if (temp->data.prioritas == cariPrioritas) {
                    hasil[jmlHasil++] = temp;
                }
                temp = temp->next;
            }
            break;
        }
        default: 
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
    
    if (jmlHasil == 0) {
        cout << "\nPasien tidak ditemukan!" << endl;
        return;
    }
    
    // Tampilkan hasil pencarian
    cout << "\n========== HASIL PENCARIAN ==========" << endl;
    for (int i = 0; i < jmlHasil; i++) {
        cout << "\nHasil ke-" << (i+1) << ":";
        tampilPasien(hasil[i]);
    }
    
    // Menu aksi setelah searching (Edit atau Hapus)
    int pilihAksi;
    cout << "\n========== MENU AKSI ==========" << endl;
    cout << "1. Edit Data" << endl;
    cout << "2. Hapus Data" << endl;
    cout << "3. Kembali ke Menu Utama" << endl;
    cout << "Pilih: ";
    cin >> pilihAksi;
    
    if (pilihAksi == 1) {
        editDataPasien();  // Panggil fungsi edit
    } 
    else if (pilihAksi == 2) {
        hapusDataPasien();  // Panggil fungsi hapus
    }
    else if (pilihAksi == 3) {
        cout << "\nKembali ke menu utama..." << endl;
    }
    else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

int main() {
   int pilih;
    
   do{
    system("cls");
    cout << "==========================================================" << endl;
    cout << "            SISTEM ANTRIAN UGD RUMAH SAKIT               " << endl;
    cout << "==========================================================" << endl;
    cout << "1. Input Data Pasien" << endl;
    cout << "2. Tampilkan Semua Data Pasien" << endl;
    cout << "3. Cari / Edit / Hapus Pasien" << endl;
    cout << "4. Sorting Data Pasien" << endl;
    cout << "5. Tampilkan Antrian by Urgensi" << endl;
    cout << "0. Keluar" << endl;
    cout << "==========================================================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    
    if (pilih < 0 || pilih > 5) {
        cout << "\nPilihan tidak valid! Silakan pilih menu 0-5." << endl;
        cout << "\nTekan Enter untuk lanjut...";
        cin.ignore();
        cin.get();
        continue;
    }

    switch(pilih) {
        case 1:
            inputPasien();  // MENU 1
            break;
        case 2:
            tampilData();   // MENU 2
            break;
        case 3:
            searchingpasien();  // MENU 3
            break;
        case 4:
            sortingData();  // MENU 4
            break;
        case 5:
            tampilAntrianByUrgensi();  // MENU 5
            break;
        case 0:
            cout << "\nTerima kasih telah menggunakan Sistem Antrian UGD!" << endl;
            break;
    }

    if (pilih != 0) {
        cout << "\nTekan Enter untuk lanjut...";
        cin.ignore();
        cin.get();
    }

   } while (pilih != 0);

    return 0;
}
