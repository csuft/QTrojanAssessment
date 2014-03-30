/***************************************************************************
*   Copyright (C) 2006-2008 by Tomasz Ziobrowski                          *
*   http://www.3electrons.com                                             *
*   e-mail: t.ziobrowski@3electrons.com                                   *
*                                                                         *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include <assert.h>
#include "abstractmeter.h"
#include "functions.h" 

AbstractMeter::AbstractMeter(QWidget * parent )
	: WidgetWithBackground (parent)
{
	m_min=m_minimum=0.0;
	m_max=m_maximum=1.0;
	m_digitOffset=1.0;
	m_nominal=0.25;
	m_critical=0.75; 
} 


bool AbstractMeter::calcMaxMin()
{
	return range(m_minimum,m_maximum,m_min,m_max,8,true); 
}

void AbstractMeter::setValue( double val )
{
	if ( m_value != val )
	{
		m_value = val;
		update(); 
		emit valueChanged(val);
		emit valueChanged((int)val); 
	}
}

void AbstractMeter::setValue( int val )
{
	if ( m_value != val )
	{
		m_value = val;
		update(); 
		
		emit valueChanged(val);
		emit valueChanged(double(val));
	}
}

void AbstractMeter::setMinimum(double i)
{
	if ((m_maximum - i) > 0.00001 )
	{
		m_minimum = i;
		if (calcMaxMin()) updateWithBackground();
	}
}

void AbstractMeter::setMaximum(double i)
{
	if ( (i - m_minimum) > 0.00001 )
	{
		m_maximum = i;
		if (calcMaxMin()) updateWithBackground();
	}
}


