#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std; // теперь std:: не нужно

class Tovar {
private:
    string name;
    string country;
    string manufacturer;
    int article;
    double price;

public:
    Tovar(string n = "", string c = "", string m = "", int a = 0, double p = 0.0)
        : name(move(n)), country(move(c)), manufacturer(move(m)), article(a), price(p) {}

    int getArticle() const { return article; }
    double getPrice() const { return price; }
    string getName() const { return name; }

    void print() const {
        cout << "Артикул: " << article << " | Название: " << name
             << " | Страна: " << country << " | Производитель: " << manufacturer
             << " | Цена: " << price << endl;
    }

    void edit() {
        cout << "Введите новое название: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите новую страну: ";
        getline(cin, country);
        cout << "Введите нового производителя: ";
        getline(cin, manufacturer);
        cout << "Введите новый артикул: ";
        cin >> article;
        cout << "Введите новую цену: ";
        cin >> price;
    }

    friend istream& operator>>(istream& in, Tovar& t) {
        cout << "Введите название: ";
        in.ignore();
        getline(in, t.name);
        cout << "Введите страну: ";
        getline(in, t.country);
        cout << "Введите производителя: ";
        getline(in, t.manufacturer);
        cout << "Введите артикул: ";
        in >> t.article;
        cout << "Введите цену: ";
        in >> t.price;
        return in;
    }
};

// Функция для поиска по артикулу
int findByArticle(const vector<Tovar>& vec, int article) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].getArticle() == article) return i;
    }
    return -1; // не найдено
}

// Функция для сортировки по артикулу
void sortByArticle(vector<Tovar>& vec) {
    sort(vec.begin(), vec.end(), [](const Tovar& a, const Tovar& b) {
        return a.getArticle() < b.getArticle();
    });
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    system("chcp 65001");

    vector<Tovar> tovars;
    int choice;

    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Добавить товар\n";
        cout << "2. Показать все товары\n";
        cout << "3. Поиск товара по артикулу\n";
        cout << "4. Редактировать товар\n";
        cout << "5. Обмен двух товаров по индексам\n";
        cout << "6. Сортировка товаров по артикулу\n";
        cout << "7. Очистить все товары\n";
        cout << "8. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Tovar t;
                cin >> t;
                tovars.push_back(t);
                cout << "Товар добавлен!\n";
                break;
            }
            case 2: {
                if (tovars.empty()) {
                    cout << "Список товаров пуст.\n";
                } else {
                    cout << "\n=== Список товаров ===\n";
                    for (const auto& t : tovars) t.print();
                }
                break;
            }
            case 3: {
                int art;
                cout << "Введите артикул для поиска: ";
                cin >> art;
                int index = findByArticle(tovars, art);
                if (index != -1) {
                    cout << "Товар найден:\n";
                    tovars[index].print();
                } else {
                    cout << "Товар с таким артикулом не найден.\n";
                }
                break;
            }
            case 4: {
                int art;
                cout << "Введите артикул товара для редактирования: ";
                cin >> art;
                int index = findByArticle(tovars, art);
                if (index != -1) {
                    tovars[index].edit();
                    cout << "Товар обновлён.\n";
                } else {
                    cout << "Товар с таким артикулом не найден.\n";
                }
                break;
            }
            case 5: {
                int i1, i2;
                cout << "Введите индексы двух товаров для обмена: ";
                cin >> i1 >> i2;
                if (i1 >= 0 && i1 < (int)tovars.size() && i2 >= 0 && i2 < (int)tovars.size()) {
                    swap(tovars[i1], tovars[i2]);
                    cout << "Обмен выполнен.\n";
                } else {
                    cout << "Неверные индексы.\n";
                }
                break;
            }
            case 6: {
                sortByArticle(tovars);
                cout << "Товары отсортированы по артикулу.\n";
                break;
            }
            case 7: {
                tovars.clear();
                cout << "Все товары удалены.\n";
                break;
            }
            case 8:
                cout << "Программа завершена.\n";
                break;
            default:
                cout << "Неверный выбор, попробуйте снова.\n";
        }

    } while (choice != 8);

    return 0;
}
