#include <iostream>

class Vec3 {
    private:
        float x, y, z;

    public:
        Vec3(float _x, float _y, float _z);

        friend Vec3 operator+(
            const Vec3 &lhs, 
            const Vec3 &rhs);

        friend Vec3 operator+(
            const Vec3 &lhs,
            const float &rhs
        );

        friend Vec3 operator+(
            const float &lhs,
            const Vec3 &rhs
        );

        friend std::ostream& operator<<(
            std::ostream& os, 
            const Vec3& o);
};