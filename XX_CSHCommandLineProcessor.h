/*
* Copyright (c) 1999-2006,2007, Craig S. Harrison
*
* All rights reserved.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
#ifndef MBCSCOMMANDLINEPROCESSOR_H
#define MBCSCOMMANDLINEPROCESSOR_H

#include "cshTypes_String.h"
#include "cshTypes_Collection.h"

class CSHCommandLineProcessorType
{
	public:

		class keyDoesNotExistException
		{
			public:
				keyDoesNotExistException()
				{
				}

				virtual ~keyDoesNotExistException()
				{
				}
		};

		class indexOutOfBounds
		{
			public:
				indexOutOfBounds()
				{
				}

				virtual ~indexOutOfBounds()
				{
				}
		};

		struct paramPair
		{
			paramPair(const char *k,const char *v):key(k),value(v)
			{
			}

			virtual ~paramPair()
			{
			}

			CSHString key;
			CSHString value;
		};

		CSHCommandLineProcessorType();
		virtual ~CSHCommandLineProcessorType();
		virtual void init(const int c,const char *v[]);
		virtual void init(const char *str);
		virtual void init(CSHCollection<CSHString *>::collection &pList);

		virtual CSHString getParamAtIndex(int index);

		virtual CSHString getParamValue(const char *);
		virtual int keyExists(const char *);

	private:
		virtual int getParamIndex(const char *);
		CSHCollection<paramPair *>::collection paramPairList;
		CSHCollection<CSHString *>::collection paramList;
};

#endif
