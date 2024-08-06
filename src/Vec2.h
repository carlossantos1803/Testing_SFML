#pragma once

class Vec2
{

	public:
		float x = 0.0f;
		float y = 0.0f;
		
		Vec2();
		Vec2(float xin, float yin);
		
		bool operator == (const Vec2& rhs) const;
		bool operator != (const Vec2& rhs) const; 
		
		Vec2 operator + (const Vec2& rhs) const ;
		Vec2 operator - (const Vec2& rhs) const ;
		Vec2 operator / (const float val) const ;
		Vec2 operator * (const float val) const ;

		void operator += (const Vec2& rhs);
		void operator -= (const Vec2& rhs);
		void operator *= (const float val);
		void operator /= (const float val);
		//void operator *  (const float val);


		void setMag( float magnitud );
		float mag() const;
		float dot(const Vec2& rhs) const; 
		float distance(const Vec2& rhs) const;
		
		void normalize(float dist);

		void speed(float _velocity, float _tita);
};
