
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

struct bd {
    int id;
    string type;
    float price;
    string stat;
};
void preobraz(string* way) {
    for (int i = 0; i < way->length(); i++) {
        if (way[i] == "\\")way[i] = '/'; //компилятор ругается, если ввести не те слеши. Поэтому сделаем так, чтобы он не ругался
    }
}
void readkol(int* k, string* way, string* str) {
    string strr = "";
    int kk = 0;
    ifstream readf(*way);
    if (readf.is_open()) {
        cout << "Началось считвание базы данных" << endl;
        while (true) {
            if (readf.eof()) {
                break;
            }
            else {
                getline(readf, *str);
                if (!str->empty()) {
                    kk++;
                }

            }
        }
        readf.clear();
        readf.seekg(0);
    }
    else {
        cout << "Считывание не удалось";
    }
    readf.close();
    *k = kk;
    Sleep(2000);
    system("cls");
}
void readinf(bd* bike, int* k, string* way) {
    int kk = *k;
    ifstream readf(*way);
    if (readf.is_open()) {
        cout << "Считываетс информация о велосипедах" << endl;
        for (int i = 0; i < kk; i++) {
            readf >> bike[i].id;
            readf >> bike[i].type;
            readf >> bike[i].price;
            readf >> bike[i].stat;
        }
        Sleep(1500);
        cout << "Информация о велосипедах считана" << endl;
        Sleep(1000);
        system("cls");
    }
    else {
        cout << "Считать данные велосипедов не удалось" << endl;
    }
    readf.close();


}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int k = 0, lastInd = 0;
    string way, otvet, str;
    cout << "Для начала работы введите путь к базе данных" << endl;
    getline(cin, way);
    system("cls");
    preobraz(&way); //C:\The work\CPP\lessons\bd.txt
    ifstream read(way);
    if (read.is_open()) {
        cout << "База данных найдена" << endl;
        system("pause");
        system("cls");
        readkol(&k, &way, &str);
        cout << "Количество велосипедов: " << k << endl;
        system("pause");
        system("cls");
        while (true) {
            bd* bike = new bd[k];
            readkol(&k, &way, &str);
            readinf(bike, &k, &way);
            cout << "Выберите один из вариантов" << endl << endl << endl;
            cout << "1. Вывести таблицу " << endl << "2. Добавить велосипед в базу данных" << endl << "3. Удалить велосипед из базы данных" << endl << "4. Изменить статус велосипеда" << endl << "5. Выйти" << endl;
            do {
                
                getline(cin, otvet);
                cout << "считывание ответа" << endl;
                Sleep(1000);
                system("cls");
                if (otvet == "1"  || otvet == "вывести таблицу" || otvet == "Вывести таблицу" || otvet == "вывести" || otvet == "Вывести") {
                    cout << "Выберите один из вариантов" << endl;
                    cout << "1. База данных велосипедов" << endl << "2. Популярные модели" << endl << "3. Свободные модели" << endl;
                    getline(cin, otvet);
                    system("cls");
                    if (otvet == "1" || otvet == "база данных велосипедов" || otvet == "База данных велосипедов" || otvet == "База данных" || otvet == "база данных") {
                        cout << left << setw(3) << "ID" << right << setw(20) << "тип велосипеда" << setw(20) << "Стоимость в сутки" << setw(10) << "Статус" << endl << endl;
                        for (int i = 0; i < k; i++) {
                            cout << left << setw(3) << bike[i].id << right << setw(20) << bike[i].type << setw(20) << bike[i].price << setw(10) << bike[i].stat << endl;
                        }
                        system("pause");
                        system("cls");
                    }
                    else if (otvet == "2" || otvet == "популярные модели" || otvet == "Популярные модели" || otvet == "популярные" || otvet == "Популярные") {
                        int* m = new int[k];
                        for (int i = 0; i < k; i++)m[i] = 0;
                        for (int i = 0; i < k; i++) {
                            for (int j = 0; j < k; j++) {
                                if (bike[i].type == bike[j].type && bike[j].stat == "арендован" && bike[i].stat == "арендован") {
                                    m[i]++;
                                }
                            }                           
                        }
                        int max = 0,index=0;
                        for (int i = 0; i < k; i++) {
                            if (max < m[i]) {
                                max = m[i];
                                index = i;
                            }
                        }
                        cout << left << setw(3) << "ID" << setw(20) << "тип велосипеда" << right << setw(10) << "Статус" << endl << endl;
                        for (int i = 0; i < k; i++) {
                            if (bike[i].stat=="арендован") {
                                cout << left << setw(3) << bike[i].id << setw(20) << bike[i].type << right << bike[i].stat << endl;
                            }                          
                        }
                        cout << endl << "Самый занятый велосипед это " << bike[index].type << endl;
                        system("pause");
                        system("cls");
                        delete[]m;
                    }
                    else if (otvet == "3" || otvet == "Свободные модели" || otvet == "свободные модели" || otvet == "Свободные" || otvet == "свободные") {
                        cout << left << setw(3) << "ID" << setw(20) << "тип велосипеда" << right << setw(10) << "Статус" << endl << endl;
                        for (int i = 0; i < k; i++) {
                            if (bike[i].stat == "свободен") {
                                cout << left << setw(3) << bike[i].id << setw(20) << bike[i].type << right << bike[i].stat << endl;
                            }
                        }
                        system("pause");
                        system("cls");
                    }
                    else {
                        cout << "Некоректный ввод команды" << endl;
                        break;
                    }

                    break;
                }
                else if (otvet == "2"  || otvet == "Добавить велосипед в базу данных" || otvet == "добавить велосипед в базу данных" || otvet == "добавить" || otvet == "Добавить") {
                    readkol(&k, &way, &str);
                    readinf(bike, &k, &way);
                    ofstream file(way);
                    if (file.is_open()) {
                        int n;
                        cout << "Файл готов к обновлению" << endl;
                        cout << "сколько велосипедов вы хотите добавить?" << endl;
                        cin >> n;
                        cin.ignore();
                        system("cls");
                        for (int i = 0; i < k; i++) {

                                file << bike[i].id << " " << bike[i].type << " " << bike[i].price << " " << bike[i].stat << endl;
                        }
                        for (int i = 0; i < n; i++) {
                            k++;
                            file << k << " ";
                            cout << "Введите тип велосипеда" << endl;
                            cin >> str;
                            file << str << " ";
                            cout << "Введите цену за сутки" << endl;
                            cin >> str;
                            cin.ignore();
                            file << str << " свободен" << endl;
                            system("cls");
                        }
                        cout << "Данные обновлены" << endl;
                        Sleep(1000);
                        system("cls");
                    }
                    else {
                        cout << "Ошибка доступа для обновления данных" << endl;
                    }
                    file.close();
                    break;
                }
                else if (otvet == "3"  || otvet == "Удалить велосипед из базы данных" ||  otvet == "удалить велосипед из базы данных" || otvet == "удалить" || otvet == "Удалить") {
                    while (true) {
                        cout << left << setw(3) << "ID" << right << setw(20) << "тип велосипеда" << setw(20) << "Стоимость в сутки" << setw(10) << "Статус" << endl << endl;
                        for (int i = 0; i < k; i++) {
                            cout << left << setw(3) << bike[i].id << right << setw(20) << bike[i].type << setw(20) << bike[i].price << setw(10) << bike[i].stat << endl;
                        }
                        cout << endl << "номер какого велосипеда вы хотите удалить?" << endl << "введите 0, если хотите завершить удаление" << endl;
                        int n,index=1;
                        cin >> n;
                        cin.ignore();
                        if (n == 0) {
                            break;
                        }                    
                        ofstream file(way);
                        for (int i = 0; i < k; i++) {                          
                            if(bike[i].id!=n){
                                file << index << " " << bike[i].type << " " << bike[i].price << " " << bike[i].stat << endl;
                                index++;
                            }
                        }
                        readkol(&k, &way, &str);
                        readinf(bike, &k, &way);
                        file.close();
                    }
                    
                    break;
                }
                else if (otvet == "4" || otvet == "Изменить статус велосипеда" || otvet == "изменить статус велосипеда" || otvet == "Изменить статус" || otvet == "изменить статус" || otvet == "Изменить" || otvet == "изменить") {
                    while (true) {
                        cout << left << setw(3) << "ID" << right << setw(20) << "тип велосипеда" << setw(20) << "Стоимость в сутки" << setw(10) << "Статус" << endl << endl;
                        for (int i = 0; i < k; i++) {
                            cout << left << setw(3) << bike[i].id << right << setw(20) << bike[i].type << setw(20) << bike[i].price << setw(10) << bike[i].stat << endl;
                        }
                        cout << endl << "статус какого велосипеда вы хотите изменить?" << endl << "введите 0, если хотите завершить изменение" << endl;
                        int n;
                        cin >> n;
                        cin.ignore();
                        if (n == 0) {
                            break;
                        }
                        for (int i = 0; i < k; i++) {
                            if (n == bike[i].id) {
                                if (bike[i].stat == "арендован")bike[i].stat = "свободен";
                                else if (bike[i].stat == "свободен")bike[i].stat = "арендован";
                            }
                        }
                        ofstream file(way);
                        for (int i = 0; i < k; i++) {
                            file << bike[i].id << " " << bike[i].type << " " << bike[i].price << " " << bike[i].stat << endl;
                        }
                        file.close();
                        system("cls");
                    }
                    break;
                }
                else if (otvet == "5" || otvet == "Выйти" || otvet == "выйти") {
                    read.close();
                    return 0;
                }
                else {
                    cout << "некоректное введение данных" << endl;
                    Sleep(1200);
                    system("cls");
                    break;
                }
            } while (true);
            delete[]bike;
        }
    }
    else {
        cout << "Не удалось получить доступ к файлу";
    }
    read.close();

    return 0;
}