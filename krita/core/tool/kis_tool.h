/*
 *  Copyright (c) 1999 Matthias Elter  <me@kde.org>
 *  Copyright (c) 2002, 2003 Patrick Julien <freak@codepimps.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KIS_TOOL_H_
#define KIS_TOOL_H_

#include <qobject.h>

#include <ksharedptr.h>
#include <kaction.h>

#include "kis_canvas_observer.h"

class QCursor;
class QEvent;
class QKeyEvent;
class QPainter;
class QRect;
class QWidget;
class KActionCollection;
class KRadioAction;
class KDialog;
class QColor;
class KisBrush;
class KisGradient;
class KisPattern;
class KisButtonPressEvent;
class KisButtonReleaseEvent;
class KisDoubleClickEvent;
class KisMoveEvent;

enum enumToolType {
	TOOL_FREEHAND = 0, // Freehand drawing tools
	TOOL_SHAPE = 1,   // Geometric shapes like ellipses and lines
	TOOL_TRANFORM = 2, // Tools that transform the layer
	TOOL_FILL = 3, // Tools that fill parts of the canvas
	TOOL_SELECT = 4, // Selection tools
	TOOL_CANVAS = 5   // Tools that affect the canvas: pan, zoom, etc.
};

const Q_UINT8 NUMBER_OF_TOOLTYPES = 6;

class KisTool : public QObject, public KisCanvasObserver, public KShared {
	Q_OBJECT

public:
	KisTool();
	virtual ~KisTool();

public:

	virtual void paint(QPainter& gc) = 0;
	virtual void paint(QPainter& gc, const QRect& rc) = 0;
	virtual void clear() = 0;
	virtual void clear(const QRect& rc) = 0;

	virtual void setup(KActionCollection *collection) = 0;

	virtual void enter(QEvent *e) = 0;
	virtual void leave(QEvent *e) = 0;
	virtual void buttonPress(KisButtonPressEvent *e) = 0;
	virtual void move(KisMoveEvent *e) = 0;
	virtual void buttonRelease(KisButtonReleaseEvent *e) = 0;
	virtual void doubleClick(KisDoubleClickEvent *e) = 0;
	virtual void keyPress(QKeyEvent *e) = 0;
	virtual void keyRelease(QKeyEvent *e) = 0;

	virtual QCursor cursor() = 0;
	virtual void setCursor(const QCursor& cursor) = 0;
	virtual QWidget* createOptionWidget(QWidget* parent) = 0;
	virtual QWidget* optionWidget() = 0;
	KRadioAction *action() const { return m_action; }

	// Methods for integration with karbon-style toolbox
	virtual Q_UINT32 priority() { return 0; }
	virtual enumToolType toolType() { return TOOL_FREEHAND; }
	virtual QString icon() { return m_action->icon(); }

public slots:
	virtual void activate() = 0;
	
private:
	KisTool(const KisTool&);
	KisTool& operator=(const KisTool&);

protected:
	KRadioAction *m_action;
	bool m_ownAction;
};

#endif // KIS_TOOL_H_

