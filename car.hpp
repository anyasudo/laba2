#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>
#include <stdexcept>

namespace mt {

    class Car {
    private:
        std::string brand_;
        std::string model_;
        std::string body_number_;
        std::string license_plate_;
        int mileage_;

        // приватные методы проверки
        bool is_mileage_valid_(int mileage) const;
        bool check_license_format_(const std::string& plate) const;

    public:
        // Конструкторы 
        Car();  // по умолчанию
        Car(const std::string& brand, const std::string& model,
            const std::string& body_number, const std::string& license_plate,
            int mileage);  // с параметрами
        Car(const Car& other);  // копирования

        Car& operator=(const Car& other);  // оператор присваивания
        ~Car();  // деструктор

        // геттеы
        std::string get_brand() const;
        std::string get_model() const;
        std::string get_body_number() const;
        std::string get_license_plate() const;
        int get_mileage() const;

        // сеттеры
        void set_body_number(const std::string& body_number);
        void set_license_plate(const std::string& license_plate);

        void print_info() const;           // вывод всей информации
        void rollback_mileage(int x);      // скручивание пробега на X
    };

}

#endif