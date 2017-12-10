#ifndef _vertex_h_
#define _vertex_h_

namespace tesslib
{
	struct __declspec( dllexport ) Vertex
	{
		double x;
		double y;
		double z;

		Vertex() : Vertex( .0, .0, .0 )
		{
		}

		Vertex( double x, double y, double z ) : x( x ), y( y ), z( z )
		{
		}

		// const�����o�֐� (�֐����� this �|�C���^�� const ��)
		bool operator ==( const Vertex& v ) const
		{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator !=( const Vertex& v ) const
		{
			return !this->operator==( v );
		}
	};
}

#endif // _vertex_h_
