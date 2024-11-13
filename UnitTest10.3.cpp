#include "pch.h"
#include "CppUnitTest.h"
#include "../lab10.3/lab10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // Тест на функцію сортування за датами днів народження
        TEST_METHOD(TestSortByBirthday)
        {
            int size = 3;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };
            people[2] = { "Sidorov", "Sidor", "Cancer", {20, 6, 1970} };

            // Викликаємо функцію сортування
            sortByBirthday(people, size);

            // Перевіряємо, чи правильно відсортовано за датами народження
            Assert::AreEqual(people[0].surname, string("Sidorov"));
            Assert::AreEqual(people[1].surname, string("Petrov"));
            Assert::AreEqual(people[2].surname, string("Ivanov"));

            // Очищення
            delete[] people;
        }

        // Тест на функцію пошуку за прізвищем
        TEST_METHOD(TestSearchBySurname)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };

            std::stringstream buffer;
            std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

            // Викликаємо функцію пошуку
            searchBySurname(people, size, "Ivanov");

            std::cout.rdbuf(oldCout);
            string output = buffer.str();

            Assert::IsTrue(output.find("Ivanov") != string::npos);

            delete[] people;
        }

        // Тест на функції збереження і завантаження з файлу
        TEST_METHOD(TestSaveToFileAndLoadFromFile)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };

            string filename = "testfile.txt";

            // Збереження у файл
            saveToFile(people, size, filename);

            // Створюємо новий масив і завантажуємо з файлу
            Zodiac* loadedPeople = nullptr;
            int loadedSize = 0;
            loadFromFile(loadedPeople, loadedSize, filename);

            // Перевірка, чи завантажені дані збігаються з оригіналом
            Assert::AreEqual(size, loadedSize);
            Assert::AreEqual(people[0].surname, loadedPeople[0].surname);
            Assert::AreEqual(people[1].surname, loadedPeople[1].surname);

            delete[] people;
            delete[] loadedPeople;

            // Видалення тестового файлу
            std::remove(filename.c_str());
        }
    };
}
