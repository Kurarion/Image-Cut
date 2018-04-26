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

	openAction = new QAction(QString::fromLocal8Bit("打开生成图片所在文件夹"), this);
	saveAction= new QAction(QString::fromLocal8Bit("分割结果图另存为"), this);
	QObject::connect(openAction, &QAction::triggered, this, &Qt_Vision_2::onOpenAction);
	QObject::connect(saveAction, &QAction::triggered, this, &Qt_Vision_2::onSaveAction);
	QMenu *file = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
	file->addAction(openAction);
	file->addAction(saveAction);

	startPreviewAction = new QAction(QString::fromLocal8Bit("开启实时预览"), this);
	closePreviewAction = new QAction(QString::fromLocal8Bit("关闭实时预览"), this);
	QObject::connect(startPreviewAction, &QAction::triggered, this, &Qt_Vision_2::onSetRealPre);
	QObject::connect(closePreviewAction, &QAction::triggered, this, &Qt_Vision_2::onCancelRealPre);
	QMenu *pre = menuBar()->addMenu(QString::fromLocal8Bit("实时预览(默认关闭)"));
	pre->addAction(startPreviewAction);
	pre->addAction(closePreviewAction);
	startPreviewAction->setCheckable(true);
	closePreviewAction->setCheckable(true);
	closePreviewAction->setChecked(true);

	sirokuma = new QAction(QString::fromLocal8Bit("By Sirokuma"), this);
	wordpress = new QAction(QString::fromLocal8Bit("访问我的博客"), this);
	QObject::connect(sirokuma, &QAction::triggered, this, &Qt_Vision_2::onWeb);
	QObject::connect(wordpress, &QAction::triggered, this, &Qt_Vision_2::onWeb);
	QMenu *me = menuBar()->addMenu(QString::fromLocal8Bit("关于"));
	me->addAction(sirokuma);
	me->addAction(wordpress);

	//cv::namedWindow("OriginalImage", CV_WINDOW_NORMAL);
	//QWidget* hWndl = (QWidget*)cvGetWindowHandle("OriginalImage");

	//hWndl->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	//hWndl->show();
	//hWndl->setParent(this);
	//
	//HWND hWndl = (HWND)cvGetWindowHandle("OriginalImage");
	//HWND hParent1 = ::GetParent(hWndl);//GetParent函数一个指定子窗口的父窗口句柄
	//::SetParent(hWndl, GetDlgItem(CO_PIC1)->m_hWnd);
	//::ShowWindow(hParent1, SW_HIDE);//ShowWindow指定窗口中显示
}

void Qt_Vision_2::onHelpButton()
{
	String x1 = "  2-左键单击图片一次开启剪刀，再次左键点击则关闭这条连线，并等待下一次左键\n";
	String x2 = "  3-右键可以删除上一个分割点\n";
	String x3 = "  1-原图打开(新窗口打开-图像大小可控)\n";
	String x4 = "  4-原图打开后最好不要右上角关闭，建议使用鼠标中建关闭，如有问题请点击关闭窗口按钮\n";
	String x5 = "  5-预览分割只是预览，只有点击分割才会生成最终分割图片\n";
	String x6 = "  6-如果对中间产生的图片感兴趣，可以点击菜单中的文件打开图片文件夹浏览和使用";
	String x = x3 + x1 + x2 + x4 + x5 + x6;
	QMessageBox::information(this, QString::fromLocal8Bit("操作说明"), QString::fromLocal8Bit(x.data()));
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
		ui.statusBar->showMessage(QString::fromLocal8Bit("预览成功"), 3000);
	}
	else {
		ui.statusBar->showMessage(QString::fromLocal8Bit("预览失败"), 3000);
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
		//这里注意一个路径问题：中文名，空格等等
		//还有一个注意点：QString 转化为 String  ： 空格和中文的路径使用QByteArray间接转化
		QByteArray cdata = fileName.toLocal8Bit();
		cv::Mat ximg = cv::imread(string(cdata));
		//QMessageBox::information(this, tr("hello"), fileName);
		ui.statusBar->setStatusTip(QString::fromLocal8Bit("当前图片路径：")+fileName);
		try {
			//cv::imshow("OriginalImage", ximg);
			//waitKey(0);
		}
		catch (cv::Exception& e)
		{

		}
	
		livewrite::clear();
		livewrite::init(notifyManager, ximg, WITHOUT_RESIZE);

		//注册鼠标回调函数进入loop
		livewrite::reg_mouse();

	}
	//cv::namedWindow("Original Image");
	//cv::imshow("Original Image", img);
}

void Qt_Vision_2::onCutButton()
{
	if (livewrite::output())
	{
		//MessageBox(_T("分割成功,同目录下有相关的中间和结果图片"));
		//ui.statusBar->setStatusTip("分割成功,同目录下有相关的中间和结果图片");
		ui.statusBar->showMessage(QString::fromLocal8Bit("分割成功,同目录下有相关的中间和结果图片.左上角的菜单栏中File可以直接打开相关文件."), 3000);
	}
	else
	{
		//MessageBox(_T("请保证至少三个点"));
		ui.statusBar->showMessage(QString::fromLocal8Bit("分割失败"), 3000);
		QMessageBox::information(this, QString::fromLocal8Bit("失败"), QString::fromLocal8Bit("请保证至少三个点"));
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
		ui.statusBar->showMessage(QString::fromLocal8Bit("手动连线开启成功"), 1500);
	}
	else {
		ui.statusBar->showMessage(QString::fromLocal8Bit("魔术棒开启成功"), 1500);
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
		QMessageBox::information(this, QString::fromLocal8Bit("失败"), QString::fromLocal8Bit("暂时没有分割结果图"));
		ui.statusBar->showMessage(QString::fromLocal8Bit("输出分割图失败"), 1500);
	}
}

void Qt_Vision_2::onHandChanged()
{
	if (livewrite::with_hand) {
		ui.radio_hand->setChecked(true);
		ui.statusBar->showMessage(QString::fromLocal8Bit("手动连线模式中..."), 800);
	}
	else {
		ui.radio_auto->setChecked(true);
		ui.statusBar->showMessage(QString::fromLocal8Bit("魔术棒模式中..."), 800);
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
		ui.statusBar->showMessage(QString::fromLocal8Bit("更新预览成功"), 500);
	}
	else {
		ui.statusBar->showMessage(QString::fromLocal8Bit("当前点数不足以预览"), 1000);
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


