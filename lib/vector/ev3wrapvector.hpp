#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace Ev3Wrap {

class Vector {
public:
    const double x = 0;
    const double y = 0;
    static Vector zero;

    Vector operator+ (Vector& vec) {
        return Vector(this->x + vec.x, this->y + vec.y);
    }

    Vector operator- (Vector& vec) {
        return Vector(this->x - vec.x, this->y - vec.y);
    }

    Vector normalize() {
        double magnitude = this->magnitude();
        return Vector(this->x / magnitude, this->y / magnitude);
    }

    double magnitude() {
        double total = pow(x, 2) + pow(y, 2);
        return sqrt(total);
    }

    double dist(Vector b = Vector(0, 0)) {
        Vector result = b - *this;
        return result.magnitude();
    }

    double getBearing() {
        float principalValueRadians = atan2f(y, x);
        float principalValueDegrees = principalValueRadians * 180 / M_PI;
        float bearing = 90 - principalValueDegrees;
        if (bearing > 180) {
            bearing -= 360;
        }
        return bearing;
    }

    // polar coordinates (0 - 360 TRUE bearing)
    Vector createPolarVector(double bearing, double magnitude) {
        const double pi = atan(1) * 4;

        // oh no more spaghetti
        // quadrant 1
        if (bearing <= 90) {
            // sin is x, cos is y
            double bearingInRadians = bearing * pi / 180;
            double xComp = magnitude * sin(bearingInRadians);
            double yComp = magnitude * cos(bearingInRadians);
            Vector newVector(xComp, yComp);
            return newVector;
        }
        // quadrant 2
        else if (bearing <= 180) {
            // cos is x, sin is y (negative)
            double bearingInRadians = (bearing - 90) * pi / 180;
            double xComp = magnitude * cos(bearingInRadians);
            double yComp = magnitude * -sin(bearingInRadians);
            Vector newVector(xComp, yComp);
            return newVector;
        }
        // quadrant 3
        else if (bearing <= 270) {
            // sin is x (negative), cos is y (negative)
            double bearingInRadians = (bearing - 180) * pi / 180;
            double xComp = magnitude * -sin(bearingInRadians);
            double yComp = magnitude * -cos(bearingInRadians);
            Vector newVector(xComp, yComp);
            return newVector;
        }
        // quadrant 4
        else if (bearing <= 360) {
            // cos is x (negative), sin is y
            double bearingInRadians = (bearing - 270) * pi / 180;
            double xComp = magnitude * -cos(bearingInRadians);
            double yComp = magnitude * sin(bearingInRadians);
            Vector newVector(xComp, yComp);
            return newVector;
        }
    }

    // i and j constructor
    Vector(double i, double j) : x(i), y(j) {}
};

} // namespace Ev3Wrap
