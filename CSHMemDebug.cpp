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
#ifdef CSH_ACTIVATE_DEBUGING

#define CSH_EXCLUDE_NEW_MACRO
#include "CSHMemDebug.h"

CSHDebugMem::objectInfoList CSHDebugMem::activeObjects;

void *operator new(size_t size,const char *fn,int ln)
{
  size += sizeof(CSHDebugMem::objectInfo);

  CSHDebugMem::objectInfo *obj = (CSHDebugMem::objectInfo *)malloc(size);
  CSHDebugMem::insert(obj,fn,ln);

  char *retVal = ((char *)obj)+sizeof(CSHDebugMem::objectInfo);
  return retVal;
}

void operator delete(void *p)
{
  char *ptr = ((char *)p)-sizeof(CSHDebugMem::objectInfo);
  CSHDebugMem::remove((CSHDebugMem::objectInfo *)ptr);
  free(ptr);
}

void *operator new [](size_t size,const char *fn,int ln)
{
  size += sizeof(CSHDebugMem::objectInfo);

  CSHDebugMem::objectInfo *obj = (CSHDebugMem::objectInfo *)malloc(size);
  CSHDebugMem::insert(obj,fn,ln);

  char *retVal = ((char *)obj)+sizeof(CSHDebugMem::objectInfo);
  return retVal;
}

CSHDebugMem masterCSHDebugMemObject;


#endif
