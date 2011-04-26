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

#ifdef CSH_ACTIVATE_DEBUGING

#include <stdio.h>
#include <string.h>
#include "cshTypes_Collection.h"


class CSHDebugMem
{
 public:
  class debugMemException
  {
  };
  
  struct objectInfo
  {
    char *filename;
    int linenumber;
  };

  CSHDebugMem()
    {
    }

  virtual ~CSHDebugMem()
    {
      printf("\n--------------------------------------------\n");
      printf("---object memory leaks at file:linenumber---\n");
      printf("--------------------------------------------\n");
      dumpActiveObjects();
    }

  static void insert(objectInfo *obj,const char *filename,int linenumber)
  {
      int fnLen = strlen(filename);
      obj->filename = (char *)malloc(fnLen+1);
    strcpy(obj->filename,filename);
    obj->linenumber = linenumber;
    activeObjects.add(obj);
  }

  static void remove(objectInfo *obj)
  {
    int foundObj = 0;

    int size = activeObjects.getNumberOfItems();
    for(int i=0;i<size;i++)
      {
	objectInfo *currObj = activeObjects.getValueAtIndex(i);
	if(currObj==obj)
	  {
	    free(currObj->filename);
	    activeObjects.removeItemAtIndex(i);

	    foundObj = 1;
	    break;
	  }
      }

    if(!foundObj)
      throw debugMemException();
  }

  static void dumpActiveObjects()
  {
    int size = activeObjects.getNumberOfItems();
    for(int i=0;i<size;i++)
      {
	objectInfo *currObj = activeObjects.getValueAtIndex(i);
	printf("%s:%d\n",currObj->filename,currObj->linenumber);
      }
  }

  typedef CSHCollection<objectInfo *>::collection objectInfoList;
  static objectInfoList activeObjects;
  
};
void *operator new(size_t size,const char *fn,int ln);
void *operator new [](size_t size,const char *fn,int ln);

#ifndef CSH_EXCLUDE_NEW_MACRO
#define new new((const char *)__FILE__,__LINE__)
#endif

#endif

#endif
