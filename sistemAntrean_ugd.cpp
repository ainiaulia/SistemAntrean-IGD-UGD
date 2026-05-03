#include <iostream>
#include <cstdio>
#include <cstring>
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

        while (true) {
            cout << "Masukkan Prioritas (1-3) : ";
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

        simpanFile(pasien);
    }

    cout << "\nData pasien berhasil disimpan!\n" << endl;
}

void tampilData() {   
    FILE *file = fopen("data_pasien.txt", "r");
    if (file == NULL) {
        cout << "Gagal membuka file!\n" << endl;
        return;
    }

    hapusLinkedList();
    Datapasien pasien;

    cout << "\n========== DATA PASIEN ==========\n" << endl;
    while (fscanf(file, "%d,%[^,],%d,%[^,],%d,%[^\n]", &pasien.noPasien, pasien.nama, &pasien.umur, pasien.keluhan, &pasien.prioritas, pasien.status) != EOF) {
        
        tambahLinkedList(pasien);
        cout << "No Pasien : " << pasien.noPasien << endl;
        cout << "Nama      : " << pasien.nama << endl;
        cout << "Umur      : " << pasien.umur << endl;
        cout << "Keluhan   : " << pasien.keluhan << endl;
        cout << "Prioritas : " << pasien.prioritas << endl;
        cout << "Status    : " << pasien.status << endl; 
        cout << "---------------------------------\n" << endl;
    }
    fclose(file);
}

void tampilPasien(Node *temp) {
    cout << "\n--- Pasien Ditemukan ---" << endl;
    cout << "No Pasien : " << temp->data.noPasien << endl;
    cout << "Nama      : " << temp->data.nama << endl;
    cout << "Umur      : " << temp->data.umur << endl;
    cout << "Keluhan   : " << temp->data.keluhan << endl;
    cout << "Prioritas : " << temp->data.prioritas << endl;
    cout << "Status    : " << temp->data.status << endl;
    cout << "---------------------------------" << endl;
}

void searchingpasien() {   
	FILE *file = fopen("data_pasien.txt", "r"); 
    if (file == NULL) {
        cout << "Gagal membuka file atau file belum ada!" << endl;
        return;
    }

    hapusLinkedList(); //function hapus, agar linked list tidak duplikat saat di searching berkali-kali
    Datapasien pasien; //data pasien
    
    while (fscanf(file, "%d,%[^,],%d,%[^,],%d,%[^\n]", &pasien.noPasien, pasien.nama, &pasien.umur, pasien.keluhan, &pasien.prioritas, pasien.status) != EOF) {
        tambahLinkedList(pasien); //function tambah, buat linkedlist baru
    } 
    fclose(file);

    if (head == NULL) {
        cout << "Data pasien kosong!" << endl;
        return;
    }

    int pilihCari;
    cout << endl;
    cout << "========== CARI PASIEN ==========" << endl;
    cout << "1. Cari berdasarkan No Pasien" << endl;
    cout << "2. Cari berdasarkan Nama" << endl;
    cout << "3. Cari berdasarkan Prioritas" << endl;
    cout << "Pilih: ";
    cin >> pilihCari;

    bool ditemukan = false;
    switch(pilihCari) {
        case 1: {
            int cariNo;
            cout << "Masukkan No Pasien yang dicari: ";

		    while (!(cin >> cariNo)) {//validasi jika memasukkan tidak sesuai tipe data
                cin.clear();              // reset error cin
                cin.ignore(100, '\n');    // mengabaikan buffer
                cout << "Input tidak valid! Masukkan angka: ";
            }
             Node *temp = head;

            while (temp != NULL) {
                if (temp->data.noPasien == cariNo) {
                 tampilPasien(temp);
                 ditemukan = true;
                 break;
                }
              temp = temp->next;
            }
            break;
        }
        case 2: {
            char cariNama[50];
            cout << "Masukkan Nama Pasien yang dicari: ";
            cin.ignore();
            cin.getline(cariNama, 50);

            Node *temp = head;

            while (temp != NULL) {
			    if (strstr(temp->data.nama, cariNama) != NULL) {
                 tampilPasien(temp);
                 ditemukan = true;
                }
                temp = temp->next;
            }
            break;
        }

        case 3: {
            int cariPrioritas;
             cout << "Masukkan Prioritas yang dicari (1-3): ";

            while (!(cin >> cariPrioritas)|| cariPrioritas < 1 || cariPrioritas > 3) { //validasi jika memasukkan tidak sesuai tipe data
                cin.clear();              // reset error cin
                cin.ignore(100, '\n');    // mengabaikan buffer
                cout << "Input tidak valid! Masukkan angka (1-3): ";
            }

            Node *temp = head;
            while (temp != NULL) {
			    if (temp->data.prioritas == cariPrioritas) {
                    tampilPasien(temp);
                    ditemukan = true;
                }
                temp = temp->next;
			  }
            break;
        }
        default: cout << "Pilihan tidak valid!" << endl;
        return;
    }
    if(!ditemukan) {
        cout << "\nPasien tidak ditemukan!" << endl;
    }
}

int main() {
   int pilih;
    
   do{
    system("cls");
    cout << "========== SISTEM ANTRIAN UGD ==========" << endl;
    cout << "1. Input Data Pasien" << endl;
    cout << "2. Tampilkan Data Pasien" << endl;
    cout << "3. Cari Pasien" << endl;
    cout << "0. Keluar" << endl;

    do{
        cout << "Pilih menu: ";
        cin >> pilih;
        if (pilih < 0 || pilih > 3) {
            cout << "\nPilihan tidak valid! Silakan pilih menu yang tersedia." << endl;
            cout << "Pilih menu: ";
            cin >> pilih;
        } else {
            break; 
        }
    }while(pilih < 0 || pilih > 3);

    switch(pilih) {
        case 1:
            inputPasien();
            break;
        case 2:
            tampilData();
            break;
        case 3:
            searchingpasien();
            break;
        case 0:
            cout << "Terima kasih!" << endl;
            break;
    }

    cout << "\nTekan Enter untuk lanjut...";
    cin.ignore();
    cin.get();

   }while (pilih != 0);

    return 0;
}