#include "geometryengine.h"

GeometryEngine::GeometryEngine() : indexBuf(QOpenGLBuffer::IndexBuffer) {
    initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();
    initGeometry();
}

GeometryEngine::~GeometryEngine() {
    arrayBuf.destroy();
    indexBuf.destroy();
}

int GeometryEngine::get_vertices_count() { return 8164; }

int GeometryEngine::get_indices_count() { return 47733; }

int GeometryEngine::get_vertex_size() { return sizeof(MeshVertexData); }

void GeometryEngine::initGeometry() {
    MeshVertexData vertices[] = {
        #include <builtins/Nikita0.gen.txt>
    }; // len = 8164

    GLushort indices[]    = {
        #include <builtins/NikitaI.gen.txt>
    }; // len = 47733

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, get_vertices_count() * get_vertex_size());

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, get_indices_count() * sizeof(GLushort));
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    /// POSITION
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(MeshVertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    /// NORMAL
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(MeshVertexData));

    offset += sizeof(QVector3D);

    /// TEXCOORD_0
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(MeshVertexData));

    // Draw cube geometry using indices from VBO 1
    // glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLES, 47733, GL_UNSIGNED_SHORT, 0);
}

struct draw_commands : protected QOpenGLFunctions {};
struct draw_variable_buffer : public draw_commands {
    attr(const QString& name, GLenum type, int offset, int tupleSize, int stride = 0 );
};
struct draw_elements : draw_commands {
    void paint() {
        glDrawElements(GL_TRIANGLES, 47733, GL_UNSIGNED_SHORT, 0);
    }
};

void SkinGeometryShared::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    /// ПЕРЕМЕЖЕННЫЙ МАССИВ АТТРИБУТОВ ВЕРШИН МАССИВ
    /// int attribute_location, QString attribute_name локация
    /// POSITION локация атрибута, тип атрибута
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(SkinVertexData));

    // Offset for normal vector
    offset += sizeof(QVector3D);

    /// NORMAL
    // Tell OpenGL programmable pipeline how to locate normal vector data
    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(SkinVertexData));

    offset += sizeof(QVector3D);

    /// WEIGHTS_0
    // Tell OpenGL programmable pipeline how to locate joint's WEIGHTS_0 vec4 data
    int weights_0_location = program->attributeLocation("a_weights_0");
    program->enableAttributeArray(weights_0_location);
    program->setAttributeBuffer(weights_0_location, GL_FLOAT, offset, 4, sizeof(SkinVertexData));

    offset += sizeof(QVector4D);

    /// JOINTS_0
    // Tell OpenGL programmable pipeline how to locate joint's WEIGHTS_0 vec4 data
    int joints_0_location = program->attributeLocation("a_joints_0");
    program->enableAttributeArray(joints_0_location);
    program->setAttributeBuffer(joints_0_location, GL_FLOAT, offset, 4, sizeof(SkinVertexData));

    offset += sizeof(QVector4D);

    /// TEXCOORD_0
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(SkinVertexData));

    // Draw cube geometry using indices from VBO 1
    // glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLES, 47733, GL_UNSIGNED_SHORT, 0);
}
