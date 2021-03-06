#include <QApplication>
#include <QtGui/QtGui>
#include <QtGui/QDialog>
#include <QtCore/QTimer>
#include <QtCore/QResource>
#include "ImageViewer.h"

class SleeperThread : public QThread
{
public:
	static void msleep(unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QResource logoRes("images/logo.png");
	QPixmap *logoPixmap = new QPixmap();
	logoPixmap->loadFromData(logoRes.data(), logoRes.size());

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(*logoPixmap);
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),topRight, Qt::white);

	SleeperThread::msleep(5000);
    splash->finish(NULL);
    delete splash;
	delete logoPixmap;

    ImageViewer *window = new ImageViewer;
    window->show();
    
    return app.exec();
}