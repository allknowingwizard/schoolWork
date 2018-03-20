#include <iostream>
#include <iomanip>

using namespace std;

struct TempScale {
    int f;
    int c;
};

struct Reading {
    int windSpeed;
    double humidity;
    TempScale temperature;
};

void findReading(Reading * r) {
		cout << "Wind Speed: ";
		cin >> r->windSpeed;
		cout << "Humidity: ";
		cin >> r->humidity;
		cout << "Temperature(F): ";
		int tempF = 0;
		cin >> tempF;
		cout << "Temperature(C): ";
		int tempC = 0;
		cin >> tempC;
		r->temperature = {tempF, tempC};
	}

int main() {
    Reading r = {};
    findReading(&r);
    cout << r.windSpeed << endl;
    cout << r.humidity << endl;
    cout << r.temperature.f << endl;
    cout << r.temperature.c << endl;
    return 0;
}
