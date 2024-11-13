#include "pch.h"
#include "CppUnitTest.h"
#include "../lab10.3/lab10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // ���� �� ������� ���������� �� ������ ��� ����������
        TEST_METHOD(TestSortByBirthday)
        {
            int size = 3;
            Zodiac* people = new Zodiac[size];

            // ������ ������ ���
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };
            people[2] = { "Sidorov", "Sidor", "Cancer", {20, 6, 1970} };

            // ��������� ������� ����������
            sortByBirthday(people, size);

            // ����������, �� ��������� ����������� �� ������ ����������
            Assert::AreEqual(people[0].surname, string("Sidorov"));
            Assert::AreEqual(people[1].surname, string("Petrov"));
            Assert::AreEqual(people[2].surname, string("Ivanov"));

            // ��������
            delete[] people;
        }

        // ���� �� ������� ������ �� ��������
        TEST_METHOD(TestSearchBySurname)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            // ������ ������ ���
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };

            std::stringstream buffer;
            std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

            // ��������� ������� ������
            searchBySurname(people, size, "Ivanov");

            std::cout.rdbuf(oldCout);
            string output = buffer.str();

            Assert::IsTrue(output.find("Ivanov") != string::npos);

            delete[] people;
        }

        // ���� �� ������� ���������� � ������������ � �����
        TEST_METHOD(TestSaveToFileAndLoadFromFile)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };

            string filename = "testfile.txt";

            // ���������� � ����
            saveToFile(people, size, filename);

            // ��������� ����� ����� � ����������� � �����
            Zodiac* loadedPeople = nullptr;
            int loadedSize = 0;
            loadFromFile(loadedPeople, loadedSize, filename);

            // ��������, �� ���������� ��� ��������� � ���������
            Assert::AreEqual(size, loadedSize);
            Assert::AreEqual(people[0].surname, loadedPeople[0].surname);
            Assert::AreEqual(people[1].surname, loadedPeople[1].surname);

            delete[] people;
            delete[] loadedPeople;

            // ��������� ��������� �����
            std::remove(filename.c_str());
        }
    };
}
