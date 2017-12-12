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

#include "functions.h"

#include <iostream>
using namespace std; 

double minimalStep(double scaleSize, int steps)
{
	scaleSize = std::abs(scaleSize); 
	double ms = scaleSize/steps; 
	double fractions[]={5,2,1}; 
	double multiply = 10; 
	double fraction = 1.0; 
	double test; 
	if (static_cast<int>(ms)<=5) multiply = 0.1 ; 

	while (true)
	{
		for (int i=0;i<3;i++)
		{
			if (fractions[i]<ms)
			{ 
				fraction =fractions[i]; 
			}

			fractions[i]*=multiply; 
			test = steps * fractions[i]; 
			if ( (test < scaleSize) && multiply< 1.0 ) return fraction; 
			if ( (test > scaleSize) && multiply> 1.0 ) return fraction; 
		}  
	}

	return fraction; 
}
