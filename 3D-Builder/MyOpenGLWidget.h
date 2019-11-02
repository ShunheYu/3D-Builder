#pragma once
#include <QtGui/QOpenGLFunctions_4_4_Core>
#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>
#include "Camera.h"
#include "Model.h"

class QOpenGLShaderProgram;
class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT
public:
	explicit MyOpenGLWidget(QWidget* parent = nullptr);
	~MyOpenGLWidget();
protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	void keyPressEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QString app_abs_path;

	Model* ourModel;
	// 顶点数组
	QVector<QVector3D> vertices;
	// 法线数组
	QVector<QVector3D> normals;
	// 索引数组
	QVector<GLuint> indices;
	// 颜色数组
	QVector<QVector3D> colors;
	QVector<QVector3D> cubePositions;

	// 纹理坐标
	QVector<QVector2D> texCoords;
	// 光源坐标
	QVector3D lightPos = { 2.0f, 2.0f, 2.0f };
	// 纹理
	QOpenGLTexture* texture;
	QOpenGLTexture* texture_specular;
	QOpenGLVertexArrayObject VAO;
	QOpenGLBuffer VBO;
	QOpenGLBuffer EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	// 渲染程序
	QOpenGLShader* v_shader, * f_shader_obj, * f_shader_light;
	QOpenGLShaderProgram* program;
	GLfloat translate, xRot, yRot, zRot;
	QPointF offset;

	float deltaTime = 0.0f;
	qint64 lastTime = 0;

	QMatrix4x4 projection;

	Camera* my_camera;

	void loadTexture();
	void loadVertices();
	void loadNormals();
	void loadIndices();
	void loadColors();
	void loadTexCoords();
	void initVAO();
	void initVBO();
	void initEBO();
	void initProgram();
	void initCamera();
	// 显示OpenGL信息
	void printContextInformation();
};
