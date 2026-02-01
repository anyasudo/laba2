#include "car.hpp"

namespace mt {

    // приватные методы проверки 

    bool Car::is_mileage_valid_(int mileage) const {
        return mileage >= 0;
    }

    bool Car::check_license_format_(const std::string& plate) const {
        if (plate.length() != 6) {
            return false;
        }

        std::string allowed_letters = "АВЕКМНОРСТУХ";

        // первый символ должен быть буква из списка
        bool first_ok = false;
        for (char letter : allowed_letters) {
            if (plate[0] == letter) {
                first_ok = true;
                break;
            }
        }

        // 2-4 символы должны быть цифры
        bool digits_ok = true;
        for (int i = 1; i <= 3; i++) {
            if (plate[i] < '0' || plate[i] > '9') {
                digits_ok = false;
                break;
            }
        }

        // 5-6 символы должны быть буквы из списка
        bool last_ok = false;
        for (char letter1 : allowed_letters) {
            for (char letter2 : allowed_letters) {
                if (plate[4] == letter1 && plate[5] == letter2) {
                    last_ok = true;
                    break;
                }
            }
            if (last_ok) break;
        }

        return first_ok && digits_ok && last_ok;
    }

    // конструкторы

    Car::Car() : brand_("Неизвестно"), model_("Неизвестно"),
        body_number_("000000"), license_plate_("А000АА"),
        mileage_(0) {
        std::cerr << "Вызван конструктор по умолчанию" << std::endl;
    }

    Car::Car(const std::string& brand, const std::string& model,
        const std::string& body_number, const std::string& license_plate,
        int mileage) :
        brand_(brand), model_(model), body_number_(body_number),
        license_plate_(license_plate), mileage_(mileage) {

        if (!is_mileage_valid_(mileage)) {
            throw std::invalid_argument("Пробег должен быть неотрицательным");
        }

        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        std::cerr << "Вызван конструктор с параметрами" << std::endl;
    }

    Car::Car(const Car& other) :
        brand_(other.brand_), model_(other.model_),
        body_number_(other.body_number_),
        license_plate_(other.license_plate_),
        mileage_(other.mileage_) {
        std::cerr << "Вызван конструктор копирования" << std::endl;
    }

    // правило трех

    Car& Car::operator=(const Car& other) {
        std::cerr << "Вызван оператор присваивания" << std::endl;

        if (this != &other) {
            brand_ = other.brand_;
            model_ = other.model_;
            body_number_ = other.body_number_;
            license_plate_ = other.license_plate_;
            mileage_ = other.mileage_;
        }
        return *this;
    }

    Car::~Car() {
        std::cerr << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
    }

    // геттеры

    std::string Car::get_brand() const {
        return brand_;
    }

    std::string Car::get_model() const {
        return model_;
    }

    std::string Car::get_body_number() const {
        return body_number_;
    }

    std::string Car::get_license_plate() const {
        return license_plate_;
    }

    int Car::get_mileage() const {
        return mileage_;
    }

    // сеттеры

    void Car::set_body_number(const std::string& body_number) {
        body_number_ = body_number;
    }

    void Car::set_license_plate(const std::string& license_plate) {
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        license_plate_ = license_plate;
        std::cout << "Гос. номер успешно изменен на: " << license_plate_ << std::endl;
    }

    // методы

    void Car::print_info() const {
        std::cout << "=== Информация об автомобиле ===" << std::endl;
        std::cout << "Марка: " << brand_ << std::endl;
        std::cout << "Модель: " << model_ << std::endl;
        std::cout << "Номер кузова: " << body_number_ << std::endl;
        std::cout << "Гос. номер: " << license_plate_ << std::endl;
        std::cout << "Пробег: " << mileage_ << " км" << std::endl;
        std::cout << "================================" << std::endl;
    }

    void Car::rollback_mileage(int x) {
        if (x < 0) {
            throw std::invalid_argument("Значение скручивания должно быть неотрицательным");
        }

        if (mileage_ - x < 0) {
            throw std::invalid_argument("Нельзя скрутить больше, чем текущий пробег");
        }

        mileage_ -= x;
        std::cout << "Пробег уменьшен на " << x << " км" << std::endl;
    }

}