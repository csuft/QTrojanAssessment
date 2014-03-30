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

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <assert.h>
#include <cmath>
//#include <iostream> // dla testów 

using namespace std;

/** 
* Znajduje najwiêksz± warto¶æ mniejsz± od scaleSize/steps i
* jednocze¶nie bêd±c± ca³kowicie podzieln± przez warto¶æ 
* 10^N  gdzie n jest dowoln± liczb± ca³kowit±.
* dla 5,2,1 jest to  odpowiedniio {...,500,50,5,0.5,...},
* {...200,20,2,0.2,0.02,...} etc. 
*/ 


double minimalStep(double scaleSize, int steps);


/**
* Szablonowa funkcja do wyznaczania skali w zadanym przedziale o wyznaczonej ilo¶ci punktów skali.
* Na podstawie warto¶ci minimalnej oraz maksymalnej, jak± chcemy osi±gnaæ ustawia
* warto¶ci m_min oraz m_max w taki sposób ca³y przedzia³ skali (m_max-m_min) by³ podzielny
* przez ilo¶æ punktów skali a odleg³o¶æ pomiêdzy punktami skali by³a wartosci± która jest
* wieloktorno¶ci± liczby 5. Dodatkowo isnieje mo¿liwo¶æ przesuniêcia skali w lewo lub prawo by
* rozpoczyna³a siê jak najbli¿ej warto¶ci minimalnej lub koñczy³a jak najbli¿ej warto¶ci
* maksymalnej.
*
* @param m_minimum - warto¶æ minilana na skali jaka ma byæ widoczna
* @param m_maximum - warto¶æ maksymalna na skali jaka ma byæ widoczna
* @param m_min     - wyliczona warto¶æ pocz±tkowa skali
* @param m_max     - wyliczona warto¶æ koñcowa skali
* @param stesp     - ilo¶æ wêz³ów jak± ma mieæ skala
* @param left      - czy skala ma byæ wyrównana do lewej czy do prawej (domy¶lnie do prawej).
* @return Funkcja zwraca warto¶æ true je¿eli warto¶ci m_min oraz m_max w wyniku zmiany zakresu
* zmieni³y swoj± warto¶æ.  Na podstawie tej warto¶ci wiadomo czy nale¿y np. przerysowaæ skalê
* - podaj±c wcze¶niej poprzednie warto¶ci zakresu skali.
*/

template <typename T>
bool range(T m_minimum,T m_maximum, T & m_min, T & m_max,unsigned int steps, bool left = false,double inc = 5.0)
{

	T max_tmp = m_max, min_tmp = m_min;
	m_max=m_maximum;
	m_min=m_minimum;
	assert( m_max > m_min );

	T diff = abs(m_max - m_min);
	T scale = 0, factor = 0 ;

	while (inc * steps > (m_maximum-m_minimum))
		if (inc/10 > 0 ) inc/=10;
		else break;

		bool done = false;
		while ( diff > scale ) 
		{ factor+=static_cast<T>(inc);  scale = factor * steps;  }

		while (!done)
		{

			// dirty hack to have zero equal exactly zero 
			if (m_max<0)  m_max=m_min - fmodf(m_min,steps);
			else m_max = 0.0; 

			while ( m_max < m_maximum ) m_max +=factor;
			m_min = m_max - scale;
			if (m_min <= m_minimum ) done = true;
			else { factor+=static_cast<T>(inc); scale = factor * steps; }
		}

		if (left)
			while (m_min + factor <= m_minimum)
			{
				m_min+=factor;
				m_max+=factor;
			}

			return (m_max != max_tmp) | (m_min != min_tmp);
}


#endif // _FUNCTIONS_H_
