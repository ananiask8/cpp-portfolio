//
// Created by José Hilario on 14 Feb 2020.
//

#ifndef X_4_GENERAL_H
#define X_4_GENERAL_H

#include <vector>

class Complex {
    double re, im;
public:
    Complex(double r, double i) : re{r}, im{i} {}
    Complex(double r) : re{r}, im{0} {}
    Complex() : re{0}, im{0} {}

    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }

    Complex& operator+=(Complex z) { re += z.re; im += z.im; return *this; }
    Complex& operator-=(Complex z) { re -=z.re; im -= z.im; return *this; }
    Complex operator-() { return {-re, -im}; }
    Complex& operator*=(Complex) {};
    Complex& operator/=(Complex) {};
};

class Vector {
    double* elem;
    int sz;
public:
    Vector() : elem{nullptr}, sz{0} {}
    Vector(int s) :elem{new double[s]}, sz{s} {
        for (int i = 0; i < s; ++i) elem[i] = 0;
    }
    Vector(std::initializer_list<double>);
    Vector(const Vector& a); // copy constructor
    Vector& operator=(const Vector& a); // copy assignment

    Vector(Vector&& a); // move constructor
    Vector& operator=(Vector&& a); // move assignment

    ~Vector() { delete[] elem; }

    double& operator[](int) const {};
    int size() const {};
    void push_back(double);
};

class Point {
    double* elem;
    int sz;
public:
    Point(int s) :elem{new double[s]}, sz{s} {
        for (int i = 0; i < s; ++i) elem[i] = 0;
    }
    Point(std::initializer_list<double> lst);
    ~Point() { delete[] elem; }
};

class Container {
public:
    virtual double& operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() {};
};

class Shape {
public:
    Shape() {}
    Shape(const Shape&) = delete; // no copy operations
    Shape& operator=(const Shape&) = delete;

    Shape(Shape&&) = delete; // no move operations
    Shape& operator=(Shape&&) = delete;

    virtual Point center() const = 0;

    virtual void move(Point to) = 0;
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;

    virtual ~Shape() {};
};

class Circle : public Shape {
public:
    Circle(Point p, int rr) : x{p}, r{rr} {}

    Point center() const { return x; }
    void move(Point to) { x = to; }
    void draw() const {};
    void rotate(int) {}
protected:
    void set_center(Point c) { x = c; }
    void set_radius(int a) { r = a; }
private:
    Point x;
    int r;
};

class Triangle : public Shape {
public:
    Triangle(double l1, double l2, double l3) : x{0, 0} {}
    Point center() const { return x; };
    void move(Point to) { x = to; }
    void draw() const {}
    void rotate(int) {}
private:
    Point x;
};

class Smiley : public Circle {
public:
    Smiley(Point p, int r) : Circle{p, r}, mouth{nullptr} {}
    Smiley(Smiley&& s) : Circle{0, 0}, mouth{nullptr} {
        set_center(s.center());
        set_mouth(s.get_mouth());
    }

    void move(Point to) override {}
    void draw() const override;
    void rotate(int) override {}

    void add_eye(Shape* s) { eyes.push_back(s); }
    Shape* get_mouth() { return mouth; }
    void set_mouth(Shape* s);
    virtual void wink(int i) {}

    ~Smiley() {
        delete mouth;
        for (auto p : eyes) delete p;
    }

private:
    std::vector<Shape*> eyes;
    Shape* mouth;
};

enum class Kind { circle, triangle, smiley };

template<typename T>
class VectorT {
private:
    T* elem;
    int sz;
public:
    VectorT(int s);
    ~VectorT() { delete[] elem; }

    // ... copy and move operations ...

    T& operator[](int i);
    const T& operator[](int i) const;
    int size() const { return sz; }
};


#endif //X_4_GENERAL_H
