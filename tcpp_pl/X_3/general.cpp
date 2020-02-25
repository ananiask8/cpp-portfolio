//
// Created by José Hilario on 13 Feb 2020.
//
#include "math.h"

using namespace std;

constexpr double square(const int x) {
    return x*x;
}

const int x = 7;
constexpr double num1 = 1.4*square(x); // eval at compile time

int y = 7;
const double num2 = 1.4*square(y); // eval at run time

bool accept() {
    int tries = 1;
    while (tries < 4) {
        cout << "Do you want to proceed (y or n)?" << endl;
        char answer = 0;
        cin >> answer;

        switch (answer) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                cout << "Sorry, I don't understand that." << endl;
                ++tries;
        }
    }
    cout << "I'll take that for a no." << endl;
    return false;
}

void copy_fct() {
    int v1[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int v2[10];
    for (auto i = 0; i != 10; ++i)
        v2[i] = v1[i];
}

void increment() {
    int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto& x : v) // don't copy
        ++x;
}

int count_x(char* p, char x) {
    if (p == nullptr) return 0;
    int count = 0;
    for(; *p != 0; ++p)
        if (*p == x)
            ++count;
    return count;
}

struct Vector {
    int sz;
    double* elem;
};

void vector_init(Vector& v, int s) {
    v.elem = new double[s]; // allocated in the free store (heap)
    v.sz = s;
}

double read_and_sum(int s) {
    Vector v;
    vector_init(v, s);
    for (int i = 0; i < s; ++i)
        cin >> v.elem[i];

    double sum = 0;
    for (int j = 0; j < s; ++j)
        sum += v.elem[j];

    return sum;
}

void f(Vector v, Vector& rv, Vector* pv) {
    int i1 = v.sz;      // access through name
    int i2 = rv.sz;     // access through reference
    int i3 = pv->sz;    // access through pointer
}

class VectorC {
public:
    VectorC(int s) {
        if (s < 0) throw length_error("Vector constructor size"); // establish invariant
        elem = new double[s];
        sz = s;
    }
    double& operator[](int i) {
        if (i < 0 || i >= size()) throw out_of_range("VectorC::operator[]");
        return elem[i];
    }
    int size() const { return sz; } // a const suffix means that it can be copied to const objects
private:
    double* elem;
    int sz;
};

double read_and_sum_c(int s) {
    VectorC v {s};
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];

    double sum = 0;
    for (int j = 0; j < v.size(); ++j)
        sum += v[j];

    return sum;
}

enum class Color {red, blue, green};
enum class Traffic_light {green, yellow, red};

Color col = Color::red;
Traffic_light light = Traffic_light::red;

Traffic_light& operator++(Traffic_light& t) {
    switch (t) {
        case Traffic_light::green:  return t = Traffic_light::yellow;
        case Traffic_light::yellow:  return t = Traffic_light::red;
        case Traffic_light::red:  return t = Traffic_light::green;
    }
}

void f(VectorC& v) {
    try {
        v[v.size()] = 7;
    } catch (out_of_range) {
        cout << "No way doods" << endl;
    }
}

// Use assertions to find errors at compile time; while exceptions can be used to capture errors at runtime
constexpr double C = 299792.458;
void f(double speed) {
    constexpr double local_max = 160.0 / (60*60);
//    static_assert(speed < C, "can't go that fast"); // error: needs a constant
    static_assert(local_max < C, "can't go that fast");
}