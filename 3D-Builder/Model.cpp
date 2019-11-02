#include "Model.h"

void Model::Draw(QOpenGLShaderProgram* program)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(program);
	}
}

void Model::loadModel(QString path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path.toStdString().c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		qDebug() << "ERROR:ASSIMP:: " << import.GetErrorString();
		return;
	}
	const int index = path.lastIndexOf('/');
	directory = path.mid(0, index + 1);

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// 处理节点所有的网格
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// 对该节点的子节点进行处理
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	QVector<Vertex> vertices;
	QVector<unsigned int> indices;
	QVector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// 顶点坐标
		QVector3D vector = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		vertex.Position = vector;
		// 法线
		vector = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		vertex.Normal = vector;
		// 纹理坐标
		if (mesh->mTextureCoords[0])
		{
			QVector2D vec;
			vec = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = { 0.0f, 0.0f };
		}
		// tangent
		vector = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
		vertex.Tangent = vector;
		// bitangent
		vector = { mesh->mBitangents[i].x,mesh->mBitangents[i].y, mesh->mBitangents[i].z };
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// 索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	// 材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		QVector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.append(diffuseMaps);
		QVector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.append(specularMaps);
		QVector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.append(normalMaps);
		QVector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.append(heightMaps);
	}
	return Mesh(vertices, indices, textures, program);
}

QVector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, QString typeName)
{
	QVector<Texture> new_textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures.size(); j++)
		{
			if (textures[j].path.compare(str.C_Str()) == 0)
			{
				new_textures.push_back(textures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.texture = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			new_textures.push_back(texture);
			textures.push_back(texture);
		}
	}
	return new_textures;
}

QOpenGLTexture* TextureFromFile(QString path, const QString& directory, bool gamma)
{
	QString filename = QString(path);
	filename = directory + '/' + filename;

	// Qt PNG图片格式不兼容时使用以下代码，只运行一次即可
	// QPixmap pixmap;
	// pixmap.load(filename);
	// QFile file(filename);
	// file.open(QIODevice::WriteOnly);
	// pixmap.save(&file, "PNG");
	// 加载纹理贴图
	QOpenGLTexture* texture = new QOpenGLTexture(QImage(filename));
	if (!texture->isCreated()) qDebug() << "Failed to load texture" << " path: " << path;
	// 设置环绕方式
	texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	// 设置过滤方式，缩小时为邻近，放大时为线性
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setWrapMode(QOpenGLTexture::Repeat);
	return texture;
}