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
#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <stdio.h>
#include "cshTypes_String.h"

class CSHStreamExceptions
{
	public:
		class couldNotOpenStream
		{
			public:
				couldNotOpenStream(char *eS):errorString(eS)
				{
				}

				virtual ~couldNotOpenStream()
				{
				}

				CSHString errorString;
		};
};

class fileStream
{
	public:
		fileStream(char *filename)
		{
			f = fopen(filename,"rt");
			if(f==NULL)
			{
				throw CSHStreamExceptions::couldNotOpenStream(filename);
			}

			::fseek(f,0,SEEK_SET);
		}

		virtual ~fileStream()
		{
			fclose(f);
		}

		size_t ftell()
		{
			return ::ftell(f);
		}

		size_t fread(void *b,int count)
		{
			return ::fread(b,1,count,f);
		}

		int fseek(int offset,int whence)
		{
			return ::fseek(f,offset,whence);
		}


	FILE *f;
};

class getsStream
{
	public:
		class noMoreStrings
		{
			public:
				noMoreStrings(int)
				{
				}

				virtual ~noMoreStrings()
				{
				}
		};

		getsStream()
		{
		}

		virtual ~getsStream()
		{
		}

		virtual char *gets() = 0;
};

class getsFileStream : public getsStream
{
	public:
		//D EBUG_THIS_CLASS;

		getsFileStream(char *filename):getsStream()
		{
			f = fopen(filename,"rt");
			if(f==NULL)
			{
				throw CSHStreamExceptions::couldNotOpenStream(filename);
			}
			::fseek(f,0,SEEK_SET);
		}

		virtual ~getsFileStream()
		{
			fclose(f);
		}

		virtual char *gets()
		{
			char *ret = ::fgets(buffer,2040,f);
			if(ret==NULL)
				throw noMoreStrings(1);

			return buffer;
		}

		char buffer[2048];

	private:
		FILE *f;
};


#endif
