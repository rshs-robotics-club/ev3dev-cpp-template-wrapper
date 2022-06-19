#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace Ev3Wrap {

class Vector {
public:
    const float x = 0;
    const float y = 0;
    static Vector zero;

    Vector operator+ (Vector& vec) {
        return Vector(this->x + vec.x, this->y + vec.y);
    }

    Vector operator- (Vector& vec) {
        return Vector(this->x - vec.x, this->y - vec.y);
    }
    bool operator== (Vector& vec) {
        return (this->x == vec.x && this->y == vec.y);
    }

    Vector normalize() {
        float magnitude = this->dist();
        return Vector(this->x / magnitude, this->y / magnitude);
    }

    float dist(Vector& otherVect = Vector::zero) {

        if (otherVect == Vector::zero) {
            float total = pow(x, 2) + pow(y, 2);
            return sqrt(total);
        } else {
            Vector res = otherVect - *this;
            return res.dist();
        }
    }

    float getBearing(Vector& otherVect = Vector::zero) {
        float principalValueRadians = atan2f(y, x);
        float principalValueDegrees = principalValueRadians * 180 / M_PI;
        float bearing = 90 - principalValueDegrees;
        if (bearing > 180) {
            bearing -= 360;
        }
        if (otherVect == Vector::zero) {
            return bearing;
        }
        else {
            // get the bearing of the other vector
            float otherBearing = otherVect.getBearing();
            // get the difference between the two bearings
            float difference = otherBearing - bearing;
            return difference;
        }
    }
    static Vector createVectorFromPolar(float bearing, float distance) {
        // the bearing is clockwise from north
        float radangle = (90 - bearing) * (M_PI / 180);
        return Vector(distance * cosf(radangle), distance * sinf(radangle));
    }
    // i and j constructor
    Vector(float i, float j) : x(i), y(j) {}
};

} // namespace Ev3Wrap
