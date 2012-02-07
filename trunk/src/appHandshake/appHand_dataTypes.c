
/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.6
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXISeGen</p>
 *
 ********************************************************************/


#include "EXITypes.h"
#include "appHand_dataTypes.h"


static  void init_protocolNamespaceType(struct protocolNamespaceType* type)
{	
	type->arraylen.data=0;

}

static  void init_AppProtocolType(struct AppProtocolType* type)
{	
	init_protocolNamespaceType(&(type->ProtocolNamespace));				

}

void init_AnonType_supportedAppProtocolReq(struct AnonType_supportedAppProtocolReq* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<5;i_loop++)
	{
		init_AppProtocolType(&(type->AppProtocol[i_loop]));
	}
	
	type->arraylen.AppProtocol=0;

}

void init_AnonType_supportedAppProtocolRes(struct AnonType_supportedAppProtocolRes* type)
{			
	type->isused.SchemaID=0;

}

void init_EXIDocumentType_appHand(struct EXIDocumentType_appHand* type)
{		
	type->isused.supportedAppProtocolReq=0;		
	type->isused.supportedAppProtocolRes=0;

}