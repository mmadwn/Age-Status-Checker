#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

struct UserData
{
    int usia;
    double pendapatanTahunan;
    double tabunganSaatIni;
};

/// Fungsi untuk menghitung target tabungan pensiun
double hitungTargetPensiun(int usia, double pendapatanTahunan)
{
    int tahunMenujuPensiun = 65 - usia;
    double targetPensiun = pendapatanTahunan * 0.8 * 20;  // Asumsi 80% pendapatan selama 20 tahun
    return targetPensiun / pow(1.07, tahunMenujuPensiun); // Asumsi 7% return investasi tahunan
}

// Fungsi untuk memberikan saran investasi
string saranInvestasi(int usia)
{
    if (usia < 30)
    {
        return "Fokus pada pertumbuhan agresif. Alokasikan 80-90% ke saham.";
    }
    else if (usia < 40)
    {
        return "Pertumbuhan moderat. Alokasikan 70-80% ke saham, sisanya ke obligasi.";
    }
    else if (usia < 50)
    {
        return "Mulai lebih konservatif. 60-70% saham, 30-40% obligasi.";
    }
    else if (usia < 60)
    {
        return "Lebih berhati-hati. 50-60% saham, 40-50% obligasi.";
    }
    else
    {
        return "Konservatif. 30-40% saham, 60-70% obligasi dan instrumen aman.";
    }
}
// Fungsi untuk menghitung anggaran bulanan sederhana
void hitungAnggaran(double pendapatanBulanan)
{
    cout << "Anggaran Bulanan yang Disarankan:\n";
    cout << "Kebutuhan (50%): Rp" << fixed << setprecision(2) << pendapatanBulanan * 0.5 << endl;
    cout << "Keinginan (30%): Rp" << pendapatanBulanan * 0.3 << endl;
    cout << "Tabungan (20%): Rp" << pendapatanBulanan * 0.2 << endl;
}

// Fungsi baru untuk perencanaan pembelian rumah
double hitungCicilanRumah(double hargaRumah, int tenorTahun, double sukuBunga)
{
    double bungaBulanan = sukuBunga / 12 / 100;
    int totalBulan = tenorTahun * 12;
    return hargaRumah * bungaBulanan * pow(1 + bungaBulanan, totalBulan) / (pow(1 + bungaBulanan, totalBulan) - 1);
}

// Fungsi baru untuk perencanaan pendidikan anak
double hitungBiayaPendidikan(double biayaAwal, int tahunMulai, int lamaPendidikan, double inflasiTahunan)
{
    double totalBiaya = 0;
    for (int i = 0; i < lamaPendidikan; i++)
    {
        totalBiaya += biayaAwal * pow(1 + inflasiTahunan / 100, tahunMulai + i);
    }
    return totalBiaya;
}

// Fungsi baru untuk perhitungan asuransi jiwa
double hitungKebutuhanAsuransiJiwa(double pendapatanTahunan, int usia, int usiapensiun)
{
    int tahunKerja = usiapensiun - usia;
    return pendapatanTahunan * tahunKerja * 0.6; // Asumsi 60% pendapatan perlu diganti
}

// Fungsi untuk menyimpan data pengguna
void simpanData(const UserData &data)
{
    ofstream file("user_data.csv", ios::app);
    if (file.is_open())
    {
        file << data.usia << "," << data.pendapatanTahunan << "," << data.tabunganSaatIni << "\n";
        file.close();
    }
}

// Fungsi untuk membaca data pengguna
vector<UserData> bacaData()
{
    vector<UserData> dataList;
    ifstream file("user_data.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        UserData data;
        string temp;
        getline(ss, temp, ',');
        data.usia = stoi(temp);
        getline(ss, temp, ',');
        data.pendapatanTahunan = stod(temp);
        getline(ss, temp, ',');
        data.tabunganSaatIni = stod(temp);
        dataList.push_back(data);
    }
    return dataList;
}

// Tambahkan fungsi baru untuk menampilkan tabel perbandingan
void tampilkanTabelPerbandingan(const vector<double> &data, const vector<string> &labels)
{
    cout << "\nTabel Perbandingan Finansial:\n";
    cout << string(70, '-') << "\n";
    cout << setw(25) << left << "Kategori" << "|" 
         << setw(20) << right << "Nilai (Rp)" << " |" 
         << setw(20) << right << "Persentase" << "\n";
    cout << string(70, '-') << "\n";

    double total = accumulate(data.begin(), data.end(), 0.0);

    for (size_t i = 0; i < data.size(); ++i)
    {
        cout << setw(25) << left << labels[i] << "|" 
             << setw(20) << right << fixed << setprecision(2) << data[i] << " |"
             << setw(19) << right << fixed << setprecision(2) << (data[i] / total * 100) << "%\n";
    }

    cout << string(70, '-') << "\n";
    cout << setw(25) << left << "Total" << "|" 
         << setw(20) << right << fixed << setprecision(2) << total << " |"
         << setw(19) << right << "100.00%\n";
    cout << string(70, '-') << "\n";
}

void tampilkanMenu() {
    cout << "\nMenu Finance Planner:\n";
    cout << "1. Input Data Baru\n";
    cout << "2. Lihat Analisis Finansial\n";
    cout << "3. Lihat Riwayat Data\n";
    cout << "4. Simulasi Skenario\n";
    cout << "5. Ekspor Data ke CSV\n";
    cout << "6. Tambah Tujuan Keuangan\n";
    cout << "7. Lihat Tujuan Keuangan\n";
    cout << "8. Hitung Pajak Penghasilan\n";
    cout << "9. Buat Laporan Keuangan Berkala\n";
    cout << "10. Konversi Mata Uang\n";
    cout << "11. Keluar\n";
    cout << "Pilih menu (1-11): ";
}

void inputDataBaru(UserData &userData) {
    while (true)
    {
        cout << "Masukkan usia Anda: ";
        if (cin >> userData.usia && userData.usia > 0 && userData.usia < 120)
            break;
        cout << "Input tidak valid. Mohon masukkan usia yang benar.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Masukkan pendapatan tahunan Anda: Rp";
        if (cin >> userData.pendapatanTahunan && userData.pendapatanTahunan >= 0)
            break;
        cout << "Input tidak valid. Mohon masukkan pendapatan yang benar.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Masukkan tabungan saat ini: Rp";
        if (cin >> userData.tabunganSaatIni && userData.tabunganSaatIni >= 0)
            break;
        cout << "Input tidak valid. Mohon masukkan tabungan yang benar.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    simpanData(userData);
    cout << "Data berhasil disimpan.\n";
}

void lihatAnalisisFinansial(const UserData &userData, double inflasiTahunan) {
    cout << "\n=== Analisis Finansial ===\n";

    // Pensiun
    double targetPensiun = hitungTargetPensiun(userData.usia, userData.pendapatanTahunan);
    cout << "1. Target Tabungan Pensiun: Rp" << fixed << setprecision(2) << targetPensiun << endl;

    // Investasi
    cout << "\n2. Saran Investasi:\n"
         << saranInvestasi(userData.usia) << endl;

    // Anggaran
    cout << "\n3. Anggaran Bulanan:\n";
    hitungAnggaran(userData.pendapatanTahunan / 12);

    // Perencanaan Rumah
    double hargaRumah = 500000000; // Asumsi harga rumah
    int tenorTahun = 20;
    double sukuBunga = 5.0;
    double cicilanBulanan = hitungCicilanRumah(hargaRumah, tenorTahun, sukuBunga);
    cout << "\n4. Perencanaan Pembelian Rumah:\n";
    cout << "   Cicilan bulanan untuk rumah seharga Rp" << hargaRumah
         << " (tenor " << tenorTahun << " tahun, bunga " << sukuBunga << "%): Rp"
         << fixed << setprecision(2) << cicilanBulanan << endl;

    // Pendidikan Anak
    double biayaKuliahAwal = 50000000; // Asumsi biaya kuliah awal
    int tahunMulaiKuliah = 18;
    int lamaKuliah = 4;
    double totalBiayaKuliah = hitungBiayaPendidikan(biayaKuliahAwal, tahunMulaiKuliah, lamaKuliah, inflasiTahunan);
    cout << "\n5. Perencanaan Pendidikan Anak:\n";
    cout << "   Total biaya pendidikan anak (kuliah): Rp" << fixed << setprecision(2) << totalBiayaKuliah << endl;

    // Asuransi Jiwa
    int usiaPensiun = 65;
    double kebutuhanAsuransi = hitungKebutuhanAsuransiJiwa(userData.pendapatanTahunan, userData.usia, usiaPensiun);
    cout << "\n6. Kebutuhan Asuransi Jiwa:\n";
    cout << "   Jumlah asuransi jiwa yang disarankan: Rp" << fixed << setprecision(2) << kebutuhanAsuransi << endl;

    // Visualisasi
    vector<double> dataVisualisasi = {
        userData.tabunganSaatIni,
        targetPensiun,
        totalBiayaKuliah,
        kebutuhanAsuransi
    };
    vector<string> labels = {
        "Tabungan Saat Ini",
        "Target Pensiun",
        "Biaya Kuliah",
        "Kebutuhan Asuransi"
    };
    tampilkanTabelPerbandingan(dataVisualisasi, labels);
}

void lihatRiwayatData() {
    vector<UserData> riwayatData = bacaData();
    cout << "\nRiwayat Data Keuangan:\n";
    for (const auto &data : riwayatData)
    {
        cout << "Usia: " << data.usia << ", Pendapatan: Rp" << data.pendapatanTahunan
             << ", Tabungan: Rp" << data.tabunganSaatIni << endl;
    }
}

void simulasiSkenario(const UserData &userData) {
    double perubahanPendapatan;
    cout << "Masukkan persentase perubahan pendapatan (contoh: 10 untuk kenaikan 10%, -10 untuk penurunan 10%): ";
    cin >> perubahanPendapatan;

    UserData skenarioData = userData;
    skenarioData.pendapatanTahunan *= (1 + perubahanPendapatan / 100);

    cout << "\n=== Hasil Simulasi Skenario ===\n";
    cout << "Pendapatan baru: Rp" << fixed << setprecision(2) << skenarioData.pendapatanTahunan << endl;
    lihatAnalisisFinansial(skenarioData, 3.0); // Asumsi inflasi 3%
}

void eksporDataKeCSV(const UserData &userData) {
    ofstream file("analisis_finansial.csv");
    if (file.is_open()) {
        file << fixed << setprecision(0); // Set presisi untuk angka bulat
        
        file << "Kategori,Nilai\n";
        file << "Usia," << userData.usia << "\n";
        file << "Pendapatan Tahunan," << userData.pendapatanTahunan << "\n";
        file << "Tabungan Saat Ini," << userData.tabunganSaatIni << "\n";
        
        file << setprecision(2); // Set presisi 2 angka di belakang koma untuk perhitungan finansial
        file << "Target Pensiun," << hitungTargetPensiun(userData.usia, userData.pendapatanTahunan) << "\n";
        
        double inflasiTahunan = 3.0;
        double hargaRumah = 500000000;
        int tenorTahun = 20;
        double sukuBunga = 5.0;
        double biayaKuliahAwal = 50000000;
        int tahunMulaiKuliah = 18;
        int lamaKuliah = 4;
        int usiaPensiun = 65;

        file << "Cicilan Rumah Bulanan," << hitungCicilanRumah(hargaRumah, tenorTahun, sukuBunga) << "\n";
        file << "Total Biaya Pendidikan," << hitungBiayaPendidikan(biayaKuliahAwal, tahunMulaiKuliah, lamaKuliah, inflasiTahunan) << "\n";
        file << "Kebutuhan Asuransi Jiwa," << hitungKebutuhanAsuransiJiwa(userData.pendapatanTahunan, userData.usia, usiaPensiun) << "\n";

        file.close();
        cout << "Data berhasil diekspor ke analisis_finansial.csv\n";
    } else {
        cout << "Gagal membuka file untuk ekspor data.\n";
    }
}

// Tambahkan fungsi ini untuk menyimpan data pengguna
void simpanUserData(const UserData &userData) {
    ofstream file("user_data.txt");
    if (file.is_open()) {
        file << userData.usia << "\n";
        file << userData.pendapatanTahunan << "\n";
        file << userData.tabunganSaatIni << "\n";
        file.close();
        cout << "Data pengguna berhasil disimpan.\n";
    } else {
        cout << "Gagal menyimpan data pengguna.\n";
    }
}

// Tambahkan fungsi ini untuk memuat data pengguna
bool muatUserData(UserData &userData) {
    ifstream file("user_data.txt");
    if (file.is_open()) {
        file >> userData.usia;
        file >> userData.pendapatanTahunan;
        file >> userData.tabunganSaatIni;
        file.close();
        cout << "Data pengguna berhasil dimuat.\n";
        return true;
    }
    return false;
}

// Tambahkan fungsi ini untuk input inflasi
double inputInflasi() {
    double inflasi;
    while (true) {
        cout << "Masukkan perkiraan tingkat inflasi tahunan (%): ";
        if (cin >> inflasi && inflasi >= 0 && inflasi <= 100) {
            return inflasi;
        }
        cout << "Input tidak valid. Mohon masukkan nilai antara 0 dan 100.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Tambahkan struktur data baru
struct TujuanKeuangan {
    string nama;
    double target;
    double progres;
    string tanggalTarget;
};

// Tambahkan fungsi untuk menambah tujuan keuangan
void tambahTujuanKeuangan(vector<TujuanKeuangan> &tujuanList) {
    TujuanKeuangan tujuan;
    cout << "Masukkan nama tujuan keuangan: ";
    cin.ignore();
    getline(cin, tujuan.nama);
    cout << "Masukkan target nominal (Rp): ";
    cin >> tujuan.target;
    cout << "Masukkan progres saat ini (Rp): ";
    cin >> tujuan.progres;
    cout << "Masukkan tanggal target (DD/MM/YYYY): ";
    cin >> tujuan.tanggalTarget;
    tujuanList.push_back(tujuan);
    cout << "Tujuan keuangan berhasil ditambahkan.\n";
}

// Tambahkan fungsi untuk menampilkan tujuan keuangan
void tampilkanTujuanKeuangan(const vector<TujuanKeuangan> &tujuanList) {
    cout << "\n=== Tujuan Keuangan ===\n";
    for (const auto &tujuan : tujuanList) {
        cout << "Nama: " << tujuan.nama << "\n";
        cout << "Target: Rp" << fixed << setprecision(2) << tujuan.target << "\n";
        cout << "Progres: Rp" << tujuan.progres << " (" 
             << (tujuan.progres / tujuan.target * 100) << "%)\n";
        cout << "Tanggal Target: " << tujuan.tanggalTarget << "\n\n";
    }
}

// Tambahkan fungsi untuk menyimpan tujuan keuangan
void simpanTujuanKeuangan(const vector<TujuanKeuangan> &tujuanList) {
    ofstream file("tujuan_keuangan.txt");
    if (file.is_open()) {
        for (const auto &tujuan : tujuanList) {
            file << tujuan.nama << "," << tujuan.target << "," << tujuan.progres << "," << tujuan.tanggalTarget << "\n";
        }
        file.close();
        cout << "Tujuan keuangan berhasil disimpan.\n";
    } else {
        cout << "Gagal menyimpan tujuan keuangan.\n";
    }
}

// Tambahkan fungsi untuk memuat tujuan keuangan
vector<TujuanKeuangan> muatTujuanKeuangan() {
    vector<TujuanKeuangan> tujuanList;
    ifstream file("tujuan_keuangan.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            TujuanKeuangan tujuan;
            string temp;
            getline(ss, tujuan.nama, ',');
            getline(ss, temp, ',');
            tujuan.target = stod(temp);
            getline(ss, temp, ',');
            tujuan.progres = stod(temp);
            getline(ss, tujuan.tanggalTarget);
            tujuanList.push_back(tujuan);
        }
        file.close();
        cout << "Tujuan keuangan berhasil dimuat.\n";
    }
    return tujuanList;
}

// Tambahkan fungsi untuk menghitung pajak penghasilan sederhana
double hitungPajakPenghasilan(double pendapatanTahunan) {
    if (pendapatanTahunan <= 50000000) {
        return pendapatanTahunan * 0.05;
    } else if (pendapatanTahunan <= 250000000) {
        return 2500000 + (pendapatanTahunan - 50000000) * 0.15;
    } else {
        return 32500000 + (pendapatanTahunan - 250000000) * 0.25;
    }
}

// Tambahkan fungsi untuk membuat laporan keuangan berkala
void buatLaporanKeuanganBerkala(const UserData &userData, const vector<TujuanKeuangan> &tujuanList) {
    ofstream file("laporan_keuangan.txt");
    if (file.is_open()) {
        file << "=== Laporan Keuangan Berkala ===\n\n";
        file << "Data Pengguna:\n";
        file << "Usia: " << userData.usia << "\n";
        file << "Pendapatan Tahunan: Rp" << fixed << setprecision(2) << userData.pendapatanTahunan << "\n";
        file << "Tabungan Saat Ini: Rp" << userData.tabunganSaatIni << "\n\n";

        file << "Tujuan Keuangan:\n";
        for (const auto &tujuan : tujuanList) {
            file << "- " << tujuan.nama << ": Rp" << tujuan.target 
                 << " (Progres: " << (tujuan.progres / tujuan.target * 100) << "%)\n";
        }

        file << "\nAnalisis Finansial:\n";
        file << "Target Pensiun: Rp" << hitungTargetPensiun(userData.usia, userData.pendapatanTahunan) << "\n";
        file << "Estimasi Pajak Penghasilan: Rp" << hitungPajakPenghasilan(userData.pendapatanTahunan) << "\n";

        file.close();
        cout << "Laporan keuangan berhasil dibuat dan disimpan dalam file 'laporan_keuangan.txt'.\n";
    } else {
        cout << "Gagal membuat laporan keuangan.\n";
    }
}

// Tambahkan fungsi untuk konversi mata uang
double konversiMataUang(double jumlah, string dari, string ke) {
    // Kurs mata uang terhadap IDR (contoh, perlu diperbarui secara berkala)
    const double USD_TO_IDR = 14500;
    const double EUR_TO_IDR = 17000;
    const double SGD_TO_IDR = 10800;

    double hasilIDR;

    if (dari == "IDR") {
        hasilIDR = jumlah;
    } else if (dari == "USD") {
        hasilIDR = jumlah * USD_TO_IDR;
    } else if (dari == "EUR") {
        hasilIDR = jumlah * EUR_TO_IDR;
    } else if (dari == "SGD") {
        hasilIDR = jumlah * SGD_TO_IDR;
    } else {
        cout << "Mata uang asal tidak dikenal.\n";
        return -1;
    }

    if (ke == "IDR") {
        return hasilIDR;
    } else if (ke == "USD") {
        return hasilIDR / USD_TO_IDR;
    } else if (ke == "EUR") {
        return hasilIDR / EUR_TO_IDR;
    } else if (ke == "SGD") {
        return hasilIDR / SGD_TO_IDR;
    } else {
        cout << "Mata uang tujuan tidak dikenal.\n";
        return -1;
    }
}

// Modifikasi fungsi main() untuk menggunakan fitur baru
int main()
{
    cout << R"(
 _____ _                           ____  _                           
|  ___(_)_ __   __ _ _ __   ___ ___|  _ \| | __ _ _ __  _ __   ___ _ __ 
| |_  | | '_ \ / _` | '_ \ / __/ _ \ |_) | |/ _` | '_ \| '_ \ / _ \ '__|
|  _| | | | | | (_| | | | | (_|  __/  __/| | (_| | | | | | | |  __/ |   
|_|   |_|_| |_|\__,_|_| |_|\___\___|_|   |_|\__,_|_| |_|_| |_|\___|_|   
                                                                        
)" << '\n';

    cout << "==================================\n";
    cout << "   Selamat datang di Finance Planner\n";
    cout << "   Asisten Keuangan Pribadi Anda\n";
    cout << "==================================\n\n";

    UserData userData;
    if (!muatUserData(userData)) {
        inputDataBaru(userData);
    }

    double inflasiTahunan = inputInflasi();

    vector<TujuanKeuangan> tujuanList = muatTujuanKeuangan();

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(pilihan) {
            case 1:
                inputDataBaru(userData);
                simpanUserData(userData);
                break;
            case 2:
                lihatAnalisisFinansial(userData, inflasiTahunan);
                break;
            case 3:
                lihatRiwayatData();
                break;
            case 4:
                simulasiSkenario(userData);
                break;
            case 5:
                eksporDataKeCSV(userData);
                break;
            case 6:
                tambahTujuanKeuangan(tujuanList);
                simpanTujuanKeuangan(tujuanList);
                break;
            case 7:
                tampilkanTujuanKeuangan(tujuanList);
                break;
            case 8:
                {
                    double pajak = hitungPajakPenghasilan(userData.pendapatanTahunan);
                    cout << "Estimasi Pajak Penghasilan: Rp" << fixed << setprecision(2) << pajak << endl;
                    cout << "Pendapatan Setelah Pajak: Rp" << (userData.pendapatanTahunan - pajak) << endl;
                }
                break;
            case 9:
                buatLaporanKeuanganBerkala(userData, tujuanList);
                break;
            case 10:
                {
                    double jumlah;
                    string dari, ke;
                    cout << "Masukkan jumlah uang: ";
                    cin >> jumlah;
                    cout << "Masukkan mata uang asal (IDR/USD/EUR/SGD): ";
                    cin >> dari;
                    cout << "Masukkan mata uang tujuan (IDR/USD/EUR/SGD): ";
                    cin >> ke;
                    double hasil = konversiMataUang(jumlah, dari, ke);
                    if (hasil != -1) {
                        cout << jumlah << " " << dari << " = " << fixed << setprecision(2) << hasil << " " << ke << endl;
                    }
                }
                break;
            case 11:
                simpanUserData(userData);
                simpanTujuanKeuangan(tujuanList);
                cout << "Data berhasil disimpan. Terima kasih telah menggunakan Finance Planner!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 11);

    return 0;
}