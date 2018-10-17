#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QImageReader>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1)
{
	setupUi(this);

	actionNuclearPleomorphism_N->setShortcut(QKeySequence(tr("Q")));
	actionNuclearPleomorphism_N->setCheckable(true);
	actionNuclearPleomorphism_N->setChecked(false);
	actionNuclearPleomorphism_N->setEnabled(false);
	actionNuclearPleomorphism_1->setShortcut(QKeySequence(tr("W")));
	actionNuclearPleomorphism_1->setCheckable(true);
	actionNuclearPleomorphism_1->setChecked(false);
	actionNuclearPleomorphism_1->setEnabled(false);
	actionNuclearPleomorphism_2->setShortcut(QKeySequence(tr("E")));
	actionNuclearPleomorphism_2->setCheckable(true);
	actionNuclearPleomorphism_2->setChecked(false);
	actionNuclearPleomorphism_2->setEnabled(false);
	actionNuclearPleomorphism_3->setShortcut(QKeySequence(tr("R")));
	actionNuclearPleomorphism_3->setCheckable(true);
	actionNuclearPleomorphism_3->setChecked(false);
	actionNuclearPleomorphism_3->setEnabled(false);

	actionTubuleFormation_N->setShortcut(QKeySequence(tr("A")));
	actionTubuleFormation_N->setCheckable(true);
	actionTubuleFormation_N->setChecked(false);
	actionTubuleFormation_N->setEnabled(false);
	actionTubuleFormation_1->setShortcut(QKeySequence(tr("S")));
	actionTubuleFormation_1->setCheckable(true);
	actionTubuleFormation_1->setChecked(false);
	actionTubuleFormation_1->setEnabled(false);
	actionTubuleFormation_2->setShortcut(QKeySequence(tr("D")));
	actionTubuleFormation_2->setCheckable(true);
	actionTubuleFormation_2->setChecked(false);
	actionTubuleFormation_2->setEnabled(false);
	actionTubuleFormation_3->setShortcut(QKeySequence(tr("F")));
	actionTubuleFormation_3->setCheckable(true);
	actionTubuleFormation_3->setChecked(false);
	actionTubuleFormation_3->setEnabled(false);

	actionMitoticCount_N->setShortcut(QKeySequence(tr("Z")));
	actionMitoticCount_N->setCheckable(true);
	actionMitoticCount_N->setChecked(false);
	actionMitoticCount_N->setEnabled(false);
	actionMitoticCount_1->setShortcut(QKeySequence(tr("X")));
	actionMitoticCount_1->setCheckable(true);
	actionMitoticCount_1->setChecked(false);
	actionMitoticCount_1->setEnabled(false);
	actionMitoticCount_2->setShortcut(QKeySequence(tr("C")));
	actionMitoticCount_2->setCheckable(true);
	actionMitoticCount_2->setChecked(false);
	actionMitoticCount_2->setEnabled(false);
	actionMitoticCount_3->setShortcut(QKeySequence(tr("V")));
	actionMitoticCount_3->setCheckable(true);
	actionMitoticCount_3->setChecked(false);
	actionMitoticCount_3->setEnabled(false);

	actionPrevious->setShortcut(QKeySequence(tr("Left")));
	actionNext->setShortcut(QKeySequence(tr("Right")));
	actionZoomIn->setShortcut(QKeySequence(tr("Up")));
	actionZoomOut->setShortcut(QKeySequence(tr("Down")));

	actionSave->setEnabled(false);
	actionLoad->setEnabled(false);

	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);
	scrollArea = new ScrollArea;
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(imageLabel);
	scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setCentralWidget(scrollArea);
	dirModel = new QDirModel(this);
	dirModel->setFilter(QDir::Dirs | QDir::Drives | QDir::NoDotAndDotDot);
	dirCurrent = new QDir();
	imageInfo = new QLabel(this);
	imageInfo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	imageInfo->setAlignment(Qt::AlignCenter);
	imageInfo->setStatusTip(tr("Display image infomation in the selected folder"));
	toolBar->addWidget(imageInfo);
	treeView->setModel(dirModel);
	treeView->header()->setVisible(false);
	treeView->setColumnHidden(1,true);	// Size
	treeView->setColumnHidden(2,true);  // Type
	treeView->setColumnHidden(3,true);  // Modified Date

	foreach (QByteArray ba, QImageReader::supportedImageFormats())
	{
		QString ext = QString("*.")+QString(ba);
		supportFormat<<ext;
	}
	resize(780,580);

	connect(scrollArea, SIGNAL(zoomIn()), this, SLOT(on_actionZoomIn_triggered()));
	connect(scrollArea, SIGNAL(zoomOut()), this, SLOT(on_actionZoomOut_triggered()));

	currentFile = displayFiles.constBegin();
	UpdateUI();
}

ImageViewer::~ImageViewer()
{
	delete dirCurrent;
}

void adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void ImageViewer::DisplayImage(const QString &fileName)
{
		QImage image(fileName);
		if (image.isNull()) {
		    QMessageBox::information(this, tr("Image Viewer"),
		                             tr("Cannot load %1.").arg(fileName));
		    return;
		}

		imageLabel->setPixmap(QPixmap::fromImage(image));
		scaleImage(1.0);
}

void ImageViewer::UpdateUI()
{
	if(currentFile == displayFiles.constEnd())
	{
		imageInfo->setText(tr("No Images, Click TreeView to select pic folder"));
		actionNext->setEnabled(false);
		actionPrevious->setEnabled(false);
		actionZoomIn->setEnabled(false);
		actionZoomOut->setEnabled(false);
		actionNormalSize->setEnabled(false);
		actionSave->setEnabled(false);

		updateNuclearPleomorphismScoreStatus(false);
		updateTubuleFormationScoreStatus(false);		
		updateMitoticCountScoreStatus(false);		
	}
	else
	{
		int i = displayFiles.indexOf(*currentFile, 0) + 1;	// non-Programmer count from 1 instead 0
		imageInfo->setText(QString(tr("%1/%2 %3 %4%")).arg(i).arg(displayFiles.size()).arg(*currentFile).arg(scaleFactor*100, 3));
		actionNext->setEnabled(true);
		actionPrevious->setEnabled(true);
		actionZoomIn->setEnabled(true);
		actionZoomOut->setEnabled(true);
		actionNormalSize->setEnabled(true);
		actionSave->setEnabled(true);

		updateNuclearPleomorphismScoreStatus(true);
		updateTubuleFormationScoreStatus(true);		
		updateMitoticCountScoreStatus(true);		
	}

	actionZoomIn->setEnabled(scaleFactor < 3.0);
	actionZoomOut->setEnabled(scaleFactor > 0.333);
	
	if(QFile::exists(dirCurrent->path() + "/Histopatho-GTM_NP.txt") ||
		QFile::exists(dirCurrent->path() + "/Histopatho-GTM_TF.txt") ||
		QFile::exists(dirCurrent->path() + "/Histopatho-GTM_MC.txt"))
	{
		actionLoad->setEnabled(true);
	}


}

void ImageViewer::on_actionNext_triggered()
{
	currentFile++;
	if(currentFile == displayFiles.constEnd())
		currentFile = displayFiles.constBegin();
	DisplayImage(dirCurrent->absoluteFilePath(*currentFile));
	UpdateUI();
}

void ImageViewer::on_actionPrevious_triggered()
{
	if(currentFile == displayFiles.constBegin())
		currentFile = displayFiles.constEnd();
	currentFile--;
	DisplayImage(dirCurrent->absoluteFilePath(*currentFile));
	UpdateUI();
}

void ImageViewer::on_actionZoomOut_triggered()
{
	scaleImage(0.8);
	UpdateUI();
}

void ImageViewer::on_actionZoomIn_triggered()
{
	scaleImage(1.25);
	UpdateUI();
}



void ImageViewer::on_treeView_clicked ( const QModelIndex &index )
{
	const QString path = dirModel->data(index, QDirModel::FilePathRole).toString();
	dirCurrent->setPath(path);
	displayFiles = dirCurrent->entryList(supportFormat, QDir::Files);
	currentFile = displayFiles.constBegin();
	if(currentFile != displayFiles.constEnd()) DisplayImage(dirCurrent->absoluteFilePath(*currentFile));
	UpdateUI();

}

const char *htmlAboutText =
"<HTML>"
"<p>This program is subject to GPL license.</p>"
"<p>Developed and maintenanted by Chao-Hui Huang (Ph.D.) @ Image & Pervasive Access Lab (IPAL), French-Singaporean International Joint Laboratory (CNRS UMI 2955, A*STAR/I2R, NUS, UJF)</p>"
"<p><a href=\"http://ipal.i2r.a-star.edu.sg/\">http://ipal.i2r.a-star.edu.sg/</a></p>"
"</HTML>";

void ImageViewer::on_actionAbout_triggered()
{
	QMessageBox::about(this, tr("About Qt Mini Image Viewer"), htmlAboutText);	
}


void ImageViewer::on_actionNormalSize_triggered()
{
	scaleFactor = 1.0;
	scaleImage(1.0);
	UpdateUI();
}

void ImageViewer::updateNuclearPleomorphismScoreStatus(bool enabled)
{
	QList<NuclearPleomorphismScore*>::iterator scoreListIterator;

	if(enabled == true)
	{
		actionNuclearPleomorphism_N->setEnabled(true);
		actionNuclearPleomorphism_1->setEnabled(true);
		actionNuclearPleomorphism_2->setEnabled(true);
		actionNuclearPleomorphism_3->setEnabled(true);

		actionNuclearPleomorphism_N->setChecked(false);
		actionNuclearPleomorphism_1->setChecked(false);
		actionNuclearPleomorphism_2->setChecked(false);
		actionNuclearPleomorphism_3->setChecked(false);

		actionNuclearPleomorphism_N->setChecked(true);

		for (scoreListIterator = m_nuclearPleomorphismScoreList.begin(); scoreListIterator != m_nuclearPleomorphismScoreList.end(); ++scoreListIterator)
		{
			QString a = (*scoreListIterator)->filePath;
			QString b = dirCurrent->absoluteFilePath(*currentFile);

			if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
			{
				switch((*scoreListIterator)->score)
				{
				case 1:
					actionNuclearPleomorphism_N->setChecked(false);
					actionNuclearPleomorphism_1->setChecked(true);
					break;
				case 2:
					actionNuclearPleomorphism_N->setChecked(false);
					actionNuclearPleomorphism_2->setChecked(true);
					break;
				case 3:
					actionNuclearPleomorphism_N->setChecked(false);
					actionNuclearPleomorphism_3->setChecked(true);
					break;
				}

				break;
			}
		}
	}
	else
	{
		actionNuclearPleomorphism_N->setChecked(false);
		actionNuclearPleomorphism_1->setChecked(false);
		actionNuclearPleomorphism_2->setChecked(false);
		actionNuclearPleomorphism_3->setChecked(false);

		actionNuclearPleomorphism_N->setEnabled(false);
		actionNuclearPleomorphism_1->setEnabled(false);
		actionNuclearPleomorphism_2->setEnabled(false);
		actionNuclearPleomorphism_3->setEnabled(false);
	}
}

void ImageViewer::on_actionNuclearPleomorphism_N_triggered()
{
	actionNuclearPleomorphism_N->setChecked(true);
	actionNuclearPleomorphism_1->setChecked(false);
	actionNuclearPleomorphism_2->setChecked(false);
	actionNuclearPleomorphism_3->setChecked(false);

	QList<NuclearPleomorphismScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_nuclearPleomorphismScoreList.begin(); scoreListIterator != m_nuclearPleomorphismScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			m_nuclearPleomorphismScoreList.erase(scoreListIterator);

			break;
		}
	}

}

void ImageViewer::on_actionNuclearPleomorphism_1_triggered()
{
	actionNuclearPleomorphism_N->setChecked(false);
	actionNuclearPleomorphism_1->setChecked(true);
	actionNuclearPleomorphism_2->setChecked(false);
	actionNuclearPleomorphism_3->setChecked(false);

	QList<NuclearPleomorphismScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_nuclearPleomorphismScoreList.begin(); scoreListIterator != m_nuclearPleomorphismScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 1;
			break;
		}
	}

	if(scoreListIterator == m_nuclearPleomorphismScoreList.end())
	{
		NuclearPleomorphismScore *score = new NuclearPleomorphismScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 1;
		m_nuclearPleomorphismScoreList.append(score);
	}
}

void ImageViewer::on_actionNuclearPleomorphism_2_triggered()
{
	actionNuclearPleomorphism_N->setChecked(false);
	actionNuclearPleomorphism_1->setChecked(false);
	actionNuclearPleomorphism_2->setChecked(true);
	actionNuclearPleomorphism_3->setChecked(false);

	QList<NuclearPleomorphismScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_nuclearPleomorphismScoreList.begin(); scoreListIterator != m_nuclearPleomorphismScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 2;
			break;
		}
	}

	if(scoreListIterator == m_nuclearPleomorphismScoreList.end())
	{
		NuclearPleomorphismScore *score = new NuclearPleomorphismScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 2;
		m_nuclearPleomorphismScoreList.append(score);
	}

}

void ImageViewer::on_actionNuclearPleomorphism_3_triggered()
{
	actionNuclearPleomorphism_N->setChecked(false);
	actionNuclearPleomorphism_1->setChecked(false);
	actionNuclearPleomorphism_2->setChecked(false);
	actionNuclearPleomorphism_3->setChecked(true);

	QList<NuclearPleomorphismScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_nuclearPleomorphismScoreList.begin(); scoreListIterator != m_nuclearPleomorphismScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 3;
			break;
		}
	}

	if(scoreListIterator == m_nuclearPleomorphismScoreList.end())
	{
		NuclearPleomorphismScore *score = new NuclearPleomorphismScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 3;
		m_nuclearPleomorphismScoreList.append(score);
	}
}

void ImageViewer::updateTubuleFormationScoreStatus(bool enabled)
{
	QList<TubuleFormationScore*>::iterator scoreListIterator;

	if(enabled == true)
	{
		actionTubuleFormation_N->setEnabled(true);
		actionTubuleFormation_1->setEnabled(true);
		actionTubuleFormation_2->setEnabled(true);
		actionTubuleFormation_3->setEnabled(true);

		actionTubuleFormation_N->setChecked(false);
		actionTubuleFormation_1->setChecked(false);
		actionTubuleFormation_2->setChecked(false);
		actionTubuleFormation_3->setChecked(false);

		for (scoreListIterator = m_tubuleFormationScoreList.begin(); scoreListIterator != m_tubuleFormationScoreList.end(); ++scoreListIterator)
		{
			if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
			{
				switch((*scoreListIterator)->score)
				{
				case 1:
					actionTubuleFormation_1->setChecked(true);
					break;
				case 2:
					actionTubuleFormation_2->setChecked(true);
					break;
				case 3:
					actionTubuleFormation_3->setChecked(true);
					break;
				}

				break;
			}
		}

		if(scoreListIterator == m_tubuleFormationScoreList.end())
		{
			actionTubuleFormation_N->setChecked(true);
		}
	}
	else
	{
		actionTubuleFormation_N->setChecked(false);
		actionTubuleFormation_1->setChecked(false);
		actionTubuleFormation_2->setChecked(false);
		actionTubuleFormation_3->setChecked(false);

		actionTubuleFormation_N->setEnabled(false);
		actionTubuleFormation_1->setEnabled(false);
		actionTubuleFormation_2->setEnabled(false);
		actionTubuleFormation_3->setEnabled(false);
	}
}

void ImageViewer::on_actionTubuleFormation_N_triggered()
{
	actionTubuleFormation_N->setChecked(true);
	actionTubuleFormation_1->setChecked(false);
	actionTubuleFormation_2->setChecked(false);
	actionTubuleFormation_3->setChecked(false);

	QList<TubuleFormationScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_tubuleFormationScoreList.begin(); scoreListIterator != m_tubuleFormationScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			m_tubuleFormationScoreList.erase(scoreListIterator);

			break;
		}
	}
}

void ImageViewer::on_actionTubuleFormation_1_triggered()
{
	actionTubuleFormation_N->setChecked(false);
	actionTubuleFormation_1->setChecked(true);
	actionTubuleFormation_2->setChecked(false);
	actionTubuleFormation_3->setChecked(false);

	QList<TubuleFormationScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_tubuleFormationScoreList.begin(); scoreListIterator != m_tubuleFormationScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 1;
			break;
		}
	}

	if(scoreListIterator == m_tubuleFormationScoreList.end())
	{
		TubuleFormationScore *score = new TubuleFormationScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 1;
		m_tubuleFormationScoreList.append(score);
	}
}

void ImageViewer::on_actionTubuleFormation_2_triggered()
{
	actionTubuleFormation_N->setChecked(false);
	actionTubuleFormation_1->setChecked(false);
	actionTubuleFormation_2->setChecked(true);
	actionTubuleFormation_3->setChecked(false);

	QList<TubuleFormationScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_tubuleFormationScoreList.begin(); scoreListIterator != m_tubuleFormationScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 2;
			break;
		}
	}

	if(scoreListIterator == m_tubuleFormationScoreList.end())
	{
		TubuleFormationScore *score = new TubuleFormationScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 2;
		m_tubuleFormationScoreList.append(score);
	}
}

void ImageViewer::on_actionTubuleFormation_3_triggered()
{
	actionTubuleFormation_N->setChecked(false);
	actionTubuleFormation_1->setChecked(false);
	actionTubuleFormation_2->setChecked(false);
	actionTubuleFormation_3->setChecked(true);

	QList<TubuleFormationScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_tubuleFormationScoreList.begin(); scoreListIterator != m_tubuleFormationScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 3;
			break;
		}
	}

	if(scoreListIterator == m_tubuleFormationScoreList.end())
	{
		TubuleFormationScore *score = new TubuleFormationScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 3;
		m_tubuleFormationScoreList.append(score);
	}
}

void ImageViewer::updateMitoticCountScoreStatus(bool enabled)
{
	QList<MitoticCountScore*>::iterator scoreListIterator;

	if(enabled == true)
	{
		actionMitoticCount_N->setEnabled(true);
		actionMitoticCount_1->setEnabled(true);
		actionMitoticCount_2->setEnabled(true);
		actionMitoticCount_3->setEnabled(true);

		actionMitoticCount_N->setChecked(false);
		actionMitoticCount_1->setChecked(false);
		actionMitoticCount_2->setChecked(false);
		actionMitoticCount_3->setChecked(false);

		for (scoreListIterator = m_mitoticCountScoreList.begin(); scoreListIterator != m_mitoticCountScoreList.end(); ++scoreListIterator)
		{
			if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
			{
				switch((*scoreListIterator)->score)
				{
				case 1:
					actionMitoticCount_1->setChecked(true);
					break;
				case 2:
					actionMitoticCount_2->setChecked(true);
					break;
				case 3:
					actionMitoticCount_3->setChecked(true);
					break;
				}

				break;
			}
		}

		if(scoreListIterator == m_mitoticCountScoreList.end())
		{
			actionMitoticCount_N->setChecked(true);
		}
	}
	else
	{
		actionMitoticCount_N->setChecked(false);
		actionMitoticCount_1->setChecked(false);
		actionMitoticCount_2->setChecked(false);
		actionMitoticCount_3->setChecked(false);

		actionMitoticCount_N->setEnabled(false);
		actionMitoticCount_1->setEnabled(false);
		actionMitoticCount_2->setEnabled(false);
		actionMitoticCount_3->setEnabled(false);
	}
}

void ImageViewer::on_actionMitoticCount_N_triggered()
{
	actionMitoticCount_N->setChecked(true);
	actionMitoticCount_1->setChecked(false);
	actionMitoticCount_2->setChecked(false);
	actionMitoticCount_3->setChecked(false);

	QList<MitoticCountScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_mitoticCountScoreList.begin(); scoreListIterator != m_mitoticCountScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			m_mitoticCountScoreList.erase(scoreListIterator);

			break;
		}
	}
}

void ImageViewer::on_actionMitoticCount_1_triggered()
{
	actionMitoticCount_N->setChecked(false);
	actionMitoticCount_1->setChecked(true);
	actionMitoticCount_2->setChecked(false);
	actionMitoticCount_3->setChecked(false);

	QList<MitoticCountScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_mitoticCountScoreList.begin(); scoreListIterator != m_mitoticCountScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 1;
			break;
		}
	}

	if(scoreListIterator == m_mitoticCountScoreList.end())
	{
		MitoticCountScore *score = new MitoticCountScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 1;
		m_mitoticCountScoreList.append(score);
	}
}

void ImageViewer::on_actionMitoticCount_2_triggered()
{
	actionMitoticCount_N->setChecked(false);
	actionMitoticCount_1->setChecked(false);
	actionMitoticCount_2->setChecked(true);
	actionMitoticCount_3->setChecked(false);

	QList<MitoticCountScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_mitoticCountScoreList.begin(); scoreListIterator != m_mitoticCountScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 2;
			break;
		}
	}

	if(scoreListIterator == m_mitoticCountScoreList.end())
	{
		MitoticCountScore *score = new MitoticCountScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 2;
		m_mitoticCountScoreList.append(score);
	}
}

void ImageViewer::on_actionMitoticCount_3_triggered()
{
	actionMitoticCount_N->setChecked(false);
	actionMitoticCount_1->setChecked(false);
	actionMitoticCount_2->setChecked(false);
	actionMitoticCount_3->setChecked(true);

	QList<MitoticCountScore*>::iterator scoreListIterator;

	for (scoreListIterator = m_mitoticCountScoreList.begin(); scoreListIterator != m_mitoticCountScoreList.end(); ++scoreListIterator)
	{
		if((*scoreListIterator)->filePath == dirCurrent->absoluteFilePath(*currentFile))
		{
			(*scoreListIterator)->score = 3;
			break;
		}
	}

	if(scoreListIterator == m_mitoticCountScoreList.end())
	{
		MitoticCountScore *score = new MitoticCountScore;
		score->filePath = dirCurrent->absoluteFilePath(*currentFile);
		score->score = 3;
		m_mitoticCountScoreList.append(score);
	}
}


void ImageViewer::on_actionSave_triggered()
{
	QMessageBox msgBox;
	int npCount = 0;
	int tfCount = 0;
	int mcCount = 0;

	msgBox.setText("Score Data will be saved to the file. Data in the file will be overwrited.");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);

	if(msgBox.exec() != QMessageBox::Yes) return;

	QFile::remove(dirCurrent->path() + "/Histopatho-GTM_NP.txt");
	QFile::remove(dirCurrent->path() + "/Histopatho-GTM_TF.txt");
	QFile::remove(dirCurrent->path() + "/Histopatho-GTM_MC.txt");

	QFile npFile(dirCurrent->path() + "/Histopatho-GTM_NP.txt");
	if (!npFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	QTextStream npOut(&npFile);

	for (QList<NuclearPleomorphismScore*>::iterator npScoreListIterator = m_nuclearPleomorphismScoreList.begin(); npScoreListIterator != m_nuclearPleomorphismScoreList.end(); ++npScoreListIterator)
	{
		npOut << (*npScoreListIterator)->filePath << ", " << (*npScoreListIterator)->score << "\n";
		npCount ++;
	}

	npFile.close();

	QFile tfFile(dirCurrent->path() + "/Histopatho-GTM_TF.txt");
	if (!tfFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	QTextStream tfOut(&tfFile);

	for (QList<TubuleFormationScore*>::iterator tfScoreListIterator = m_tubuleFormationScoreList.begin(); tfScoreListIterator != m_tubuleFormationScoreList.end(); ++tfScoreListIterator)
	{
		tfOut << (*tfScoreListIterator)->filePath << ", " << (*tfScoreListIterator)->score << "\n";
		tfCount ++;
	}

	tfFile.close();

	QFile mcFile(dirCurrent->path() + "/Histopatho-GTM_MC.txt");
	if (!mcFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	QTextStream mcOut(&mcFile);

	for (QList<MitoticCountScore*>::iterator mcScoreListIterator = m_mitoticCountScoreList.begin(); mcScoreListIterator != m_mitoticCountScoreList.end(); ++mcScoreListIterator)
	{
		mcOut << (*mcScoreListIterator)->filePath << ", " << (*mcScoreListIterator)->score << "\n";
		mcCount ++;
	}

	mcFile.close();

	msgBox.setText(QString("%1 Nuclear Pleomorphism Score(s)\n%2 Tubule Formation Score(s)\n%3 Mitotic Count Score(s)").arg(npCount).arg(tfCount).arg(mcCount));
	msgBox.setStandardButtons(QMessageBox::Ok);

	msgBox.exec();

	actionLoad->setEnabled(true);

}

void ImageViewer::UpdateScoreLists()
{
	QString line;
	QStringList lineList;
	int npCount = 0;
	int tfCount = 0;
	int mcCount = 0;

	QMessageBox msgBox;

	msgBox.setText("Score Data will be loaded from the file. Data in the memory will be overwrited.");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);

	if(msgBox.exec() != QMessageBox::Yes) return;

	QFile npFile(dirCurrent->path() + "/Histopatho-GTM_NP.txt");

	if(npFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_nuclearPleomorphismScoreList.clear();

		QTextStream npIn(&npFile);

		for(;;)
		{
			line = npIn.readLine();
			if(line.isNull()) break;
			lineList = line.split(",");
			QString filePath = lineList.at(0);
			int scr = lineList.at(1).toInt();

			NuclearPleomorphismScore *score = new NuclearPleomorphismScore;
			score->filePath = filePath;
			score->score = scr;
			m_nuclearPleomorphismScoreList.append(score);

			npCount ++;
		}

		npFile.close();
	}

	QFile tfFile(dirCurrent->path() + "/Histopatho-GTM_TF.txt");

	if(tfFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_tubuleFormationScoreList.clear();

		QTextStream tfIn(&tfFile);

		for(;;)
		{
			line = tfIn.readLine();
			if(line.isNull()) break;
			lineList = line.split(",");
			QString filePath = lineList.at(0);
			int scr = lineList.at(1).toInt();

			TubuleFormationScore *score = new TubuleFormationScore;
			score->filePath = filePath;
			score->score = scr;
			m_tubuleFormationScoreList.append(score);

			tfCount ++;
		}

		tfFile.close();
	}

	QFile mcFile(dirCurrent->path() + "/Histopatho-GTM_MC.txt");

	if(mcFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_mitoticCountScoreList.clear();

		QTextStream mcIn(&mcFile);

		for(;;)
		{
			line = mcIn.readLine();
			if(line.isNull()) break;
			lineList = line.split(",");
			QString filePath = lineList.at(0);
			int scr = lineList.at(1).toInt();

			MitoticCountScore *score = new MitoticCountScore;
			score->filePath = filePath;
			score->score = scr;
			m_mitoticCountScoreList.append(score);

			mcCount ++;
		}

		mcFile.close();
	}

	msgBox.setText(QString("%1 Nuclear Pleomorphism Score(s)\n%2 Tubule Formation Score(s)\n%3 Mitotic Count Score(s).").arg(npCount).arg(tfCount).arg(mcCount));
	msgBox.setStandardButtons(QMessageBox::Ok);

	msgBox.exec();

	UpdateUI();

}


void ImageViewer::on_actionLoad_triggered()
{
	UpdateScoreLists();
}