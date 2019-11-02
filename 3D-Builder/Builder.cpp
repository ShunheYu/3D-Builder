#include "Builder.h"

Builder::Builder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setMinimumWidth(800);
	this->setMinimumHeight(600);

	QVBoxLayout* layout = new QVBoxLayout(this->centralWidget());
	MyOpenGLWidget* openGLWidget = new MyOpenGLWidget(this);
	layout->addWidget(openGLWidget);
}
