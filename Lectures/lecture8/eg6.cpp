#include "eg6.h"

Vec3::Vec3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {}

Vec3 operator+(
    const Vec3 &lhs, 
    const Vec3 &rhs);

Vec3 operator+(
    const Vec3 &lhs,
    const float &rhs
);

Vec3 operator+(
    const float &lhs,
    const Vec3 &rhs
);

std::ostream& operator<<(
    std::ostream& os, 
    const Vec3& o);

int main() {
    Vec3 a(1,1,1), b(1,2,3);

    Vec3 c = a + b + 5;

    return 0;
}