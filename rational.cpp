#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

int GCD(int a, int b)
{
	while (a != b) {
		if (a > b) {
			a -= b;
		} else {
			b -= a;
		}
	}
	return b;
}

class Rational {
public:
    Rational() {
    	numerator = 0;
    	denominator = 1;
    }

    Rational(int new_numerator, int new_denominator) {
    	numerator = new_numerator;
    	denominator = new_denominator;
    	if (denominator == 0) {
    		throw invalid_argument("");
    	}
    	//обработка особых случаев
    	if (denominator < 0) {
    		numerator *= -1;
    		denominator *= -1;
    	}
    	if (numerator == 0) {
    		denominator = 1;
    	}
    	//сокращение дроби
    	if (numerator != 0) {
    		int gcd = GCD(abs(numerator), abs(denominator));
    		numerator /= gcd;
    		denominator /= gcd;
    	}
    }

    int Numerator() const {
    	return numerator;
    }

    int Denominator() const {
    	return denominator;
    }

private:
    int numerator;
    int denominator;
};

Rational operator+(const Rational& a, const Rational& b) {
	int numerator = a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator();
	int denominator = a.Denominator() * b.Denominator();
	return Rational(numerator, denominator);
}

Rational operator-(const Rational& a, const Rational& b) {
	int numerator = a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator();
	int denominator = a.Denominator() * b.Denominator();
	return Rational(numerator, denominator);
}

bool operator==(const Rational& a, const Rational& b) {
	return a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator();
}

Rational operator*(const Rational& a, const Rational& b) {
	int numerator = a.Numerator() * b.Numerator();
	int denominator = a.Denominator() * b.Denominator();
	return Rational(numerator, denominator);
}

Rational operator/(const Rational& a, const Rational& b) {
	if (b.Numerator() == 0) {
		throw domain_error("");
	}
	int numerator = a.Numerator() * b.Denominator();
	int denominator = a.Denominator() * b.Numerator();
	return Rational(numerator, denominator);
}

istream& operator>>(istream& is, Rational& r) {
	int numerator, denominator;
	if (is >> numerator && is.ignore(1) && is >> denominator) {
		r = Rational(numerator, denominator);
	}
	return is;
}

ostream& operator<<(ostream& os, const Rational& r) {
	os << r.Numerator() << '/' << r.Denominator();
	return os;
}

bool operator<(const Rational& a, const Rational& b) {
	return (a - b).Numerator() < 0;
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
