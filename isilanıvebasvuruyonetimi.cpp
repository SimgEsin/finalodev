#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <string>
using namespace std;
void IsilanEkle();
void IlanListeleme();
void IlanSil();
void BasvuruEkle();
void BasvuruListele();
void BasvuruSil();

struct Basvuru
{
    char firma[80];
    char pozisyon[80];
    char ad_soyad[80];
    char CV[1000];
};

// iş ilanları ve başvuru yönetimi

struct IsIlan
{
    char firma[80];
    char pozisyon[80];
    char deneyim[5];
    unsigned int maas;
    char sehir_firma[80];
    unsigned int ID;
};

int main()
{
    char anamenu;
    do
    {
        system("cls");
        cout << "|------Hos Geldiniz------|" << endl;
        cout << "|& Lutfen Secim Yapiniz &|" << endl;
        cout << "|   1- Ilan Ekleme       |" << endl;
        cout << "|   2- Ilan Listeleme    |" << endl;
        cout << "|   3- Ilan Sil          |" << endl;
        cout << "|   4-Basvuru Ekleme     |" << endl;
        cout << "|   5-Basvuru Listele    |" << endl;
        cout << "|   6-Basvuru Sil        |" << endl;
        cout << "|------------------------|" << endl;
        char secim;
        cin >> secim;
        switch (secim)
        {
        case '1':
        {
            IsilanEkle();
            break;
        }
        case '2':
        {
            IlanListeleme();
            break;
        }
        case '3':
        {
            IlanSil();
            break;
        }
        case '4':
        {
            BasvuruEkle();
            break;
        }
        case '5':
        {
            BasvuruListele();
            break;
        }
        case '6':
        {
            BasvuruSil();
            break;
        }
        }
        cout << "Anamenuye Donmek icin: a basin cikmak icin : c" << endl;
        anamenu = getche();

    } while (anamenu == 'a');

    return 0;
}

void IsilanEkle()
{
    IsIlan ilan;

    ofstream yaz("ilanlar.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do
    {
        cin.ignore();
        cout << "Firma Adi Giriniz: " << endl;
        cin.getline(ilan.firma, sizeof(ilan.firma));
        cout << "Pozisyon Giriniz: " << endl;
        cin.getline(ilan.pozisyon, sizeof(ilan.pozisyon));
        cout << "Deneyim Giriniz: " << endl;
        cin.getline(ilan.deneyim, sizeof(ilan.deneyim));
        cout << "Maas Giriniz" << endl;
        cin >> ilan.maas;
        cin.ignore();
        cout << "Sehir Giriniz: " << endl;
        cin.getline(ilan.sehir_firma, sizeof(ilan.sehir_firma));

        cout << endl;
        yaz.write((char *)&ilan, sizeof(ilan));
        adet++;
        cout << "Baska Kayit Eklemek Ister misiniz? (E/H)" << endl;
        secim = getche();
        cin.ignore();
        cout << endl;
    } while (secim == 'e' || secim == 'E');
    cout << adet << " adet Is Ilani Eklendi.." << endl;
    yaz.close();
}

void IlanListeleme()
{
    IsIlan ilan;
    ifstream oku("ilanlar.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(ilan);
    cout << "Toplam Is Ilani Sayisi:" << kayits << endl;

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(ilan));
            oku.read((char *)&ilan, sizeof(ilan));

            cout << i + 1 << ". Is Ilaninin Bilgileri: " << endl;

            cout << "Firma Adi Giriniz: " << ilan.firma << endl;

            cout << "Pozisyon Giriniz: " << ilan.pozisyon << endl;

            cout << "Deneyim Giriniz: " << ilan.deneyim << endl;

            cout << "Maas Giriniz" << ilan.maas << endl;

            cout << "Sehir Giriniz: " << ilan.sehir_firma << endl;

            cout << endl;
        }
    }
    else
        cout << "Ilan  Bulunamadi..." << endl;

    oku.close();
}

void IlanSil()
{
    IsIlan ilan;
    char firma[80];
    char secim = ' ';
    bool var = false;

    ifstream oku("ilanlar.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(ilan);
    cout << " Sileceginiz Firma Adi Giriniz : ";
    cin.ignore();
    cin.getline(firma, sizeof(ilan.firma));

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(ilan));
        oku.read((char *)&ilan, sizeof(ilan));

        if (strcmp(ilan.firma, firma) == 0)
        {
            cout << i + 1 << ". Is Ilaninin Bilgileri: " << endl;

            cout << "Firma Adi Giriniz: " << ilan.firma << endl;

            cout << "Pozisyon Giriniz: " << ilan.pozisyon << endl;

            cout << "Deneyim Giriniz: " << ilan.deneyim << endl;

            cout << "Maas Giriniz" << ilan.maas << endl;

            cout << "Sehir Giriniz: " << ilan.sehir_firma << endl;

            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();
            if (secim == 'H' || secim == 'h')
            {
                IsIlan y_ilan;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

                strcpy(y_ilan.firma, ilan.firma);
                strcpy(y_ilan.pozisyon, ilan.pozisyon);
                strcpy(y_ilan.deneyim, ilan.deneyim);
                y_ilan.maas = ilan.maas;
                strcpy(y_ilan.sehir_firma, ilan.sehir_firma);

                y_dosya.write((char *)&ilan, sizeof(ilan));
                y_dosya.close();
            }
            if (secim == 'e' || secim == 'E')
            {
                var = true;
            }
        }
        else
        {
            IsIlan y_ilan;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

            strcpy(y_ilan.firma, ilan.firma);
            strcpy(y_ilan.pozisyon, ilan.pozisyon);
            strcpy(y_ilan.deneyim, ilan.deneyim);
            y_ilan.maas = ilan.maas;
            strcpy(y_ilan.sehir_firma, ilan.sehir_firma);

            y_dosya.write((char *)&ilan, sizeof(ilan));
            y_dosya.close();
        }
    }
    oku.close();
    if (var)
    {
        remove("ilanlar.dat");
        rename("Yedek.dat", "ilanlar.dat");
        cout << "\n Kayit Silindi" << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\n Kayit Bulunamadi" << endl;
    }
}

void BasvuruEkle()
{
    Basvuru basvuru;

    ofstream yaz("basvurular.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do
    {

        cin.ignore();
        cout << "Firmanin Adini Giriniz: " << endl;
        cin.getline(basvuru.firma, sizeof(basvuru.firma));

        cout << "Adinizi ve Soyadinizi  Giriniz: " << endl;
        cin.getline(basvuru.ad_soyad, sizeof(basvuru.ad_soyad));

        cout << "Pozisyon Giriniz: " << endl;
        cin.getline(basvuru.pozisyon, sizeof(basvuru.pozisyon));

        cout << " CV nizi Giriniz: " << endl;
        cin.getline(basvuru.CV, sizeof(basvuru.CV));

        cout << endl;
        yaz.write((char *)&basvuru, sizeof(basvuru));
        adet++;
        cout << "Baska Basvuru Eklemek Ister misiniz? (E/H)" << endl;
        secim = getche();
        cin.ignore();
        cout << endl;
    } while (secim == 'e' || secim == 'E');
    cout << adet << " adet Basvuru Eklendi.." << endl;
    yaz.close();
}

void BasvuruListele()
{
    Basvuru basvuru;
    ifstream oku("basvurular.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(basvuru);
    cout << "Toplam Basvuru Sayisi:" << kayits << endl;

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(basvuru));
            oku.read((char *)&basvuru, sizeof(basvuru));

            cout << i + 1 << ". Basvuru  Bilgileri: " << endl;

            cout << "Basvurulan Firma Adi : " << basvuru.firma << endl;
            cout << "AD ve Soyad: " << basvuru.ad_soyad << endl;
            cout << "Pozisyon : " << basvuru.pozisyon << endl;
            cout << "CV  : " << basvuru.CV << endl;

            cout << endl;
        }
    }
    else
        cout << "Basvuru  Bulunamadi..." << endl;

    oku.close();
}

void BasvuruSil()
{
    Basvuru basvuru;
    char ad_soyad[80];
    char secim = ' ';
    bool var = false;

    ifstream oku("basvurular.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(basvuru);
    cout << " Sileceginiz Kisinin Adini ve Soyadini Giriniz : ";
    cin.ignore();
    cin.getline(ad_soyad, sizeof(basvuru.ad_soyad));

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(basvuru));
        oku.read((char *)&basvuru, sizeof(basvuru));

        if (strcmp(basvuru.ad_soyad, ad_soyad) == 0)
        {
            cout << i + 1 << ". Basvuru Bilgileri: " << endl;

            cout << " Adi ve Soyadi:  " << basvuru.ad_soyad << endl;

            cout << "Firma Adi : " << basvuru.firma << endl;

            cout << "Pozisyonu: " << basvuru.pozisyon << endl;

            cout << "CV si : " << basvuru.CV << endl;

            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();
            if (secim == 'H' || secim == 'h')
            {
                Basvuru y_basvuru;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

                strcpy(y_basvuru.firma, basvuru.firma);
                strcpy(y_basvuru.pozisyon, basvuru.pozisyon);
                strcpy(y_basvuru.ad_soyad, basvuru.ad_soyad);
                strcpy(y_basvuru.CV, basvuru.CV);

                y_dosya.write((char *)&basvuru, sizeof(basvuru));
                y_dosya.close();
            }
            if (secim == 'e' || secim == 'E')
            {
                var = true;
            }
        }
        else
        {
            Basvuru y_basvuru;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

            strcpy(y_basvuru.firma, basvuru.firma);
            strcpy(y_basvuru.pozisyon, basvuru.pozisyon);
            strcpy(y_basvuru.ad_soyad, basvuru.ad_soyad);
            strcpy(y_basvuru.CV, basvuru.CV);

            y_dosya.write((char *)&basvuru, sizeof(basvuru));
            y_dosya.close();
        }
    }
    oku.close();
    if (var)
    {
        remove("basvurular.dat");
        rename("Yedek.dat", "basvurular.dat");
        cout << "\n Kayit Silindi" << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\n Kayit Bulunamadi" << endl;
    }
}
