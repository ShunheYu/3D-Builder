#include "MyOpenGLWidget.h"
#include <QtGui/QKeyEvent>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent)
{
	this->grabKeyboard();
	this->grabMouse();
	this->app_abs_path = QCoreApplication::applicationDirPath();

	// loadVertices();
	// loadNormals();
	// loadTexCoords();

	// this->cubePositions.append({
		// {0.0f,  0.0f,  0.0f},
		// {2.0f,  5.0f, -15.0f},
		// {-1.5f, -2.2f, -2.5f},
		// {-3.8f, -2.0f, -12.3f},
		// {2.4f, -0.4f, -3.5f},
		// {-1.7f,  3.0f, -7.5f},
		// {1.3f, -2.0f, -2.5f},
		// {1.5f,  2.0f, -2.5f},
		// {1.5f,  0.2f, -1.5f},
		// {-1.3f,  1.0f, -1.5f}
	// });

	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(4, 4);
	setFormat(format);
	setCursor(Qt::ArrowCursor);

	this->translate = 0.0;
	this->xRot = this->zRot = 0.0;
	this->yRot = -30.0;
}

MyOpenGLWidget::~MyOpenGLWidget()
{
	VAO.destroy();
	VBO.destroy();
	EBO.destroy();
	delete program;
	delete texture;
	delete texture_specular;
	delete my_camera;
}

void MyOpenGLWidget::initializeGL()
{
	// 为当前环境初始化OpenGL函数
	initializeOpenGLFunctions();
	printContextInformation();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	initProgram();

	program->bind();
	QFileInfo file_info(QFile(this->app_abs_path + "/Resources/nanosuit/nanosuit.obj"));
	ourModel = new Model(file_info.absoluteFilePath(), program);
	// initVBO();
	// loadTexture();
	initCamera();
	program->release();
	// initVAO();
}

void MyOpenGLWidget::paintGL()
{
	const int w = width();
	const int h = height();
	// 将视口设置为窗口内最大的正方形
	const int side = qMin(w, h);
	glViewport((w - side) / 2, (h - side) / 2, side, side);
	// 清除上一帧的颜色和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 投影矩阵，设置视锥为45度
	projection.setToIdentity();
	projection.perspective(my_camera->Zoom,
		(GLfloat)width() / (GLfloat)height(), 0.1f, 100.0f);

	// 绘制光源
	// QMatrix4x4 lightModel;
	// lightModel.translate(lightPos);
	// lightModel.scale(0.2f, 0.2f, 0.2f);
	// program->bind();
	// program->removeAllShaders();
	// program->addShader(v_shader);
	// program->addShader(f_shader_light);
	// program->link();
	// {
		// program->setUniformValue("view", my_camera->GetViewMatrix());
		// program->setUniformValue("projection", projection);
		// program->setUniformValue("model", lightModel);
		// VAO[1].bind();
		// frame_time_1 = QDateTime::currentDateTime().toMSecsSinceEpoch() - frame_start_time_1;
		// glDrawArrays(GL_TRIANGLES, 0, 36);
		// frame_start_time_2 = QDateTime::currentDateTime().toMSecsSinceEpoch();
		// VAO[1].release();
	// }
	// program->release();

	// QMatrix4x4 matrix4[10];
	// for (int i = 0; i < 10; i++)
	// {
	// 	matrix4[i].rotate(xRot, 1, 0, 0);
	// 	matrix4[i].rotate(yRot, 0, 1, 0);
	// 	matrix4[i].rotate(zRot, 0, 0, 1);
	// 	matrix4[i].translate(cubePositions[i] + QVector3D({ 0,0,translate }));
	// }

	// 渲染Shader
	program->bind();

	QMatrix4x4 model;
	model.translate(0.0f, -1.75f, 0.0f);
	model.scale(0.2f, 0.2f, 0.2f);

	program->setUniformValue("view", my_camera->GetViewMatrix());
	program->setUniformValue("projection", projection);
	program->setUniformValue("model", model);
	ourModel->Draw(program);
	program->release();

	// glActiveTexture(GL_TEXTURE0);
	// texture->bind();
	// glActiveTexture(GL_TEXTURE1);
	// texture_specular->bind();
	//
	// VAO[0].bind();
	// frame_time_2 = QDateTime::currentDateTime().toMSecsSinceEpoch() - frame_start_time_2;
	// for (unsigned int i = 0; i < 10; i++)
	// {
	// 	// matrix4[i].rotate(qDegreesToRadians(20.0f * i), { 1.0f, 0.3f, 0.5f });
	// 	program->setUniformValue("model", matrix4[i]);
	// 	glDrawArrays(GL_TRIANGLES, 0, 36);
	// }
	// VAO[0].release();
	// frame_start_time_3 = QDateTime::currentDateTime().toMSecsSinceEpoch();
	// // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// program->release();


	const qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	if ((currentTime % 10) == 0)
	{
		qDebug() << "FPS:" << static_cast<int>(1000 / deltaTime);
	}
	update();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
	// 将视口设置为窗口内最大的正方形
	const int side = qMin(w, h);
	glViewport((w - side) / 2, (h - side) / 2, side, side);
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
	const float cameraSpeed = 0.005f * deltaTime;
	switch (event->key())
	{
	case Qt::Key_Up:
		xRot -= 10.0;
		break;
	case Qt::Key_Left:
		yRot -= 10.0;
		break;
	case Qt::Key_Right:
		yRot += 10.0;
		break;
	case Qt::Key_Down:
		xRot += 10.0;
		break;
	case Qt::Key_Space:
		// translate += 1.0;
		break;
	case Qt::Key_W:
		my_camera->ProcessKeyboard(FORWARD, deltaTime);
		break;
	case Qt::Key_S:
		my_camera->ProcessKeyboard(BACKWARD, deltaTime);
		break;
	case Qt::Key_A:
		my_camera->ProcessKeyboard(LEFT, deltaTime);
		break;
	case Qt::Key_D:
		my_camera->ProcessKeyboard(RIGHT, deltaTime);
		break;
	case Qt::Key_Q:
		my_camera->ProcessKeyboard(TURN_LEFT, deltaTime);
		break;
	case Qt::Key_E:
		my_camera->ProcessKeyboard(TURN_RIGHT, deltaTime);
		break;
	default:
		break;
	}
	update();
	QOpenGLWidget::keyPressEvent(event);
}

void MyOpenGLWidget::wheelEvent(QWheelEvent* event)
{
	my_camera->ProcessMouseScroll(event->delta());
	update();
	QOpenGLWidget::wheelEvent(event);
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		QPointF tmp = offset;
		offset = event->localPos();
		tmp = offset - tmp;
		xRot += tmp.y() * 1.0;
		yRot += tmp.x() * 1.0;
	}
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		QCursor cursor;
		cursor.setShape(Qt::OpenHandCursor);
		setCursor(cursor);
		offset = event->localPos();
	}
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	QCursor cursor;
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);
}

void MyOpenGLWidget::loadTexture()
{
	// 加载纹理贴图
	texture = new QOpenGLTexture(QImage(":/image/container2.png").mirrored());
	if (!texture->isCreated()) qDebug() << "Failed to load texture";
	// 设置环绕方式
	texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	// 设置过滤方式，缩小时为邻近，放大时为线性
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setWrapMode(QOpenGLTexture::Repeat);

	// QPixmap pixmap;
	// pixmap.load(":/image/container2_specular.png");
	// QFile file("Resources/container2_specular.png");
	// file.open(QIODevice::WriteOnly);
	// pixmap.save(&file, "PNG");
	texture_specular = new QOpenGLTexture(QImage(":/image/container2_specular.png").mirrored());
	if (!texture_specular->isCreated()) qDebug() << "Failed to load texture";
	// 设置环绕方式
	texture_specular->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	texture_specular->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	// 设置过滤方式，缩小时为邻近，放大时为线性
	texture_specular->setMinificationFilter(QOpenGLTexture::Nearest);
	texture_specular->setMagnificationFilter(QOpenGLTexture::Linear);
	texture_specular->setWrapMode(QOpenGLTexture::Repeat);
}

void MyOpenGLWidget::loadVertices()
{
	//设置顶点数据
	this->vertices.append(
		{ {-0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f,  0.5f, -0.5f},

			{0.5f,  0.5f, -0.5f},
			{-0.5f,  0.5f, -0.5f},
			{-0.5f, -0.5f, -0.5f},

			{-0.5f, -0.5f,  0.5f},
			{0.5f, -0.5f,  0.5f},
			{0.5f,  0.5f,  0.5f},

			{0.5f,  0.5f,  0.5f},
			{-0.5f,  0.5f,  0.5f},
			{-0.5f, -0.5f,  0.5f},

			{-0.5f,  0.5f,  0.5f},
			{-0.5f,  0.5f, -0.5f},
			{-0.5f, -0.5f, -0.5f},

			{-0.5f, -0.5f, -0.5f},
			{-0.5f, -0.5f,  0.5f},
			{-0.5f,  0.5f,  0.5f},

			{0.5f,  0.5f,  0.5f},
			{0.5f,  0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},

			{0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f,  0.5f},
			{0.5f,  0.5f,  0.5f},

			{-0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, 0.5f},

			{0.5f, -0.5f, 0.5f},
			{-0.5f, -0.5f, 0.5f},
			{-0.5f, -0.5f, -0.5f},

			{-0.5f, 0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{0.5f, 0.5f, 0.5f},

			{0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, -0.5f} });
}

void MyOpenGLWidget::loadNormals()
{
	this->normals.append({
		{0.0f,  0.0f, -1.0f},
		{0.0f,  0.0f, -1.0f},
		{0.0f,  0.0f, -1.0f},
		{0.0f,  0.0f, -1.0f},
		{0.0f,  0.0f, -1.0f},
		{0.0f,  0.0f, -1.0f},

		{0.0f,  0.0f, 1.0f},
		{0.0f,  0.0f, 1.0f},
		{0.0f,  0.0f, 1.0f},
		{0.0f,  0.0f, 1.0f},
		{0.0f,  0.0f, 1.0f},
		{0.0f,  0.0f, 1.0f},

		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},

		{1.0f,  0.0f,  0.0f},
		{1.0f,  0.0f,  0.0f},
		{1.0f,  0.0f,  0.0f},
		{1.0f,  0.0f,  0.0f},
		{1.0f,  0.0f,  0.0f},
		{1.0f,  0.0f,  0.0f},

		{0.0f, -1.0f,  0.0f},
		{0.0f, -1.0f,  0.0f},
		{0.0f, -1.0f,  0.0f},
		{0.0f, -1.0f,  0.0f},
		{0.0f, -1.0f,  0.0f},
		{0.0f, -1.0f,  0.0f},

		{0.0f,  1.0f,  0.0f},
		{0.0f,  1.0f,  0.0f},
		{0.0f,  1.0f,  0.0f},
		{0.0f,  1.0f,  0.0f},
		{0.0f,  1.0f,  0.0f},
		{0.0f,  1.0f,  0.0f}
		});
}

void MyOpenGLWidget::loadIndices()
{
}

void MyOpenGLWidget::loadColors()
{
}

void MyOpenGLWidget::loadTexCoords()
{
	this->texCoords.append(
		{ {0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 0.0f},

			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 0.0f},

			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},

			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},

			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f},
			{1.0f, 0.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f},

			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f},
			{1.0f, 0.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f} });
}

void MyOpenGLWidget::initVAO()
{
	// // 创建VAO
	// VAO[0].create();
	// VAO[0].bind();
	// // 返回参数位置
	// GLuint vPosition = program->attributeLocation("vPosition");
	// GLuint vNormal = program->attributeLocation("vNormal");
	// GLuint vTexCoord = program->attributeLocation("vTexCoord");
	// VBO.bind();
	// // EBO.bind();
	// program->bind();
	// program->enableAttributeArray(vPosition);
	// program->enableAttributeArray(vNormal);
	// program->enableAttributeArray(vTexCoord);
	// program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
	// program->setAttributeBuffer(vNormal, GL_FLOAT, 
	// 	vertices.size() * 3 * sizeof(GLfloat), 3, 0);
	// program->setAttributeBuffer(vTexCoord, GL_FLOAT,
	// 	(vertices.size() + normals.size()) * 3 * sizeof(GLfloat), 2, 0);
	// program->release();
	// VAO[0].release();
	// VBO.release();
	//
	// // 光源VAO
	// VAO[1].create();
	// VAO[1].bind();
	// VBO.bind();
	// program->bind();
	// program->enableAttributeArray(vPosition);
	// program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
	// program->release();
	// VAO[1].release();
	// VBO.release();

	// EBO.release();
}

void MyOpenGLWidget::initVBO()
{
	// 创建VBO
	VBO.create();
	// 将VBO绑定到上下文
	VBO.bind();
	VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	// 分配空间并缓存顶点数据
	VBO.allocate(vertices.constData(),
		((vertices.size() + normals.size()) * 3 + texCoords.size() * 2) * sizeof(GLfloat));
	VBO.write(vertices.size() * 3 * sizeof(GLfloat), normals.constData(),
		normals.size() * 3 * sizeof(GLfloat));
	VBO.write((vertices.size() + normals.size()) * 3 * sizeof(GLfloat), texCoords.constData(),
		texCoords.size() * 2 * sizeof(GLfloat));
	// VBO.write(vertices.size() * 3 * sizeof(GLfloat), texCoords.constData(), 
		// sizeof(GLfloat) * texCoords.size() * 2);
}

void MyOpenGLWidget::initEBO()
{
	// 创建EBO
	EBO.create();
	EBO.bind();
	EBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	EBO.allocate(indices.constData(), indices.size() * sizeof(GLuint));
}

void MyOpenGLWidget::initProgram()
{
	// 创建顶点着色器
	v_shader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	v_shader->compileSourceFile(this->app_abs_path + "/shaders/model_loading.vert");
	// 创建片段着色器
	f_shader_obj = new QOpenGLShader(QOpenGLShader::Fragment, this);
	f_shader_obj->compileSourceFile(this->app_abs_path + "/shaders/model_loading.frag");
	// 创建着色器程序
	f_shader_light = new QOpenGLShader(QOpenGLShader::Fragment, this);
	f_shader_light->compileSourceFile(this->app_abs_path + "/shaders/light_shader.frag");

	program = new QOpenGLShaderProgram;
	program->addShader(v_shader);
	program->addShader(f_shader_obj);
	program->link();

	// program->setUniformValue("projection", projection);
	// program->setUniformValue("material.shininess", 64.0f);
	// program->setUniformValue("spotLight.position", my_camera->Position);
	// program->setUniformValue("spotLight.direction", my_camera->Front);
	// float cutOff = qCos(qDegreesToRadians(12.5f));
	// float outerCutOff = qCos(qDegreesToRadians(17.5f));
	// program->setUniformValue("spotLight.cutOff", cutOff);
	// program->setUniformValue("spotLight.outerCutOff", outerCutOff);
	// program->setUniformValue("spotLight.ambient", 0.2f, 0.2f, 0.2f);
	// program->setUniformValue("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
	// program->setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);
	// program->setUniformValue("spotLight.constant", 1.0f);
	// program->setUniformValue("spotLight.linear", 0.09f);
	// program->setUniformValue("spotLight.quadratic", 0.032f);
}

void MyOpenGLWidget::initCamera()
{
	// 设置Look-At矩阵
	my_camera = new Camera({ 0.0f, 0.0f, 3.0f });
}

void MyOpenGLWidget::printContextInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	qDebug() << "Maximum nr of vertex attributes supported: " << nrAttributes;

	// Get Version Information
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	// Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile())
	{
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	// qPrintable() will print our QString w/o quotes around it.
	qDebug() << qPrintable(glType) << qPrintable(glVersion)
		<< "(" << qPrintable(glProfile) << ")";

}
