#include "Qt_Vision_2.h"

Qt_Vision_2::Qt_Vision_2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(this->width(), this->height());
	//this->setWindowFlags(Qt::FramelessWindowHint);
	notifyManager =new NotifyManager();
	//connect
	QObject::connect(notifyManager, &NotifyManager::handChanged, this, &Qt_Vision_2::onHandChanged);
	QObject::connect(notifyManager, &NotifyManager::previewChanged, this, &Qt_Vision_2::onPreviewChanged);

	//connect
	QObject::connect(ui.pushButton_open,&QPushButton::clicked, this, &Qt_Vision_2::onOpenButton);
	QObject::connect(ui.pushButton_cut, &QPushButton::clicked, this, &Qt_Vision_2::onCutButton);
	QObject::connect(ui.pushButton_help, &QPushButton::clicked, this, &Qt_Vision_2::onHelpButton);
	QObject::connect(ui.pushButton_preview, &QPushButton::clicked, this, &Qt_Vision_2::onPreview);
	QObject::connect(ui.pushButton_exit, &QPushButton::clicked, this, &Qt_Vision_2::onExit);
	QObject::connect(ui.pushButton_close, &QPushButton::clicked, this, &Qt_Vision_2::onCloseWindow);

	

	group = new QButtonGroup(this);
	group->addButton(ui.radio_hand,1);
	group->addButton(ui.radio_auto,0);
	ui.radio_auto->setChecked(true);
	QObject::connect(ui.radio_auto, &QRadioButton::clicked, this, &Qt_Vision_2::onRadioButton);
	QObject::connect(ui.radio_hand, &QRadioButton::clicked, this, &Qt_Vision_2::onRadioButton);

	openAction = new QAction(QString::fromLocal8Bit("������ͼƬ�����ļ���"), this);
	saveAction= new QAction(QString::fromLocal8Bit("�ָ���ͼ���Ϊ"), this);
	QObject::connect(openAction, &QAction::triggered, this, &Qt_Vision_2::onOpenAction);
	QObject::connect(saveAction, &QAction::triggered, this, &Qt_Vision_2::onSaveAction);
	QMenu *file = menuBar()->addMenu(QString::fromLocal8Bit("�ļ�"));
	file->addAction(openAction);
	file->addAction(saveAction);

	startPreviewAction = new QAction(QString::fromLocal8Bit("����ʵʱԤ��"), this);
	closePreviewAction = new QAction(QString::fromLocal8Bit("�ر�ʵʱԤ��"), this);
	QObject::connect(startPreviewAction, &QAction::triggered, this, &Qt_Vision_2::onSetRealPre);
	QObject::connect(closePreviewAction, &QAction::triggered, this, &Qt_Vision_2::onCancelRealPre);
	QMenu *pre = menuBar()->addMenu(QString::fromLocal8Bit("ʵʱԤ��(Ĭ�Ϲر�)"));
	pre->addAction(startPreviewAction);
	pre->addAction(closePreviewAction);
	startPreviewAction->setCheckable(true);
	closePreviewAction->setCheckable(true);
	closePreviewAction->setChecked(true);

	sirokuma = new QAction(QString::fromLocal8Bit("By Sirokuma"), this);
	wordpress = new QAction(QString::fromLocal8Bit("�����ҵĲ���"), this);
	QObject::connect(sirokuma, &QAction::triggered, this, &Qt_Vision_2::onWeb);
	QObject::connect(wordpress, &QAction::triggered, this, &Qt_Vision_2::onWeb);
	QMenu *me = menuBar()->addMenu(QString::fromLocal8Bit("����"));
	me->addAction(sirokuma);
	me->addAction(wordpress);

	//cv::namedWindow("OriginalImage", CV_WINDOW_NORMAL);
	//QWidget* hWndl = (QWidget*)cvGetWindowHandle("OriginalImage");

	//hWndl->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	//hWndl->show();
	//hWndl->setParent(this);
	//
	//HWND hWndl = (HWND)cvGetWindowHandle("OriginalImage");
	//HWND hParent1 = ::GetParent(hWndl);//GetParent����һ��ָ���Ӵ��ڵĸ����ھ��
	//::SetParent(hWndl, GetDlgItem(CO_PIC1)->m_hWnd);
	//::ShowWindow(hParent1, SW_HIDE);//ShowWindowָ����������ʾ
}

void Qt_Vision_2::onHelpButton()
{
	String x1 = "  2-�������ͼƬһ�ο����������ٴ���������ر��������ߣ����ȴ���һ�����\n";
	String x2 = "  3-�Ҽ�����ɾ����һ���ָ��\n";
	String x3 = "  1-ԭͼ��(�´��ڴ�-ͼ���С�ɿ�)\n";
	String x4 = "  4-ԭͼ�򿪺���ò�Ҫ���Ͻǹرգ�����ʹ������н��رգ��������������رմ��ڰ�ť\n";
	String x5 = "  5-Ԥ���ָ�ֻ��Ԥ����ֻ�е���ָ�Ż��������շָ�ͼƬ\n";
	String x6 = "  6-������м������ͼƬ����Ȥ�����Ե���˵��е��ļ���ͼƬ�ļ��������ʹ��";
	String x = x3 + x1 + x2 + x4 + x5 + x6;
	QMessageBox::information(this, QString::fromLocal8Bit("����˵��"), QString::fromLocal8Bit(x.data()));
}

void Qt_Vision_2::onPreview()
{
	
	QImage image_pre;
	scene.clear();
	scene.destroyed();

	preview = livewrite::preview();

	//cv::imshow("test", preview);
	if (!preview.empty()) {

		
		cv::cvtColor(preview, preview, CV_BGR2BGRA);
		image_pre = QImage((const unsigned char*)(preview.data), preview.cols, preview.rows, QImage::Format_RGB32);
		

		scene.addPixmap(QPixmap::fromImage(image_pre));

		ui.graphicsView->setScene(&scene);
		ui.graphicsView->resize(image_pre.width(), image_pre.height());
		ui.graphicsView->show();
		ui.statusBar->showMessage(QString::fromLocal8Bit("Ԥ���ɹ�"), 3000);
	}
	else {
		ui.statusBar->showMessage(QString::fromLocal8Bit("Ԥ��ʧ��"), 3000);
	}
	
}


void Qt_Vision_2::onOpenButton()
{
	//QMessageBox::information(this, tr("hello"), tr("hello!!"));
	//QDialog dialog(this);
	//dialog.setWindowTitle(tr("Hello, dialog!"));
	//dialog.exec();
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
	
	if (!fileName.isNull()) {
		//fileName.replace("\/", "\\\\");
		//����ע��һ��·�����⣺���������ո�ȵ�
		//����һ��ע��㣺QString ת��Ϊ String  �� �ո�����ĵ�·��ʹ��QByteArray���ת��
		QByteArray cdata = fileName.toLocal8Bit();
		cv::Mat ximg = cv::imread(string(cdata));
		//QMessageBox::information(this, tr("hello"), fileName);
		ui.statusBar->setStatusTip(QString::fromLocal8Bit("��ǰͼƬ·����")+fileName);
		try {
			//cv::imshow("OriginalImage", ximg);
			//waitKey(0);
		}
		catch (cv::Exception& e)
		{

		}
	
		livewrite::clear();
		livewrite::init(notifyManager, ximg, WITHOUT_RESIZE);

		//ע�����ص���������loop
		livewrite::reg_mouse();

	}
	//cv::namedWindow("Original Image");
	//cv::imshow("Original Image", img);
}

void Qt_Vision_2::onCutButton()
{
	if (livewrite::output())
	{
		//MessageBox(_T("�ָ�ɹ�,ͬĿ¼������ص��м�ͽ��ͼƬ"));
		//ui.statusBar->setStatusTip("�ָ�ɹ�,ͬĿ¼������ص��м�ͽ��ͼƬ");
		ui.statusBar->showMessage(QString::fromLocal8Bit("�ָ�ɹ�,ͬĿ¼������ص��м�ͽ��ͼƬ.���ϽǵĲ˵�����File����ֱ�Ӵ�����ļ�."), 3000);
	}
	else
	{
		//MessageBox(_T("�뱣֤����������"));
		ui.statusBar->showMessage(QString::fromLocal8Bit("�ָ�ʧ��"), 3000);
		QMessageBox::information(this, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit("�뱣֤����������"));
	}
}

void Qt_Vision_2::onExit()
{
	livewrite::clear();
	this->close();
}

void Qt_Vision_2::onCloseWindow()
{
	livewrite::close_window();
}

void Qt_Vision_2::onRadioButton()
{
	int x = group->checkedId();
	switch (x) {
	case 0:
		
		livewrite::with_hand = false;
		break;
	case 1:
		
		livewrite::with_hand = true;
		break;
	}
	if (livewrite::with_hand) {
		ui.statusBar->showMessage(QString::fromLocal8Bit("�ֶ����߿����ɹ�"), 1500);
	}
	else {
		ui.statusBar->showMessage(QString::fromLocal8Bit("ħ���������ɹ�"), 1500);
	}
}

void Qt_Vision_2::onOpenAction()
{
	QString path = QDir::currentPath();
	//QMessageBox::information(this,"dd", path);
	QDesktopServices::openUrl("file:///"+path+"/output");
}

void Qt_Vision_2::onSaveAction()
{
	if (!livewrite::img_rgba.empty())
	{
		QString fileNamex = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
		if (!fileNamex.isNull()) {
			QByteArray cdatax = fileNamex.toLocal8Bit();
			imwrite(string(cdatax), livewrite::img_rgba);
		}
	}
	else
	{
		QMessageBox::information(this, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit("��ʱû�зָ���ͼ"));
		ui.statusBar->showMessage(QString::fromLocal8Bit("����ָ�ͼʧ��"), 1500);
	}
}

void Qt_Vision_2::onHandChanged()
{
	if (livewrite::with_hand) {
		ui.radio_hand->setChecked(true);
		ui.statusBar->showMessage(QString::fromLocal8Bit("�ֶ�����ģʽ��..."), 800);
	}
	else {
		ui.radio_auto->setChecked(true);
		ui.statusBar->showMessage(QString::fromLocal8Bit("ħ����ģʽ��..."), 800);
	}
}

void Qt_Vision_2::onPreviewChanged()
{

	QImage image_pre;
	scene.clear();
	scene.destroyed();

	preview = livewrite::preview();

	//cv::imshow("test", preview);
	if (!preview.empty()) {


		cv::cvtColor(preview, preview, CV_BGR2BGRA);
		image_pre = QImage((const unsigned char*)(preview.data), preview.cols, preview.rows, QImage::Format_RGB32);


		scene.addPixmap(QPixmap::fromImage(image_pre));

		ui.graphicsView->setScene(&scene);
		ui.graphicsView->resize(image_pre.width(), image_pre.height());
		ui.graphicsView->show();
		ui.statusBar->showMessage(QString::fromLocal8Bit("����Ԥ���ɹ�"), 500);
	}
	else {
		ui.statusBar->showMessage(QString::fromLocal8Bit("��ǰ����������Ԥ��"), 1000);
	}
}

void Qt_Vision_2::onSetRealPre()
{
	livewrite::real_preview = true;
	startPreviewAction->setChecked(true);
	closePreviewAction->setChecked(false);
}

void Qt_Vision_2::onCancelRealPre()
{
	livewrite::real_preview = false;
	closePreviewAction->setChecked(true);
	startPreviewAction->setChecked(false);
}

void Qt_Vision_2::onWeb()
{
	QDesktopServices::openUrl(QString::fromLocal8Bit("http:///www.sirokuma.cc"));
}


