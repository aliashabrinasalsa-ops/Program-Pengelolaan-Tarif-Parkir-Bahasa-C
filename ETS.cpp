#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRANSAKSI 1000
#define DATA_UJI 100000

typedef struct {
    int jenis;
    int jam;
    int biaya;
} Transaksi;

Transaksi transaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

// Fungsi menentukan tarif kendaraan
int hitungTarif(int jenis) {
    if (jenis == 1)
        return 2000;
    else if (jenis == 2)
        return 5000;
    else if (jenis == 3)
        return 8000;
    else
        return 0;
}

// Prosedur menampilkan menu
void tampilkanMenu() {
    printf("\n=== PROGRAM PENGELOLAAN TARIF PARKIR ===\n");
    printf("1. Tambah transaksi parkir\n");
    printf("2. Lihat transaksi\n");
    printf("3. Total pendapatan (iterasi dan rekursi)\n");
    printf("4. Uji 3 algoritma sorting (100.000 data)\n");
    printf("0. Keluar\n");
    printf("Pilih menu: ");
}

// Prosedur input transaksi
void tambahTransaksi() {
    int jenis, jam, tarif, biaya;

    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("Data transaksi sudah penuh!\n");
        return;
    }

    printf("\nJenis kendaraan:\n");
    printf("1. Motor (Rp2.000/jam)\n");
    printf("2. Mobil (Rp5.000/jam)\n");
    printf("3. Truk  (Rp8.000/jam)\n");
    printf("Pilih jenis: ");
    scanf("%d", &jenis);

    tarif = hitungTarif(jenis);

    if (tarif == 0) {
        printf("Jenis kendaraan tidak valid!\n");
        return;
    }

    printf("Lama parkir (jam): ");
    scanf("%d", &jam);

    if (jam <= 0) {
        printf("Lama parkir harus lebih dari 0!\n");
        return;
    }

    biaya = tarif * jam;

    transaksi[jumlahTransaksi].jenis = jenis;
    transaksi[jumlahTransaksi].jam = jam;
    transaksi[jumlahTransaksi].biaya = biaya;
    jumlahTransaksi++;

    printf("\nBiaya parkir: Rp%d\n", biaya);
    printf("Transaksi berhasil disimpan.\n");
}

// Prosedur menampilkan transaksi
void lihatTransaksi() {
    int i;

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi.\n");
        return;
    }

    printf("\n=== DATA TRANSAKSI ===\n");

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("%d. Jenis: %s | Lama: %d jam | Biaya: Rp%d\n",
            i + 1,
            transaksi[i].jenis == 1 ? "Motor" :
            transaksi[i].jenis == 2 ? "Mobil" : "Truk",
            transaksi[i].jam,
            transaksi[i].biaya);
    }
}

// Fungsi total menggunakan iterasi
long long totalIterasi() {
    long long total = 0;
    int i;

    for (i = 0; i < jumlahTransaksi; i++) {
        total += transaksi[i].biaya;
    }

    return total;
}

// Fungsi total menggunakan rekursi
long long totalRekursi(int indeks) {
    if (indeks == jumlahTransaksi)
        return 0;

    return transaksi[indeks].biaya
           + totalRekursi(indeks + 1);
}

// Prosedur membandingkan iterasi dan rekursi
void bandingkanTotal() {
    clock_t mulai, selesai;
    long long hasilIterasi, hasilRekursi;
    double waktuIterasi, waktuRekursi;

    mulai = clock();
    hasilIterasi = totalIterasi();
    selesai = clock();
    waktuIterasi = (double)(selesai - mulai)
                   / CLOCKS_PER_SEC;

    mulai = clock();
    hasilRekursi = totalRekursi(0);
    selesai = clock();
    waktuRekursi = (double)(selesai - mulai)
                   / CLOCKS_PER_SEC;

    printf("\n=== PERBANDINGAN TOTAL PENDAPATAN ===\n");
    printf("Total iterasi : Rp%lld\n", hasilIterasi);
    printf("Total rekursi : Rp%lld\n", hasilRekursi);
    printf("Waktu iterasi : %.8f detik\n", waktuIterasi);
    printf("Waktu rekursi : %.8f detik\n", waktuRekursi);

    if (hasilIterasi == hasilRekursi)
        printf("Hasil kedua metode sama.\n");
}

// Bubble Sort
void bubbleSort(int data[], int n) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int data[], int n) {
    int i, j, kunci;

    for (i = 1; i < n; i++) {
        kunci = data[i];
        j = i - 1;

        while (j >= 0 && data[j] > kunci) {
            data[j + 1] = data[j];
            j--;
        }

        data[j + 1] = kunci;
    }
}

// Fungsi partisi untuk Quick Sort
int partisi(int data[], int rendah, int tinggi) {
    int pivot = data[tinggi];
    int i = rendah - 1;
    int j, temp;

    for (j = rendah; j < tinggi; j++) {
        if (data[j] <= pivot) {
            i++;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    temp = data[i + 1];
    data[i + 1] = data[tinggi];
    data[tinggi] = temp;

    return i + 1;
}

// Quick Sort menggunakan rekursi
void quickSort(int data[], int rendah, int tinggi) {
    if (rendah < tinggi) {
        int posisi = partisi(data, rendah, tinggi);

        quickSort(data, rendah, posisi - 1);
        quickSort(data, posisi + 1, tinggi);
    }
}

// Prosedur menguji performa sorting
void ujiSorting() {
    int *asli, *data;
    int i;
    clock_t mulai, selesai;
    double waktu;

   asli = (int *)malloc(DATA_UJI * sizeof(int));
   data = (int *)malloc(DATA_UJI * sizeof(int));

    if (asli == NULL || data == NULL) {
        printf("Memori tidak cukup!\n");
        free(asli);
        free(data);
        return;
    }

    srand((unsigned int)time(NULL));

    for (i = 0; i < DATA_UJI; i++) {
        asli[i] = rand() % 1000000;
    }

    printf("\n=== UJI SORTING %d DATA ===\n", DATA_UJI);
    printf("Pengujian dimulai. Bubble dan Insertion "
           "dapat memerlukan waktu lama.\n");

    // Bubble Sort
    for (i = 0; i < DATA_UJI; i++)
        data[i] = asli[i];

    mulai = clock();
    bubbleSort(data, DATA_UJI);
    selesai = clock();

    waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;
    printf("Bubble Sort    : %.4f detik\n", waktu);

    // Insertion Sort
    for (i = 0; i < DATA_UJI; i++)
        data[i] = asli[i];

    mulai = clock();
    insertionSort(data, DATA_UJI);
    selesai = clock();

    waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;
    printf("Insertion Sort : %.4f detik\n", waktu);

    // Quick Sort
    for (i = 0; i < DATA_UJI; i++)
        data[i] = asli[i];

    mulai = clock();
    quickSort(data, 0, DATA_UJI - 1);
    selesai = clock();

    waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;
    printf("Quick Sort     : %.4f detik\n", waktu);

    printf("Data terurut Quick Sort (10 pertama):\n");
    for (i = 0; i < 10; i++)
        printf("%d ", data[i]);
    printf("\n");

    free(asli);
    free(data);
}

int main() {
    int pilihan;

    do {
        tampilkanMenu();

        if (scanf("%d", &pilihan) != 1) {
            printf("Input harus berupa angka!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (pilihan) {
            case 1:
                tambahTransaksi();
                break;
            case 2:
                lihatTransaksi();
                break;
            case 3:
                bandingkanTotal();
                break;
            case 4:
                ujiSorting();
                break;
            case 0:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    return 0;
}

