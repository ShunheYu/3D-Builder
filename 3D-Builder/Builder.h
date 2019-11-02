#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Builder.h"
#include "MyOpenGLWidget.h"

class Builder : public QMainWindow
{
	Q_OBJECT

public:
	Builder(QWidget *parent = Q_NULLPTR);

private:
	Ui::BuilderClass ui;
};
