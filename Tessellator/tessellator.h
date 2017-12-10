#ifndef _tessellator_h_
#define _tessellator_h_

#include <FGL/freeglut.h>
#include <list>
#include <vector>
#include <iostream>
#include "vertex.h"
#include "primitiveState.h"

using namespace std;

namespace tesslib
{
	class __declspec( dllexport ) Tessellator
	{
		public:
			Tessellator();
			virtual ~Tessellator();
			vector<Vertex> tessellate( vector<Vertex>& outerLoop, list<vector<Vertex> *>& innerLoops );

		private:
			void init();
			bool ready( GLUtesselator *& tess );
			void tessellate( GLUtesselator * tess, vector<Vertex>& outerLoop, list<vector<Vertex> *>& innerLoops );
			void tessellateContour( GLUtesselator * tess, vector<Vertex>& contour );
			void clearHeap();
			void registerCallbacks( GLUtesselator * tess );

			static void addPrimitive();
			static void addPrimitiveTriangles( int length );
			static void addPrimitiveTriangleStrip( int length );
			static void addPrimitiveTriangleFan( int length );

			static void CALLBACK tessBeginCallback( GLenum primitiveType );
			static void CALLBACK tessEndCallback();
			static void CALLBACK tessErrorCallback();
			static void CALLBACK tessVertexCallback( const GLvoid *data );

			static list<GLdouble *> pointsHeap;
			static PrimitiveState primitiveState;
			static vector<Vertex> triangleVertices;
	};
}

#endif // _tessellator_h_
