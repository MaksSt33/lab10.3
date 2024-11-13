#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Zodiac {
    string surname;
    string name;
    string zodiac_sign;
    int birthday[3]; // [0] - день, [1] - місяць, [2] - рік
};

// Функція для виведення меню
void displayMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Додати дані про людину\n";
    cout << "2. Відсортувати за датами днів народження\n";
    cout << "3. Показати інформацію про людину за прізвищем\n";
    cout << "4. Зберегти дані у файл\n";
    cout << "5. Зчитати дані з файлу\n";
    cout << "6. Вийти\n";
    cout << "Виберіть опцію: ";
}

// Функція для додавання людини
void addPerson(Zodiac*& people, int& size) {
    Zodiac newPerson;
    cout << "Введіть прізвище: ";
    cin >> newPerson.surname;
    cout << "Введіть ім'я: ";
    cin >> newPerson.name;
    cout << "Введіть знак Зодіаку: ";
    cin >> newPerson.zodiac_sign;
    cout << "Введіть день народження (день, місяць, рік): ";
    cin >> newPerson.birthday[0] >> newPerson.birthday[1] >> newPerson.birthday[2];

    Zodiac* temp = new Zodiac[size + 1];
    for (int i = 0; i < size; ++i) {
        temp[i] = people[i];
    }
    temp[size] = newPerson;
    delete[] people;
    people = temp;
    size++;
}

// Функція для сортування масиву за датами днів народження
void sortByBirthday(Zodiac* people, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (people[i].birthday[2] > people[j].birthday[2] ||
                (people[i].birthday[2] == people[j].birthday[2] && people[i].birthday[1] > people[j].birthday[1]) ||
                (people[i].birthday[2] == people[j].birthday[2] && people[i].birthday[1] == people[j].birthday[1] && people[i].birthday[0] > people[j].birthday[0])) {

                Zodiac temp = people[i];
                people[i] = people[j];
                people[j] = temp;
            }
        }
    }
    cout << "Масив відсортовано за датами днів народження.\n";
}

// Функція для пошуку людини за прізвищем
void searchBySurname(Zodiac* people, int size, const string& surname) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (people[i].surname == surname) {
            cout << "Прізвище: " << people[i].surname
                << ", Ім'я: " << people[i].name
                << ", Знак Зодіаку: " << people[i].zodiac_sign
                << ", День народження: " << people[i].birthday[0] << "."
                << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Людина з таким прізвищем не знайдена.\n";
    }
}

// Функція для збереження масиву у файл
void saveToFile(Zodiac* people, int size, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        file << people[i].surname << " "
            << people[i].name << " "
            << people[i].zodiac_sign << " "
            << people[i].birthday[0] << " "
            << people[i].birthday[1] << " "
            << people[i].birthday[2] << "\n";
    }
    file.close();
    cout << "Дані збережено у файл.\n";
}

// Функція для зчитування масиву з файлу
void loadFromFile(Zodiac*& people, int& size, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Помилка відкриття файлу для зчитування.\n";
        return;
    }
    size = 0;
    Zodiac temp[100];
    while (file >> temp[size].surname >> temp[size].name >> temp[size].zodiac_sign
        >> temp[size].birthday[0] >> temp[size].birthday[1] >> temp[size].birthday[2]) {
        size++;
    }
    delete[] people;
    people = new Zodiac[size];
    for (int i = 0; i < size; ++i) {
        people[i] = temp[i];
    }
    file.close();
    cout << "Дані зчитано з файлу.\n";
    for (int i = 0; i < size; ++i) {
        cout << "Прізвище: " << people[i].surname
            << ", Ім'я: " << people[i].name
            << ", Знак Зодіаку: " << people[i].zodiac_sign
            << ", День народження: " << people[i].birthday[0] << "."
            << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
    
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Zodiac* people = nullptr;
    int size = 0;
    bool running = true;

    while (running) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addPerson(people, size);
            break;
        case 2:
            sortByBirthday(people, size);
            break;
        case 3: {
            string surname;
            cout << "Введіть прізвище: ";
            cin >> surname;
            searchBySurname(people, size, surname);
            break;
        }
        case 4: {
            string filename;
            cout << "Введіть ім'я файлу для збереження: ";
            cin >> filename;
            saveToFile(people, size, filename);
            break;
        }
        case 5: {
            string filename;
            cout << "Введіть ім'я файлу для зчитування: ";
            cin >> filename;
            loadFromFile(people, size, filename);
            break;
        }
        case 6:
            running = false;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    delete[] people;
    return 0;
}
