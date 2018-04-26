#pragma once
#include <qobject.h>

class NotifyManager :public QObject
{
	Q_OBJECT

public:
	void notifyHandChanged()
	{
		emit handChanged();
	}
	void notifyPreviewChanged()
	{
		emit previewChanged();
	}
signals:

	void handChanged();
	void previewChanged();

};