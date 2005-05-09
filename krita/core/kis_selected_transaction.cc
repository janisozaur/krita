/*
 *  Copyright (c) 2002 Patrick Julien <freak@codepimps.org>
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
#include "kis_types.h"
#include "kis_global.h"
#include "kis_selected_transaction.h"
#include "kis_selection.h"

KisSelectedTransaction::KisSelectedTransaction(const QString& name, KisPaintDeviceSP device) :
	KisTransaction(name, device),
	m_device(device),
	m_hadSelection(device->hasSelection())
{
	m_selTransaction = new KisTransaction(name, device->selection().data());
}

KisSelectedTransaction::~KisSelectedTransaction()
{
	delete m_selTransaction;
}

void KisSelectedTransaction::execute()
{
	super::execute();
	m_selTransaction->execute();
}

void KisSelectedTransaction::unexecute()
{
	super::unexecute();
	m_selTransaction->unexecute();
	if(!m_hadSelection)
	{
		m_device->deselect();
	}
	m_device->emitSelectionChanged();
}
