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
#include "CSHMemDebug.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "XX_CSHStringType.h"

CSHStringType::CSHStringType()
{
	buf = new char[1];
	buf[0] = 0;
}

CSHStringType::CSHStringType(const char *str)
{
	size_t len = strlen(str);
	buf = new char[len+1];
	strcpy(buf,str);
}

CSHStringType::CSHStringType(const CSHStringType &str)
{
	size_t len = strlen(str.buf);
	buf = new char[len+1];
	strcpy(buf,str.buf);
}

CSHStringType::~CSHStringType()
{
	delete []buf;
}

CSHStringType &CSHStringType::operator =(const char *s)
{
	init(s);
	return *this;
}

CSHStringType &CSHStringType::operator =(const CSHStringType &s)
{
	init(s.buf);
	return *this;
}

char CSHStringType::operator [](int n)
{
	return *(buf+n);
}

CSHStringType::operator char *()
{
	return buf;
}

CSHStringType::operator const char *()
{
	return buf;
}

char *CSHStringType::cat(const char *str)
{
	char *newbuff = new char[strlen(buf)+strlen(str)+1];
	strcpy(newbuff,buf);
	strcat(newbuff,str);

	delete []buf;
	buf = newbuff;

	return buf;
}

char *CSHStringType::Cat(const char *str)
{
  return cat(str);
}

char *CSHStringType::Cat(const char str)
{
	char astring[50];
	sprintf(astring, "%c", str);
	return Cat(astring);
}

void CSHStringType::toUpper()
{
	size_t len = strlen(buf);
	for(size_t i=0;i<len;i++)
		buf[i] = toupper(buf[i]);
}

int CSHStringType::equals(const char *str)
{
	int retVal = 0;
	if(strcmp(buf,str)==0)
		retVal = 1;

	return retVal;
}

int CSHStringType::equal(const char *str)
{
	return equals(str);
}

int CSHStringType::equals(const CSHStringType &str)
{
	int retVal = 0;
	if(strcmp(buf,str.buf)==0)
		retVal = 1;

	return retVal;
}

int CSHStringType::equal(const CSHStringType &str)
{
	return equals(str);
}

char *CSHStringType::GetBuffer()
{
	return buf;
}

size_t CSHStringType::GetLength()
{
	return strlen(buf);
}

int CSHStringType::length()
{
  return GetLength();
}

char *CSHStringType::swap(char *newbuff)
{
	char *oldBuff = buf;
	buf = newbuff;

	return oldBuff;
}

CSHStringType CSHStringType::extract(const int passed_from, const int passed_to)
{
	CSHStringType retVal;
	int from = passed_from;
	int to = passed_to;
	if(to==-1)
	{
		to = (int)GetLength();
	}

	if((from>=0) && (to>=0) && (to>=from))
	{
		if(to>from)
		{
			int newSize = to-from;
			char *newbuff = new char[newSize+1];
			strncpy(newbuff,buf+from,newSize);
			newbuff[newSize] = 0;
			delete []retVal.swap(newbuff);
		}
	}

	return retVal;
}

int CSHStringType::findNextNonWhitespace(int from)
{
	char *rawBuff = GetBuffer();
	size_t size = GetLength();
	int retPos = -1;
	for(size_t i=from;i<size;i++)
	{
		if((rawBuff[i]!=' ') && (rawBuff[i]!='\t'))
		{
			retPos = (int)i;
			break;
		}
	}

	return retPos;
}

int CSHStringType::findNextWhitespace(int from)
{
	char *rawBuff = GetBuffer();
	size_t size = GetLength();
	int retPos = -1;
	for(size_t i=from;i<size;i++)
	{
		if((rawBuff[i]==' ') || (rawBuff[i]=='\t'))
		{
			retPos = (int)i;
			break;
		}
	}

	return retPos;
}

int CSHStringType::find(const char *str,const int fromPos)
{
	size_t slen = strlen(str);
	size_t tLen = GetLength();

	int foundAtPos = -1;
	if(slen<=tLen)
	{
		size_t stopAt = tLen-slen+1;
		for(size_t i=fromPos;i<stopAt;i++)
		{
			if(strncmp(buf+i,str,slen)==0)
			{
				foundAtPos = (int)i;
				break;
			}
		}
	}

	return foundAtPos;
}

void CSHStringType::init(const char *str)
{
	delete []buf;
	size_t len = strlen(str);
	buf = new char[len+1];
	strcpy(buf,str);
}

int CSHStringType::reverseFindChar(const char c,int from)
{
  if(from==-1)
    from = strlen(buf);

  int retVal = -1;
  for(int i=from;i>=0;i--)
    {
      if(buf[i]==c)
	{
	  retVal = i;
	  break;
	}
    }

  return retVal;
}

int CSHStringType::findChar(char c,int from)
{
	int retVal = -1;

	int size = strlen(buf);
	for(unsigned int i=from;i<size;i++)
	{
		if((*(buf+i))==(c))
		{	
			retVal = i;
			break;
		}
	}
	return retVal;
}

int CSHStringType::like(char *likeS)
{
  int retVal = 0;
  CSHStringType likeStr = likeS;
  switch(likeStr.occurs('*'))
  {
    case 0:
    {
      if(likeStr.equals(buf))
	 retVal = 1;
      break;
    }

    case 1:
    {
      //Is the * at the begining or the end?
      if(likeStr[0]=='*')
      {
	//The * is at the begining.
	//So does our string have the passed in string at the end?
	//Well for a start it does not have it if our string is smaller than the passed in one!

	int len = length();

	// -1 for the *
	int lenPassedIn = likeStr.length()-1;

	if(len>=lenPassedIn)
	{
	  const char *cmpStr = likeStr.GetBuffer()+1;

	  if(strcmp(buf+(len-lenPassedIn),cmpStr) == 0)
	    retVal = 1;
	}
	 
      }

      if(likeStr[likeStr.length()-1]=='*')
      {
	//The * is at the end.
	//So does our string have the passed in string at the end?
	//We for a start it does not have it if our string is smaller than the passed in one!

	int len = length();

	// -1 for the *
	int lenPassedIn = likeStr.length()-1;

	if(len>=lenPassedIn)
	{
	  const char *cmpStr = likeStr.GetBuffer();

	  if(strncmp(buf,cmpStr,lenPassedIn) == 0)
	    retVal = 1;
	}
	 
      }

      break;
    }

    case 2:
    {
      //We only support the case when the *s are at either end.  So check for this...
      if((likeStr[0]=='*') && (likeStr[likeStr.length()-1]=='*'))
      {
	CSHStringType newCmpStr = likeStr.extract(1,likeStr.length()-1);
	if(contains(newCmpStr)!=-1)
	  retVal = 1;
      }
      break;
    }
      
  }

  return retVal;
}

int CSHStringType::findFirstNonCharOccurence(const char *s,int from)
{
  int retVal = -1;

  int numberOfChars = strlen(s);

  for(int i=from;i<strlen(buf);i++)
  {
    int foundOne = 0;
    for(int currCharIndex=0;currCharIndex<numberOfChars;currCharIndex++)
    {
      if(*(buf+i)==*(s+currCharIndex))
      {
        foundOne = 1;
        break;
      }
    }
    if(!foundOne)
    {
      retVal = i;
      break;
    }
  }

  return retVal;
}

void CSHStringType::CatInt(int Value)
{
	char String[50];
	sprintf(String, "%d", Value);
	Cat(String);
}

void CSHStringType::truncate(int stopAt)
{
  if(stopAt<=(strlen(buf)-1))
  {
    char *newBuffer = new char[stopAt+2];
    strncpy(newBuffer,buf,stopAt+1);
    *(newBuffer+stopAt) = '\0';
    delete []buf;
    buf = newBuffer;
  }
  else
  {
    delete []buf;
    buf = new char[1];
    *buf = '\0';
  }
}

int CSHStringType::findBackwardsFirstNonCharOccurence(const char *s,int from)
{
  int retVal = -1;

  int startFrom = from;

  if(startFrom==-1)
    startFrom = strlen(buf)-1;

  int numberOfChars = strlen(s);

  for(int i=startFrom;i>=0;i--)
  {
    int foundOne = 0;
    for(int currCharIndex=0;currCharIndex<numberOfChars;currCharIndex++)
    {
      if(*(buf+i)==*(s+currCharIndex))
      {
        foundOne = 1;
        break;
      }
    }
    if(!foundOne)
    {
      retVal = i;
      break;
    }
  }

  return retVal;
}

int CSHStringType::occurs(const char &c)
{
  int retVal = 0;
  for(int i=0;i<length();i++)
    if(*(buf+i)==c)
      retVal++;

  return retVal;
}

int CSHStringType::contains(const char *anOtherString,int fromCharacter)
{
	int retVal = -1;
	for(int i1 = fromCharacter; i1 < length();i1++)
	{
		if(strncmp(anOtherString,GetBuffer()+i1,strlen(anOtherString))== 0)
		{
			retVal = i1;
			break;
		}
	}

	 return retVal;
}

int CSHStringType::stringSubstitution(CSHStringType *str,char *lookFor,char *replaceWith)
{
	int didASubst = 0;
	int pos = str->find(lookFor);
	if(pos!=-1)
	{
		didASubst = 1;
		CSHStringType newString;
		if(pos>0)
		{
			newString = str->extract(0,pos);
		}
		
		newString.Cat(replaceWith);
		CSHStringType stringTail = str->extract(pos+strlen(lookFor),str->GetLength());
		newString.Cat(stringTail);

		char *newStringBuff = newString.swap(NULL);
		delete [](str->swap(newStringBuff));
	}

	return didASubst;
}

void CSHStringType::removeWhitespaceFromBothEnds()
{
        int i;
	for(i = 0;i<length();i++)
	{
		if((*(buf+i)!=' ') && (*(buf+i)!='\t'))
			break;
	}

	if(i != length())
	{
		int beginingOfString = i;
		for(i=length()-1;i>=0;i--)
		{
			char r = *(buf+i);
			if((r!=' ') && (r!='\t'))
				break;
		}
		int endOfString = i;

		char *newString = new char[endOfString-beginingOfString+2];
		strncpy(newString,buf + beginingOfString,endOfString-beginingOfString+1);
		*(newString+endOfString-beginingOfString+1) = '\0';
		delete [](swap(newString));
	}
}

