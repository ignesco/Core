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
#include "stdafx.h"
#include "XX_CSHCommandLineProcessor.h"
#include "string.h"

CSHCommandLineProcessorType::CSHCommandLineProcessorType()
{
}

CSHCommandLineProcessorType::~CSHCommandLineProcessorType()
{
	for(int i=0;i<paramPairList.getNumberOfItems();i++)
		delete paramPairList.getValueAtIndex(i);

	for(int i=0;i<paramList.getNumberOfItems();i++)
		delete paramList.getValueAtIndex(i);
}

void CSHCommandLineProcessorType::init(const int c,const char *v[])
{
	for(int i=0;i<c;i++)
		paramList.add(new CSHString(v[i]));

	init(paramList);
}

void CSHCommandLineProcessorType::init(const char *str)
{
	CSHString ss(str);
	int sizeOfString = ss.GetLength();
	int finished = 0;
	int currPos = 0;
	while(!finished)
	{
		//Skip whitespace
		currPos = ss.findNextNonWhitespace(currPos);
		if(currPos==-1)
		{
			finished = 1;
		}
		else
		{
			//We have a parameter to extract.
			if(str[currPos]=='\"')
			{
				currPos++;
				//We need to search for the first dquote from here
				//Then we need to trim the param to the last nonwhitespace char.

				int dquotePos = -1;
				for(int i=currPos;i<sizeOfString;i++)
				{
					if(str[i]=='\"')
					{
						dquotePos = i;
						break;
					}
				}

				//If we have not found a dquote, then assume the end of the param string.
				if(dquotePos==-1)
					dquotePos = sizeOfString;

				if(currPos!=dquotePos)
				{
					CSHString ex = ss.extract(currPos,dquotePos);
					paramList.add(new CSHString(ex));
				}

				currPos = dquotePos+1;
			}
			else
			{
				//We need to search for the first whitespace from here!
				int nextWSPos = ss.findNextWhitespace(currPos);
				if(nextWSPos==-1)
					nextWSPos = sizeOfString;

				CSHString ex = ss.extract(currPos,nextWSPos);
				paramList.add(new CSHString(ex));
				currPos = nextWSPos;
			}
		}
	}

	init(paramList);
}

void CSHCommandLineProcessorType::init(CSHCollection<CSHString *>::collection &pList)
{
	int i=1;
	int c = pList.getNumberOfItems();
	while(i<c)
	{
		CSHString *currString = pList.getValueAtIndex(i);
		if((strncmp(currString->GetBuffer(),"-",1)==0) || (strncmp(currString->GetBuffer(),"/",1)==0))
		{
			if(currString->GetLength()!=1)
			{
				CSHString currentKey(currString->GetBuffer()+1);
				currentKey.toUpper();
				CSHString currentValue;

				if((i+1)<c)
				{
					i++;
					currString = pList.getValueAtIndex(i);
					if((strncmp(currString->GetBuffer(),"-",1)!=0) && (strncmp(currString->GetBuffer(),"/",1)!=0))
					{
						currentValue = currString->GetBuffer();
					}
				}

				paramPairList.add(new paramPair(currentKey,currentValue));
			}
		}

		i++;
	}

}

int CSHCommandLineProcessorType::getParamIndex(const char *key)
{
	int retVal = -1;

	CSHString uppercaseKey(key);
	uppercaseKey.toUpper();

	for(int i=0;i<paramPairList.getNumberOfItems();i++)
	{
		paramPair *currentItem = paramPairList.getValueAtIndex(i); 
		CSHString currentKey(currentItem->key);
		if(currentItem->key.equals(uppercaseKey))
		{
			retVal = i;
			break;
		}
	}

	return retVal;
}

CSHString CSHCommandLineProcessorType::getParamValue(const char *key)
{
	paramPair *retVal = NULL;

	int index = getParamIndex(key);

	if(index==-1)
		throw CSHCommandLineProcessorType::keyDoesNotExistException();

	return CSHString(paramPairList.getValueAtIndex(index)->value);
}

int CSHCommandLineProcessorType::keyExists(const char *key)
{
	int retVal = 1;
	int index = getParamIndex(key);

	if(index==-1)
		retVal = 0;

	return retVal;
}

CSHString CSHCommandLineProcessorType::getParamAtIndex(int index)
{
	if(index>=paramList.getNumberOfItems())
		throw indexOutOfBounds();

	return CSHString(*paramList.getValueAtIndex(index));
}
