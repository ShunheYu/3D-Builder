#pragma once
#include <QtCore/QString>
#include <QtGui/QtGui>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

QOpenGLTexture* TextureFromFile(QString path, const QString& directory, bool gamma = false);

class Model
{
public:
	QVector<Texture> textures;
	QVector<Mesh> meshes;
	QString directory;
	bool gammaCorrection;
	QOpenGLShaderProgram* program;

	Model(QString path, QOpenGLShaderProgram* program, bool gamma = false) : gammaCorrection(gamma), program(program)
	{
		loadModel(path);
	}
	void Draw(QOpenGLShaderProgram* program);
private:
	void loadModel(QString path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	QVector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, QString typeName);
};
