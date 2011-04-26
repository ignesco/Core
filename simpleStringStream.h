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
#ifndef SIMPLESTRINGSTREAM_H
#define SIMPLESTRINGSTREAM_H

class simpleStringStream
{
	public:
		simpleStringStream(char *b,int len):buff(b),maxSize(len),currPos(0)
		{
		}

		virtual ~simpleStringStream()
		{
		}

		virtual int ftell()
		{
			return currPos;
		}

		virtual int fread(char *tempBuff,int numOfChars)
		{
			//123
			// currPos = 0;
			// numOfChars = 3
			// maxLen = 3;
			int retVal = 0;
			if((currPos+numOfChars-1)<maxSize)
			{
				retVal = numOfChars;
			}
			else
			{
				if(numOfChars - currPos<0)
					retVal = 0;
				else
					retVal = numOfChars - currPos;
			}

			for(int i=0;i<retVal;i++)
			{
				tempBuff[i] = buff[i+currPos];
			}

			currPos +=retVal;

			return retVal;
		}

		virtual void fseek(int offset,int origin)
		{
			if(origin==SEEK_SET)
			{
				currPos = offset;
			}
			else
				cshexit(1);
		}

	private:
		int currPos;
		int maxSize;
		char *buff;
};

#endif

