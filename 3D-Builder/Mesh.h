#pragma once
#include <QtCore/QString>
#include <QtGui/QVector3D>
#include <QtOpenGLExtensions/QtOpenGLExtensions>
#include <QtGui/QOpenGLFunctions_4_4_Core>

struct Vertex
{
	QVector3D Position;
	QVector3D Normal;
	QVector2D TexCoords;
	QVector3D Tangent;
	QVector3D Bitangent;
};

struct Texture
{
	// unsigned int id;
	QOpenGLTexture* texture;
	QString type;
	QString path;
};

class Mesh : protected QOpenGLFunctions_4_4_Core
{
public:
	QVector<Vertex> vertices;
	QVector<unsigned int> indices;
	QVector<Texture> textures;
	// unsigned int VAO;
	QOpenGLVertexArrayObject* VAO;
	QOpenGLShaderProgram* program;
	Mesh() {}
	Mesh(const Mesh& mesh)
	{
		this->vertices = mesh.vertices;
		this->indices = mesh.indices;
		this->textures = mesh.textures;

		this->VAO = mesh.VAO;
		this->VBO = mesh.VBO;
		this->EBO = mesh.EBO;
		this->program = mesh.program;
		//setupMesh();
	}
	Mesh(QVector<Vertex> vertices, QVector<unsigned int> indices, QVector<Texture> textures, QOpenGLShaderProgram* program);
	void Draw(QOpenGLShaderProgram* program);
private:
	// unsigned int VBO, EBO;
	QOpenGLBuffer* VBO;
	QOpenGLBuffer* EBO;
	// = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	void setupMesh();
};