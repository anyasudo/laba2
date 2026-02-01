#include "car.hpp"

namespace mt {

    // ïðèâàòíûå ìåòîäû ïðîâåðêè 

    bool Car::is_mileage_valid_(int mileage) const {
        return mileage >= 0;
    }

    bool Car::check_license_format_(const std::string& plate) const {
        if (plate.length() != 6) {
            return false;
        }

        std::string allowed_letters = "ÀÂÅÊÌÍÎÐÑÒÓÕ";

        // ïåðâûé ñèìâîë äîëæåí áûòü áóêâà èç ñïèñêà
        bool first_ok = false;
        for (char letter : allowed_letters) {
            if (plate[0] == letter) {
                first_ok = true;
                break;
            }
        }

        // 2-4 ñèìâîëû äîëæíû áûòü öèôðû
        bool digits_ok = true;
        for (int i = 1; i <= 3; i++) {
            if (plate[i] < '0' || plate[i] > '9') {
                digits_ok = false;
                break;
            }
        }

        // 5-6 ñèìâîëû äîëæíû áûòü áóêâû èç ñïèñêà
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

    // êîíñòðóêòîðû

    Car::Car() : brand_("Íåèçâåñòíî"), model_("Íåèçâåñòíî"),
        body_number_("000000"), license_plate_("À000ÀÀ"),
        mileage_(0) {
        std::cerr << "Âûçâàí êîíñòðóêòîð ïî óìîë÷àíèþ" << std::endl;
    }

    Car::Car(const std::string& brand, const std::string& model,
        const std::string& body_number, const std::string& license_plate,
        int mileage) :
        brand_(brand), model_(model), body_number_(body_number),
        license_plate_(license_plate), mileage_(mileage) {

        if (!is_mileage_valid_(mileage)) {
            throw std::invalid_argument("Ïðîáåã äîëæåí áûòü íåîòðèöàòåëüíûì");
        }

        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Ãîñ. íîìåð äîëæåí áûòü â ôîðìàòå: ÁÓÊÂÀ + 3 ÖÈÔÐÛ + 2 ÁÓÊÂÛ\n"
                "Ðàçðåøåííûå áóêâû: À, Â, Å, Ê, Ì, Í, Î, Ð, Ñ, Ò, Ó, Õ\n"
                "Ïðèìåð: À123ÂÑ, Ì456ÎÐ, Õ789ÒÓ");
        }

        std::cerr << "Âûçâàí êîíñòðóêòîð ñ ïàðàìåòðàìè" << std::endl;
    }

    Car::Car(const Car& other) :
        brand_(other.brand_), model_(other.model_),
        body_number_(other.body_number_),
        license_plate_(other.license_plate_),
        mileage_(other.mileage_) {
        std::cerr << "Âûçâàí êîíñòðóêòîð êîïèðîâàíèÿ" << std::endl;
    }

    // ïðàâèëî òðåõ

    Car& Car::operator=(const Car& other) {
        std::cerr << "Âûçâàí îïåðàòîð ïðèñâàèâàíèÿ" << std::endl;

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
        std::cerr << "Âûçâàí äåñòðóêòîð äëÿ " << brand_ << " " << model_ << std::endl;
    }

    // ãåòòåðû

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

    // ñåòòåðû

    void Car::set_body_number(const std::string& body_number) {
        body_number_ = body_number;
    }

    void Car::set_license_plate(const std::string& license_plate) {
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Ãîñ. íîìåð äîëæåí áûòü â ôîðìàòå: ÁÓÊÂÀ + 3 ÖÈÔÐÛ + 2 ÁÓÊÂÛ\n"
                "Ðàçðåøåííûå áóêâû: À, Â, Å, Ê, Ì, Í, Î, Ð, Ñ, Ò, Ó, Õ\n"
                "Ïðèìåð: À123ÂÑ, Ì456ÎÐ, Õ789ÒÓ");
        }

        license_plate_ = license_plate;
        std::cout << "Ãîñ. íîìåð óñïåøíî èçìåíåí íà: " << license_plate_ << std::endl;
    }

    // ìåòîäû

    void Car::print_info() const {
        std::cout << "=== Èíôîðìàöèÿ îá àâòîìîáèëå ===" << std::endl;
        std::cout << "Ìàðêà: " << brand_ << std::endl;
        std::cout << "Ìîäåëü: " << model_ << std::endl;
        std::cout << "Íîìåð êóçîâà: " << body_number_ << std::endl;
        std::cout << "Ãîñ. íîìåð: " << license_plate_ << std::endl;
        std::cout << "Ïðîáåã: " << mileage_ << " êì" << std::endl;
        std::cout << "================================" << std::endl;
    }

    void Car::rollback_mileage(int x) {
        if (x < 0) {
            throw std::invalid_argument("Çíà÷åíèå ñêðó÷èâàíèÿ äîëæíî áûòü íåîòðèöàòåëüíûì");
        }

        if (mileage_ - x < 0) {
            throw std::invalid_argument("Íåëüçÿ ñêðóòèòü áîëüøå, ÷åì òåêóùèé ïðîáåã");
        }

        mileage_ -= x;
        std::cout << "Ïðîáåã óìåíüøåí íà " << x << " êì" << std::endl;
    }


}

