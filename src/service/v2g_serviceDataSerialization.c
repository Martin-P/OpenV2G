
/*
 * Copyright (C) 2007-2010 Siemens AG
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
 * @version 0.3.1
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/


#include "v2g_service.h"
#include "v2g_serviceDataTypes.h"
/* #include "v2g_serviceDataSerializiation.h" */
#include "EXITypes.h"
#include "EXIEncoder.h"
 
 
 
 
 

static int serialize_SessionInformationType(struct SessionInformationType* type, struct EXIService* service)
{
	
			/* element ID assignment of SessionID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=34;	
			/* encode start element SessionID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->SessionID.arraylen.data;
		service->val.binary.data= type->SessionID.data;
		
		/* encode character  SessionID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
		{
				 
				return -1;
		}

			
			 
			/* encode end element of SessionID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.ServiceSessionID)
		{		
					
			/* element ID assignment of ServiceSessionID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=32;	
			/* encode start element ServiceSessionID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->ServiceSessionID.arraylen.data;
		service->val.binary.data= type->ServiceSessionID.data;
		
		/* encode character  ServiceSessionID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
		{
				 
				return -1;
		}

			
			 
			/* encode end element of ServiceSessionID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ProtocolVersion)
		{		
					
			/* element ID assignment of ProtocolVersion*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=24;	
			/* encode start element ProtocolVersion */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ProtocolVersion.arraylen.data;
			service->val.string.codepoints = type->ProtocolVersion.data;
		
			/* encode character  ProtocolVersion */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of ProtocolVersion */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_EventListType(struct EventListType* type, struct EXIService* service)
{
	
			/* element ID assignment of Event*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=9;	
			/* encode start element Event */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->Event;
			
			/* encode character  Event */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of Event */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_NotificationType(struct NotificationType* type, struct EXIService* service)
{

	if(type->isused.FaultCode)
		{		
					
			/* element ID assignment of FaultCode*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=13;	
			/* encode start element FaultCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->FaultCode;
			
			/* encode character  FaultCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of FaultCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.FaultMsg)
		{		
					
			/* element ID assignment of FaultMsg*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=14;	
			/* encode start element FaultMsg */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->FaultMsg.arraylen.data;
			service->val.string.codepoints = type->FaultMsg.data;
		
			/* encode character  FaultMsg */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of FaultMsg */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.EventList)
		{		
					
			/* element ID assignment of EventList*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=10;	
			/* encode start element EventList */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EventList */
			if(serialize_EventListType( &(type->EventList),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EventList */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_HeaderType(struct HeaderType* type, struct EXIService* service)
{
	
			/* element ID assignment of SessionInformation*/
			service->eqn.namespaceURI=7;			
			service->eqn.localPart=2;	
			/* encode start element SessionInformation */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of SessionInformation */
			if(serialize_SessionInformationType( &(type->SessionInformation),service))
			{
				return -1;
			}

			
			 
			/* encode end element of SessionInformation */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.Notification)
		{		
					
			/* element ID assignment of Notification*/
			service->eqn.namespaceURI=7;			
			service->eqn.localPart=1;	
			/* encode start element Notification */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of Notification */
			if(serialize_NotificationType( &(type->Notification),service))
			{
				return -1;
			}

			
			 
			/* encode end element of Notification */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_PEVStatusType(struct PEVStatusType* type, struct EXIService* service)
{
	
			/* element ID assignment of ConnectorLocked*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=4;	
			/* encode start element ConnectorLocked */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->ConnectorLocked;
			
			/* encode character  ConnectorLocked */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ConnectorLocked */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of ChargerStandby*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=0;	
			/* encode start element ChargerStandby */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->ChargerStandby;
			
			/* encode character  ChargerStandby */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ChargerStandby */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_SessionSetupReqType(struct SessionSetupReqType* type, struct EXIService* service)
{

	if(type->isused.PEVID)
		{		
					
			/* element ID assignment of PEVID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=24;	
			/* encode start element PEVID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->PEVID.arraylen.data;
			service->val.string.codepoints = type->PEVID.data;
		
			/* encode character  PEVID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of PEVID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
					
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=29;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType( &(type->PEVStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_EVSEStatusType(struct EVSEStatusType* type, struct EXIService* service)
{
	
			/* element ID assignment of FatalError*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=12;	
			/* encode start element FatalError */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->FatalError;
			
			/* encode character  FatalError */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of FatalError */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEStandby*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=7;	
			/* encode start element EVSEStandby */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->EVSEStandby;
			
			/* encode character  EVSEStandby */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of EVSEStandby */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of ConnectorLocked*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=4;	
			/* encode start element ConnectorLocked */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->ConnectorLocked;
			
			/* encode character  ConnectorLocked */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ConnectorLocked */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of PowerSwitchClosed*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=23;	
			/* encode start element PowerSwitchClosed */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->PowerSwitchClosed;
			
			/* encode character  PowerSwitchClosed */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of PowerSwitchClosed */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of RCD*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=25;	
			/* encode start element RCD */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->RCD;
			
			/* encode character  RCD */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of RCD */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of ShutDownTime*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=36;	
			/* encode start element ShutDownTime */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->ShutDownTime;
			
			/* encode character  ShutDownTime */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ShutDownTime */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_SessionSetupResType(struct SessionSetupResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=2;	
			/* encode start element EVSEID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->EVSEID.arraylen.data;
		service->val.binary.data= type->EVSEID.data;
		
		/* encode character  EVSEID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
		{
				 
				return -1;
		}

			
			 
			/* encode end element of EVSEID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=6;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType( &(type->EVSEStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of TCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=60;	
			/* encode start element TCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->TCurrent;
			
			/* encode character  TCurrent */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of TCurrent */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_ServiceDiscoveryReqType(struct ServiceDiscoveryReqType* type, struct EXIService* service)
{

	if(type->isused.ServiceType)
		{		
					
			/* element ID assignment of ServiceType*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=55;	
			/* encode start element ServiceType */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ServiceType;
			
			/* encode character  ServiceType */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ServiceType */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServiceScope)
		{		
					
			/* element ID assignment of ServiceScope*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=54;	
			/* encode start element ServiceScope */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ServiceScope.arraylen.data;
			service->val.string.codepoints = type->ServiceScope.data;
		
			/* encode character  ServiceScope */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of ServiceScope */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_ServiceDescriptionType(struct ServiceDescriptionType* type, struct EXIService* service)
{
	
			/* element ID assignment of ServiceID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=28;	
			/* encode start element ServiceID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->ServiceID.arraylen.data;
		service->val.binary.data= type->ServiceID.data;
		
		/* encode character  ServiceID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
		{
				 
				return -1;
		}

			
			 
			/* encode end element of ServiceID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.ServiceName)
		{		
					
			/* element ID assignment of ServiceName*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=30;	
			/* encode start element ServiceName */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ServiceName.arraylen.data;
			service->val.string.codepoints = type->ServiceName.data;
		
			/* encode character  ServiceName */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of ServiceName */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServiceType)
		{		
					
			/* element ID assignment of ServiceType*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=33;	
			/* encode start element ServiceType */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ServiceType;
			
			/* encode character  ServiceType */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ServiceType */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServiceScope)
		{		
					
			/* element ID assignment of ServiceScope*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=31;	
			/* encode start element ServiceScope */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ServiceScope.arraylen.data;
			service->val.string.codepoints = type->ServiceScope.data;
		
			/* encode character  ServiceScope */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of ServiceScope */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_ServiceListType(struct ServiceListType* type, struct EXIService* service)
{

			size_t i_loop;
	
	for(i_loop=0;i_loop < type->arraylen.Service;i_loop++)
		{
			
			/* element ID assignment of Service*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=26;	
			/* encode start element Service */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			/* encode children of Service */
			if(serialize_ServiceDescriptionType(&(type->Service[i_loop]),service))
			{
				return -1;
			}
			
			 
			/* encode end element of Service */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_ServiceDiscoveryResType(struct ServiceDiscoveryResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.ServiceList)
		{		
					
			/* element ID assignment of ServiceList*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=49;	
			/* encode start element ServiceList */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of ServiceList */
			if(serialize_ServiceListType( &(type->ServiceList),service))
			{
				return -1;
			}

			
			 
			/* encode end element of ServiceList */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_ServicePaymentSelectionReqType(struct ServicePaymentSelectionReqType* type, struct EXIService* service)
{
	
			/* element ID assignment of ServiceList*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=49;	
			/* encode start element ServiceList */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of ServiceList */
			if(serialize_ServiceListType( &(type->ServiceList),service))
			{
				return -1;
			}

			
			 
			/* encode end element of ServiceList */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_ServicePaymentSelectionResType(struct ServicePaymentSelectionResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_PaymentDetailsReqType(struct PaymentDetailsReqType* type, struct EXIService* service)
{
	
			/* element ID assignment of ContractID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=0;	
			/* encode start element ContractID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ContractID.arraylen.data;
			service->val.string.codepoints = type->ContractID.data;
		
			/* encode character  ContractID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of ContractID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_PaymentDetailsResType(struct PaymentDetailsResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_FloatingValueType(struct FloatingValueType* type, struct EXIService* service)
{
	
			/* element ID assignment of Multiplier*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=20;	
			/* encode start element Multiplier */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->Multiplier;
			
			/* encode character  Multiplier */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of Multiplier */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of Unit*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=49;	
			/* encode start element Unit */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->Unit;
			
			/* encode character  Unit */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of Unit */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of Value*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=50;	
			/* encode start element Value */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->Value;
			
			/* encode character  Value */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of Value */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_PowerDiscoveryReqType(struct PowerDiscoveryReqType* type, struct EXIService* service)
{
	
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=29;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType( &(type->PEVStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EoC*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=9;	
			/* encode start element EoC */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->EoC;
			
			/* encode character  EoC */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of EoC */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EAmount*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=1;	
			/* encode start element EAmount */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EAmount */
			if(serialize_FloatingValueType( &(type->EAmount),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EAmount */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of PEVMaxPower*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=26;	
			/* encode start element PEVMaxPower */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVMaxPower */
			if(serialize_FloatingValueType( &(type->PEVMaxPower),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVMaxPower */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of PEVMaxPhases*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=25;	
			/* encode start element PEVMaxPhases */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=type->PEVMaxPhases;
			
			/* encode character  PEVMaxPhases */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of PEVMaxPhases */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of PEVMaxVoltage*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=27;	
			/* encode start element PEVMaxVoltage */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVMaxVoltage */
			if(serialize_FloatingValueType( &(type->PEVMaxVoltage),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVMaxVoltage */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of PEVMinVoltage*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=28;	
			/* encode start element PEVMinVoltage */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVMinVoltage */
			if(serialize_FloatingValueType( &(type->PEVMinVoltage),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVMinVoltage */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_TariffEntryType(struct TariffEntryType* type, struct EXIService* service)
{
	
			/* element ID assignment of TariffStart*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=47;	
			/* encode start element TariffStart */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = UNSIGNED_INTEGER_32;
			service->val.uint32=type->TariffStart;
			
			/* encode character  TariffStart */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of TariffStart */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of TariffPMax*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=46;	
			/* encode start element TariffPMax */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of TariffPMax */
			if(serialize_FloatingValueType( &(type->TariffPMax),service))
			{
				return -1;
			}

			
			 
			/* encode end element of TariffPMax */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.EPrice)
		{		
					
			/* element ID assignment of EPrice*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=6;	
			/* encode start element EPrice */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EPrice */
			if(serialize_FloatingValueType( &(type->EPrice),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EPrice */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_TariffEntriesType(struct TariffEntriesType* type, struct EXIService* service)
{

			size_t i_loop;
	
	for(i_loop=0;i_loop < type->arraylen.TariffEntry;i_loop++)
		{
			
			/* element ID assignment of TariffEntry*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=43;	
			/* encode start element TariffEntry */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			/* encode children of TariffEntry */
			if(serialize_TariffEntryType(&(type->TariffEntry[i_loop]),service))
			{
				return -1;
			}
			
			 
			/* encode end element of TariffEntry */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_TariffDescrType(struct TariffDescrType* type, struct EXIService* service)
{
	
			/* element ID assignment of TariffID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=45;	
			/* encode start element TariffID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->TariffID;
			
			/* encode character  TariffID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of TariffID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.TariffDescription)
		{		
					
			/* element ID assignment of TariffDescription*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=40;	
			/* encode start element TariffDescription */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->TariffDescription.arraylen.data;
			service->val.string.codepoints = type->TariffDescription.data;
		
			/* encode character  TariffDescription */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of TariffDescription */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
					
			/* element ID assignment of TariffEntries*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=41;	
			/* encode start element TariffEntries */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of TariffEntries */
			if(serialize_TariffEntriesType( &(type->TariffEntries),service))
			{
				return -1;
			}

			
			 
			/* encode end element of TariffEntries */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_TariffTableType(struct TariffTableType* type, struct EXIService* service)
{

			size_t i_loop;
		
			/* element ID assignment of Currency*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=5;	
			/* encode start element Currency */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->Currency.arraylen.data;
			service->val.string.codepoints = type->Currency.data;
		
			/* encode character  Currency */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of Currency */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	for(i_loop=0;i_loop < type->arraylen.Tariff;i_loop++)
		{
			
			/* element ID assignment of Tariff*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=38;	
			/* encode start element Tariff */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			/* encode children of Tariff */
			if(serialize_TariffDescrType(&(type->Tariff[i_loop]),service))
			{
				return -1;
			}
			
			 
			/* encode end element of Tariff */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_PowerDiscoveryResType(struct PowerDiscoveryResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=6;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType( &(type->EVSEStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEVoltage*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=7;	
			/* encode start element EVSEVoltage */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEVoltage */
			if(serialize_FloatingValueType( &(type->EVSEVoltage),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEVoltage */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEIMax*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=3;	
			/* encode start element EVSEIMax */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEIMax */
			if(serialize_FloatingValueType( &(type->EVSEIMax),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEIMax */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEMaxPhases*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=4;	
			/* encode start element EVSEMaxPhases */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=type->EVSEMaxPhases;
			
			/* encode character  EVSEMaxPhases */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of EVSEMaxPhases */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.EnergyProvider)
		{		
					
			/* element ID assignment of EnergyProvider*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=8;	
			/* encode start element EnergyProvider */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->EnergyProvider.arraylen.data;
			service->val.string.codepoints = type->EnergyProvider.data;
		
			/* encode character  EnergyProvider */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of EnergyProvider */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.TariffTable)
		{		
					
			/* element ID assignment of TariffTable*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=62;	
			/* encode start element TariffTable */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of TariffTable */
			if(serialize_TariffTableType( &(type->TariffTable),service))
			{
				return -1;
			}

			
			 
			/* encode end element of TariffTable */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_LineLockReqType(struct LineLockReqType* type, struct EXIService* service)
{
	
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=29;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType( &(type->PEVStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of ReqLockStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=42;	
			/* encode start element ReqLockStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->ReqLockStatus;
			
			/* encode character  ReqLockStatus */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ReqLockStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_LineLockResType(struct LineLockResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=6;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType( &(type->EVSEStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_PowerDeliveryReqType(struct PowerDeliveryReqType* type, struct EXIService* service)
{
	
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=29;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType( &(type->PEVStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of ReqSwitchStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=43;	
			/* encode start element ReqSwitchStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=type->ReqSwitchStatus;
			
			/* encode character  ReqSwitchStatus */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ReqSwitchStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.Tariff)
		{		
					
			/* element ID assignment of Tariff*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=61;	
			/* encode start element Tariff */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->Tariff;
			
			/* encode character  Tariff */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of Tariff */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_PowerDeliveryResType(struct PowerDeliveryResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_MeteringStatusReqType(struct MeteringStatusReqType* type, struct EXIService* service)
{


	return 0;			
}


static int serialize_MeterInfoType(struct MeterInfoType* type, struct EXIService* service)
{

	if(type->isused.MeterID)
		{		
					
			/* element ID assignment of MeterID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=16;	
			/* encode start element MeterID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->MeterID.arraylen.data;
			service->val.string.codepoints = type->MeterID.data;
		
			/* encode character  MeterID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of MeterID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeterReading)
		{		
					
			/* element ID assignment of MeterReading*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=18;	
			/* encode start element MeterReading */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeterReading */
			if(serialize_FloatingValueType( &(type->MeterReading),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeterReading */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeterStatus)
		{		
					
			/* element ID assignment of MeterStatus*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=19;	
			/* encode start element MeterStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=type->MeterStatus;
			
			/* encode character  MeterStatus */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of MeterStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.TMeter)
		{		
					
			/* element ID assignment of TMeter*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=37;	
			/* encode start element TMeter */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->TMeter;
			
			/* encode character  TMeter */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of TMeter */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_MeteringStatusResType(struct MeteringStatusResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=2;	
			/* encode start element EVSEID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->EVSEID.arraylen.data;
		service->val.binary.data= type->EVSEID.data;
		
		/* encode character  EVSEID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
		{
				 
				return -1;
		}

			
			 
			/* encode end element of EVSEID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=6;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType( &(type->EVSEStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of TCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=60;	
			/* encode start element TCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->TCurrent;
			
			/* encode character  TCurrent */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of TCurrent */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of EVSEMaxPower*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=5;	
			/* encode start element EVSEMaxPower */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of EVSEMaxPower */
			if(serialize_FloatingValueType( &(type->EVSEMaxPower),service))
			{
				return -1;
			}

			
			 
			/* encode end element of EVSEMaxPower */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.PCurrent)
		{		
					
			/* element ID assignment of PCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=23;	
			/* encode start element PCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PCurrent */
			if(serialize_FloatingValueType( &(type->PCurrent),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PCurrent */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeterInfo)
		{		
					
			/* element ID assignment of MeterInfo*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=14;	
			/* encode start element MeterInfo */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeterInfo */
			if(serialize_MeterInfoType( &(type->MeterInfo),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeterInfo */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_MeteringReceiptReqType(struct MeteringReceiptReqType* type, struct EXIService* service)
{

	if(type->isused.PEVID)
		{		
					
			/* element ID assignment of PEVID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=24;	
			/* encode start element PEVID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->PEVID.arraylen.data;
			service->val.string.codepoints = type->PEVID.data;
		
			/* encode character  PEVID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
					return -1;
			}
			
			 
			/* encode end element of PEVID */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
					
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=29;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType( &(type->PEVStatus),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PEVStatus */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		
	if(type->isused.TCurrent)
		{		
					
			/* element ID assignment of TCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=60;	
			/* encode start element TCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = INTEGER_32;
			service->val.int32=type->TCurrent;
			
			/* encode character  TCurrent */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of TCurrent */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
					
			/* element ID assignment of Tariff*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=61;	
			/* encode start element Tariff */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->Tariff;
			
			/* encode character  Tariff */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of Tariff */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of MeterInfo*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=14;	
			/* encode start element MeterInfo */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeterInfo */
			if(serialize_MeterInfoType( &(type->MeterInfo),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeterInfo */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_MeteringReceiptResType(struct MeteringReceiptResType* type, struct EXIService* service)
{
	
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=44;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=type->ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val))) 
			{
				 
				return -1;
			}
				
			 
			/* encode end element of ResponseCode */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_BodyType(struct BodyType* type, struct EXIService* service)
{

	if(type->isused.SessionSetupReq)
		{		
					
			/* element ID assignment of SessionSetupReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=56;	
			/* encode start element SessionSetupReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of SessionSetupReq */
			if(serialize_SessionSetupReqType( (type->SessionSetupReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of SessionSetupReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.SessionSetupRes)
		{		
					
			/* element ID assignment of SessionSetupRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=58;	
			/* encode start element SessionSetupRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of SessionSetupRes */
			if(serialize_SessionSetupResType( (type->SessionSetupRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of SessionSetupRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServiceDiscoveryReq)
		{		
					
			/* element ID assignment of ServiceDiscoveryReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=45;	
			/* encode start element ServiceDiscoveryReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of ServiceDiscoveryReq */
			if(serialize_ServiceDiscoveryReqType( (type->ServiceDiscoveryReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of ServiceDiscoveryReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServiceDiscoveryRes)
		{		
					
			/* element ID assignment of ServiceDiscoveryRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ServiceDiscoveryRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of ServiceDiscoveryRes */
			if(serialize_ServiceDiscoveryResType( (type->ServiceDiscoveryRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of ServiceDiscoveryRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServicePaymentSelectionReq)
		{		
					
			/* element ID assignment of ServicePaymentSelectionReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=50;	
			/* encode start element ServicePaymentSelectionReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of ServicePaymentSelectionReq */
			if(serialize_ServicePaymentSelectionReqType( (type->ServicePaymentSelectionReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of ServicePaymentSelectionReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.ServicePaymentSelectionRes)
		{		
					
			/* element ID assignment of ServicePaymentSelectionRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=52;	
			/* encode start element ServicePaymentSelectionRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of ServicePaymentSelectionRes */
			if(serialize_ServicePaymentSelectionResType( (type->ServicePaymentSelectionRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of ServicePaymentSelectionRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.PaymentDetailsReq)
		{		
					
			/* element ID assignment of PaymentDetailsReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=30;	
			/* encode start element PaymentDetailsReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PaymentDetailsReq */
			if(serialize_PaymentDetailsReqType( (type->PaymentDetailsReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PaymentDetailsReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.PaymentDetailsRes)
		{		
					
			/* element ID assignment of PaymentDetailsRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=32;	
			/* encode start element PaymentDetailsRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PaymentDetailsRes */
			if(serialize_PaymentDetailsResType( (type->PaymentDetailsRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PaymentDetailsRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.PowerDiscoveryReq)
		{		
					
			/* element ID assignment of PowerDiscoveryReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=38;	
			/* encode start element PowerDiscoveryReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PowerDiscoveryReq */
			if(serialize_PowerDiscoveryReqType( (type->PowerDiscoveryReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PowerDiscoveryReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.PowerDiscoveryRes)
		{		
					
			/* element ID assignment of PowerDiscoveryRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=40;	
			/* encode start element PowerDiscoveryRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PowerDiscoveryRes */
			if(serialize_PowerDiscoveryResType( (type->PowerDiscoveryRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PowerDiscoveryRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.LineLockReq)
		{		
					
			/* element ID assignment of LineLockReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=10;	
			/* encode start element LineLockReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of LineLockReq */
			if(serialize_LineLockReqType( (type->LineLockReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of LineLockReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.LineLockRes)
		{		
					
			/* element ID assignment of LineLockRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=12;	
			/* encode start element LineLockRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of LineLockRes */
			if(serialize_LineLockResType( (type->LineLockRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of LineLockRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.PowerDeliveryReq)
		{		
					
			/* element ID assignment of PowerDeliveryReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=34;	
			/* encode start element PowerDeliveryReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PowerDeliveryReq */
			if(serialize_PowerDeliveryReqType( (type->PowerDeliveryReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PowerDeliveryReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.PowerDeliveryRes)
		{		
					
			/* element ID assignment of PowerDeliveryRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=36;	
			/* encode start element PowerDeliveryRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of PowerDeliveryRes */
			if(serialize_PowerDeliveryResType( (type->PowerDeliveryRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of PowerDeliveryRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeteringStatusReq)
		{		
					
			/* element ID assignment of MeteringStatusReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=19;	
			/* encode start element MeteringStatusReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeteringStatusReq */
			if(serialize_MeteringStatusReqType( (type->MeteringStatusReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeteringStatusReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeteringStatusRes)
		{		
					
			/* element ID assignment of MeteringStatusRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=21;	
			/* encode start element MeteringStatusRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeteringStatusRes */
			if(serialize_MeteringStatusResType( (type->MeteringStatusRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeteringStatusRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeteringReceiptReq)
		{		
					
			/* element ID assignment of MeteringReceiptReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=15;	
			/* encode start element MeteringReceiptReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeteringReceiptReq */
			if(serialize_MeteringReceiptReqType( (type->MeteringReceiptReq),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeteringReceiptReq */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				
	if(type->isused.MeteringReceiptRes)
		{		
					
			/* element ID assignment of MeteringReceiptRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=17;	
			/* encode start element MeteringReceiptRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of MeteringReceiptRes */
			if(serialize_MeteringReceiptResType( (type->MeteringReceiptRes),service))
			{
				return -1;
			}

			
			 
			/* encode end element of MeteringReceiptRes */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		}
				

	return 0;			
}


static int serialize_AnonType_V2G_Message(struct AnonType_V2G_Message* type, struct EXIService* service)
{
	
			/* element ID assignment of Header*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=4;	
			/* encode start element Header */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of Header */
			if(serialize_HeaderType( (type->Header),service))
			{
				return -1;
			}

			
			 
			/* encode end element of Header */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

			
			/* element ID assignment of Body*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=0;	
			/* encode start element Body */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of Body */
			if(serialize_BodyType( &(type->Body),service))
			{
				return -1;
			}

			
			 
			/* encode end element of Body */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}


static int serialize_EXIDocumentType(struct EXIDocumentType* type, struct EXIService* service)
{
	
			/* element ID assignment of V2G_Message*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=5;	
			/* encode start element V2G_Message */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn))) 
			{
					return -1;
			}
						
			/* encode children of V2G_Message */
			if(serialize_AnonType_V2G_Message( &(type->V2G_Message),service))
			{
				return -1;
			}

			
			 
			/* encode end element of V2G_Message */
			exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn));

		

	return 0;			
}

 
 
 
 
 
 /* marshal data to EXI stream */
static int serialize_message(struct EXIService* service)
 {
	

	/* encode start document */ 	
	if (exiEncodeStartDocument(&(service->outStream), &(service->stateEncode)) ) 
	{
	 
		return -1;
	}

	/* encode root element of V2G_Message */
	if (serialize_EXIDocumentType(&(service->exiMsg), service)) 
	{
			 
		return -1;
	}


	/* encode end document */
	if (exiEncodeEndDocument(&(service->outStream), &(service->stateEncode))) {
	 
	return -1;
	}	
 	
 	return 0;
 	
 }

 
 
 
