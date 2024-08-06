#include "Vec2.h"
#include <math.h>
#define PI 3.14159265

Vec2::Vec2(){}

Vec2::Vec2(float xin, float yin): x(xin), y(yin)
{}

bool Vec2::operator == (const Vec2& rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return (this->x != rhs.x || this->y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y );
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y );
}


Vec2 Vec2::operator * (const float val) const
{
	return Vec2(x*val,y*val);
}

Vec2 Vec2::operator / (const float val) const
{
	if(val > 0)
	{
		return Vec2(x/val,y/val);
	}
	else return Vec2(0.0f,0.0f);
}


/*void Vec2::operator * (const float val)
{
	this->x*val;
	this->y*val;
}*/

void Vec2::operator += (const Vec2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
	this->x *= val;
	this->y *= val;
}

void Vec2::operator /= (const float val)
{
	if(val > 0)
	{
		this->x /= val;
		this->y /= val;	
	}
	else
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	
}

float Vec2::dot(const Vec2& rhs) const
{
	return ((this->x*rhs.x)+(this->y*rhs.y));
}

float Vec2::mag() const
{
	return sqrt((this->x*this->x)+(this->y*this->y));
}

void Vec2::setMag( float magnitud )
{
	float currentMag = this->mag();
	if (currentMag == 0)
	{
        	//printf("Cannot set magnitude for a zero vector.\n");
       	return;
    	}
    	
    	float scale = magnitud/currentMag;
    	this->x *= scale;
    	this->y *= scale;	
}

float Vec2::distance(const Vec2& rhs) const
{
	return sqrt((rhs.x-this->x)*(rhs.x-this->x) + (rhs.y - this->y)*(rhs.y - this->y));
}

void Vec2::normalize(float dist)
{
	this->x /= dist, this->y /= dist;
}

void Vec2::speed(float _velocity, float _tita)
{
	this->x = _velocity*cos(_tita*PI / 180.0);  
	this->y = _velocity*sin(_tita*PI / 180.0);
}
		
