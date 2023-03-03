#include <iostream>
using namespace std;

int main(){
    char yt;
// Menu Utama Program
do{
cout << "Wellcome!!!  Selamat Datang!!!" << endl <<endl;
cout << "================================================================================================="<<endl;
cout << "MENENTUKAN STATUS SESEORANG DARI JENIS KELAMIN DAN UMUR"<<endl;
cout << "=================================================================================================" << endl;
cout << "Jenis Kelamin : \n\t";
cout << "1. Laki-Laki \n\t2. Perempuan \n";

 home:

int pilihan;

cout << "Masukkan Pilihan Anda (1-2):";

cin >> pilihan;

switch(pilihan){
case 1:
// Jenis Kelamin Laki-Laki
    cout << "Anda Memilih Laki-Laki"<<endl;
    cout << "----------------------------------------------------------------"<<endl;
    awal:
    cout << "Masukkan Umur (0-100) \n";
    int x;
    cin >> x;

        if (x==0){
            cout << "Belum Lahir"<<endl;
        }
        else if (x>=1&&x<=4){
            cout << "Balita (lk)"<<endl;
        }
        else if (x>=5&&x<=8){
            cout << "Anak kecil laki-laki"<<endl;
        }
        else if (x>=9&&x<=12){
            cout << "Anak besar laki-laki"<<endl;
        }
        else if (x>=13&&x<=16){
            cout << "Perjaka"<<endl;
        }
        else if (x>=17&&x<=25){
            cout << "Pria Dewasa Muda"<<endl;
        }
        else if (x>=26&&x<=49){
            cout << "Pria Dewasa"<<endl;
        }
        else if (x>=50&&x<=100){
            cout << "Kakek"<<endl;
        }
    // Inputan yang dimasukkan salah
        else{
            cout << "*** Angka yang Anda masukkan melebihi range yang telah ditentukan ***"<<endl;
            cout << "Silahkan coba lagi \n";
            goto awal;
            }
        cout <<endl;
break;
//Jenis Kelamin Perempuan
case 2:
    cout << "Anda Memilih Perempuan"<<endl;
        cout << "----------------------------------------------------------------"<<endl;
    pertama:
    cout << "Masukkan Umur (0-100)"<<endl;
    int y;
    cin >> y;

        if (y==0){
            cout << "Belum Lahir"<<endl;
        }
        else if (y>=1&&y<=4){
            cout << "Balita (pr)"<<endl;
        }
        else if (y>=5&&y<=8){
            cout << "Anak kecil perempuan"<<endl;
        }
        else if (y>=9&&y<=12){
            cout << "Anak besar perempuan"<<endl;
        }
        else if (y>=13&&y<=16){
            cout << "Gadis"<<endl;
        }
        else if (y>=17&&y<=25){
            cout << "Wanita Dewasa Muda"<<endl;
        }
        else if (y>=26&&y<=49){
            cout << "Wanita Dewasa"<<endl;
        }
        else if (y>=50&&y<=100){
            cout << "Nenek"<<endl;
        }
    //Inputan yang dimasukkan salah
        else{
            cout << "*** Angka yang Anda masukkan melebihi range yang telah ditentukan ***"<<endl;
            cout << "Silahkan coba lagi! \n";
            goto pertama;
            }
        cout <<endl;
break;
//Kode Error
default:
    cout << "*** Maaf, data yang Anda inputkan salah ***"<<endl;
    cout << "Silahkan coba lagi! \n\n";
    goto home;
}
// Menampilkan Pilihan Ulangan
     cout << "----------------------------------------------------------------"<<endl;
     cout << "Apakah Anda ingin mengulang?(Y/Any keys?) \n";
        cin >> yt;
    }
        while(yt=='Y'||yt=='y');
        cout << "Terima Kasih"<<endl;
return 0;
}
