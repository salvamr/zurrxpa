#ifndef _h_vector
#define _h_vector

#include <math.h> 

typedef float vec_t;
class Vector
{
public:
	// Construction/destruction
	inline Vector( void )							{ }
	inline Vector( float X, float Y, float Z )		{ x = X; y = Y; z = Z;								}
	inline Vector( double X, double Y, double Z )	{ x = ( float )X; y = ( float )Y; z = ( float )Z;	}
	inline Vector( int X, int Y, int Z )			{ x = ( float )X; y = ( float )Y; z = ( float )Z;	}
	inline Vector( const Vector& v )				{ x = v.x; y = v.y; z = v.z;						} 
	inline Vector( float rgfl[3] )					{ x = rgfl[0]; y = rgfl[1]; z = rgfl[2];			}

	// Operators
	inline Vector operator-( void ) const			{ return Vector(-x,-y,-z);				}
	inline int operator==( const Vector& v ) const	{ return x==v.x && y==v.y && z==v.z;	}
	inline int operator!=( const Vector& v ) const	{ return !(*this==v);					}
	inline Vector operator+( const Vector& v ) const{ return Vector(x+v.x, y+v.y, z+v.z);	}
	inline Vector operator-( const Vector& v ) const{ return Vector(x-v.x, y-v.y, z-v.z);	}
	inline Vector operator*( float fl ) const		{ return Vector(x*fl, y*fl, z*fl);		}
	inline Vector operator/( float fl ) const		{ return Vector(x/fl, y/fl, z/fl);		}



	// Methods
	inline void CopyToArray( float* rgfl ) const	{ rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline float Length( void ) const				{ return ( float )sqrt(x*x + y*y + z*z); }
	inline bool IsZero( float flToleranse = 0.01f ) const {
		return ( x > -flToleranse && x < flToleranse && y > -flToleranse && y < flToleranse && z > -flToleranse && z < flToleranse );
	}
	operator float *( )								{ return &x; } // Vectors will now automatically convert to float * when needed
	operator const float *( ) const					{ return &x; } // Vectors will now automatically convert to float * when needed
	
	inline Vector Normalize( void ) const {
		float flLen = Length( );
		
		if( flLen == 0 )
			return Vector( 0, 0, 1 );

		flLen = 1 / flLen;
		return Vector( x * flLen, y * flLen, z * flLen );
	}

	inline vec_t* Base() {
		return ( vec_t* )this;
	}

	inline float Length2D( void ) const					{ return ( float )sqrt( x * x + y * y ); }

	vec_t x, y, z;
};
inline Vector operator* ( float fl, const Vector& v )	{ return v * fl; }
#endif
