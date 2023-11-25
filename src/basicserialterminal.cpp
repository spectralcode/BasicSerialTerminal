#include "basicserialterminal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>


BasicSerialTerminal::BasicSerialTerminal(QWidget *parent)
	: QWidget(parent),
	  serialCom(new SerialCom(this)),
	  comPortSelectWidget(new ComPortSelectWidget(this))
{
	connect(this->comPortSelectWidget, &ComPortSelectWidget::connectToComPortRequested, this->serialCom, &SerialCom::connectToComPort);
	connect(this->comPortSelectWidget, &ComPortSelectWidget::disconnectFromComPortRequested, this->serialCom, &SerialCom::disconnectFromComPort);
	this->setupUI();
}

void BasicSerialTerminal::setupUI()
{
	//custom command gui elements
	QLineEdit* customCommandLineEdit = new QLineEdit(this);
	QPushButton* sendCommandButton = new QPushButton("Send", this);
	sendCommandButton->setFocusPolicy(Qt::NoFocus);
	QHBoxLayout *commandLayout = new QHBoxLayout();
	commandLayout->addWidget(customCommandLineEdit);
	commandLayout->addWidget(sendCommandButton);

	connect(sendCommandButton, &QPushButton::clicked, [this, customCommandLineEdit]() {
		this->serialCom->sendCommand(customCommandLineEdit->text());
	});
	connect(customCommandLineEdit, &QLineEdit::returnPressed, sendCommandButton, &QPushButton::click);


	//response text area
	QTextEdit *responseTextEdit = new QTextEdit(this);
	responseTextEdit->setReadOnly(true);
	connect(this->serialCom, &SerialCom::responseReceived, this,
		[responseTextEdit](const QString &response) {
			responseTextEdit->append(response);
			//limit how much text can be in text area
			int maxTextLength = 30000;
			if (responseTextEdit->toPlainText().length() > maxTextLength) {
				responseTextEdit->setPlainText(responseTextEdit->toPlainText().right(maxTextLength));
				responseTextEdit->moveCursor(QTextCursor::End);
			}
		});

	//main layout
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(comPortSelectWidget);
	mainLayout->addLayout(commandLayout);
	mainLayout->addWidget(responseTextEdit);
	setLayout(mainLayout);

	this->setLayoutEnabled(commandLayout, false);
	responseTextEdit->setEnabled(false);

	connect(this->serialCom, &SerialCom::connectionEstablished, this,
		[this, commandLayout, responseTextEdit](bool connected) {
			this->setLayoutEnabled(commandLayout, connected);
			responseTextEdit->setEnabled(connected);
		});
}

void BasicSerialTerminal::setLayoutEnabled(QLayout *layout, bool enabled)
{
	if(!layout){
		return;
	}
	for(int i = 0; i < layout->count(); ++i){
		QWidget* widget = layout->itemAt(i)->widget();
		if(widget){
			widget->setEnabled(enabled);
		}
	}
}
