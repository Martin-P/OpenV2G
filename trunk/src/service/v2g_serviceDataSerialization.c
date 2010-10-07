
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
 * @version 0.2.1
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/


#include "v2g_service.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceDataSerializiation.h"
#include "EXITypes.h"
#include "EXIEncoder.h"
 
 
 
 
 

static int serialize_SessionInformationType(struct SessionInformationType* type, struct v2gService* service)
{
			
			/* element ID assignment of SessionID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=35;	
			/* encode start element SessionID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->SessionID.arraylen.data;
		memcpy(service->val.binary.data, type->SessionID.data, service->val.binary.len);
		
		/* encode character  SessionID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of SessionID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.ServiceSessionID)
		{		
				
			
			/* element ID assignment of ServiceSessionID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=33;	
			/* encode start element ServiceSessionID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->ServiceSessionID.arraylen.data;
		memcpy(service->val.binary.data, type->ServiceSessionID.data, service->val.binary.len);
		
		/* encode character  ServiceSessionID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of ServiceSessionID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ProtocolVersion)
		{		
				
			
			/* element ID assignment of ProtocolVersion*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=25;	
			/* encode start element ProtocolVersion */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ProtocolVersion.arraylen.data;
			memcpy(service->val.string.codepoints, type->ProtocolVersion.data, service->val.string.len);
		
			/* encode character  ProtocolVersion */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of ProtocolVersion */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_EventListType(struct EventListType* type, struct v2gService* service)
{
			
			/* element ID assignment of Event*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=9;	
			/* encode start element Event */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Header.Notification.EventList.Event;
			
			/* encode character  Event */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of Event */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_NotificationType(struct NotificationType* type, struct v2gService* service)
{if(type->isused.FaultCode)
		{		
				
			
			/* element ID assignment of FaultCode*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=13;	
			/* encode start element FaultCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Header.Notification.FaultCode;
			
			/* encode character  FaultCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of FaultCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.FaultMsg)
		{		
				
			
			/* element ID assignment of FaultMsg*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=14;	
			/* encode start element FaultMsg */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->FaultMsg.arraylen.data;
			memcpy(service->val.string.codepoints, type->FaultMsg.data, service->val.string.len);
		
			/* encode character  FaultMsg */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of FaultMsg */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.EventList)
		{		
				
			
			/* element ID assignment of EventList*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=10;	
			/* encode start element EventList */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EventList */
			if(serialize_EventListType(&(type->EventList),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EventList */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_HeaderType(struct HeaderType* type, struct v2gService* service)
{
			
			/* element ID assignment of SessionInformation*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=7;	
			/* encode start element SessionInformation */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of SessionInformation */
			if(serialize_SessionInformationType(&(type->SessionInformation),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of SessionInformation */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.Notification)
		{		
				
			
			/* element ID assignment of Notification*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=6;	
			/* encode start element Notification */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of Notification */
			if(serialize_NotificationType(&(type->Notification),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of Notification */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_PEVStatusType(struct PEVStatusType* type, struct v2gService* service)
{
			
			/* element ID assignment of ConnectorLocked*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=4;	
			/* encode start element ConnectorLocked */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupReq.PEVStatus.ConnectorLocked;
			
			/* encode character  ConnectorLocked */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ConnectorLocked */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of ChargerStandby*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=0;	
			/* encode start element ChargerStandby */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupReq.PEVStatus.ChargerStandby;
			
			/* encode character  ChargerStandby */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ChargerStandby */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_SessionSetupReqType(struct SessionSetupReqType* type, struct v2gService* service)
{if(type->isused.PEVID)
		{		
				
			
			/* element ID assignment of PEVID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=26;	
			/* encode start element PEVID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->PEVID.arraylen.data;
			memcpy(service->val.string.codepoints, type->PEVID.data, service->val.string.len);
		
			/* encode character  PEVID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of PEVID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				
			
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=32;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType(&(type->PEVStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_EVSEStatusType(struct EVSEStatusType* type, struct v2gService* service)
{
			
			/* element ID assignment of FatalError*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=12;	
			/* encode start element FatalError */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupRes.EVSEStatus.FatalError;
			
			/* encode character  FatalError */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of FatalError */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEStandby*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=7;	
			/* encode start element EVSEStandby */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupRes.EVSEStatus.EVSEStandby;
			
			/* encode character  EVSEStandby */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of EVSEStandby */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of ConnectorLocked*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=4;	
			/* encode start element ConnectorLocked */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupRes.EVSEStatus.ConnectorLocked;
			
			/* encode character  ConnectorLocked */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ConnectorLocked */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of PowerSwitchClosed*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=24;	
			/* encode start element PowerSwitchClosed */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupRes.EVSEStatus.PowerSwitchClosed;
			
			/* encode character  PowerSwitchClosed */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of PowerSwitchClosed */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of RCD*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=26;	
			/* encode start element RCD */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.SessionSetupRes.EVSEStatus.RCD;
			
			/* encode character  RCD */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of RCD */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of ShutDownTime*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=37;	
			/* encode start element ShutDownTime */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.SessionSetupRes.EVSEStatus.ShutDownTime;
			
			/* encode character  ShutDownTime */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ShutDownTime */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_SessionSetupResType(struct SessionSetupResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.SessionSetupRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=3;	
			/* encode start element EVSEID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->EVSEID.arraylen.data;
		memcpy(service->val.binary.data, type->EVSEID.data, service->val.binary.len);
		
		/* encode character  EVSEID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of EVSEID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=7;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType(&(type->EVSEStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of TCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=63;	
			/* encode start element TCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.SessionSetupRes.TCurrent;
			
			/* encode character  TCurrent */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of TCurrent */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_ServiceDiscoveryReqType(struct ServiceDiscoveryReqType* type, struct v2gService* service)
{if(type->isused.ServiceType)
		{		
				
			
			/* element ID assignment of ServiceType*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=58;	
			/* encode start element ServiceType */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.ServiceDiscoveryReq.ServiceType;
			
			/* encode character  ServiceType */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ServiceType */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServiceScope)
		{		
				
			
			/* element ID assignment of ServiceScope*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=57;	
			/* encode start element ServiceScope */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ServiceScope.arraylen.data;
			memcpy(service->val.string.codepoints, type->ServiceScope.data, service->val.string.len);
		
			/* encode character  ServiceScope */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of ServiceScope */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_ServiceDescriptionType(struct ServiceDescriptionType* type, struct v2gService* service)
{
			
			/* element ID assignment of ServiceID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=29;	
			/* encode start element ServiceID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->ServiceID.arraylen.data;
		memcpy(service->val.binary.data, type->ServiceID.data, service->val.binary.len);
		
		/* encode character  ServiceID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of ServiceID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.ServiceName)
		{		
				
			
			/* element ID assignment of ServiceName*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=31;	
			/* encode start element ServiceName */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ServiceName.arraylen.data;
			memcpy(service->val.string.codepoints, type->ServiceName.data, service->val.string.len);
		
			/* encode character  ServiceName */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of ServiceName */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServiceType)
		{		
				
			
			/* element ID assignment of ServiceType*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=34;	
			/* encode start element ServiceType */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceType;
			
			/* encode character  ServiceType */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ServiceType */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServiceScope)
		{		
				
			
			/* element ID assignment of ServiceScope*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=32;	
			/* encode start element ServiceScope */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ServiceScope.arraylen.data;
			memcpy(service->val.string.codepoints, type->ServiceScope.data, service->val.string.len);
		
			/* encode character  ServiceScope */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of ServiceScope */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_ServiceListType(struct ServiceListType* type, struct v2gService* service)
{
			int i_loop;
	
			
			/* element ID assignment of Service*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=27;	
			/* encode start element Service */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			for(i_loop=0;i_loop < type->arraylen.Service;i_loop++)
			{
				/* encode children of Service */
				if(serialize_ServiceDescriptionType(&(type->Service[i_loop]),service)<0)
				{
					return -1;
				}
			
			}
			
			
			

			 
			
			/* encode end element of Service */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_ServiceDiscoveryResType(struct ServiceDiscoveryResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.ServiceDiscoveryRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.ServiceList)
		{		
				
			
			/* element ID assignment of ServiceList*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=52;	
			/* encode start element ServiceList */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ServiceList */
			if(serialize_ServiceListType(&(type->ServiceList),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ServiceList */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_ServicePaymentSelectionReqType(struct ServicePaymentSelectionReqType* type, struct v2gService* service)
{
			
			/* element ID assignment of ServiceList*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=52;	
			/* encode start element ServiceList */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ServiceList */
			if(serialize_ServiceListType(&(type->ServiceList),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ServiceList */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of PEVPubKey*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=31;	
			/* encode start element PEVPubKey */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->PEVPubKey.arraylen.data;
		memcpy(service->val.binary.data, type->PEVPubKey.data, service->val.binary.len);
		
		/* encode character  PEVPubKey */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of PEVPubKey */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_ServicePaymentSelectionResType(struct ServicePaymentSelectionResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.ServicePaymentSelectionRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.MeteringAuthPubKey)
		{		
				
			
			/* element ID assignment of MeteringAuthPubKey*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=16;	
			/* encode start element MeteringAuthPubKey */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->MeteringAuthPubKey.arraylen.data;
		memcpy(service->val.binary.data, type->MeteringAuthPubKey.data, service->val.binary.len);
		
		/* encode character  MeteringAuthPubKey */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of MeteringAuthPubKey */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_PaymentDetailsReqType(struct PaymentDetailsReqType* type, struct v2gService* service)
{
			
			/* element ID assignment of ContractID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=1;	
			/* encode start element ContractID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->ContractID.arraylen.data;
			memcpy(service->val.string.codepoints, type->ContractID.data, service->val.string.len);
		
			/* encode character  ContractID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of ContractID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_PaymentDetailsResType(struct PaymentDetailsResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PaymentDetailsRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_FloatingValueType(struct FloatingValueType* type, struct v2gService* service)
{
			
			/* element ID assignment of Multiplier*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=21;	
			/* encode start element Multiplier */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Multiplier;
			
			/* encode character  Multiplier */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of Multiplier */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of Unit*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=50;	
			/* encode start element Unit */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Unit;
			
			/* encode character  Unit */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of Unit */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of Value*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=51;	
			/* encode start element Value */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Value;
			
			/* encode character  Value */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of Value */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_PowerDiscoveryReqType(struct PowerDiscoveryReqType* type, struct v2gService* service)
{
			
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=32;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType(&(type->PEVStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EoC*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=10;	
			/* encode start element EoC */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.PowerDiscoveryReq.EoC;
			
			/* encode character  EoC */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of EoC */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EAmount*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=2;	
			/* encode start element EAmount */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EAmount */
			if(serialize_FloatingValueType(&(type->EAmount),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EAmount */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of PEVMaxPower*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=28;	
			/* encode start element PEVMaxPower */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVMaxPower */
			if(serialize_FloatingValueType(&(type->PEVMaxPower),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVMaxPower */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of PEVMaxPhases*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=27;	
			/* encode start element PEVMaxPhases */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxPhases;
			
			/* encode character  PEVMaxPhases */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of PEVMaxPhases */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of PEVMaxVoltage*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=29;	
			/* encode start element PEVMaxVoltage */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVMaxVoltage */
			if(serialize_FloatingValueType(&(type->PEVMaxVoltage),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVMaxVoltage */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of PEVMinVoltage*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=30;	
			/* encode start element PEVMinVoltage */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVMinVoltage */
			if(serialize_FloatingValueType(&(type->PEVMinVoltage),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVMinVoltage */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_TariffEntryType(struct TariffEntryType* type, struct v2gService* service)
{
			
			/* element ID assignment of TariffStart*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=48;	
			/* encode start element TariffStart */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = UNSIGNED_INTEGER_32;
			service->val.uint32=service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffStart;
			
			/* encode character  TariffStart */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of TariffStart */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of TariffPMax*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=47;	
			/* encode start element TariffPMax */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of TariffPMax */
			if(serialize_FloatingValueType(&(type->TariffPMax),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of TariffPMax */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.EPrice)
		{		
				
			
			/* element ID assignment of EPrice*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=6;	
			/* encode start element EPrice */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EPrice */
			if(serialize_FloatingValueType(&(type->EPrice),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EPrice */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_TariffEntriesType(struct TariffEntriesType* type, struct v2gService* service)
{
			int i_loop;
	
			
			/* element ID assignment of TariffEntry*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=44;	
			/* encode start element TariffEntry */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			for(i_loop=0;i_loop < type->arraylen.TariffEntry;i_loop++)
			{
				/* encode children of TariffEntry */
				if(serialize_TariffEntryType(&(type->TariffEntry[i_loop]),service)<0)
				{
					return -1;
				}
			
			}
			
			
			

			 
			
			/* encode end element of TariffEntry */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_TariffDescrType(struct TariffDescrType* type, struct v2gService* service)
{
			
			/* element ID assignment of TariffID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=46;	
			/* encode start element TariffID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffID;
			
			/* encode character  TariffID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of TariffID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.TariffDescription)
		{		
				
			
			/* element ID assignment of TariffDescription*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=41;	
			/* encode start element TariffDescription */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->TariffDescription.arraylen.data;
			memcpy(service->val.string.codepoints, type->TariffDescription.data, service->val.string.len);
		
			/* encode character  TariffDescription */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of TariffDescription */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				
			
			/* element ID assignment of TariffEntries*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=42;	
			/* encode start element TariffEntries */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of TariffEntries */
			if(serialize_TariffEntriesType(&(type->TariffEntries),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of TariffEntries */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_TariffTableType(struct TariffTableType* type, struct v2gService* service)
{
			int i_loop;
	
			
			/* element ID assignment of Currency*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=5;	
			/* encode start element Currency */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->Currency.arraylen.data;
			memcpy(service->val.string.codepoints, type->Currency.data, service->val.string.len);
		
			/* encode character  Currency */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of Currency */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of Tariff*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=39;	
			/* encode start element Tariff */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			for(i_loop=0;i_loop < type->arraylen.Tariff;i_loop++)
			{
				/* encode children of Tariff */
				if(serialize_TariffDescrType(&(type->Tariff[i_loop]),service)<0)
				{
					return -1;
				}
			
			}
			
			
			

			 
			
			/* encode end element of Tariff */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_PowerDiscoveryResType(struct PowerDiscoveryResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PowerDiscoveryRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=7;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType(&(type->EVSEStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEVoltage*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=8;	
			/* encode start element EVSEVoltage */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEVoltage */
			if(serialize_FloatingValueType(&(type->EVSEVoltage),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEVoltage */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEIMax*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=4;	
			/* encode start element EVSEIMax */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEIMax */
			if(serialize_FloatingValueType(&(type->EVSEIMax),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEIMax */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEMaxPhases*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=5;	
			/* encode start element EVSEMaxPhases */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=service->v2gMsg.Body.PowerDiscoveryRes.EVSEMaxPhases;
			
			/* encode character  EVSEMaxPhases */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of EVSEMaxPhases */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.EnergyProvider)
		{		
				
			
			/* element ID assignment of EnergyProvider*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=9;	
			/* encode start element EnergyProvider */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->EnergyProvider.arraylen.data;
			memcpy(service->val.string.codepoints, type->EnergyProvider.data, service->val.string.len);
		
			/* encode character  EnergyProvider */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of EnergyProvider */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.TariffTable)
		{		
				
			
			/* element ID assignment of TariffTable*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=65;	
			/* encode start element TariffTable */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of TariffTable */
			if(serialize_TariffTableType(&(type->TariffTable),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of TariffTable */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_LineLockReqType(struct LineLockReqType* type, struct v2gService* service)
{
			
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=32;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType(&(type->PEVStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of ReqLockStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=45;	
			/* encode start element ReqLockStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.LineLockReq.ReqLockStatus;
			
			/* encode character  ReqLockStatus */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ReqLockStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_LineLockResType(struct LineLockResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.LineLockRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=7;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType(&(type->EVSEStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_ChargingProfileType(struct ChargingProfileType* type, struct v2gService* service)
{
			
			/* element ID assignment of ChargingProfileEntryStart*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=2;	
			/* encode start element ChargingProfileEntryStart */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.PowerDeliveryReq.ChargingProfile.ChargingProfileEntryStart;
			
			/* encode character  ChargingProfileEntryStart */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ChargingProfileEntryStart */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of ChargingProfileEntryMaxPower*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=1;	
			/* encode start element ChargingProfileEntryMaxPower */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ChargingProfileEntryMaxPower */
			if(serialize_FloatingValueType(&(type->ChargingProfileEntryMaxPower),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ChargingProfileEntryMaxPower */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_PowerDeliveryReqType(struct PowerDeliveryReqType* type, struct v2gService* service)
{
			
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=32;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType(&(type->PEVStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of ReqSwitchStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=46;	
			/* encode start element ReqSwitchStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = BOOLEAN;
			service->val.boolean=service->v2gMsg.Body.PowerDeliveryReq.ReqSwitchStatus;
			
			/* encode character  ReqSwitchStatus */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ReqSwitchStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.Tariff)
		{		
				
			
			/* element ID assignment of Tariff*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=64;	
			/* encode start element Tariff */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PowerDeliveryReq.Tariff;
			
			/* encode character  Tariff */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of Tariff */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ChargingProfile)
		{		
				
			
			/* element ID assignment of ChargingProfile*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=0;	
			/* encode start element ChargingProfile */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ChargingProfile */
			if(serialize_ChargingProfileType(&(type->ChargingProfile),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ChargingProfile */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_PowerDeliveryResType(struct PowerDeliveryResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.PowerDeliveryRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_MeteringStatusReqType(struct MeteringStatusReqType* type, struct v2gService* service)
{

	return 0;			
}


static int serialize_MeterInfoType(struct MeterInfoType* type, struct v2gService* service)
{if(type->isused.MeterID)
		{		
				
			
			/* element ID assignment of MeterID*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=16;	
			/* encode start element MeterID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->MeterID.arraylen.data;
			memcpy(service->val.string.codepoints, type->MeterID.data, service->val.string.len);
		
			/* encode character  MeterID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of MeterID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeterPubKey)
		{		
				
			
			/* element ID assignment of MeterPubKey*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=18;	
			/* encode start element MeterPubKey */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->MeterPubKey.arraylen.data;
		memcpy(service->val.binary.data, type->MeterPubKey.data, service->val.binary.len);
		
		/* encode character  MeterPubKey */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of MeterPubKey */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeterReading)
		{		
				
			
			/* element ID assignment of MeterReading*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=19;	
			/* encode start element MeterReading */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeterReading */
			if(serialize_FloatingValueType(&(type->MeterReading),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeterReading */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeterStatus)
		{		
				
			
			/* element ID assignment of MeterStatus*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=20;	
			/* encode start element MeterStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_16;
			service->val.int32=service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterStatus;
			
			/* encode character  MeterStatus */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of MeterStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.TMeter)
		{		
				
			
			/* element ID assignment of TMeter*/
			service->eqn.namespaceURI=5;			
			service->eqn.localPart=38;	
			/* encode start element TMeter */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.MeteringStatusRes.MeterInfo.TMeter;
			
			/* encode character  TMeter */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of TMeter */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_MeteringStatusResType(struct MeteringStatusResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.MeteringStatusRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=3;	
			/* encode start element EVSEID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			service->val.type = BINARY_HEX;
		service->val.binary.len = type->EVSEID.arraylen.data;
		memcpy(service->val.binary.data, type->EVSEID.data, service->val.binary.len);
		
		/* encode character  EVSEID */	
		if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
		{
				 
				return -1;
		}
			
			
			
			

			 
			
			/* encode end element of EVSEID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=7;	
			/* encode start element EVSEStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEStatus */
			if(serialize_EVSEStatusType(&(type->EVSEStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of TCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=63;	
			/* encode start element TCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.MeteringStatusRes.TCurrent;
			
			/* encode character  TCurrent */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of TCurrent */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of EVSEMaxPower*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=6;	
			/* encode start element EVSEMaxPower */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of EVSEMaxPower */
			if(serialize_FloatingValueType(&(type->EVSEMaxPower),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of EVSEMaxPower */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.PCurrent)
		{		
				
			
			/* element ID assignment of PCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=25;	
			/* encode start element PCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PCurrent */
			if(serialize_FloatingValueType(&(type->PCurrent),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PCurrent */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeterInfo)
		{		
				
			
			/* element ID assignment of MeterInfo*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=15;	
			/* encode start element MeterInfo */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeterInfo */
			if(serialize_MeterInfoType(&(type->MeterInfo),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeterInfo */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_MeteringReceiptReqType(struct MeteringReceiptReqType* type, struct v2gService* service)
{if(type->isused.PEVID)
		{		
				
			
			/* element ID assignment of PEVID*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=26;	
			/* encode start element PEVID */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = STRING;
			service->val.string.len = type->PEVID.arraylen.data;
			memcpy(service->val.string.codepoints, type->PEVID.data, service->val.string.len);
		
			/* encode character  PEVID */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
					return -1;
			}
			
			
			

			 
			
			/* encode end element of PEVID */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				
			
			/* element ID assignment of PEVStatus*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=32;	
			/* encode start element PEVStatus */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PEVStatus */
			if(serialize_PEVStatusType(&(type->PEVStatus),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PEVStatus */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}if(type->isused.TCurrent)
		{		
				
			
			/* element ID assignment of TCurrent*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=63;	
			/* encode start element TCurrent */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = INTEGER_64;
			service->val.int64=service->v2gMsg.Body.MeteringReceiptReq.TCurrent;
			
			/* encode character  TCurrent */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of TCurrent */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				
			
			/* element ID assignment of Tariff*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=64;	
			/* encode start element Tariff */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.MeteringReceiptReq.Tariff;
			
			/* encode character  Tariff */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of Tariff */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of MeterInfo*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=15;	
			/* encode start element MeterInfo */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeterInfo */
			if(serialize_MeterInfoType(&(type->MeterInfo),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeterInfo */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_MeteringReceiptResType(struct MeteringReceiptResType* type, struct v2gService* service)
{
			
			/* element ID assignment of ResponseCode*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=47;	
			/* encode start element ResponseCode */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			service->val.type = ENUMERATION;
			service->val.enumeration=service->v2gMsg.Body.MeteringReceiptRes.ResponseCode;
			
			/* encode character  ResponseCode */	
			if (exiEncodeCharacters(&(service->outStream), &(service->stateEncode), &(service->val)) < 0) 
			{
				 
				return -1;
			}
				
			

			 
			
			/* encode end element of ResponseCode */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}


static int serialize_BodyType(struct BodyType* type, struct v2gService* service)
{if(type->isused.SessionSetupReq)
		{		
				
			
			/* element ID assignment of SessionSetupReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=59;	
			/* encode start element SessionSetupReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of SessionSetupReq */
			if(serialize_SessionSetupReqType(&(type->SessionSetupReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of SessionSetupReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.SessionSetupRes)
		{		
				
			
			/* element ID assignment of SessionSetupRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=61;	
			/* encode start element SessionSetupRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of SessionSetupRes */
			if(serialize_SessionSetupResType(&(type->SessionSetupRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of SessionSetupRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServiceDiscoveryReq)
		{		
				
			
			/* element ID assignment of ServiceDiscoveryReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=48;	
			/* encode start element ServiceDiscoveryReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ServiceDiscoveryReq */
			if(serialize_ServiceDiscoveryReqType(&(type->ServiceDiscoveryReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ServiceDiscoveryReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServiceDiscoveryRes)
		{		
				
			
			/* element ID assignment of ServiceDiscoveryRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=50;	
			/* encode start element ServiceDiscoveryRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ServiceDiscoveryRes */
			if(serialize_ServiceDiscoveryResType(&(type->ServiceDiscoveryRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ServiceDiscoveryRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServicePaymentSelectionReq)
		{		
				
			
			/* element ID assignment of ServicePaymentSelectionReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=53;	
			/* encode start element ServicePaymentSelectionReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ServicePaymentSelectionReq */
			if(serialize_ServicePaymentSelectionReqType(&(type->ServicePaymentSelectionReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ServicePaymentSelectionReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.ServicePaymentSelectionRes)
		{		
				
			
			/* element ID assignment of ServicePaymentSelectionRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=55;	
			/* encode start element ServicePaymentSelectionRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of ServicePaymentSelectionRes */
			if(serialize_ServicePaymentSelectionResType(&(type->ServicePaymentSelectionRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of ServicePaymentSelectionRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.PaymentDetailsReq)
		{		
				
			
			/* element ID assignment of PaymentDetailsReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=33;	
			/* encode start element PaymentDetailsReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PaymentDetailsReq */
			if(serialize_PaymentDetailsReqType(&(type->PaymentDetailsReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PaymentDetailsReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.PaymentDetailsRes)
		{		
				
			
			/* element ID assignment of PaymentDetailsRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=35;	
			/* encode start element PaymentDetailsRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PaymentDetailsRes */
			if(serialize_PaymentDetailsResType(&(type->PaymentDetailsRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PaymentDetailsRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.PowerDiscoveryReq)
		{		
				
			
			/* element ID assignment of PowerDiscoveryReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=41;	
			/* encode start element PowerDiscoveryReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PowerDiscoveryReq */
			if(serialize_PowerDiscoveryReqType(&(type->PowerDiscoveryReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PowerDiscoveryReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.PowerDiscoveryRes)
		{		
				
			
			/* element ID assignment of PowerDiscoveryRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=43;	
			/* encode start element PowerDiscoveryRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PowerDiscoveryRes */
			if(serialize_PowerDiscoveryResType(&(type->PowerDiscoveryRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PowerDiscoveryRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.LineLockReq)
		{		
				
			
			/* element ID assignment of LineLockReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=11;	
			/* encode start element LineLockReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of LineLockReq */
			if(serialize_LineLockReqType(&(type->LineLockReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of LineLockReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.LineLockRes)
		{		
				
			
			/* element ID assignment of LineLockRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=13;	
			/* encode start element LineLockRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of LineLockRes */
			if(serialize_LineLockResType(&(type->LineLockRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of LineLockRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.PowerDeliveryReq)
		{		
				
			
			/* element ID assignment of PowerDeliveryReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=37;	
			/* encode start element PowerDeliveryReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PowerDeliveryReq */
			if(serialize_PowerDeliveryReqType(&(type->PowerDeliveryReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PowerDeliveryReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.PowerDeliveryRes)
		{		
				
			
			/* element ID assignment of PowerDeliveryRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=39;	
			/* encode start element PowerDeliveryRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of PowerDeliveryRes */
			if(serialize_PowerDeliveryResType(&(type->PowerDeliveryRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of PowerDeliveryRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeteringStatusReq)
		{		
				
			
			/* element ID assignment of MeteringStatusReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=21;	
			/* encode start element MeteringStatusReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeteringStatusReq */
			if(serialize_MeteringStatusReqType(&(type->MeteringStatusReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeteringStatusReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeteringStatusRes)
		{		
				
			
			/* element ID assignment of MeteringStatusRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=23;	
			/* encode start element MeteringStatusRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeteringStatusRes */
			if(serialize_MeteringStatusResType(&(type->MeteringStatusRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeteringStatusRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeteringReceiptReq)
		{		
				
			
			/* element ID assignment of MeteringReceiptReq*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=17;	
			/* encode start element MeteringReceiptReq */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeteringReceiptReq */
			if(serialize_MeteringReceiptReqType(&(type->MeteringReceiptReq),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeteringReceiptReq */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				if(type->isused.MeteringReceiptRes)
		{		
				
			
			/* element ID assignment of MeteringReceiptRes*/
			service->eqn.namespaceURI=4;			
			service->eqn.localPart=19;	
			/* encode start element MeteringReceiptRes */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of MeteringReceiptRes */
			if(serialize_MeteringReceiptResType(&(type->MeteringReceiptRes),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of MeteringReceiptRes */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}}
				

	return 0;			
}


static int serialize_AnonType_V2G_Message(struct AnonType_V2G_Message* type, struct v2gService* service)
{
			
			/* element ID assignment of Header*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=4;	
			/* encode start element Header */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of Header */
			if(serialize_HeaderType(&(type->Header),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of Header */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
			
			/* element ID assignment of Body*/
			service->eqn.namespaceURI=6;			
			service->eqn.localPart=0;	
			/* encode start element Body */	
			if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}
						
			/* encode children of Body */
			if(serialize_BodyType(&(type->Body),service)<0)
			{
				return -1;
			}

			
			

			 
			
			/* encode end element of Body */
			if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
			{
				 
					return -1;
			}

	return 0;			
}

 
 
 
 
 
 /* marshal data to EXI stream */
 int serialize_message(struct v2gService* service)
 {
	

	/* encode start document */ 	
	if (exiEncodeStartDocument(&(service->outStream), &(service->stateEncode)) < 0) 
	{
	 
		return -1;
	}

	/* element ID assignment of V2G_Message*/
	service->eqn.namespaceURI=6;			
	service->eqn.localPart=8;
	
	/* encode start element V2G_Message */	
	if (exiEncodeStartElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
	{
			 
		return -1;
	}
		

	serialize_AnonType_V2G_Message(&(service->v2gMsg), service);

			
	/* encode end element of V2G_Message */
	if (exiEncodeEndElement(&(service->outStream), &(service->stateEncode), &(service->eqn)) < 0) 
	{
			 
		return -1;
	}


	/* encode end document */
	if (exiEncodeEndDocument(&(service->outStream), &(service->stateEncode)) < 0) {
	 
	return -1;
	}	
 	
 	return 0;
 	
 }
