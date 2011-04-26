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
#ifndef CSHMEMDEBUG_H
#define CSHMEMDEBUG_H

#include <stdio.h>
#include "cshTypes_Collection.h"


class debugMemException
{
};

struct debugItem
{
	void *ptr;
	int id;
};

typedef CSHCollection<debugItem *>::collection CSHMemDebug_Collection_debugItem;
typedef CSHCollection<int>::collection CSHMemDebug_Collection_Int;


class debugMem
{
	public:
		static void debug()
		{
			int nonDelItems = getDIList()->getNumberOfItems();
			if(nonDelItems>0)
			{
				printf("\nDEBUG MEM:memory leak\n");
			}
			for(int i=0;i<nonDelItems;i++)
			{
				printf("id %d not deleted\n",getDIList()->getValueAtIndex(i)->id);
				delete getDIList()->getValueAtIndex(i);
			}
		}

		static void stopAtCreationOfID(int id)
		{
			getIDList()->add(id);
		}

		static void cshdebug(int id)
		{
			printf("\ncreating registered object id %d\n",id);
		}

		static int debug_id;

		static CSHMemDebug_Collection_debugItem *getDIList()
		{
			if(newedList==NULL)
				newedList = new CSHMemDebug_Collection_debugItem;
			return newedList;
		}

		static CSHMemDebug_Collection_Int *getIDList()
		{
			if(idList==NULL)
				idList = new CSHMemDebug_Collection_Int;
			return idList;
		}

	private:
		static CSHMemDebug_Collection_debugItem *newedList;
		static CSHMemDebug_Collection_Int *idList;
};


#define DEBUG_THIS_CLASS \
		void *operator new(unsigned int size ) \
		{ \
			void *ptr = ::operator new(size); \
			debugItem *di = new debugItem; \
			di->ptr = ptr; \
			di->id =debugMem::debug_id++; \
 \
			for(int i=0;i<debugMem::getIDList()->getNumberOfItems();i++) \
				if(di->id==(debugMem::getIDList()->getValueAtIndex(i))) \
				{ \
					debugMem::cshdebug(di->id); \
				} \
 \
			debugMem::getDIList()->add(di); \
			return ptr; \
		} \
 \
		void operator delete(void *ptr) \
		{ \
			int foundItem = 0; \
			for(int i=0;i<debugMem::getDIList()->getNumberOfItems();i++) \
				if(debugMem::getDIList()->getValueAtIndex(i)->ptr==ptr) \
				{ \
					delete debugMem::getDIList()->getValueAtIndex(i); \
					debugMem::getDIList()->removeItemAtIndex(i); \
					foundItem = 1; \
					break; \
				} \
 \
			if(!foundItem) \
			{ \
				debugMemException e; \
				throw e; \
			} \
 \
			::operator delete(ptr); \
		} 


#endif

