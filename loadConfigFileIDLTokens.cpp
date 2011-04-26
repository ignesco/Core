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
#include "loadConfigFileIDLTokens.h"
#include "textHelperFunctions.h"

void loadTokensFromConfigFile(CSHCommandLineProcessor *clp,genericTokeniser<fileStream> *toker,fileStream **msc)
{
	try
	{
		CSHString ss = clp->getParamValue("f");
		printf("#Processing file : %s\n",ss.GetBuffer());

		try
		{
			getsFileStream commandFile(ss);

			try
			{
				while(1)
				{
					CSHString instLine = commandFile.gets();
					int posOfIDLFile = instLine.find("IDLFILE:");
					if(posOfIDLFile==0)
					{
						CSHString idlFile(instLine.extract(8));
						trimString(idlFile,';');
						printf("#loading idl file : !%s!\n",idlFile.GetBuffer());

						*msc = new fileStream(idlFile);
						toker->tokenise(*msc);
						delete *msc;
						*msc = NULL;
					}
				}
			}
			catch(getsStream::noMoreStrings &)
			{
			}
		}
		catch(CSHStreamExceptions::couldNotOpenStream &e)
		{
			printf("ERROR : Could not open file : !%!s\n",e.errorString.GetBuffer());
		}
	}
	catch(CSHCommandLineProcessor::keyDoesNotExistException &)
	{
		printf("Usage %s -f filename\n",clp->getParamAtIndex(0).GetBuffer());
	}
}
