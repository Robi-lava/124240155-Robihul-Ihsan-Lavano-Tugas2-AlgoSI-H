#include <iostream>
using namespace std;

struct Node{
    string nama;
    string keluhan;
    int noAntre;
    Node *kanan;
    Node *kiri;
};

struct Node *buatNode(string nama, string keluhan, int noAntre){
    Node *newNode = new Node;
    newNode->nama=nama;
    newNode->keluhan=keluhan;
    newNode->noAntre=noAntre;
    newNode->kanan=nullptr;
    newNode->kiri=nullptr;
    return newNode;
};

Node *cekDuplikat(Node *head, int noAntre) {
    Node *temp = head;
    while (temp != nullptr) {
        if (temp->noAntre == noAntre) return temp;
        temp = temp->kanan;
    }
    return nullptr;
}

void tambahData(Node *&head, string nama, string keluhan, int noAntre){
    if (cekDuplikat(head, noAntre)) {
        cout << "Error: No Antrean sudah ada.\n";
        return;
    }
    Node *newNode=buatNode(nama,keluhan,noAntre);
    
    if (head==nullptr){
        head=newNode;
        return;
    }
    Node *temp=head;

    if (noAntre < head->noAntre) {
        newNode->kanan = head;
        head->kiri = newNode;
        head = newNode;
        return;
    }

    while(temp->kanan!=nullptr&&temp->kanan->noAntre<noAntre){
        temp=temp->kanan;
    }
    newNode->kanan = temp->kanan;
    if (temp->kanan != nullptr) {
        temp->kanan->kiri = newNode;
    }
    temp->kanan = newNode;
    newNode->kiri = temp;
    cout<<"Pasien berhasil ditambahkan ke daftar\n";
}

void tampilkanAntreanDepan(Node *head){
    if (head==nullptr){
        cout << "Antean kosong.\n";
        return;
    }
    cout<<"Daftar Antrean (Dari Awal)\n";
    cout<<"========================================"<<endl;

    Node *temp=head;
    while(temp!=nullptr){
        cout<<"No Antrean   : "<<temp->noAntre<<endl;
        cout<<"Nama         : "<<temp->nama<<endl;
        cout<<"Keluhan      : "<<temp->keluhan<<endl;
        cout<<"----------------------------------------"<<endl;
        temp=temp->kanan;
    }
}

void tampilkanAnteanBelakang(Node *head){
    if (head==nullptr){
        cout << "Antean kosong.\n";
        return;
    }

    Node* temp = head;
    while (temp->kanan != nullptr) {
        temp = temp->kanan;
    }

    cout<<"Daftar Antrean (Dari Akhir)\n";
    cout<<"========================================"<<endl;
    while(temp!=nullptr){
        cout<<"No Antrean   : "<<temp->noAntre<<endl;
        cout<<"Nama         : "<<temp->nama<<endl;
        cout<<"Keluhan      : "<<temp->keluhan<<endl;
        cout<<"----------------------------------------"<<endl;
        temp=temp->kiri;
    }
}

void cariNoAntre (Node *&head, int key){
    if (head == nullptr) {
        cout << "Antrean kosong.\n";
        return;
    }
    Node *temp=head;
    while (temp!=nullptr&&temp->noAntre!=key){
        temp=temp->kanan;
    }

    if (temp == nullptr) {
        cout << "No Antrean " << key << " Tidak ditemukan\n";
        return;
    }
    cout<<"\nPasien ditemukan:\n";
    cout<<"No Antrean   :"<<temp->noAntre<<endl;
    cout<<"Nama         :"<<temp->nama<<endl;
    cout<<"Keluhan      :"<<temp->keluhan<<endl;
    return;
    
}

void hapusData(Node *&head, int key){
    if (head == nullptr) {
        cout << "Antrean kosong.\n";
        return;
    }
    Node *temp=head;
    while (temp!=nullptr&&temp->noAntre!=key){
        temp=temp->kanan;
    }
    if (temp==nullptr){
        cout<<"No Antrean -"<<key<<"- Tidak ditemukan";
        return;
    }
    if (temp==head){
        head=temp->kanan;
        if(head!=nullptr){
            head->kiri=nullptr;
        }
    } else {
        if (temp->kiri!=nullptr){
            temp->kiri->kanan=temp->kanan;
        }
        if (temp->kanan!=nullptr){
            temp->kanan->kiri=temp->kiri;
        }
    }
    delete temp;
    cout << "Data pasien berhasil dihapus.\n";
}

int main(){
    int menu,noAntre;
    string nama,keluhan;
    Node *head=nullptr;
    do{
    cout<<"=== MENU ANTRIAN PASIEN KLINIK SEHAT SELALU ===\n";
    cout<<"1. Tambah Data Pasien\n";
    cout<<"2. Tampil Antrean dari Awal\n";
    cout<<"3. Tampil Antrean dari Akhir\n";
    cout<<"4. Cari Data Pasien\n";
    cout<<"5. Hapus Data pasien\n";
    cout<<"6. Keluar\n";
    cout<<"Pilih Menu: ";
    cin >> menu;
    switch(menu){
        case 1:
            cout << "Masukkan No Antrean      : ";
            cin >> noAntre;
            cin.ignore(); // bersihkan karakter newline
            cout << "Masukkan Nama Pasien     : ";
            getline(cin, nama);
            cout << "Masukkan Keluhan         : ";
            getline(cin, keluhan);
            tambahData(head, nama, keluhan, noAntre);
            break;

        case 2:
            tampilkanAntreanDepan(head);
            break;

        case 3:
            tampilkanAnteanBelakang(head);
            break;

        case 4:
            cout << "Masukkan No Antrean yang dicari: ";
            cin >> noAntre;
            cariNoAntre(head, noAntre);
            break;

        case 5:
            cout << "Masukkan No Antrean yang akan dihapus: ";
            cin >> noAntre;
            hapusData(head, noAntre);
            break;

        case 6:
            cout << "Terima kasih, program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
            break;
    }
    }while(menu!=6);
}