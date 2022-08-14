/*
    A class for a representation of a 2d vector

    Copyright (c) 2022 - txvvgnx, Eisverygoodletter

    This file is part of The Ev3dev C++ Wrapper Library.
    The Ev3dev C++ Wrapper Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    The Ev3dev C++ Wrapper Library is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License 
    along with The Ev3dev C++ Wrapper Library. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef EV3WRAPVECTOR_HPP_
#define EV3WRAPVECTOR_HPP_
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
#endif