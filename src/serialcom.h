#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QObject>
#include <QSerialPort>

class SerialCom : public QObject
{
	Q_OBJECT

public:
	explicit SerialCom(QObject *parent = nullptr);
	~SerialCom();

public slots:
	void connectToComPort(const QString &comPortName, qint32 baudRate);
	void disconnectFromComPort();
	void sendCommand(const QString &command);

private:
	QSerialPort *serialPort;

private slots:
	void readData();
	void handleError(QSerialPort::SerialPortError error);

signals:
	void responseReceived(const QString &response);
	void connectionEstablished(bool connected);
	void errorOccurred(const QString &errorString);
	void startRecordingRequested();
};

#endif // SERIALCOM_H
