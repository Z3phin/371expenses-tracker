#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape {
   
    public: 
        Shape();
        virtual ~Shape();

        virtual std::string to_string() const = 0;
        virtual void centre_at(const double x, const double y) = 0;

};

class Circle : public Shape {
    private: 
        double x;
        double y;
        double r;

    public:
    
        Circle(double x, double y, double r);
        virtual ~Circle();

        virtual std::string to_string() const;
        virtual void centre_at(const double x, const double y);

};

class Rectangle : public Shape {
    private:
        double x0;
        double y0;
        double x1;
        double y1;

    public:
        Rectangle(const double _x0, const double _y0, 
                  const double _x1, const double _y1);

        virtual ~Rectangle();

        virtual std::string to_string() const;
        virtual void centre_at(const double x, const double y);
};

class Triangle : public Shape {
    private:
        double x0;
        double y0;
        double x1;
        double y1;
        double x2;
        double y2;

    public:
        Triangle(const double _x0, const double _y0, 
                 const double _x1, const double _y1,
                 const double _x2, const double _y2);
        virtual ~Triangle();

        virtual std::string to_string() const;
        virtual void centre_at(const double x, const double y);

};

#endif // SHAPE_H