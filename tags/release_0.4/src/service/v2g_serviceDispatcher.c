


/*
 * Copyright (C) 2007-2011 Siemens AG
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
 * @version 0.3.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/


#include "v2g_service.h"
#include "v2g_serviceDispatcher.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceDataTypes.c"
#include "v2g_serviceMethods.h"
#include "v2g_serviceDataSerialization.c"
#include "EXITypes.h"
#include "EXIDecoder.h"
#include "EXIEncoder.h"


static int deserializeMessage(struct EXIService* service);

/**
 * Deserialize an element value of the EXI stream and assign it to the
 * service data structure 
 */
static int deserializeElementCharacter(struct EXIService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 43: /*PEVID*/
		if(service->val.type == STRING) 
					{
						if( service->idPath.id[2] == 78)
						{
							memcpy(service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVID.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.SessionSetupReq->isused.PEVID=1;

						} else if(service->idPath.id[2] == 33)
						{
							memcpy(service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVID.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->isused.PEVID=1;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 77: /*ServiceType*/
		if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->ServiceType = service->val.enumeration;
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->isused.ServiceType=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 76: /*ServiceScope*/
		if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->ServiceScope.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->ServiceScope.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->isused.ServiceScope=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 9: /*ContractID*/
		if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.PaymentDetailsReq->ContractID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.PaymentDetailsReq->ContractID.arraylen.data = service->val.string.len;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 8: /*ChargingMode*/
		if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->ChargingMode = service->val.enumeration;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 27: /*EoC*/
		if(service->val.type == INTEGER_32) 
					{
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->EoC = service->val.int32;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 45: /*PEVMaxPhases*/
		if(service->val.type == INTEGER_16) 
					{
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxPhases = service->val.int32;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 64: /*ReqLockStatus*/
		if(service->val.type == BOOLEAN) 
					{
						service->exiMsg.V2G_Message.Body.LineLockReq->ReqLockStatus = service->val.boolean;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 65: /*ReqSwitchStatus*/
		if(service->val.type == BOOLEAN) 
					{
						service->exiMsg.V2G_Message.Body.PowerDeliveryReq->ReqSwitchStatus = service->val.boolean;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 83: /*Tariff*/
		if(service->val.type == ENUMERATION) 
					{
						if( service->idPath.id[2] == 56)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->Tariff = service->val.enumeration;
						service->exiMsg.V2G_Message.Body.PowerDeliveryReq->isused.Tariff=1;

						} else if(service->idPath.id[2] == 33)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->Tariff = service->val.enumeration;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 82: /*TCurrent*/
		if(service->val.type == INTEGER_32) 
					{
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->TCurrent = service->val.int32;
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->isused.TCurrent=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
		case 5:
			switch(service->eqn.localPart) {
				case 36: /*SessionID*/
		if(service->val.type == BINARY_HEX) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.SessionID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Header->SessionInformation.SessionID.arraylen.data = service->val.binary.len;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 34: /*ServiceSessionID*/
		if(service->val.type == BINARY_HEX) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.ServiceSessionID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Header->SessionInformation.ServiceSessionID.arraylen.data = service->val.binary.len;
						service->exiMsg.V2G_Message.Header->SessionInformation.isused.ServiceSessionID=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 25: /*ProtocolVersion*/
		if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.ProtocolVersion.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Header->SessionInformation.ProtocolVersion.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Header->SessionInformation.isused.ProtocolVersion=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 10: /*Event*/
		if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Header->Notification.EventList.Event = service->val.enumeration;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 14: /*FaultCode*/
		if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Header->Notification.FaultCode = service->val.enumeration;
						service->exiMsg.V2G_Message.Header->Notification.isused.FaultCode=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 15: /*FaultMsg*/
		if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->Notification.FaultMsg.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Header->Notification.FaultMsg.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Header->Notification.isused.FaultMsg=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 4: /*ConnectorLocked*/
		if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 78)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 4)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 28)
						{
							service->exiMsg.V2G_Message.Body.LineLockReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 56)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 33)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 0)
						{
							service->exiMsg.V2G_Message.Body.CableCheckReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 90)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionReq->PEVStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 85)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingReq->PEVStatus.ConnectorLocked = service->val.boolean;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 0: /*ChargerStandby*/
		if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 78)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 4)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 28)
						{
							service->exiMsg.V2G_Message.Body.LineLockReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 56)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 33)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 0)
						{
							service->exiMsg.V2G_Message.Body.CableCheckReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 90)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionReq->PEVStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 85)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingReq->PEVStatus.ChargerStandby = service->val.boolean;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 27: /*ReadyToCharge*/
		if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 78)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 4)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 28)
						{
							service->exiMsg.V2G_Message.Body.LineLockReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 56)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 33)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 0)
						{
							service->exiMsg.V2G_Message.Body.CableCheckReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 90)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionReq->PEVStatus.ReadyToCharge = service->val.boolean;

						} else if(service->idPath.id[2] == 85)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingReq->PEVStatus.ReadyToCharge = service->val.boolean;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 21: /*Multiplier*/
		if(service->val.type == INTEGER_16) 
					{
						if( service->idPath.id[3] == 15)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->EAmount.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 46)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxPower.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 47)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 49)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMinVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 44)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 48)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMinCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 51 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVTargetVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 42 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVDemandCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 89 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->VoltageDifferential.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 51 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVTargetVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 42 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVDemandCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 14)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->CurrentDifferential.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 89 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->VoltageDifferential.Multiplier = service->val.int32;

						} else if(service->idPath.id[4] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterReading.Multiplier = service->val.int32;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 52: /*Unit*/
		if(service->val.type == ENUMERATION) 
					{
						if( service->idPath.id[3] == 15)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->EAmount.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 46)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxPower.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 47)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 49)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMinVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 44)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 48)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMinCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 51 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVTargetVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 42 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVDemandCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 89 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->VoltageDifferential.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 51 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVTargetVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 42 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVDemandCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 14)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->CurrentDifferential.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 89 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->VoltageDifferential.Unit = service->val.enumeration;

						} else if(service->idPath.id[4] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterReading.Unit = service->val.enumeration;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 53: /*Value*/
		if(service->val.type == INTEGER_32) 
					{
						if( service->idPath.id[3] == 15)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->EAmount.Value = service->val.int32;

						} else if(service->idPath.id[3] == 46)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxPower.Value = service->val.int32;

						} else if(service->idPath.id[3] == 47)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 49)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMinVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 44)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMaxCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 48)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq->PEVMinCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 51 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVTargetVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 42 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->PEVDemandCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 89 && service->idPath.id[2] == 60)
						{
							service->exiMsg.V2G_Message.Body.PreChargeReq->VoltageDifferential.Value = service->val.int32;

						} else if(service->idPath.id[3] == 51 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVTargetVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 42 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->PEVDemandCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 14)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->CurrentDifferential.Value = service->val.int32;

						} else if(service->idPath.id[3] == 89 && service->idPath.id[2] == 10)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandReq->VoltageDifferential.Value = service->val.int32;

						} else if(service->idPath.id[4] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterReading.Value = service->val.int32;
						}


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 17: /*MeterID*/
		if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterID.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.isused.MeterID=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 20: /*MeterStatus*/
		if(service->val.type == INTEGER_16) 
					{
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterStatus = service->val.int32;
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.isused.MeterStatus=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;
				case 40: /*TMeter*/
		if(service->val.type == INTEGER_32) 
					{
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.TMeter = service->val.int32;
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.isused.TMeter=1;


					} 
					else
					{
						return -1; /* wrong data type */
					}

				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
	
	} /* close switch(service->eqn.namespaceURI) */
	return 0;
}

/**
 * Depending on the current EXI event a message element is deserialized or a
 * defined service method is called in here
 */
static int deserializeElementOrServiceCall(struct EXIService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 78:/* SessionSetupReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					sessionSetup((service->exiMsg.V2G_Message.Body.SessionSetupReq), (service->exiMsg.V2G_Message.Body.SessionSetupRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.SessionSetupRes=1;
					service->exiMsg.V2G_Message.Body.isused.SessionSetupReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 67:/* ServiceDiscoveryReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					serviceDiscovery((service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq), (service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.ServiceDiscoveryRes=1;
					service->exiMsg.V2G_Message.Body.isused.ServiceDiscoveryReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 72:/* ServicePaymentSelectionReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					selectedServicePayment((service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq), (service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.ServicePaymentSelectionRes=1;
					service->exiMsg.V2G_Message.Body.isused.ServicePaymentSelectionReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 52:/* PaymentDetailsReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					paymentDetails((service->exiMsg.V2G_Message.Body.PaymentDetailsReq), (service->exiMsg.V2G_Message.Body.PaymentDetailsRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.PaymentDetailsRes=1;
					service->exiMsg.V2G_Message.Body.isused.PaymentDetailsReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 4:/* ChargeParameterDiscoveryReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					chargeParameterDiscovery((service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq), (service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.ChargeParameterDiscoveryRes=1;
					service->exiMsg.V2G_Message.Body.isused.ChargeParameterDiscoveryReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 28:/* LineLockReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					lineLock((service->exiMsg.V2G_Message.Body.LineLockReq), (service->exiMsg.V2G_Message.Body.LineLockRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.LineLockRes=1;
					service->exiMsg.V2G_Message.Body.isused.LineLockReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 56:/* PowerDeliveryReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					powerDelivery((service->exiMsg.V2G_Message.Body.PowerDeliveryReq), (service->exiMsg.V2G_Message.Body.PowerDeliveryRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.PowerDeliveryRes=1;
					service->exiMsg.V2G_Message.Body.isused.PowerDeliveryReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 37:/* MeteringStatusReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					meteringStatus((service->exiMsg.V2G_Message.Body.MeteringStatusReq), (service->exiMsg.V2G_Message.Body.MeteringStatusRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.MeteringStatusRes=1;
					service->exiMsg.V2G_Message.Body.isused.MeteringStatusReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 33:/* MeteringReceiptReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					meteringReceipt((service->exiMsg.V2G_Message.Body.MeteringReceiptReq), (service->exiMsg.V2G_Message.Body.MeteringReceiptRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.MeteringReceiptRes=1;
					service->exiMsg.V2G_Message.Body.isused.MeteringReceiptReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 0:/* CableCheckReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					cableCheck((service->exiMsg.V2G_Message.Body.CableCheckReq), (service->exiMsg.V2G_Message.Body.CableCheckRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.CableCheckRes=1;
					service->exiMsg.V2G_Message.Body.isused.CableCheckReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 60:/* PreChargeReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					preCharge((service->exiMsg.V2G_Message.Body.PreChargeReq), (service->exiMsg.V2G_Message.Body.PreChargeRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.PreChargeRes=1;
					service->exiMsg.V2G_Message.Body.isused.PreChargeReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 10:/* CurrentDemandReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					currentDemand((service->exiMsg.V2G_Message.Body.CurrentDemandReq), (service->exiMsg.V2G_Message.Body.CurrentDemandRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.CurrentDemandRes=1;
					service->exiMsg.V2G_Message.Body.isused.CurrentDemandReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 90:/* WeldingDetectionReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					weldingDetection((service->exiMsg.V2G_Message.Body.WeldingDetectionReq), (service->exiMsg.V2G_Message.Body.WeldingDetectionRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.WeldingDetectionRes=1;
					service->exiMsg.V2G_Message.Body.isused.WeldingDetectionReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 85:/* TerminateChargingReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					terminateCharging((service->exiMsg.V2G_Message.Body.TerminateChargingReq), (service->exiMsg.V2G_Message.Body.TerminateChargingRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.TerminateChargingRes=1;
					service->exiMsg.V2G_Message.Body.isused.TerminateChargingReq=0;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
			}
		break;
		case 5:
			switch(service->eqn.localPart) {
				case 11:/* EventList */	
	
 					service->exiMsg.V2G_Message.Header->Notification.isused.EventList=1;

				break;
				case 28:/* Service */	
	
 					service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq->ServiceList.arraylen.Service++;

				break;
				case 19:/* MeterReading */	
	
 					service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.isused.MeterReading=1;

				break;
			}
		break;
		case 7:
			switch(service->eqn.localPart) {
				case 1:/* Notification */	
	
 					service->exiMsg.V2G_Message.Header->isused.Notification=1;

				break;
			}
		break;
		

	}
	return 0;
}

static int deserializeSessionSetupReqMsg(struct EXIService* service)
{
	struct SessionSetupReqType reqMsg;
	struct SessionSetupResType resMsg;
	init_SessionSetupReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.SessionSetupReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.SessionSetupRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeServiceDiscoveryReqMsg(struct EXIService* service)
{
	struct ServiceDiscoveryReqType reqMsg;
	struct ServiceDiscoveryResType resMsg;
	init_ServiceDiscoveryReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeServicePaymentSelectionReqMsg(struct EXIService* service)
{
	struct ServicePaymentSelectionReqType reqMsg;
	struct ServicePaymentSelectionResType resMsg;
	service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializePaymentDetailsReqMsg(struct EXIService* service)
{
	struct PaymentDetailsReqType reqMsg;
	struct PaymentDetailsResType resMsg;
	service->exiMsg.V2G_Message.Body.PaymentDetailsReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.PaymentDetailsRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeChargeParameterDiscoveryReqMsg(struct EXIService* service)
{
	struct ChargeParameterDiscoveryReqType reqMsg;
	struct ChargeParameterDiscoveryResType resMsg;
	init_ChargeParameterDiscoveryReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeLineLockReqMsg(struct EXIService* service)
{
	struct LineLockReqType reqMsg;
	struct LineLockResType resMsg;
	init_LineLockReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.LineLockReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.LineLockRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializePowerDeliveryReqMsg(struct EXIService* service)
{
	struct PowerDeliveryReqType reqMsg;
	struct PowerDeliveryResType resMsg;
	init_PowerDeliveryReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.PowerDeliveryReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.PowerDeliveryRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeMeteringStatusReqMsg(struct EXIService* service)
{
	struct MeteringStatusReqType reqMsg;
	struct MeteringStatusResType resMsg;
	service->exiMsg.V2G_Message.Body.MeteringStatusReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.MeteringStatusRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeMeteringReceiptReqMsg(struct EXIService* service)
{
	struct MeteringReceiptReqType reqMsg;
	struct MeteringReceiptResType resMsg;
	init_MeteringReceiptReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.MeteringReceiptReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.MeteringReceiptRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeCableCheckReqMsg(struct EXIService* service)
{
	struct CableCheckReqType reqMsg;
	struct CableCheckResType resMsg;
	service->exiMsg.V2G_Message.Body.CableCheckReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.CableCheckRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializePreChargeReqMsg(struct EXIService* service)
{
	struct PreChargeReqType reqMsg;
	struct PreChargeResType resMsg;
	init_PreChargeReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.PreChargeReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.PreChargeRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeCurrentDemandReqMsg(struct EXIService* service)
{
	struct CurrentDemandReqType reqMsg;
	struct CurrentDemandResType resMsg;
	init_CurrentDemandReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.CurrentDemandReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.CurrentDemandRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeWeldingDetectionReqMsg(struct EXIService* service)
{
	struct WeldingDetectionReqType reqMsg;
	struct WeldingDetectionResType resMsg;
	service->exiMsg.V2G_Message.Body.WeldingDetectionReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.WeldingDetectionRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeTerminateChargingReqMsg(struct EXIService* service)
{
	struct TerminateChargingReqType reqMsg;
	struct TerminateChargingResType resMsg;
	service->exiMsg.V2G_Message.Body.TerminateChargingReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.TerminateChargingRes = &resMsg;
	
	return deserializeMessage(service);
}

/** 
 * Deserialize the EXI stream
 * @return 0 = 0K; -1 = ERROR
 */
static int deserializeMessage(struct EXIService* service)
{
	int noEndOfDocument = 1; /* true */
	int returnCode=0;


	do {
			exiDecodeNextEvent(&(service->inStream), &(service->stateDecode), &(service->event));
			if (returnCode) 
			{
				
				if(service->errorCode==0) 
				{
					service->errorCode= EXI_NON_VALID_MESSAGE;
				}
			
				return returnCode;
			}

			switch (service->event) {
			case START_DOCUMENT:

				returnCode = exiDecodeStartDocument(&(service->inStream), &(service->stateDecode));

				break;
			case END_DOCUMENT:

				returnCode = exiDecodeEndDocument(&(service->inStream), &(service->stateDecode));
				noEndOfDocument = 0; /* false */
				break;
			case START_ELEMENT:
				returnCode = exiDecodeStartElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				service->idPath.id[service->idPath.pos++]=service->eqn.localPart;
				 
				 /* setup the request context*/
				 if(service->eqn.localPart==78 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeSessionSetupReqMsg(service);
				   } else if(service->eqn.localPart==67 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeServiceDiscoveryReqMsg(service);
				   } else if(service->eqn.localPart==72 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeServicePaymentSelectionReqMsg(service);
				   } else if(service->eqn.localPart==52 && service->eqn.namespaceURI==4)
				  {
				 	return deserializePaymentDetailsReqMsg(service);
				   } else if(service->eqn.localPart==4 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeChargeParameterDiscoveryReqMsg(service);
				   } else if(service->eqn.localPart==28 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeLineLockReqMsg(service);
				   } else if(service->eqn.localPart==56 && service->eqn.namespaceURI==4)
				  {
				 	return deserializePowerDeliveryReqMsg(service);
				   } else if(service->eqn.localPart==37 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeMeteringStatusReqMsg(service);
				   } else if(service->eqn.localPart==33 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeMeteringReceiptReqMsg(service);
				   } else if(service->eqn.localPart==0 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeCableCheckReqMsg(service);
				   } else if(service->eqn.localPart==60 && service->eqn.namespaceURI==4)
				  {
				 	return deserializePreChargeReqMsg(service);
				   } else if(service->eqn.localPart==10 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeCurrentDemandReqMsg(service);
				   } else if(service->eqn.localPart==90 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeWeldingDetectionReqMsg(service);
				   } else if(service->eqn.localPart==85 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeTerminateChargingReqMsg(service);
				   } 				 
				 
				 
				break;
			case END_ELEMENT:

				returnCode = exiDecodeEndElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				returnCode = deserializeElementOrServiceCall(service);
				service->idPath.pos--;
				 
				break;
			case CHARACTERS:
				/* decode */
				returnCode = exiDecodeCharacters(&(service->inStream), &(service->stateDecode), &(service->val));
				 
				/* assign data to the EXI message structure */
				returnCode = deserializeElementCharacter(service);
				break;
			case ATTRIBUTE:
				/* decode */
				/*	returnCode = exiDecodeAttribute(&isStream, &stateDecode, &eqn, &val); */
				break;
			default:
				/* ERROR */
				return -1;
			}

		} while (noEndOfDocument);

	return 0;
}


/** 
 * \brief Takes the EXI stream, invokes the called service method, and provides the response EXI stream
 * \param	service   struct EXIService* Represent the service data structure
 * \param	inStream   uint8_t* EXI in stream
 * \param	sizeInStream   uint16_t Length of the inStream
 * \param	outStream   uint8_t* Represent the out stream
 * \param	sizeOutStream   uint16_t Size of the out stream
 * \param	outStreamLength   uint16_t* Length of the stream
 * \return  0 = 0K; -1 = ERROR
 */
int messageDispatcher(struct EXIService* service, uint8_t* inStream, uint16_t sizeInStream, uint8_t* outStream, uint16_t sizeOutStream, uint16_t* outStreamLength)
{
	struct HeaderType header;	

	
	uint16_t inPos, outPos;
	
	/* assign inStream data to service EXI structure */
	inPos = service->transportHeaderOffset;
	service->inStream.data = inStream;
	service->inStream.size = sizeInStream+inPos;
	service->inStream.pos = &inPos;
	service->inStream.buffer=0;
	service->inStream.capacity=0;

	
	/* assign outStream data to service EXI structure */
	outPos=service->transportHeaderOffset;
	service->outStream.data = outStream;
	service->outStream.size = sizeOutStream;
	service->outStream.pos = &outPos;
	service->outStream.buffer=0;
	service->outStream.capacity=8;
	
	/* clear error code */
	service->errorCode = 0;
	
	/* init EXI decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));
	
	/* init EXI encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init uniqueID stack */
	service->idPath.pos=0;

	init_HeaderType(&header);
	service->exiMsg.V2G_Message.Header = &header;	

	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));

	/* deserialize the input stream and call the corresponding service */
	if(deserializeMessage(service))
	{
		return -1; /* something went wrong */
	}

	/* determine payload size (without transport offset) */	
	outPos -= service->transportHeaderOffset;
	*outStreamLength = outPos;

	
	return 0;
}

/** 
 * \brief Init the v2g service data structure
 * \param	service   struct EXIService* Service data structure
 * \param	bytes   bytes_t setted up byte data structure
 * \param	string_ucs_t   setted up string data structure
 * \param	transportHeaderOffset uint16_t Transport protocol offset
 * \return  0 = 0K; -1 = ERROR
 */
int init_v2gservice(struct EXIService* service, bytes_t bytes, string_ucs_t string, uint16_t transportHeaderOffset)
{

	/* init byte array */
	 service->val.binary = bytes;

	/* init string array */
	 service->val.string = string;

	/* init offset for transport protocoll */
	 service->transportHeaderOffset=transportHeaderOffset;

	return 0;
}
