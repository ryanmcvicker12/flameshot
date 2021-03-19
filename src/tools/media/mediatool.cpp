//Made by Ryan McVicker - 3.19.21
#include "mediatool.h"
#include "src/core/qguiappcurrentscreen.h"
#include "src/tools/media/mediawidget.h"
#include <QScreen>
//TODO: give button icon

MediaTool::MediaTool(QObject* parent) 
	: AbstractActionTool(parent)
{}

bool MediaTool::closeOnButtonPressed() const
{
	return true;
}

QIcon MediaTool::icon(const QColor& backround, bool inEditor) const
{
	Q_UNUSED(inEditor);
	return QIcon(iconPath(backround) + "media.svg");// TODO: add media.svg
}

QString MediaTool::name() const
{
	return tr("Media Tool");
}

ToolType MediaTool::nameID() const
{
	return ToolType::MEDIA; //TODO: add MEDIA?
}

QString MediaTool::description() const
{
	return tr("Upload image to various social media platforms");
}	

QWidget* MediaTool::widget()
{
	qreal devicePixelRatio = 1;
#if defined(Q_OS_MACOS)
	QScreen* currentScreen = QGuiAppCurrentScreen().currentScreen();
	if(currentScreen) {
		devicePixelRatio = currentScreen->devicePixelRatio();
	}
#endif
	MediaWidget* w = new MediaWidget(m_pixmap);
	const int m = w->margin() * devicePixelRatio;
	QRect adjusted_pos = m_geometry + QMargins(m, m, m, m);
	w->setGeometry(adjusted_pos);
#if defined(Q_OS_MACOS)
	if(currentScreen) {
		QPoint topLeft = currentScreen->geometry().topLeft();
		adjusted_pos.setX((adjusted_pos.x() - topLeft.x())/ devicePixelRatio + topLeft.x());

		adjusted_pos.setY((adjusted_pos.y() - topLeft.y())/ devicePixelRatio + topLeft.y());
		
		adjusted_pos.setWidth(adjusted_pos.size().width() / devicePixelRatio);


		adjusted_pos.setHeight(adjusted_pos.size().height() / devicePixelRatio);

		w->resize(0, 0);
		w->move(adjusted_pos.x(), adjusted_pos.y());
	}
#endif
	return w;
}

CaptureTool* MediaTool::copy(QObject* parent)
{
	return new MediaTool(parent);
}

void MediaTool::pressed(const CaptureContext& context)
{
	emit requestAction(REQ_CAPTURE_DONE_OK);
	m_geometry = context.selection;
	m_geometry.setTopLeft(m_geometry.topLeft() + context.widgetOffset);
	m_pixmap = context.selectedScreenshotArea();
	emit requestAction(REQ_ADD_EXTERNAL_WIDGETS);
}
