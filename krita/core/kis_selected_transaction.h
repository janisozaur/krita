/*
 *  Copyright (c) 2005 Casper Boemann <cbr@boemann.dk>
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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef KIS_SELECTED_TRANSACTION_H_
#define KIS_SELECTED_TRANSACTION_H_

#include <map>
#include <qglobal.h>
#include <qstring.h>
#include <kcommand.h>
#include "kis_transaction.h"

class KisSelectedTransaction : public KisTransaction {
	typedef KisTransaction super;
public:
	KisSelectedTransaction(const QString& name, KisPaintDeviceSP device);
	virtual ~KisSelectedTransaction();

public:
	virtual void execute();
	virtual void unexecute();

public:

private:
	KisPaintDeviceSP m_device;
	KisTransaction *m_selTransaction;
	bool m_hadSelection;
};

#endif // KIS_SELECTED_TRANSACTION_H_
