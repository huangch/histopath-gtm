#include <QDirModel>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QScrollArea>
#include <QMouseEvent>
#include <QScrollBar>
#include "ui_ImageViewer.h"

class NuclearPleomorphismScore
{
public:
	QString filePath;
	int score;
};

class TubuleFormationScore
{
public:
	QString filePath;
	int score;
};

class MitoticCountScore
{
public:
	QString filePath;
	int score;
};

class ScrollArea : public QScrollArea
{
Q_OBJECT
protected:

    void mousePressEvent(QMouseEvent *e)
	{
		if(e->button() == Qt::LeftButton)
            mousePos = e->pos();
    }

    void mouseMoveEvent(QMouseEvent *e)
	{
        QPoint diff = e->pos() - mousePos;
        mousePos = e->pos();
        verticalScrollBar()->setValue(verticalScrollBar()->value() - diff.y());
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - diff.x());
    }

    void wheelEvent(QWheelEvent *e) {
		

		if(e->delta() > 0) emit zoomIn();
		else emit zoomOut();
    }
signals:
	void zoomIn();
	void zoomOut();

    private:
    QPoint mousePos;
};

class ImageViewer : public QMainWindow, private Ui::ImageViewer
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = 0);
	~ImageViewer();
    
private slots:
	void on_actionLoad_triggered();
	void on_actionSave_triggered();
	void on_actionMitoticCount_3_triggered();
	void on_actionMitoticCount_2_triggered();
	void on_actionMitoticCount_1_triggered();
	void on_actionMitoticCount_N_triggered();
	void on_actionTubuleFormation_3_triggered();
	void on_actionTubuleFormation_2_triggered();
	void on_actionTubuleFormation_1_triggered();
	void on_actionTubuleFormation_N_triggered();
	void on_actionNuclearPleomorphism_3_triggered();
	void on_actionNuclearPleomorphism_2_triggered();
	void on_actionNuclearPleomorphism_1_triggered();
	void on_actionNuclearPleomorphism_N_triggered();
    void on_actionNext_triggered();
    void on_actionPrevious_triggered();
	void on_actionZoomOut_triggered();
	void on_actionZoomIn_triggered();
	void on_actionNormalSize_triggered();
	void on_treeView_clicked(const QModelIndex & index);
    void on_actionAbout_triggered();
    
private:
	void DisplayImage(const QString &fileName);
	void scaleImage(double factor);
	void updateNuclearPleomorphismScoreStatus(bool enabled);
	void updateTubuleFormationScoreStatus(bool enabled);
	void updateMitoticCountScoreStatus(bool enabled);
	void UpdateUI();
	void UpdateScoreLists();
	QLabel *imageLabel;
	ScrollArea *scrollArea;
	QDirModel *dirModel;
	QLabel *imageInfo;
	QDir *dirCurrent;
	QStringList supportFormat;
	QStringList displayFiles;
	QStringList::const_iterator currentFile;
	double scaleFactor;

	QList<NuclearPleomorphismScore*> m_nuclearPleomorphismScoreList;
	QList<TubuleFormationScore*> m_tubuleFormationScoreList;
	QList<MitoticCountScore*> m_mitoticCountScoreList;
};
