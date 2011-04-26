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
#ifndef CSHCOLLECTIONTYPE_H
#define CSHCOLLECTIONTYPE_H

#include <stdlib.h>

#include "CSH_ASSERTE.h"

template<class T>
class CSHCollectionType
{
	public :
		CSHCollectionType(int initialMaxNumOfItems=20):numberOfItems(0),maximumNumberOfItems(initialMaxNumOfItems)
		{
			storage	=(T *) malloc(maximumNumberOfItems*sizeof(T *));
		}

		virtual ~CSHCollectionType()
		{
			free(storage);
		}

		void add(T value)
		{
			if(numberOfItems>=maximumNumberOfItems)
			{
				maximumNumberOfItems+=50;
				storage = (T *)realloc(storage,maximumNumberOfItems*sizeof(T *));
			}
			_ASSERTE(numberOfItems<maximumNumberOfItems);
			storage[numberOfItems++] = value;
		}

		void removeItemAtIndex(int index)
		{
			_ASSERTE(numberOfItems>0);

			//Basically we move all the values above
			//the indexed item down 1 in the list.
			for(int i=index+1;i<numberOfItems;i++)
			{
				storage[i-1] = storage[i];
			}
			
			//And decrease the number of items in the list..
			numberOfItems--;
		}

		int getNumberOfItems()
		{
			return numberOfItems;
		}

		int getSize()
		{
			return numberOfItems;
		}
	
		T getValueAtIndex(int index)
		{
			_ASSERTE(index!=-1);
			_ASSERTE(index<numberOfItems);
			return storage[index];
		}

		void replaceValueAtIndex(int index,T value)
		{
			_ASSERTE(index<numberOfItems);
			storage[index] = value;
		}

		//You should only use this for "short" lists
		//its not very efficient.
		int getIndexOf(T val)
		{
			int retVal = -1;
			for(int i=0;i<numberOfItems;i++)
			{
				if(storage[i]==val)
				{
					retVal = i;
					break;
				}
			}
			return retVal;
		}

	private:
		T *storage;
		int maximumNumberOfItems;

	private:
		int numberOfItems;

};

#endif




