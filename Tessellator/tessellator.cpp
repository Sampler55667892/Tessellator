#include "tessellator.h"

namespace tesslib
{
	// http://www.songho.ca/opengl/gl_tessellation.html が提供するサンプルコードを少しだけ一般化したもの
	Tessellator::Tessellator()
	{
		init();
	}

	Tessellator::~Tessellator()
	{
		clearHeap();
	}

	vector<Vertex> Tessellator::tessellate( vector<Vertex>& outerLoop, list<vector<Vertex> *>& innerLoops )
	{
		GLUtesselator * tess;
		if (ready( tess )) {
			tessellate( tess, outerLoop, innerLoops );
			gluDeleteTess( tess );
		}

		return triangleVertices;
	}

	void Tessellator::init()
	{
		int argc = 0;
		char * argv = "";
		glutInit( &argc, &argv );
	}

	bool Tessellator::ready( GLUtesselator *& tess )
	{
		triangleVertices.clear();
		primitiveState.clear();
		clearHeap();

		tess = gluNewTess();
		if (tess == nullptr)
			return false;

		registerCallbacks( tess );

		return true;
	}

	void Tessellator::tessellate( GLUtesselator * tess, vector<Vertex>& outerLoop, list<vector<Vertex> *>& innerLoops )
	{
		gluTessBeginPolygon( tess, 0 );

		tessellateContour( tess, outerLoop );
		for (list<vector<Vertex> *>::iterator itr = innerLoops.begin(); itr != innerLoops.end(); ++itr)
			tessellateContour( tess, *(*itr) );

		gluTessEndPolygon( tess );
	}

	void Tessellator::tessellateContour( GLUtesselator * tess, vector<Vertex>& contour )
	{
		gluTessBeginContour( tess );

		for (auto i = 0; i < (int)contour.size(); ++i) {
			auto v = contour[ i ];
			auto p = new GLdouble[ 3 ] { v.x, v.y, v.z };
			pointsHeap.push_back( p );
			gluTessVertex( tess, p, p );
		}

		gluTessEndContour( tess );
	}

	void Tessellator::clearHeap()
	{
		for (list<GLdouble *>::iterator itr = pointsHeap.begin(); itr != pointsHeap.end(); ++itr)
			delete *itr;
		pointsHeap.clear();
	}

	void Tessellator::registerCallbacks( GLUtesselator * tess )
	{
		gluTessCallback( tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCallback );
		gluTessCallback( tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCallback );
		gluTessCallback( tess, GLU_TESS_ERROR, (void (__stdcall*)(void))tessErrorCallback );
		gluTessCallback( tess, GLU_TESS_VERTEX, (void (__stdcall*)())tessVertexCallback );
	}

	void Tessellator::addPrimitive()
	{
		auto length = (int)primitiveState.points.size();

		if (primitiveState.type == GL_TRIANGLES)
			addPrimitiveTriangles( length );
		else if (primitiveState.type == GL_TRIANGLE_STRIP)
			addPrimitiveTriangleStrip( length );
		else if (primitiveState.type == GL_TRIANGLE_FAN)
			addPrimitiveTriangleFan( length );
	}

	void Tessellator::addPrimitiveTriangles( int length )
	{
		for (auto i = 0; i < length; ++i)
			triangleVertices.push_back( primitiveState.points[ i ] );
	}

	void Tessellator::addPrimitiveTriangleStrip( int length )
	{
		for (auto i = 0; i < length - 2; ++i) {
			triangleVertices.push_back( primitiveState.points[ i ] );
			triangleVertices.push_back( primitiveState.points[ i + 1 ] );
			triangleVertices.push_back( primitiveState.points[ i + 2 ] );
		}
	}

	void Tessellator::addPrimitiveTriangleFan( int length )
	{
		auto v0 = primitiveState.points[ 0 ];
		for (auto i = 1; i < length - 1; ++i) {
			triangleVertices.push_back( v0 );
			triangleVertices.push_back( primitiveState.points[ i ] );
			triangleVertices.push_back( primitiveState.points[ i + 1 ] );
		}
	}

	#pragma region callbacks

	void CALLBACK Tessellator::tessBeginCallback( GLenum primitiveType )
	{
		cout << "tessBeginCallback(): ";
		if (primitiveType == GL_TRIANGLES)
			cout << "GL_TRIANGLES";
		else if (primitiveType == GL_TRIANGLE_STRIP)
			cout << "GL_TRIANGLE_STRIP";
		else if (primitiveType == GL_TRIANGLE_FAN)
			cout << "GL_TRIANGLE_FAN";
		cout << endl;

		primitiveState.type = primitiveType;
	}

	void CALLBACK Tessellator::tessEndCallback()
	{
		cout << "tessEndCallback()" << endl;

		addPrimitive();
		primitiveState.clear();
	}

	void CALLBACK Tessellator::tessErrorCallback()
	{
		cout << "tessErrorCallback()" << endl;
	}

	void CALLBACK Tessellator::tessVertexCallback( const GLvoid *data )
	{
		cout << "  tessVertexCallback(): ";

		const GLdouble *ptr = (const GLdouble *)data;
		glVertex3dv( ptr );

		Vertex v;
		v.x = *ptr;
		v.y = *(ptr + 1);
		v.z = *(ptr + 2);
		primitiveState.points.push_back( v );

		cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
	}

	#pragma endregion

	list<GLdouble *> Tessellator::pointsHeap;
	PrimitiveState Tessellator::primitiveState;
	vector<Vertex> Tessellator::triangleVertices;
}
