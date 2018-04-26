/********************************************************************************
** Form generated from reading UI file 'Qt_Vision_2.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_VISION_2_H
#define UI_QT_VISION_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_Vision_2Class
{
public:
    QAction *actionopen_file;
    QAction *action;
    QWidget *centralWidget;
    QPushButton *pushButton_open;
    QPushButton *pushButton_cut;
    QPushButton *pushButton_exit;
    QGraphicsView *graphicsView;
    QPushButton *pushButton_help;
    QPushButton *pushButton_preview;
    QPushButton *pushButton_close;
    QRadioButton *radio_auto;
    QRadioButton *radio_hand;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_Vision_2Class)
    {
        if (Qt_Vision_2Class->objectName().isEmpty())
            Qt_Vision_2Class->setObjectName(QStringLiteral("Qt_Vision_2Class"));
        Qt_Vision_2Class->resize(898, 590);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Qt_Vision_2Class->sizePolicy().hasHeightForWidth());
        Qt_Vision_2Class->setSizePolicy(sizePolicy);
        Qt_Vision_2Class->setMouseTracking(false);
        Qt_Vision_2Class->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qt_Vision_2/Z:/\347\264\240\346\235\220/\345\244\264\345\203\217.png"), QSize(), QIcon::Normal, QIcon::Off);
        Qt_Vision_2Class->setWindowIcon(icon);
        actionopen_file = new QAction(Qt_Vision_2Class);
        actionopen_file->setObjectName(QStringLiteral("actionopen_file"));
        action = new QAction(Qt_Vision_2Class);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(Qt_Vision_2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_open = new QPushButton(centralWidget);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(300, 510, 91, 31));
        pushButton_cut = new QPushButton(centralWidget);
        pushButton_cut->setObjectName(QStringLiteral("pushButton_cut"));
        pushButton_cut->setGeometry(QRect(500, 510, 91, 31));
        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(800, 510, 91, 31));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(0, 0, 901, 501));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(901, 501));
        graphicsView->setMaximumSize(QSize(901, 501));
        pushButton_help = new QPushButton(centralWidget);
        pushButton_help->setObjectName(QStringLiteral("pushButton_help"));
        pushButton_help->setGeometry(QRect(700, 510, 91, 31));
        pushButton_preview = new QPushButton(centralWidget);
        pushButton_preview->setObjectName(QStringLiteral("pushButton_preview"));
        pushButton_preview->setGeometry(QRect(400, 510, 91, 31));
        pushButton_close = new QPushButton(centralWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(600, 510, 91, 31));
        radio_auto = new QRadioButton(centralWidget);
        radio_auto->setObjectName(QStringLiteral("radio_auto"));
        radio_auto->setGeometry(QRect(20, 520, 131, 16));
        radio_hand = new QRadioButton(centralWidget);
        radio_hand->setObjectName(QStringLiteral("radio_hand"));
        radio_hand->setGeometry(QRect(160, 520, 131, 16));
        Qt_Vision_2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qt_Vision_2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 898, 23));
        Qt_Vision_2Class->setMenuBar(menuBar);
        statusBar = new QStatusBar(Qt_Vision_2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_Vision_2Class->setStatusBar(statusBar);

        retranslateUi(Qt_Vision_2Class);
        QObject::connect(pushButton_help, SIGNAL(clicked()), Qt_Vision_2Class, SLOT(onHelpButton()));
        QObject::connect(pushButton_open, SIGNAL(clicked()), Qt_Vision_2Class, SLOT(onOpenButton()));
        QObject::connect(pushButton_cut, SIGNAL(clicked()), Qt_Vision_2Class, SLOT(onOpenZoomButton()));
        QObject::connect(pushButton_exit, SIGNAL(clicked()), Qt_Vision_2Class, SLOT(onExit()));
        QObject::connect(pushButton_preview, SIGNAL(clicked()), Qt_Vision_2Class, SLOT(onPreview()));
        QObject::connect(pushButton_close, SIGNAL(clicked()), Qt_Vision_2Class, SLOT(onCloseWindow()));

        QMetaObject::connectSlotsByName(Qt_Vision_2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_Vision_2Class)
    {
        Qt_Vision_2Class->setWindowTitle(QApplication::translate("Qt_Vision_2Class", "\345\233\276\347\211\207\345\211\252\345\210\200", Q_NULLPTR));
        actionopen_file->setText(QApplication::translate("Qt_Vision_2Class", "\346\211\223\345\274\200\345\233\276\347\211\207\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionopen_file->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        action->setText(QApplication::translate("Qt_Vision_2Class", "\345\210\206\345\211\262\347\273\223\346\236\234\345\217\246\345\255\230\344\270\272", Q_NULLPTR));
        pushButton_open->setText(QApplication::translate("Qt_Vision_2Class", "\345\216\237\345\233\276\346\211\223\345\274\200", Q_NULLPTR));
        pushButton_cut->setText(QApplication::translate("Qt_Vision_2Class", "\345\210\206\345\211\262", Q_NULLPTR));
        pushButton_exit->setText(QApplication::translate("Qt_Vision_2Class", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_help->setText(QApplication::translate("Qt_Vision_2Class", "\345\270\256\345\212\251", Q_NULLPTR));
        pushButton_preview->setText(QApplication::translate("Qt_Vision_2Class", "\351\242\204\350\247\210\345\210\206\345\211\262", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("Qt_Vision_2Class", "\345\205\263\351\227\255\345\233\276\347\211\207\347\252\227\345\217\243", Q_NULLPTR));
        radio_auto->setText(QApplication::translate("Qt_Vision_2Class", "\351\255\224\346\234\257\346\243\222\357\274\210\345\277\253\346\215\267\351\224\256Z\357\274\211", Q_NULLPTR));
        radio_hand->setText(QApplication::translate("Qt_Vision_2Class", "\346\211\213\345\212\250\350\277\236\347\272\277\357\274\210\345\277\253\346\215\267\351\224\256X\357\274\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Qt_Vision_2Class: public Ui_Qt_Vision_2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_VISION_2_H
