/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Position
*/

#include "Position.hpp"

Position::Position(float x, float y, float z) :
 _x(x), _y(y), _z(z)
{
}

Position::Position(Position const &position) :
 _x(position._x), _y(position._y), _z(position._z)
{
}

Position::Position() :
 _x(0), _y(0), _z(0)
{
}

Position::~Position()
{
}

bool Position::operator ==(Position const &position)
{
    if (_x == position._x && _y == position._y && _z == position._z)
        return true;
    return false;
}

Position &Position::operator =(Position const &position)
{
    _x = position._x;
    _y = position._y;
    _z = position._z;
    return *this;
}

Position &Position::operator =(float pos)
{
    _x = pos;
    _y = pos;
    _z = pos;
    return *this;
}

Position &Position::operator +=(Position const &position)
{
    _x += position._x;
    _y += position._y;
    _z += position._z;
    return *this;
}

Position &Position::operator +=(float number)
{
    _x += number;
    _y += number;
    _z += number;
    return *this;
}

Position &Position::operator -=(Position const &position)
{
    _x -= position._x;
    _y -= position._y;
    _z -= position._z;
    return *this;
}

Position &Position::operator -=(float number)
{
    _x -= number;
    _y -= number;
    _z -= number;
    return *this;
}

Position &Position::operator *=(Position const &position)
{
    _x *= position._x;
    _y *= position._y;
    _z *= position._z;
    return *this;
}

Position &Position::operator *=(float number)
{
    _x *= number;
    _y *= number;
    _z *= number;
    return *this;
}

Position &Position::operator /=(Position const &position)
{
    if (position._x == 0 || position._y == 0 || position._z == 0)
        throw Error::PositionError("can't divide by 0");
    _x /= position._x;
    _y /= position._y;
    _z /= position._z;
    return *this;
}

Position &Position::operator /=(float number)
{
    if (number == 0)
        throw Error::PositionError("can't divide by 0");
    _x /= number;
    _y /= number;
    _z /= number;
    return *this;
}

void Position::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void Position::setPosition(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

void Position::setPosition(Position const &position)
{
    _x = position._x;
    _y = position._y;
    _z = position._z;
}

void Position::setX(float x)
{
    _x = x;
}

void Position::setY(float y)
{
    _y = y;
}

void Position::setZ(float z)
{
    _z = z;
}

void Position::reset()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

std::vector<float> Position::getPosition() const
{
    return {_x, _y, _z};
}

float Position::getX() const
{
    return _x;
}

float Position::getY() const
{
    return _y;
}

float Position::getZ() const
{
    return _z;
}
