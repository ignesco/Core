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
#ifndef CSHSTRINGTYPE_H
#define CSHSTRINGTYPE_H

#include <sys/types.h>  //size_t defined here

class CSHStringType
{
	public:
		CSHStringType();
		CSHStringType(const char *str);
		CSHStringType(const CSHStringType &str);

		virtual ~CSHStringType();

		virtual void init(const char *str);

		virtual CSHStringType &operator =(const char *s);
		virtual CSHStringType &operator =(const CSHStringType &s);
		virtual operator char *();
		virtual operator const char *();

		virtual char *cat(const char *str);
		virtual char *Cat(const char *str);
		virtual char *Cat(const char str);
		virtual void CatInt(int Value);
		virtual void truncate(int stopAt);
		virtual void toUpper();
		virtual int equals(const char *str);
		virtual int equals(const CSHStringType &str);
		virtual int equal(const char *str);
		virtual int equal(const CSHStringType &str);
		virtual char *GetBuffer();
		virtual size_t GetLength();
		virtual int length();
		virtual CSHStringType extract(const int passed_from, const int passed_to=-1);
		virtual char *swap(char *newbuff);
		virtual int findNextNonWhitespace(int from);
		virtual int findNextWhitespace(int from);
		virtual int find(const char *str,const int fromPos=0);
		virtual int findChar(char c,int from=0);
		virtual int reverseFindChar(const char c,int from=-1);
		virtual int like(char *likeS);
		virtual int occurs(const char &c);
		virtual int contains(const char *anOtherString,int fromCharacter=0);

		virtual int findFirstNonCharOccurence(const char *s,int from=0);
		virtual int findBackwardsFirstNonCharOccurence(const char *s,int from=-1);
		int stringSubstitution(CSHStringType *str,char *lookFor,char *replaceWith);		
		void removeWhitespaceFromBothEnds();



		char operator [](const int n);



	private:
		char *buf;
};

#endif
