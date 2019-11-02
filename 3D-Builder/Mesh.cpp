#include "Mesh.h"

Mesh::Mesh(QVector<Vertex> vertices, QVector<unsigned> indices, QVector<Texture> textures, QOpenGLShaderProgram* program)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->program = program;
	setupMesh();
}

void Mesh::Draw(QOpenGLShaderProgram* program)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	program->bind();
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		f->glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
		// 获取纹理序号（diffuse_textureN 中的 N）
		QString number;
		QString name = textures[i].type;
		if (name == "texture_diffuse")
			number = QString::number(diffuseNr++);
		else if (name == "texture_specular")
			number = QString::number(specularNr++);
		else if (name == "texture_normal")
			number = QString::number(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = QString::number(heightNr++); // transfer unsigned int to stream
		QString str = "material." + name + number;
		program->setUniformValue(str.data()->toLatin1(), i);
		// glBindTexture(GL_TEXTURE_2D, textures[i].id);
		textures[i].texture->bind();
	}
	// 绘制网格
	VAO->bind();
	f->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0);
	VAO->release();

	f->glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{

	// create buffers/arrays
	// glGenVertexArrays(1, &VAO);
	// glGenBuffers(1, &VBO);
	// glGenBuffers(1, &EBO);
	// VAO.create();
	// if (VAO.isCreated())
	// {
	// 	qDebug() << "success";
	// }
	// VBO.create();
	// EBO.create();
	//
	// VAO.bind();
	// VBO.bind();
	//
	// // load data into vertex buffers
	// // glBindBuffer(GL_ARRAY_BUFFER, VBO.bufferId());
	// // A great thing about structs is that their memory layout is sequential for all its items.
	// // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// // again translates to 3/2 floats which translates to a byte array.
	// glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	//
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO.bufferId());
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//
	// // set the vertex attribute pointers
	// // vertex Positions
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// // vertex normals
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// // vertex texture coords
	// glEnableVertexAttribArray(2);
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// // vertex tangent
	// glEnableVertexAttribArray(3);
	// glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// // vertex bitangent
	// glEnableVertexAttribArray(4);
	// glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
	//
	// glBindVertexArray(0);
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	VAO = new QOpenGLVertexArrayObject;
	VBO = new QOpenGLBuffer;
	EBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

	VAO->create();
	VBO->create();
	EBO->create();

	VAO->bind();
	VBO->bind();
	VBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
	VBO->allocate(vertices.constData(), vertices.size() * sizeof(Vertex));
	EBO->bind();
	EBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
	EBO->allocate(indices.constData(), indices.size() * sizeof(unsigned int));

	// 顶点位置
	f->glEnableVertexAttribArray(0);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// 顶点法线
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// 顶点纹理坐标
	f->glEnableVertexAttribArray(2);
	f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	VAO->release();
	EBO->release();
	VBO->release();
}

