#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qfiledialog.h>
#include <QMessageBox>
#include <QDesktopServices>
#include "ui_Qt_Vision_2.h"

#include "NotifyManager.h"
#include "livewrite.h"
#include "highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

class Qt_Vision_2 : public QMainWindow
{
	Q_OBJECT

public:
	Qt_Vision_2(QWidget *parent = Q_NULLPTR);
	void onHelpButton();
	void onPreview();
	void onOpenButton();
	void onCutButton();
	void onExit();
	void onCloseWindow();
	void onRadioButton();
	void onOpenAction();
	void onSaveAction();
	void onHandChanged();
	void onPreviewChanged();
	void onSetRealPre();
	void onCancelRealPre();
	void onWeb();
private:
	Ui::Qt_Vision_2Class ui;
	cv::Mat img;
	QGraphicsScene scene;
	cv::Mat preview;
	QButtonGroup*  group;
	QAction* openAction;
	QAction* saveAction;
	QAction* startPreviewAction;
	QAction* closePreviewAction;
	QAction* sirokuma;
	QAction* wordpress;
	NotifyManager* notifyManager;


};
