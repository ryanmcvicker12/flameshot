
#pragma once

#include "src/tools/abstractiontool.h"

class MediaTool : public AbstractActionTool
{
	Q_OBJECT
public:
	explicit MediaTool(QObject* parent = nullptr);

	bool closeOnButtonPressed() const override;

	QIcon icon(const QColor& backround, bool inEditor) const override;
	QString name() const override;
	QString description() const override;

	QWidget* widget() override;

	CaptureTool* copy(QObject* parent = nullptr) override;

protected:
	ToolType nameID() const override;

public slots:
	void pressed(const CaptureContext& context) override;

private:
	QRect m_geometry;
	QPixmap m_pixmap;
}
