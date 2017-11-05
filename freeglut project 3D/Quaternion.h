#pragma once
#include "PuntoVector3D.h"
	class Quaternion
	{
	public:
		union
		{
			struct
			{
				float r;
				float i;
				float j;
				float k;
			};
			float data[4];
		};
	public:
		explicit Quaternion()
			:
			r(1.f), i(0.f), j(0.f), k(0.f) {}

		explicit Quaternion(float _r, float _i, float _j, float _k)
			:
			r(_r), i(_i), j(_j), k(_k) {}
		inline void normalize()
		{
			float d = r*r + i*i + j*j + k*k;
			if (esIgual(d, 0))
			{
				r = 1;
				return;
			}

			d = static_cast<float>(1.0f) / sqrt(d);
			r *= d;
			i *= d;
			j *= d;
			k *= d;
		}

		inline void rotateByVector(PuntoVector3D &vector)
		{
			Quaternion q(0, vector.getX(), vector.getY(), vector.getZ());
			(*this) *= q;
		}
		inline void addScaledVector(PuntoVector3D &vector, float scale)
		{
			Quaternion q(0,
				vector.getX() * scale,
				vector.getY() * scale,
				vector.getZ() * scale);
			q *= *this;

			float half = static_cast<float>(0.5f);
			r += q.r * half;
			i += q.i * half;
			j += q.j * half;
			k += q.k * half;
		}

		inline Quaternion getConjugate()
		{
			return Quaternion(r, -i, -j, -k);
		}

	public:/* Rotation utilities */
		inline void fillAngleAxis(float &angle, float &x, float &y, float &z) const
		{
			Quaternion q = (*this);
			if (r > 1) q.normalize();

			angle = 2 * acos(q.r);
			double s = sqrt(1 - q.r*q.r); // Assuming quaternion normalized then w is less than 1, so term always positive.
			if (s < 0.001) { // To avoid divide by zero, s is always positive due to sqrt
				x = q.i;
				y = q.j;
				z = q.k;
			}
			else { // normalize
				x = q.i / s;
				y = q.j / s;
				z = q.k / s;
			}
			angle = 180.0f*angle / 3.141592f;
		}

		inline void fillAngleAxis(float &angle, PuntoVector3D &axis)
		{
			Quaternion q = (*this);
			if (r > 1) q.normalize();

			angle = 2 * acos(q.r);
			double s = sqrt(1 - q.r*q.r);
			if (s < 0.001) {
				axis.setX(q.i);
				axis.setY(q.j);
				axis.setZ(q.k);
			}
			else {
				axis.setX(q.i/s);
				axis.setY(q.j/s);
				axis.setZ(q.k/s);
			}
			angle = 180.0f*angle / 3.141592f;
		}

		// These set methods can be static method and returns its quaternion.
		inline void setByAngleAxis(float angle, float x, float y, float z)
		{
			angle = 3.141592f*angle / 180.f;
			PuntoVector3D axis(x, y, z,0);
			axis.normalizar();

			double s = sin(angle / 2.f);
			this->r = cos(angle / 2.f);
			this->i = axis.getX()*s;
			this->j = axis.getY()*s;
			this->k = axis.getZ()*s;
		}

		inline void setByAngleAxis(float angle, PuntoVector3D axis)
		{
			angle = 3.141592*angle / 180.f;
			axis.normalizar();

			double s = sin(angle / 2.f);
			this->r = cos(angle / 2.f);
			this->i = axis.getX()*s;
			this->j = axis.getY()*s;
			this->k = axis.getZ()*s;
		}

		inline void rotateByAngleAxis(float angle, PuntoVector3D axis)
		{
			Quaternion temp;
			temp.setByAngleAxis(angle, axis);
			*this *= temp;
		}

		inline void rotateByAngleAxis(float angle, float x, float y, float z)
		{
			PuntoVector3D axis(x, y, z,0);
			Quaternion temp;
			temp.setByAngleAxis(angle, axis);
			*this *= temp;
		}

		// Returns a rotated vector by current quaterion.
		inline PuntoVector3D operator*(PuntoVector3D& target)
		{
			// qVq*
			Quaternion V(0, target.getX(), target.getY(), target.getZ());
			Quaternion q(*this);
			q.normalize();				//  normalize current quaternion.
			q *= V;						// qV
			q *= getConjugate();		// qVq*
			// q == qVq*
			return PuntoVector3D(q.i, q.j, q.k,0);
		}

	public:
		inline void operator*=(const Quaternion &multiplier)
		{
			Quaternion q = *this;
			r = q.r*multiplier.r - q.i*multiplier.i -
				q.j*multiplier.j - q.k*multiplier.k;

			i = q.r*multiplier.i + q.i*multiplier.r +
				q.j*multiplier.k - q.k*multiplier.j;

			j = q.r*multiplier.j + q.j*multiplier.r +
				q.k*multiplier.i - q.i*multiplier.k;

			k = q.r*multiplier.k + q.k*multiplier.r +
				q.i*multiplier.j - q.j*multiplier.i;
		}
	private:
		bool esIgual(float real_value_a, float real_value_b, float epsilon = 0.0001)
		{
			return (abs(real_value_a - real_value_b) < epsilon) ? true : false;
		}
	};