#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

struct MeshVertexData {  // P3N3T2
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
};

struct SkinVertexData {  // P3N3W4J4T2
    QVector3D position;
    QVector3D normal;
    QVector4D weights_0;
    QVector4D joints_0;
    QVector2D texCoord;
};

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();
    virtual int get_indices_count();
    virtual int get_vertices_count();
    virtual int get_vertex_size();
    virtual void drawGeometry(QOpenGLShaderProgram *program);
    virtual void initGeometry();

protected:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

class MeshGeometryShared : public GeometryEngine
{
public:
    MeshGeometryShared();
    virtual ~MeshGeometryShared();
    virtual void drawGeometry(QOpenGLShaderProgram *program);
    virtual void initGeometry();
};

class SkinGeometryShared : public GeometryEngine
{
public:
    SkinGeometryShared();
    virtual ~SkinGeometryShared();
    virtual void drawGeometry(QOpenGLShaderProgram *program);
    virtual void initGeometry();
};

#endif // GEOMETRYENGINE_H
