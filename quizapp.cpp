#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h> 
#include <sstream>
#include <vector>

using namespace std;

string cevapGir() {
    string input;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 27) { 
            cout << endl;
            return "__ESC_PRESSED__";
        } else if (ch == 13) { 
            cout << endl;
            return input;
        } else if (ch == 8) {
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
        } else {
            input += ch;
            cout << ch;
        }
    }
}


const int MAX_WORDS = 100;
const int MAX_SCORES = 50;
const int MAX_USERS = 50;
bool escBasildi() {
    if (_kbhit()) {
        int key = _getch();
        if (key == 27) { 
            return true;
        }
    }
    return false;
}

string escliGiris() {
    string input;
    char ch;
    while (true) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) { 
                cout << endl;
                return "__ESC_PRESSED__";
            } else if (ch == 13) { 
                cout << endl;
                return input;
            } else if (ch == 8) { 
                if (!input.empty()) {
                    input.pop_back();
                    cout << "\b \b";
                }
            } else {
                input += ch;
                cout << ch;
            }
        }
    }
}

string gizliSifre() {
    string password;
    char ch;
    
    
    if (_kbhit()) {
        ch = _getch();
        if (ch == 27) { 
            return "__ESC_PRESSED__";
        }
        
        if (ch != 13) { 
            password += ch;
            cout << "*";
        } else {
            cout << endl;
            return password;
        }
    }
    
    
    while(true) {
        ch = _getch();
        
        if(ch == 13) { 
            cout << endl;
            return password;
        } 
        else if(ch == 27) { 
            cout << endl;
            return "__ESC_PRESSED__"; 
        } 
        else if(ch == 8) { 
            if(password.length() > 0) {
                password.pop_back();
                cout << "\b \b";
            }
        } 
        else {
            password += ch;
            cout << "*";
        }
    }
}

string englishWords[MAX_WORDS];
string turkishWords[MAX_WORDS];
int wordCount = 0;


string usernames[MAX_USERS];
string passwords[MAX_USERS];
int scores[MAX_USERS][MAX_SCORES];
int scoreCount[MAX_USERS];
int userCount = 0;

void kelimeYukle() {
    wordCount = 0;
    ifstream file("kelimeler.txt");
    string eng, tur;
    
    while (wordCount < MAX_WORDS && getline(file, eng) && getline(file, tur)) {
        englishWords[wordCount] = eng;
        turkishWords[wordCount] = tur;
        wordCount++;
    }
}

void kelimeKaydet() {
    ofstream file("kelimeler.txt");
    for(int i = 0; i < wordCount; i++) {
        file << englishWords[i] << endl << turkishWords[i] << endl;
    }
}

void kullaniciYukle() {
    userCount = 0;
    std::ifstream file("users.txt");
    std::string line;
    while (userCount < MAX_USERS && std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream ss(line);
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 2) {
            usernames[userCount] = tokens[0];
            passwords[userCount] = tokens[1];
            scoreCount[userCount] = tokens.size() - 2;
            for (int j = 2; j < tokens.size(); j++) {
                scores[userCount][j - 2] = std::stoi(tokens[j]);
            }
            userCount++;
        }
    }
}

void kullaniciKaydet() {
    std::ofstream file("users.txt");
    for (int i = 0; i < userCount; i++) {
        file << usernames[i] << "," << passwords[i];
        for (int j = 0; j < scoreCount[i]; j++) {
            file << "," << scores[i][j];
        }
        file << std::endl;
    }
}

void eskiKullanicilariDonustur() {
    std::ifstream infile("users.txt");
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty())
            lines.push_back(line);
    }
    infile.close();
    std::ofstream outfile("users_new.txt");
    for (size_t i = 0; i + 2 < lines.size(); ) {
        std::string username = lines[i];
        std::string password = lines[i+1];
        int score_count = std::stoi(lines[i+2]);
        std::string scores = (i+3 < lines.size()) ? lines[i+3] : "";
        outfile << username << "," << password;
        if (score_count > 0 && !scores.empty()) {
            std::istringstream ss(scores);
            int score;
            for (int j = 0; j < score_count; j++) {
                ss >> score;
                outfile << "," << score;
            }
        }
        outfile << std::endl;
        i += 3 + (score_count > 0 ? 1 : 0);
    }
    outfile.close();
    std::cout << "Eski kullanıcılar users_new.txt dosyasına CSV olarak aktarıldı!" << std::endl;
}

bool ogretmenGiris() {
    system("cls");
    string username, password;
    cout << "=== Ogretmen Girisi ===\n\n";
    cout << "Kullanici adi: ";
    
    username = escliGiris();
    if (username == "__ESC_PRESSED__") {
        return false;
    }
    
    cout << "Sifre: ";
    password = gizliSifre();
    
    if (password == "__ESC_PRESSED__") {
        return false;
    }
    
    return (username == "admin" && password == "1234");
}

void kelimeEkle() {
    system("cls");
    if(wordCount >= MAX_WORDS) {
        cout << "Maksimum kelime sayisina ulasildi!\n";
        cout << "\nDevam etmek icin Enter'a basin...";
        if (escBasildi()) {
            return;
        }
        cin.get();
        return;
    }

    cout << "=== Yeni Kelime Ekleme ===\n\n";
    cout << "Ingilizce kelimeyi girin: ";
    
    string engWord = escliGiris();
    if (engWord == "__ESC_PRESSED__") {
        return;
    }
    
    cout << "Turkce anlamini girin: ";
    
    string turWord = escliGiris();
    if (turWord == "__ESC_PRESSED__") {
        return;
    }
    
    englishWords[wordCount] = engWord;
    turkishWords[wordCount] = turWord;
    wordCount++;
    kelimeKaydet();
    
    cout << "\nKelime basariyla eklendi!\n";
    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        return;
    }
    cin.get();
}

void kelimeListele() {
    system("cls");
    cout << "=== Kelime Listesi ===\n\n";
    
    if(wordCount == 0) {
        cout << "Kelime listesi bos!\n";
    } else {
        for(int i = 0; i < wordCount; i++) {
            cout << (i+1) << ". " << englishWords[i] << " - " << turkishWords[i] << endl;
            if (escBasildi()) {
                return;
            }
        }
    }
    
    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        return;
    }
    cin.get();
}

void kelimeSil() {
    system("cls");
    cout << "=== Kelime Silme ===\n\n";
    
    if(wordCount == 0) {
        cout << "Silinecek kelime yok!\n";
        cout << "\nDevam etmek icin Enter'a basin...";
        if (escBasildi()) {
            return;
        }
        cin.get();
        return;
    } else {
        kelimeListele();
        cout << "\nSilmek istediginiz kelimenin numarasini girin (1-" << wordCount << "): ";
        
        string choice = escliGiris();
        if (choice == "__ESC_PRESSED__") {
            return;
        }
        
        try {
            int index = stoi(choice) - 1;
            if(index >= 0 && index < wordCount) {
                for(int i = index; i < wordCount - 1; i++) {
                    englishWords[i] = englishWords[i + 1];
                    turkishWords[i] = turkishWords[i + 1];
                }
                wordCount--;
                kelimeKaydet();
                cout << "\nKelime basariyla silindi!\n";
            } else {
                cout << "\nGecersiz numara!\n";
            }
        } catch(...) {
            cout << "\nGecersiz giris!\n";
        }
    }
    
    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        return;
    }
    cin.get();
}

void kelimeAra() {
    system("cls");
    cout << "=== Kelime Arama ===\n\n";
    cout << "Aramak istediginiz kelimeyi girin: ";
    
    string search = escliGiris();
    if (search == "__ESC_PRESSED__") {
        return;
    }
    
    bool found = false;
    for(int i = 0; i < wordCount; i++) {
        if(englishWords[i].find(search) != string::npos || 
           turkishWords[i].find(search) != string::npos) {
            if(!found) {
                cout << "\nBulunan kelimeler:\n";
                found = true;
            }
            cout << "- " << englishWords[i] << " - " << turkishWords[i] << endl;
        }
    }
    
    if(!found) {
        cout << "\nAranan kelime bulunamadi!\n";
    }
    
    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        return;
    }
    cin.get();
}

void puanListele() {
    system("cls");
    cout << "=== Ogrenci Puanlari ===\n\n";
    
    for(int i = 0; i < userCount; i++) {
        cout << "Ogrenci: " << usernames[i] << "  Puanlar: ";
        if(scoreCount[i] > 0) {
            for(int j = 0; j < scoreCount[i]; j++) {
                cout << scores[i][j] << " ";
            }
            cout << "\n\n";
        } else {
            cout << "Henuz test cozmedi\n\n";
        }
    }
    
    cout << "Devam etmek icin Enter'a basin...";
    cin.get();
}

void kullaniciListele() {
    system("cls");
    cout << "=== Kayitli Kullanicilar ===\n\n";
    
    if(userCount == 0) {
        cout << "Henuz kayitli kullanici yok!\n";
    } else {
        for(int i = 0; i < userCount; i++) {
            cout << (i+1) << ". " << usernames[i] << endl;
        }
    }
    
    cout << "\nDevam etmek icin Enter'a basin...";
    cin.get();
}

void ogretmenMenu() {
    while(true) {
        system("cls");
        cout << "=== Ogretmen Menusu ===\n\n";
        cout << "1. Kelime Ekle\n";
        cout << "2. Kelimeleri Listele\n";
        cout << "3. Kelime Sil\n";
        cout << "4. Kelime Ara\n";
        cout << "5. Ogrenci Puanlarini Goruntule\n";
        cout << "6. Ogrencileri Listele\n";
        cout << "7. Cikis\n\n";
        cout << "Seciminiz: ";
        
        if (escBasildi()) {
            break;
        }
        
        string choice;
        getline(cin, choice);
        
        if(choice == "1") kelimeEkle();
        else if(choice == "2") kelimeListele();
        else if(choice == "3") kelimeSil();
        else if(choice == "4") kelimeAra();
        else if(choice == "5") puanListele();
        else if(choice == "6") kullaniciListele();
        else if(choice == "7") break;
    }
}

bool ogrenciKayit() {
    system("cls");
    if(userCount >= MAX_USERS) {
        cout << "Maksimum kullanici sayisina ulasildi!\n";
        cout << "\nDevam etmek icin Enter'a basin...";
        if (escBasildi()) {
            return false;
        }
        cin.get();
        return false;
    }

    cout << "=== Ogrenci Kayit ===\n\n";
    cout << "Kullanici adi: ";
    
    string username = escliGiris();
    if (username == "__ESC_PRESSED__") {
        return false;
    }
    
    for(int i = 0; i < userCount; i++) {
        if(usernames[i] == username) {
            cout << "\nBu kullanici adi zaten alinmis!\n";
            cout << "\nDevam etmek icin Enter'a basin...";
            if (escBasildi()) {
                return false;
            }
            cin.get();
            return false;
        }
    }
    
    cout << "Sifre: ";
    string password = gizliSifre();
    
    if (password == "__ESC_PRESSED__") {
        return false;
    }
    
    usernames[userCount] = username;
    passwords[userCount] = password;
    scoreCount[userCount] = 0;
    userCount++;
    
    kullaniciKaydet();
    
    cout << "\nKayit basarili!\n";
    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        return false;
    }
    cin.get();
    return true;
}

int ogrenciGiris() {
    system("cls");
    cout << "=== Ogrenci Girisi ===\n\n";
    cout << "Kullanici adi: ";
    
    string username = escliGiris();
    if (username == "__ESC_PRESSED__") {
        return -1;
    }
    
    cout << "Sifre: ";
    string password = gizliSifre();
    
    if (password == "__ESC_PRESSED__") {
        return -1;
    }
    
    for(int i = 0; i < userCount; i++) {
        if(usernames[i] == username && passwords[i] == password) {
            return i;
        }
    }
    
    cout << "\nHatali kullanici adi veya sifre!\n";
    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        return -1;
    }
    cin.get();
    return -1;
}

void kelimeKaristir() {
    srand(time(0));
    for(int i = wordCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(englishWords[i], englishWords[j]);
        swap(turkishWords[i], turkishWords[j]);
    }
}

void testYap(int userIndex) {
    if(wordCount < 10) {
        cout << "Test icin yeterli kelime yok! En az 10 kelime gerekli.\n";
        cout << "\nDevam etmek icin Enter'a basin...";
        if (escBasildi()) {
            return;
        }
        cin.get();
        return;
    }
    
    system("cls");
    cout << "=== Kelime Testi ===\n\n";
    
    kelimeKaristir();
    int score = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes = 0;
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
        saved_attributes = consoleInfo.wAttributes;
    }

    bool erkenCikis = false;
    for(int i = 0; i < 10; i++) {
        cout << (i+1) << ". soru:\n";
        cout << englishWords[i] << " kelimesinin Turkce karsiligi nedir?\n";

        if (escBasildi()) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Testten cikildi.\n";
            SetConsoleTextAttribute(hConsole, saved_attributes);
            erkenCikis = true;
            break;
        }

        string answer = cevapGir();
        if (answer == "__ESC_PRESSED__") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Testten cikildi.\n";
            SetConsoleTextAttribute(hConsole, saved_attributes);
            erkenCikis = true;
            break;
        }

        if(answer == turkishWords[i]) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "Dogru!\n\n";
            score += 10;
        } else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Yanlis! Dogru cevap: " << turkishWords[i] << "\n\n";
        }
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }

    if (erkenCikis) {
        cout << "Test erken sonlandirildi.\n";
    } else {
        cout << "Test tamamlandi!\n";
    }
    cout << "Puaniniz: " << score << "/100\n";

    scores[userIndex][scoreCount[userIndex]] = score;
    scoreCount[userIndex]++;
    kullaniciKaydet();

    cout << "\nDevam etmek icin Enter'a basin...";
    if (escBasildi()) {
        SetConsoleTextAttribute(hConsole, saved_attributes);
        return;
    }
    cin.get();
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void puanGoster(int userIndex) {
    system("cls");
    cout << "=== Puanlariniz ===\n\n";
    
    if(scoreCount[userIndex] == 0) {
        cout << "Henuz test cozmediniz!\n";
    } else {
        for(int i = 0; i < scoreCount[userIndex]; i++) {
            cout << (i+1) << ". Test: " << scores[userIndex][i] << " puan\n";
        }
    }
    
    cout << "\nDevam etmek icin Enter'a basin...";
    cin.get();
}

void ogrenciMenu(int userIndex) {
    while(true) {
        system("cls");
        cout << "=== Ogrenci Menusu ===\n\n";
        cout << "Hos geldin, " << usernames[userIndex] << "!\n\n";
        cout << "1. Test Ol\n";
        cout << "2. Puanlarimi Goruntule\n";
        cout << "3. Cikis\n\n";
        cout << "Seciminiz: ";
        
        if (escBasildi()) {
            break;
        }
        
        string choice;
        getline(cin, choice);
        
        if(choice == "1") testYap(userIndex);
        else if(choice == "2") puanGoster(userIndex);
        else if(choice == "3") break;
    }
}

int main() {
    setlocale(LC_ALL, "Turkish");
    kelimeYukle();
    kullaniciYukle(); 
    while(true) {
        system("cls");
        cout << "=== Kelime Ogrenme Uygulamasi ===\n\n";
        cout << "1. Ogretmen Girisi\n";
        cout << "2. Ogrenci Girisi\n";
        cout << "3. Ogrenci Kayit\n";
        cout << "4. Cikis\n\n";
        cout << "Seciminiz: ";
        
        if (escBasildi()) {
            cout << "\nUygulamadan cikiliyor...\n";
            break;
        }
        
        string choice;
        getline(cin, choice);
        
        if(choice == "1") {
            if(ogretmenGiris()) {
                ogretmenMenu();
            } else {
                cout << "\nHatali kullanici adi veya sifre!\n";
                cout << "\nDevam etmek icin Enter'a basin...";
                if (escBasildi()) {
                    continue;
                }
                cin.get();
            }
        }
        else if(choice == "2") {
            int userIndex = ogrenciGiris();
            if(userIndex != -1) {
                ogrenciMenu(userIndex);
            }
        }
        else if(choice == "3") ogrenciKayit();
        else if(choice == "4") break;
    }
    
    return 0;
}
