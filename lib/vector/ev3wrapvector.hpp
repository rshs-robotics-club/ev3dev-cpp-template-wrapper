#include <cmath>

namespace Ev3Wrap {

class Vector {
public:
    const double x = 0;
    const double y = 0;
    inline static const Vector* zero {new Ev3Wrap::Vector(0, 0)};

    Vector operator+ (Vector& vec) {
        double newX = this->x + vec.x;
        double newY = this->y + vec.y;
        Vector newVector(newX, newY);
        return newVector;
    }

    Vector operator- (Vector& vec) {
        double newX = this->x - vec.x;
        double newY = this->y - vec.y;
        Vector newVector(newX, newY);
        return newVector;
    }

    Vector normalize() {
        double magnitude = this->magnitude();
        double unitX = this->x / magnitude;
        double unitY = this->y / magnitude;
        Vector newVector(unitX, unitY);
        return newVector;
    }

    double magnitude() {
        double total = pow(x, 2) + pow(y, 2);
        double mag = sqrt(total);
        return mag;
    }

    double dist(Vector b = Vector(0, 0)) {
        Vector a(x, y);
        Vector result = b - a;
        double mag = result.magnitude();
        return mag;
    }

    double getBearing() {
        double pi = atan(1) * 4;
        double angleFromPositiveX = atan2(y, x);
        angleFromPositiveX = angleFromPositiveX * 180 / pi;

        // time for some spaghetti
        // quadrant 1
        if (angleFromPositiveX <= 90 && angleFromPositiveX >= 0) {
            angleFromPositiveX = 90 - angleFromPositiveX;
        }
        // quadrant 2 
        else if (angleFromPositiveX > 90) {
            angleFromPositiveX = 180 - angleFromPositiveX;
            angleFromPositiveX = 90 - angleFromPositiveX;
            angleFromPositiveX = 360 - angleFromPositiveX;
        }
        // quadrant 3
        else if (angleFromPositiveX < -90) {
            angleFromPositiveX = 180 - abs(angleFromPositiveX);
            angleFromPositiveX = 90 - angleFromPositiveX;
            angleFromPositiveX = 180 + angleFromPositiveX;
        }
        // quadrant 4 
        else if (angleFromPositiveX >= -90 && angleFromPositiveX <= 0) {
            angleFromPositiveX = 90 + abs(angleFromPositiveX);
        }

        return angleFromPositiveX;
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

}
