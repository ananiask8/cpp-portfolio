//
// Created by José Hilario on 14 Feb 2020.
//

#include <iostream>
#include <thread>
#include <list>
#include <complex>
#include "general.h"

Complex operator+(Complex a, const Complex& b) { return a += b; }
Complex operator-(Complex a, const Complex& b) { return a -= b; }
Complex operator*(Complex a, const Complex& b) { return a *= b; }
Complex operator/(Complex a, const Complex& b) { return a /= b; }
bool operator==(Complex a, Complex b) {
    return a.real() == b.real() && a.imag() == b.imag();
}
bool operator!=(Complex a, Complex b) { return !(a == b); }

void f(Complex z) {
    Complex a {2.3};
    Complex b {1/a};
    Complex c {a + z*Complex{1, 2.3}};
    if (c != b)
        c = -(b/a) + 2*b;
}

Vector read(std::istream& is) {
    Vector v;
    for (double d; is >> d;)
        v.push_back(d);
    return v;
}

Vector::Vector(std::initializer_list<double> lst)
    :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
    std::copy(lst.begin(), lst.end(), elem);
}

void Vector::push_back(double x) { /*pass*/ }
Vector& Vector::operator=(Vector&& v) { /*pass*/ }

Point::Point(std::initializer_list<double> lst)
        :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
    std::copy(lst.begin(), lst.end(), elem);
}

void use(Container& c) {
    const int sz = c.size();
    for (int i = 0; i < sz; ++i)
        std::cout << c[i] << "\n";
}

void rotate_all(std::vector<Shape*>& v, int angle) {
    for (auto p : v)
        p->rotate(angle);
}

void Smiley::draw() const {
    Circle::draw();
    for (auto p : eyes)
        p->draw();
    if (mouth)
        mouth->draw();
}

void Smiley::set_mouth(Shape *s) {
    mouth = s;
}

void draw_all(std::vector<Shape*> v) {
    for (auto p : v) p->draw();
}

Shape* read_shape(std::istream& is) {
    Point p{1,2};
    double p1, p2, p3;
    int r;
    Kind k;
    Shape* e1;
    Shape* e2;
    Shape* m;
    // .. read all the stuff

    switch (k) {
        case Kind::circle:
            return new Circle{p, r};
        case Kind::triangle:
            return new Triangle{p1, p2, p3};
        case Kind::smiley:
            Smiley* ps = new Smiley{p, r};
            ps->add_eye(e1);
            ps->add_eye(e2);
            ps->set_mouth(m);
            return ps;
    }
}

void user() {
    std::vector<Shape*> v;
    while (std::cin)
        v.push_back(read_shape(std::cin));
    draw_all(v);
    rotate_all(v, 45);
    for (auto p : v) delete p;
}

std::unique_ptr<Shape> read_shape_unique(std::istream& is) {
    Kind k;
    Point p{1,2};
    int r;
    // read shape header from is and find its Kind k
    switch (k) {
        case Kind::circle:
            return std::unique_ptr<Shape>{ new Circle{p, r} };
            // ...
    }
}

void user_unique_ptr() {
    std::vector<std::unique_ptr<Shape>> v;
    while (std::cin)
        v.push_back(read_shape_unique(std::cin));
    // needs version which uses unique pointers
//    draw_all(v);
//    rotate_all(v, 45);
} // all Shapes implicitly destroyed

void test(Complex z1){
    Complex z2{z1}; // copy initialization
    Complex z3;
    z3 = z2; // copy assignment
}

void bad_copy(Vector& v1) {
    Vector v2 = v1;
    v1[0] = 2; // v2[0] is also 2
    v2[1] = 3; // v2[1] is also 3
}

Vector::Vector(const Vector& a)
    : elem{new double[a.sz]},
    sz{a.sz} {
    for (int i = 0; i < sz; ++i)
        elem[i] = a.elem[i];
}

Vector& Vector::operator=(const Vector& a) {
    double* p = new double[a.sz];
    for (int i = 0; i < a.sz; ++i)
        p[i] = a.elem[i];
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}

class Vector_size_mismatch : public std::exception {
    const char* what() const throw() {
        return "Size mismatch between you two.";
    }
};

Vector operator+(const Vector& a, const Vector& b) {
    if (a.size() != b.size())
        throw Vector_size_mismatch{};

    Vector res(a.size());
    for (int i = 0; i < a.size(); ++i)
        res[i] = a[i] + b[i];
    return res;
}

void f(const Vector& x, const Vector& y, const Vector& z) {
    Vector r;
    // ...
    r = x + y + z;
    // ...
}

Vector::Vector(Vector&& a)
    : elem{a.elem}, // "grab the elements" from a
    sz{a.sz} {
    a.elem = nullptr;
    a.sz = 0;
}

Vector f() {
    Vector x(1000);
    Vector y(1000);
    Vector z(1000);
    // ...
    z = x; // we get a copy
    y = std::move(x); // we get a move
    // ...
    return z; // we get a move
}

//std::vector<std::thread> my_threads;
//Vector init(int n) {
//    std::thread t(&Vector::size);
//    my_threads.push_back(move(t));
//    // ... more initialization
//    Vector vec(n);
//    for (int i = 0; i < vec.size(); ++i) vec[i] = 777;
//    return vec; // move vec out of init
//}
//auto v = init(1000000);

class Negative_size : public std::exception {
    const char* what() const throw() {
        return "Cannot have a negative size";
    }
};

template<typename T>
VectorT<T>::VectorT(int s) {
    if (s < 0) throw Negative_size{};
    elem = new T[s];
    sz = s;
}

template<typename T>
const T& VectorT<T>::operator[](int i) const {
    if (i < 0 || size() <= i)
        throw std::out_of_range{"VectorT::operator[]"};
    return elem[i];
}

VectorT<char> vc(200);
VectorT<std::string> vs(17);
VectorT<std::list<int>> vli(45);

void write(const VectorT<std::string>& vs) {
    for (int i = 0; i < vs.size(); ++i)
        std::cout << vs[i] << "\n";
}

template<typename T>
const T* begin(const VectorT<T>& x) {
    return x.size() ? &x[0] : nullptr;
}

template<typename T>
const T* end(const VectorT<T>& x) {
    return begin(x) + x.size();
}

void f2(VectorT<std::string>& vs) {
    for (auto& s : vs)
        std::cout << s << "\n";
}

template<typename Container, typename Value>
Value sum(const Container& c, Value v) {
    for (auto x : c)
        v += x;
    return v;
}

void user(VectorT<int>& vi, std::list<double>& ld, std::vector<std::complex<double>>& vc) {
    int x = sum(vi, 0);
    double d = sum(vi, 0.0);
    double dd = sum(ld, 0.0);
    auto z = sum(vc, std::complex<double>{});
}

template<typename T>
class Less_than {
    const T val;
public:
    Less_than(const T& v) : val(v) {}
    bool operator()(const T& x) const { return x < val; } // call operator
};


Less_than<int> lti {42};
Less_than<std::string> lts {"Backus"};
void fct(int n, const std::string& s) {
    bool b1 = lti(n);
    bool b2 = lts(s);
    // ...
}

template<typename C, typename P>
int count(const C& c, P pred) {
    int cnt = 0;
    for (const auto& x : c)
        if (pred(x))
            ++cnt;
    return cnt;
}

void f(const VectorT<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {
    std::cout << "number of values less than " << x
        << ": " << count(vec, Less_than<int>{x})
        << "\n";
    std::cout << "number of values less than " << s
        << ": " << count(lst, Less_than<std::string>{s})
        << "\n";
}

void ff(const VectorT<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {
    std::cout << "number of values less than " << x
        << ": " << count(vec, [&](int a){ return a < x; })
        << "\n";
    std::cout << "number of values less than " << s
        << ": " << count(lst, [&](const std::string& a){ return a < s; })
        << "\n";
}

template<typename C, typename Oper>
void for_all(C& c, Oper op) { // Assume C is a container of pointers
    for (auto& x : c)
        op(*x); // pass op() a ref to each element pointed to
}

void user2() {
    std::vector<std::unique_ptr<Shape>> v;
    while (std::cin)
        v.push_back(read_shape_unique(std::cin));
    for_all(v, [](Shape& s){ s.draw(); }); // draw all
    for_all(v, [](Shape& s){ s.rotate(45); }); // rotate all
}

template<typename T>
void g(T x) {
    std::cout << x << " ";
}

//template<typename T, typename... Tail>
//void fff(T head, Tail... tail) {
//    g(head); // do something to the head
//    fff(tail...); // try again with the tail
//}
//
//void some_call() {
//    std::cout << "first: ";
//    fff(1, 2.2, "hello");
//    std::cout << "\nsecond: ";
//    fff(0.2, 'c', "yuck!", 0, 1, 2);
//    std::cout << "\n";
//}

template<typename T>
class VectorT2 {
public:
    using value_type = T;
    // ...
};

template<typename C>
using Value_type = typename C::value_type; // the type of C's elements

template<typename Container>
void algo(Container& c) {
    VectorT<Value_type<Container>> vec;
    // ...
}

template<typename Key, typename Value>
class Map {
    // ...
};

template<typename Value>
using String_map = Map<std::string, Value>;

String_map<int> m; // m is a Map<string, int>
