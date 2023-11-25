#ifndef BASICSERIALTERMINAL_H
#define BASICSERIALTERMINAL_H

#include <QWidget>

#include "serialcom.h"
#include "comportselectwidget.h"

class BasicSerialTerminal : public QWidget
{
	Q_OBJECT

public:
	explicit BasicSerialTerminal(QWidget *parent = nullptr);
	SerialCom* getSerialCom(){return this->serialCom;}

private slots:

private:
	SerialCom* serialCom;
	ComPortSelectWidget* comPortSelectWidget;

	void setupUI();
	void setLayoutEnabled(QLayout* layout, bool enabled);
};

#endif // BASICSERIALTERMINAL_H
