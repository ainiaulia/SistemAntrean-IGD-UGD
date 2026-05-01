#include <iostream>
#include <cstdio>
using namespace std;

struct Pasien{      
    int noPasien;
    char nama[50];
    int umur;
    char keluhan[100];
    int prioritas;
    char status[20];
};

struct Node{        
    Pasien data;
    Node* next;
};

Node* head = NULL;

void tambahLinkedList(Pasien pasien) {    
    Node* newNode = new Node;
    newNode->data = pasien;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    }else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void hapusLinkedList() {    
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}

void simpanFile(Pasien pasien) {   
    FILE *file = fopen("data_pasien.txt", "a");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    fprintf(file, "%d,%s,%d,%s,%d,%s\n", pasien.noPasien, pasien.nama, pasien.umur, pasien.keluhan, pasien.prioritas, pasien.status);
    fclose(file);
}

void inputPasien() {    
    Pasien pasien;
    int jmlInput;

    cout << "========== INPUT DATA PASIEN ==========\n" << endl;
    cout << "Jumlah Pasien yang akan diinput : ";
    cin >> jmlInput;
    cin.ignore(); 

    for (int i = 0; i < jmlInput; i++) {
        cout << "\nData Pasien ke-" << (i + 1) << ":\n";

        cout << "Masukkan No Pasien : ";
        cin >> pasien.noPasien;

        cout << "Masukkan Nama Pasien : ";
        cin.ignore();
        cin.getline(pasien.nama, 50);

        cout << "Masukkan Umur Pasien : ";
        cin >> pasien.umur;

        cout << "Masukkan Keluhan : ";
        cin.ignore();
        cin.getline(pasien.keluhan, 100);

        cout << "Masukkan Prioritas (1-3) : ";
        cin >> pasien.prioritas;

        cout << "Masukkan Status : ";
        cin.ignore();
        cin.getline(pasien.status, 20);

        simpanFile(pasien);
    }

    cout << "\nData pasien berhasil disimpan!\n" << endl;
}

void tampilkanData() {   
    FILE *file = fopen("data_pasien.txt", "r");
    if (file == NULL) {
        cout << "Gagal membuka file!\n" << endl;
        return;
    }

    hapusLinkedList();
    Pasien pasien;

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
            tampilkanData();
            break;
        case 3:
            cout << "Cari Pasien";
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
