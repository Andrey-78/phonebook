/*
Задание
Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер телефона.
Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.
В теле конструктора происходит считывание данных из файла и заполнение контейнера.
Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.
В классе PhoneBook реализуйте метод SortByName,
который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке. Если фамилии будут одинаковыми,
то сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка производится по отчествам.
Используйте алгоритмическую функцию sort.
Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов.
Используйте алгоритмическую функцию sort.
Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber.
Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке.
Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found»,
если было найдено больше одного человека, то в строке должно быть «found more than 1».
Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и,
если находит заданного человека в контейнере, то меняет его номер телефона на новый, иначе ничего не делает.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct PhoneNumber {
   string number;
};

class PhoneBook {
private:
   vector<pair<string, PhoneNumber>> records;

public:
   PhoneBook(ifstream& file) {
      string name, number;
      while (file >> name >> number) {
         records.push_back(make_pair(name, PhoneNumber{ number }));
      }
   }

   void SortByName() {
      sort(records.begin(), records.end(), [](const auto& a, const auto& b) {
         if (a.first != b.first) {
            return a.first < b.first;
         }
         else if (a.second.number != b.second.number) {
            return a.second.number < b.second.number;
         }
         else {
            return false;
         }
         });
   }

   void SortByPhone() {
      sort(records.begin(), records.end(), [](const auto& a, const auto& b) {
         if (a.second.number != b.second.number) {
            return a.second.number < b.second.number;
         }
         else if (a.first != b.first) {
            return a.first < b.first;
         }
         else {
            return false;
         }
         });
   }

   tuple<string, PhoneNumber> GetPhoneNumber(const string& name) {
      int count = 0;
      string result;
      PhoneNumber phoneNumber;

      for (const auto& record : records) {
         if (record.first == name) {
            count++;
            phoneNumber = record.second;
         }
      }

      if (count == 0) {
         result = "not found";
      }
      else if (count > 1) {
         result = "found more than 1";
      }

      return make_tuple(result, phoneNumber);
   }

   void ChangePhoneNumber(const std::string& name, const string& newNumber) {
      for (auto& record : records) {
         if (record.first == name) {
            record.second.number = newNumber;
         }
      }
   }

   friend ostream& operator<<(ostream& os, const PhoneBook& phoneBook) {
      for (const auto& record : phoneBook.records) {
         os << record.first << " " << record.second.number << endl;
      }
      return os;
   }
};

int main() {
   ifstream file("phonebook.txt");
   PhoneBook phoneBook(file);
   cout << "Initial records:" << endl;
   cout << phoneBook << endl;

   phoneBook.SortByName();
   cout << "Sorted by name:" << endl;
   cout << phoneBook << endl;

   phoneBook.SortByPhone();
   cout << "Sorted by phone number:" << endl;
   cout << phoneBook << endl;

   string name;
   cout << "Enter a name to get phone number: ";
   cin >> name;
   string result;
   PhoneNumber phoneNumber;
   tie(result, phoneNumber) = phoneBook.GetPhoneNumber(name);
   cout << "Result: " << result << ", Phone number: " << phoneNumber.number << endl;

   string newName, newNumber;
   cout << "Enter a name to change phone number: ";
   cin >> newName;
   cout << "Enter a new phone number: ";
   cin >> newNumber;
   phoneBook.ChangePhoneNumber(newName, newNumber);
   cout << "Updated records:" << endl;
   cout << phoneBook << endl;

   return 0;
}