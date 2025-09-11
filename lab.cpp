#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

class Tovar {
private:
    std::string name;
    std::string country;
    std::string manufacturer;
    int article;
    double price;

public:
    Tovar(std::string n = "", std::string c = "", std::string m = "", int a = 0, double p = 0.0)
        : name(std::move(n)), country(std::move(c)), manufacturer(std::move(m)), article(a), price(p) {}

    int getArticle() const { return article; }
    double getPrice() const { return price; }
    std::string getName() const { return name; }

    void print() const {
        std::cout << "Артикул: " << article << " | Название: " << name
                  << " | Страна: " << country << " | Производитель: " << manufacturer
                  << " | Цена: " << price << std::endl;
    }

    void edit() {
        std::cout << "Введите новое название: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Введите новую страну: ";
        std::getline(std::cin, country);
        std::cout << "Введите нового производителя: ";
        std::getline(std::cin, manufacturer);
        std::cout << "Введите новый артикул: ";
        std::cin >> article;
        std::cout << "Введите новую цену: ";
        std::cin >> price;
    }

    friend std::istream& operator>>(std::istream& in, Tovar& t) {
        std::cout << "Введите название: ";
        in.ignore();
        std::getline(in, t.name);
        std::cout << "Введите страну: ";
        std::getline(in, t.country);
        std::cout << "Введите производителя: ";
        std::getline(in, t.manufacturer);
        std::cout << "Введите артикул: ";
        in >> t.article;
        std::cout << "Введите цену: ";
        in >> t.price;
        return in;
    }
};

// Функция для поиска по артикулу
int findByArticle(const std::vector<Tovar>& vec, int article) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].getArticle() == article) return i;
    }
    return -1; // не найдено
}

// Функция для сортировки по артикулу
void sortByArticle(std::vector<Tovar>& vec) {
    std::sort(vec.begin(), vec.end(), [](const Tovar& a, const Tovar& b) {
        return a.getArticle() < b.getArticle();
    });
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    system("chcp 65001");

    std::vector<Tovar> tovars;
    int choice;

    do {
        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1. Добавить товар\n";
        std::cout << "2. Показать все товары\n";
        std::cout << "3. Поиск товара по артикулу\n";
        std::cout << "4. Редактировать товар\n";
        std::cout << "5. Обмен двух товаров по индексам\n";
        std::cout << "6. Сортировка товаров по артикулу\n";
        std::cout << "7. Очистить все товары\n";
        std::cout << "8. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Tovar t;
                std::cin >> t;
                tovars.push_back(t);
                std::cout << "Товар добавлен!\n";
                break;
            }
            case 2: {
                if (tovars.empty()) {
                    std::cout << "Список товаров пуст.\n";
                } else {
                    std::cout << "\n=== Список товаров ===\n";
                    for (const auto& t : tovars) t.print();
                }
                break;
            }
            case 3: {
                int art;
                std::cout << "Введите артикул для поиска: ";
                std::cin >> art;
                int index = findByArticle(tovars, art);
                if (index != -1) {
                    std::cout << "Товар найден:\n";
                    tovars[index].print();
                } else {
                    std::cout << "Товар с таким артикулом не найден.\n";
                }
                break;
            }
            case 4: {
                int art;
                std::cout << "Введите артикул товара для редактирования: ";
                std::cin >> art;
                int index = findByArticle(tovars, art);
                if (index != -1) {
                    tovars[index].edit();
                    std::cout << "Товар обновлён.\n";
                } else {
                    std::cout << "Товар с таким артикулом не найден.\n";
                }
                break;
            }
            case 5: {
                int i1, i2;
                std::cout << "Введите индексы двух товаров для обмена: ";
                std::cin >> i1 >> i2;
                if (i1 >= 0 && i1 < (int)tovars.size() && i2 >= 0 && i2 < (int)tovars.size()) {
                    std::swap(tovars[i1], tovars[i2]);
                    std::cout << "Обмен выполнен.\n";
                } else {
                    std::cout << "Неверные индексы.\n";
                }
                break;
            }
            case 6: {
                sortByArticle(tovars);
                std::cout << "Товары отсортированы по артикулу.\n";
                break;
            }
            case 7: {
                tovars.clear();
                std::cout << "Все товары удалены.\n";
                break;
            }
            case 8:
                std::cout << "Программа завершена.\n";
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }

    } while (choice != 8);

    return 0;
}
