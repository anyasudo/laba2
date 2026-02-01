#include "car.hpp"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");

    cout << "=== ТЕСТИРОВАНИЕ ПРАВИЛА ТРЕХ ===" << endl;

    try {
        // создание объектов
        cout << "\n1. Создание car1 (конструктор по умолчанию):" << endl;
        mt::Car car1;

        cout << "\n2. Создание car2 (конструктор с параметрами):" << endl;
        mt::Car car2("Toyota", "Camry", "123456789", "А123ВС", 50000);
        car2.print_info();

        // конструктор копирования
        cout << "\n3. Правило трех - конструктор копирования (car3 = car2):" << endl;
        mt::Car car3 = car2;
        car3.print_info();

        // оператор присваивания
        cout << "\n4. Правило трех - оператор присваивания (car1 = car2):" << endl;
        car1 = car2;
        car1.print_info();

        // тест самоприсваивания
        cout << "\n5. Тест самоприсваивания (car1 = car1):" << endl;
        car1 = car1;
        cout << "Самоприсваивание выполнено успешно" << endl;

        // цепочка присваиваний
        cout << "\n6. Цепочка присваиваний (car4 = car5 = car2):" << endl;
        mt::Car car4, car5;
        car4 = car5 = car2;
        car4.print_info();

        cout << "\n=== ОСТАЛЬНЫЕ МЕТОДЫ ПО ВАРИАНТУ 2 ===" << endl;

        // сеттеры
        cout << "\n7. Тестирование сеттера гос. номера:" << endl;
        car1.set_license_plate("М456ОР");
        car1.print_info();

        cout << "\n8. Тестирование сеттера номера кузова:" << endl;
        car1.set_body_number("987654321");
        car1.print_info();

        cout << "\n9. Тестирование скручивания пробега:" << endl;
        car1.rollback_mileage(10000);
        car1.print_info();

        cout << "\n10. Тестирование геттеров:" << endl;
        cout << "Марка: " << car2.get_brand() << endl;
        cout << "Модель: " << car2.get_model() << endl;
        cout << "Номер кузова: " << car2.get_body_number() << endl;
        cout << "Гос. номер: " << car2.get_license_plate() << endl;
        cout << "Пробег: " << car2.get_mileage() << " км" << endl;

        // Тест ошибок
        cout << "\n11. Тестирование ошибок:" << endl;
        try {
            car1.rollback_mileage(100000); // слишком много
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

        try {
            car1.set_license_plate("НЕПРАВИЛЬНЫЙ");
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

    }
    catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
    }

    cout << "\n=== КОНЕЦ ПРОГРАММЫ ===" << endl;
    return 0;
}