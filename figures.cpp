#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cmath>
#include <memory>

using namespace std;

const double PI = 3.14;

class Figure {
public:
    explicit Figure(const string& new_name) : name(new_name) {

    }
    virtual string Name() const {
        return name;
    }
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
private:
    const string name;
};

class Triangle : public Figure {
public:
    explicit Triangle(int new_a, int new_b, int new_c) : Figure("TRIANGLE") {
        a = new_a;
        b = new_b;
        c = new_c;
    }
    double Perimeter() const override {
        return a + b + c;
    }
    double Area() const override {
        double half_perimeter = 0.5 * Perimeter();
        double area = half_perimeter;
        area *= (half_perimeter - a);
        area *= (half_perimeter - b);
        area *= (half_perimeter - c);
        area = sqrt(area);
        return area;
    }
private:
    int a, b, c;
};

class Rect : public Figure {
public:
    explicit Rect(int new_a, int new_b) : Figure("RECT"){
        a = new_a;
        b = new_b;
    }
    double Perimeter() const override {
        return 2 * (a + b);
    }
    double Area() const override {
        return a * b;
    }
private:
    int a, b;
};

class Circle : public Figure {
public:
    explicit Circle(int radius) : Figure("CIRCLE") {
        r = radius;
    }
    double Perimeter() const override {
        return 2 * PI * r;
    }
    double Area() const override {
        return PI * r * r;
    }
private:
    int r;
};

shared_ptr<Figure> CreateFigure(istream & is) {
    string figure_type;
    is >> figure_type;
    if (figure_type == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    if (figure_type == "RECT") {
        int a, b;
        is >> a >> b;
        return make_shared<Rect>(a, b);
    }
    if (figure_type == "CIRCLE") {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    } else {
        throw out_of_range("Wrong type.");
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}