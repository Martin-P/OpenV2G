
/*******************************************************************
 * Command line interface for OpenV2G
 * Maintained in http://github.com/uhi22/OpenV2Gx, a fork of https://github.com/Martin-P/OpenV2G
 *
 ********************************************************************/

/* Question1: Where to find information regarding the message structures?
 1. Search in the related decoder header files. There is a c structure definition for each message type,
    which contains all elements.
 2. Look into the "official" xsd schema file. This can be found e.g. in
    https://github.com/FlUxIuS/V2Gdecoder/tree/master/schemas_din
 */

/* Question2: Are units for physical values optional? 
 Yes, in DIN they are optional, according to https://github.com/FlUxIuS/V2Gdecoder/blob/master/schemas_din/V2G_CI_MsgDataTypes.xsd
 the unit has the attribute minOccurs="0":
 	<!-- 					   -->
	<!-- Physical value type   -->
	<!-- 					   -->
	<xs:complexType name="PhysicalValueType">
		<xs:sequence>
			<xs:element name="Multiplier" type="unitMultiplierType"/>
			<xs:element name="Unit" type="unitSymbolType" minOccurs="0"/>
			<xs:element name="Value" type="xs:short"/>
		</xs:sequence>
	</xs:complexType>
  On the other hand, for the ISO schemas, the unit is NOT optional, see https://github.com/FlUxIuS/V2Gdecoder/blob/master/schemas/V2G_CI_MsgDataTypes.xsd
  <xs:complexType name="PhysicalValueType">
   <xs:sequence>
    <xs:element name="Multiplier" type="unitMultiplierType"/>
    <xs:element name="Unit" type="unitSymbolType"/>
    <xs:element name="Value" type="xs:short"/>
   </xs:sequence>
  </xs:complexType>
*/
	
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <string.h>

#include "EXITypes.h"

#include "appHandEXIDatatypes.h"
#include "appHandEXIDatatypesEncoder.h"
#include "appHandEXIDatatypesDecoder.h"

/* Activate support for DIN */
#include "dinEXIDatatypes.h"
#if DEPLOY_DIN_CODEC == SUPPORT_YES
#include "dinEXIDatatypesEncoder.h"
#include "dinEXIDatatypesDecoder.h"
#endif /* DEPLOY_DIN_CODEC == SUPPORT_YES */

/* Activate support for XMLDSIG */
#include "xmldsigEXIDatatypes.h"
#if DEPLOY_XMLDSIG_CODEC == SUPPORT_YES
#include "xmldsigEXIDatatypesEncoder.h"
#include "xmldsigEXIDatatypesDecoder.h"
#endif /* DEPLOY_XMLDSIG_CODEC == SUPPORT_YES */

/* Activate support for ISO1 */
#include "iso1EXIDatatypes.h"
#if DEPLOY_ISO1_CODEC == SUPPORT_YES
#include "iso1EXIDatatypesEncoder.h"
#include "iso1EXIDatatypesDecoder.h"
#endif /* DEPLOY_ISO1_CODEC == SUPPORT_YES */

/* Activate support for ISO2 */
#include "iso2EXIDatatypes.h"
#if DEPLOY_ISO2_CODEC == SUPPORT_YES
#include "iso2EXIDatatypesEncoder.h"
#include "iso2EXIDatatypesDecoder.h"
#endif /* DEPLOY_ISO2_CODEC == SUPPORT_YES */

#include "v2gtp.h"

struct appHandEXIDocument aphsDoc;
struct dinEXIDocument dinDoc;
struct iso1EXIDocument iso1Doc;
struct iso2EXIDocument iso2Doc;

#define BUFFER_SIZE 256
uint8_t mybuffer[BUFFER_SIZE];
bitstream_t global_stream1;
size_t global_pos1;
int g_errn;
char gMessageName[200];
char gResultString[4096];
char gInfoString[4096];
char gErrorString[4096];
char gPropertiesString[10000];
char gDebugString[20000];
char s[1000];
char gAdditionalParamList[1000];
#define NUM_OF_ADDITIONAL_PARAMS 5
char gAdditionalParam[NUM_OF_ADDITIONAL_PARAMS][100];
uint8_t nNumberOfFoundAdditionalParameters;
#define MAX_LEN_OF_SESSION_ID 8 /* session ID has 8 bytes (may be longer, but the Ioniq uses 8 bytes) */
uint8_t gLenOfSessionId=8; /* The dynamic length of the session ID. E.g. superChargerV3 use 4 bytes (8 hex characters), other chargers use 8 bytes (16 hex characters) */
uint8_t gSessionID[MAX_LEN_OF_SESSION_ID]={1, 2, 3, 4, 5, 6, 7, 8}; /* default value in case we are the charger. May be overwritten by command line. */

#define LEN_OF_EVCCID 6 /* The EVCCID is the MAC according to spec. Ioniq uses exactly these 6 byte. */
uint8_t EVCCID[LEN_OF_EVCCID];

#define ERROR_UNEXPECTED_REQUEST_MESSAGE -601
#define ERROR_UNEXPECTED_SESSION_SETUP_RESP_MESSAGE -602
#define ERROR_UNEXPECTED_SERVICE_DISCOVERY_RESP_MESSAGE -602
#define ERROR_UNEXPECTED_SERVICE_DETAILS_RESP_MESSAGE -603
#define ERROR_UNEXPECTED_PAYMENT_SERVICE_SELECTION_RESP_MESSAGE -604
#define ERROR_UNEXPECTED_PAYMENT_DETAILS_RESP_MESSAGE -605
#define ERROR_UNEXPECTED_AUTHORIZATION_RESP_MESSAGE -606
#define ERROR_UNEXPECTED_CHARGE_PARAMETER_DISCOVERY_RESP_MESSAGE -607
#define ERROR_UNEXPECTED_POWER_DELIVERY_RESP_MESSAGE -608
#define ERROR_UNEXPECTED_CHARGING_STATUS_RESP_MESSAGE -609
#define ERROR_UNEXPECTED_METERING_RECEIPT_RESP_MESSAGE -610
#define ERROR_UNEXPECTED_SESSION_STOP_RESP_MESSAGE -611
#define ERROR_UNEXPECTED_CABLE_CHECK_RESP_MESSAGE -612
#define ERROR_UNEXPECTED_PRE_CHARGE_RESP_MESSAGE -612
#define ERROR_UNEXPECTED_CURRENT_DEMAND_RESP_MESSAGE -613
#define ERROR_UNEXPECTED_WELDING_DETECTION_RESP_MESSAGE -614




void debugAddStringAndInt(char *s, int i) {
	char sTmp[1000];
	sprintf(sTmp, "%s%d", s, i);
	strcat(gDebugString, sTmp);
}

/*
static int writeStringToEXIString(char* string, exi_string_character_t* exiString) {
	int pos = 0;
	while(string[pos]!='\0')
	{
		exiString[pos] = string[pos];
		pos++;
	}
	return pos;
}
*/

static void printASCIIString(exi_string_character_t* string, uint16_t len) {
	unsigned int i;
	char strShort[10];
	strcpy(s, "");
	for(i=0; i<len; i++) {
		sprintf(strShort, "%c",(char)string[i]);
		strcat(s, strShort);
	}
	//printf("\n");
}

/*
static void printBinaryArray(uint8_t* byte, uint16_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%d ",byte[i]);
	}
	printf("\n");
}
*/

/*
static void copyBytes(uint8_t* from, uint16_t len, uint8_t* to) {
	int i;
	for(i=0; i<len; i++) {
		to[i] = from[i];
	}
}
*/

/* prepare an empty stream */
static void prepareGlobalStream(void) {
	global_stream1.size = BUFFER_SIZE;
	global_stream1.data = mybuffer;
	global_stream1.pos = &global_pos1;	
	*(global_stream1.pos) = 0; /* start adding data at position 0 */	
}

/* print the global stream into the result string */
void printGlobalStream(void) {
	int i;
	char strTmp[10];	
	if (g_errn!=0) {
		sprintf(gErrorString, "encoding failed %d", g_errn);
	} else {
		strcpy(gResultString, "");
		/* byte per byte, write a two-character-hex value into the result string */
		for (i=0; i<*global_stream1.pos; i++) {
			sprintf(strTmp, "%02x", global_stream1.data[i]);
			strcat(gResultString, strTmp);
		}
	}	
}

void initProperties(void) {
	strcpy(gPropertiesString, "");
}

/* add to the JSON properties string a new line with name and value, e.g.
    , "responseCode": "ok"
*/	
void addProperty(char *strPropertyName, char *strPropertyValue) {
	strcat(gPropertiesString, ",\n\"");
	strcat(gPropertiesString, strPropertyName);
	strcat(gPropertiesString, "\": \"");
	strcat(gPropertiesString, strPropertyValue);
	strcat(gPropertiesString, "\"");	
}

void addMessageName(char *messagename) {
	strcpy(gMessageName, messagename);
}

/* parsing of command line argument, extracting the single parameters. */
/* Examples for command lines:
  (1) OpenV2G.exe EDg_350
  (2) OpenV2G.exe EDx_380_2_something_
  Input: The parameter list, in the examples "_350" or "_380_2_something_".
  The parameter must be separated by underscores.
  Output: Array of strings containing the paramters, and the number of parameters in nNumberOfFoundAdditionalParameters
 */
void parseAdditionalParameters(void) {
  int i,k, iParamNumber;
  int a, b;
  char s[1000];
  nNumberOfFoundAdditionalParameters = 0;
  if (gAdditionalParamList[strlen(gAdditionalParamList)-1]!='_') {
	  strcat(gAdditionalParamList, "_");
  }
  for (iParamNumber=0; iParamNumber<NUM_OF_ADDITIONAL_PARAMS; iParamNumber++) {
	a=-1;
	b=-1;
	for (i=0; i<strlen(gAdditionalParamList); i++) {
		if ((gAdditionalParamList[i]=='_') && (a>=0) && (b==-1)) b=i; /* the index of the second underscore */
		if ((gAdditionalParamList[i]=='_') && (a==-1)) a=i; /* the index of the first underscore */
	}
	//printf("parameter search indexes %d %d\n", a, b);
	if ((a>=0) && (b>a+1)) {
		/* we have a valid start index and end index. Means: we have a parameter. */
		nNumberOfFoundAdditionalParameters++;
		k=0;
		for (i=a+1; i<b; i++) { /* copy the parameter from the list to a local string */
			s[k]=gAdditionalParamList[i];
			k++;
		}
		s[k]=0; /* add terminating zero */
		gAdditionalParamList[a] = ' '; /* replace the leading underscore of the current parameter by blank, so it will be skipped in the next round. */
		strcpy(gAdditionalParam[iParamNumber], s);
		//printf("Parameter is >%s<\n", s);
	}
  }
  //printf("We have %d additional parameters.\n", nNumberOfFoundAdditionalParameters);
  for (i=0; i<nNumberOfFoundAdditionalParameters; i++) {
	  sprintf(s, "parameter%d", i);
	  addProperty(s, gAdditionalParam[i]);
  }
}

/* Get the element k of the gAdditionalParam, and convert it into int. */
/* In case the element is not available, we return value 0 and set the gErrorString. */
/* In case the element is no number, we return 0. */
int getIntParam(uint8_t k) {
	int retval;
	if (k>=nNumberOfFoundAdditionalParameters) {
		sprintf(gErrorString, "Too less parameters to handle getIntParam(%d)", k);
		return 0;
	}
	retval = atoi(gAdditionalParam[k]);
	//printf("getIntParam %d returns %d\n", k, retval);
	return retval;
}

/* If we are PEV, we need to use the sessionID which was decided by the charger.
   This sessionID must be given on command line for each relevant message.
   Here, we check whether the parameter has the correct format and if yes, we transfer
   the sessionID to a global variable, which will later be used to fill the encoder input structure. */
void useSessionIdFromCommandLine(void) {
	char s3[3];
	int i;
	uint8_t x;
	
	/* for the case, that the command line does not provide a valid sessionID, we set here a marker to detect the issue */
	gSessionID[0] = 0xDE;
	gSessionID[1] = 0xAD;
	gSessionID[2] = 0xBE;
	gSessionID[3] = 0xEF;
	gSessionID[4] = 0xDE;
	gSessionID[5] = 0xAD;
	gSessionID[6] = 0xBE;
	gSessionID[7] = 0xEF;
	gLenOfSessionId = 8; /* just as default value to show deadbeefdeadbeef */
	
	if (nNumberOfFoundAdditionalParameters>0) {
		gLenOfSessionId = strlen(gAdditionalParam[0]) / 2; /* two hex chars are forming one byte */
		if ((gLenOfSessionId>0) && (gLenOfSessionId<=MAX_LEN_OF_SESSION_ID)) { /* normal chargers use 8 bytes SessionID. SuperCharger use 4 bytes. */
			for (i=0; i<gLenOfSessionId; i++) { /* run through 8 bytes */
				/* take 2 characters from the parameter, and convert them into a byte */
				s3[0] = gAdditionalParam[0][2*i];
				s3[1] = gAdditionalParam[0][2*i+1];
				s3[2] = 0;
				x = strtol(s3, NULL, 16); /* convert the two-character hex to a uint8. If this fails, we get 0. Good enough. */
				//printf("%02x,  ", x);
				gSessionID[i]=x;
			}
		} else {
			sprintf(gErrorString, "useSessionIdFromCommandLine: wrong length of sessionID in first parameter. Expected 16 or 8 hex characters.");
			gLenOfSessionId = 8; /* just as default value to show deadbeefdeadbeef */
		}
	} else {
		sprintf(gErrorString, "useSessionIdFromCommandLine: too less parameters");
	}

}

/* If we are PEV, we need to use the EVCCID.
   This EVCCID must be given on command line for the SessionSetupReq.
   Here, we check whether the parameter has the correct format and if yes, we transfer
   the EVCCID to a global variable, which will later be used to fill the encoder input structure. */
void useEVCCIDFromCommandLine(void) {
	char s3[3];
	int i;
	uint8_t x, evccIdStringLen;
	
	/* for the case, that the command line does not provide a valid sessionID, we set here a marker to detect the issue */
	EVCCID[0] = 0xDE;
	EVCCID[1] = 0xAD;
	EVCCID[2] = 0xBE;
	EVCCID[3] = 0xEF;
	EVCCID[4] = 0xDE;
	EVCCID[5] = 0xAD;
	
	if (nNumberOfFoundAdditionalParameters>0) {
		evccIdStringLen = strlen(gAdditionalParam[0]); /* two hex chars are forming one byte */
		if (evccIdStringLen==12) { /* The MAC must be 12 characters, means 6 bytes. The EVCCID needs to be filled with the MAC. */
			for (i=0; i<6; i++) { /* run through 6 bytes */
				/* take 2 characters from the parameter, and convert them into a byte */
				s3[0] = gAdditionalParam[0][2*i];
				s3[1] = gAdditionalParam[0][2*i+1];
				s3[2] = 0;
				x = strtol(s3, NULL, 16); /* convert the two-character hex to a uint8. If this fails, we get 0. Good enough. */
				//printf("%02x,  ", x);
				EVCCID[i]=x;
			}
		} else {
			sprintf(gErrorString, "useEVSEIDFromCommandLine: wrong length of EVCCID in first parameter. Expected 12 hex characters.");
		}
	} else {
		sprintf(gErrorString, "useEVSEIDFromCommandLine: too less parameters");
	}

}


/*********************************************************************************************************
*  Decoder --> JSON
**********************************************************************************************************
*  This chapter contains the four functions, to translate the C structs, which are filled by
*  the decoder, into JSON. Why four function? Because one for each schema: Handshake, Din, Iso1, Iso2.
*********************************************************************************************************/
 
/* translate the struct aphsDoc into JSON, to have it ready to give it over stdout to the caller application. */
void translateDocAppHandToJson(void) {
	int i;
	initProperties();
	addProperty("schema", "appHandshake");
	if (aphsDoc.supportedAppProtocolReq_isUsed) {
			/* it is a request */
			/* EVSE side: List of application handshake protocols of the EV */
			addMessageName("supportedAppProtocolReq");
			sprintf(s, "Vehicle supports %d protocols. ", aphsDoc.supportedAppProtocolReq.AppProtocol.arrayLen);
			strcat(gResultString, s);

			for(i=0;i<aphsDoc.supportedAppProtocolReq.AppProtocol.arrayLen;i++) {
				sprintf(s, "ProtocolEntry#%d ",(i+1));
				strcat(gResultString, s);
				sprintf(s, "ProtocolNamespace=");
				strcat(gResultString, s);
				printASCIIString(aphsDoc.supportedAppProtocolReq.AppProtocol.array[i].ProtocolNamespace.characters, aphsDoc.supportedAppProtocolReq.AppProtocol.array[i].ProtocolNamespace.charactersLen);
				strcat(gResultString, s);
				sprintf(s, " Version=%d.%d ", aphsDoc.supportedAppProtocolReq.AppProtocol.array[i].VersionNumberMajor, aphsDoc.supportedAppProtocolReq.AppProtocol.array[i].VersionNumberMinor);
				strcat(gResultString, s);
				sprintf(s, "SchemaID=%d ", aphsDoc.supportedAppProtocolReq.AppProtocol.array[i].SchemaID);
				strcat(gResultString, s);
				sprintf(s, "Priority=%d ", aphsDoc.supportedAppProtocolReq.AppProtocol.array[i].Priority);
				strcat(gResultString, s);
			}
	}
	if (aphsDoc.supportedAppProtocolRes_isUsed) {
			/* it is a response */
			addMessageName("supportedAppProtocolRes");
			sprintf(gResultString, "ResponseCode %d, SchemaID_isUsed %d, SchemaID %d",
				aphsDoc.supportedAppProtocolRes.ResponseCode,
				aphsDoc.supportedAppProtocolRes.SchemaID_isUsed,
				aphsDoc.supportedAppProtocolRes.SchemaID);
			//if (aphsDoc.supportedAppProtocolRes.SchemaID_isUsed) {
			//	SchemaID
			//}	
	}	
}

void translateDinHeaderToJson(void) {
	char sTmp[40], s2[30];
	int i, n;
	#define h dinDoc.V2G_Message.Header
	n = h.SessionID.bytesLen;
	//sprintf(sTmp, "%d", n); addProperty("header.SessionID.byteLen", sTmp);
	strcpy(sTmp,"");
	for (i=0; (i<n)&&(i<30); i++) {
			sprintf(s2, "%02x", h.SessionID.bytes[i]);
			strcat(sTmp, s2);
	}
	addProperty("header.SessionID", sTmp);
	sprintf(sTmp, "%d", h.Notification_isUsed); addProperty("header.Notification_isUsed", sTmp);
	sprintf(sTmp, "%d", h.Signature_isUsed); addProperty("header.Signature_isUsed", sTmp);	
}

void translateUnitToJson(char *property, int unit) {
	/* Hint: Units are optional in DIN schema, see Question2. Means: Not guaranteed, that we get sensful result here. */
	char sTmp[40];
	strcpy(sTmp, "UNKNOWN_UNIT");
	switch (unit) {
		case dinunitSymbolType_h: strcpy(sTmp, "h"); break;
		case dinunitSymbolType_m: strcpy(sTmp, "m"); break;
		case dinunitSymbolType_s: strcpy(sTmp, "s"); break;
		case dinunitSymbolType_A: strcpy(sTmp, "A"); break;
		case dinunitSymbolType_Ah: strcpy(sTmp, "Ah"); break;
		case dinunitSymbolType_V: strcpy(sTmp, "V"); break;
		case dinunitSymbolType_VA: strcpy(sTmp, "VA"); break;
		case dinunitSymbolType_W: strcpy(sTmp, "W"); break;
		case dinunitSymbolType_W_s: strcpy(sTmp, "W_s"); break;
		case dinunitSymbolType_Wh: strcpy(sTmp, "Wh"); break;
	}
	addProperty(property, sTmp);
}

void translateDinResponseCodeToJson(dinresponseCodeType rc) {
	char sLoc[40];
	strcpy(sLoc, "UNKNOWN_ERROR_CODE");
	switch (rc) {
		case dinresponseCodeType_OK: strcpy(sLoc, "OK"); break;
		case dinresponseCodeType_OK_NewSessionEstablished: strcpy(sLoc, "OK_NewSessionEstablished"); break;
		case dinresponseCodeType_OK_OldSessionJoined: strcpy(sLoc, "OK_OldSessionJoined"); break;
		case dinresponseCodeType_OK_CertificateExpiresSoon: strcpy(sLoc, "OK_CertificateExpiresSoon"); break;
		case dinresponseCodeType_FAILED: strcpy(sLoc, "FAILED"); break;
		case dinresponseCodeType_FAILED_SequenceError: strcpy(sLoc, "FAILED_SequenceError"); break;
		case dinresponseCodeType_FAILED_ServiceIDInvalid: strcpy(sLoc, "FAILED_ServiceIDInvalid"); break;
		case dinresponseCodeType_FAILED_UnknownSession: strcpy(sLoc, "FAILED_UnknownSession"); break;
		case dinresponseCodeType_FAILED_ServiceSelectionInvalid: strcpy(sLoc, "FAILED_ServiceSelectionInvalid"); break;
		case dinresponseCodeType_FAILED_PaymentSelectionInvalid: strcpy(sLoc, "FAILED_PaymentSelectionInvalid"); break;
		case dinresponseCodeType_FAILED_CertificateExpired: strcpy(sLoc, "FAILED_CertificateExpired"); break;
		case dinresponseCodeType_FAILED_SignatureError: strcpy(sLoc, "FAILED_SignatureError"); break;
		case dinresponseCodeType_FAILED_NoCertificateAvailable: strcpy(sLoc, "FAILED_NoCertificateAvailable"); break;
		case dinresponseCodeType_FAILED_CertChainError: strcpy(sLoc, "FAILED_CertChainError"); break;
		case dinresponseCodeType_FAILED_ChallengeInvalid: strcpy(sLoc, "FAILED_ChallengeInvalid"); break;
		case dinresponseCodeType_FAILED_ContractCanceled: strcpy(sLoc, "FAILED_ContractCanceled"); break;
		case dinresponseCodeType_FAILED_WrongChargeParameter: strcpy(sLoc, "FAILED_WrongChargeParameter"); break;
		case dinresponseCodeType_FAILED_PowerDeliveryNotApplied: strcpy(sLoc, "FAILED_PowerDeliveryNotApplied"); break;
		case dinresponseCodeType_FAILED_TariffSelectionInvalid: strcpy(sLoc, "FAILED_TariffSelectionInvalid"); break;
		case dinresponseCodeType_FAILED_ChargingProfileInvalid: strcpy(sLoc, "FAILED_ChargingProfileInvalid"); break;
		case dinresponseCodeType_FAILED_EVSEPresentVoltageToLow: strcpy(sLoc, "FAILED_EVSEPresentVoltageToLow"); break;
		case dinresponseCodeType_FAILED_MeteringSignatureNotValid: strcpy(sLoc, "FAILED_MeteringSignatureNotValid"); break;
		case dinresponseCodeType_FAILED_WrongEnergyTransferType: strcpy(sLoc, "FAILED_WrongEnergyTransferType"); break;
	}
	addProperty("ResponseCode", sLoc);
}

void translatedinDC_EVSEStatusCodeTypeToJson(dinDC_EVSEStatusCodeType st) {
	char sLoc[40];
	strcpy(sLoc, "UNKNOWN_STATUS");
	switch (st) {
		case dinDC_EVSEStatusCodeType_EVSE_NotReady: strcpy(sLoc, "EVSE_NotReady"); break;
		case dinDC_EVSEStatusCodeType_EVSE_Ready: strcpy(sLoc, "EVSE_Ready"); break;
		case dinDC_EVSEStatusCodeType_EVSE_Shutdown: strcpy(sLoc, "EVSE_Shutdown"); break;
		case dinDC_EVSEStatusCodeType_EVSE_UtilityInterruptEvent: strcpy(sLoc, "EVSE_UtilityInterruptEvent"); break;
		case dinDC_EVSEStatusCodeType_EVSE_IsolationMonitoringActive: strcpy(sLoc, "EVSE_IsolationMonitoringActive"); break;
		case dinDC_EVSEStatusCodeType_EVSE_EmergencyShutdown: strcpy(sLoc, "EVSE_EmergencyShutdown"); break;
		case dinDC_EVSEStatusCodeType_EVSE_Malfunction: strcpy(sLoc, "EVSE_Malfunction"); break;
		default: strcpy(sLoc, "UNKNOWN_STATUS");
	}
	addProperty("EVSEStatusCode_text", sLoc);
}

/* translate the struct dinDoc into JSON, to have it ready to give it over stdout to the caller application. */
void translateDocDinToJson(void) {
	char sTmp[30];
	char s2[30];
	int i,n;
	initProperties();
	addProperty("schema", "DIN");
	sprintf(sTmp, "%d", g_errn);
	addProperty("g_errn", sTmp);
	
	/* unclear, which is the correct flag:
	   dinDoc.SessionSetupReq_isUsed or
	   dinDoc.V2G_Message.Body.SessionSetupReq_isUsed. <-- This works with the example EXI 809a0011d00000.
	*/
	translateDinHeaderToJson();
	if (dinDoc.V2G_Message.Body.SessionSetupReq_isUsed) {
		addMessageName("SessionSetupReq");
		n=dinDoc.V2G_Message.Body.SessionSetupReq.EVCCID.bytesLen;
		sprintf(sTmp, "%d", n); addProperty("EVCCID.bytesLen", sTmp);
		strcpy(sTmp,"");
		for (i=0; (i<n)&&(i<20); i++) {
			/* this is no ASCII, at least not at the Ioniq. Show just Hex. */
			sprintf(s2, "%02x", dinDoc.V2G_Message.Body.SessionSetupReq.EVCCID.bytes[i]);
			strcat(sTmp, s2);
		}
		addProperty("EVCCID", sTmp);
	}
	if (dinDoc.V2G_Message.Body.SessionSetupRes_isUsed) {
		addMessageName("SessionSetupRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.SessionSetupRes.ResponseCode);
		n=dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytesLen;
		sprintf(sTmp, "%d", n); addProperty("EVSEID.bytesLen", sTmp);
		strcpy(sTmp,"");
		for (i=0; (i<n)&&(i<20); i++) {
			/* this is no ASCII, at least not at the Ioniq. Show just Hex. */
			sprintf(s2, "%02x", dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[i]);
			strcat(sTmp, s2);
		}
		addProperty("EVSEID", sTmp);
		
	}
	if (dinDoc.V2G_Message.Body.ServiceDiscoveryReq_isUsed) {
		addMessageName("ServiceDiscoveryReq");
		#define m dinDoc.V2G_Message.Body.ServiceDiscoveryReq
		if (m.ServiceScope_isUsed) {
			addProperty("ServiceScope_isUsed", "True");
			n = m.ServiceScope.charactersLen;
			sprintf(sTmp, "%d", n); addProperty("ServiceScope.charactersLen", sTmp);
		}
		if (m.ServiceCategory_isUsed) {
			addProperty("ServiceCategory_isUsed", "True");
		}
		#undef m
	}
	if (dinDoc.V2G_Message.Body.ServiceDiscoveryRes_isUsed) {
		addMessageName("ServiceDiscoveryRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ResponseCode);
	}

	if (dinDoc.V2G_Message.Body.ServicePaymentSelectionReq_isUsed) {
		addMessageName("ServicePaymentSelectionReq");
		#define m dinDoc.V2G_Message.Body.ServicePaymentSelectionReq
		if (m.SelectedPaymentOption==dinpaymentOptionType_Contract) { addProperty("SelectedPaymentOption", "Contract"); }
		if (m.SelectedPaymentOption==dinpaymentOptionType_ExternalPayment) { addProperty("SelectedPaymentOption", "ExternalPayment"); }
		
		n = m.SelectedServiceList.SelectedService.arrayLen;
		sprintf(sTmp, "%d", n); addProperty("SelectedService.arrayLen", sTmp);
		for (i=0; i<n; i++) {
			sprintf(sTmp, "%d:%d", i, m.SelectedServiceList.SelectedService.array[i].ServiceID); addProperty("SelectedService.array", sTmp);
		}
		// ParameterSetID_isUsed
		// ParameterSetID
		#undef m		
	}
	if (dinDoc.V2G_Message.Body.ServicePaymentSelectionRes_isUsed) {
		addMessageName("ServicePaymentSelectionRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.ServicePaymentSelectionRes.ResponseCode);
	}
	/* not supported in DIN 
	if (dinDoc.V2G_Message.Body.AuthorizationReq_isUsed) {
		addProperty("msgName", "AuthorizationReq");
	}
	if (dinDoc.V2G_Message.Body.AuthorizationRes_isUsed) {
		addProperty("msgName", "AuthorizationRes");
	}
	*/
	if (dinDoc.V2G_Message.Body.ContractAuthenticationReq_isUsed) {
		addMessageName("ContractAuthenticationReq");
	}
	if (dinDoc.V2G_Message.Body.ContractAuthenticationRes_isUsed) {
		addMessageName("ContractAuthenticationRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.ContractAuthenticationRes.ResponseCode);
		#define processing dinDoc.V2G_Message.Body.ContractAuthenticationRes.EVSEProcessing
		if (processing==dinEVSEProcessingType_Finished) {
			addProperty("EVSEProcessing", "Finished");
		}
		if (processing==dinEVSEProcessingType_Ongoing) {
			addProperty("EVSEProcessing", "Ongoing");
		}
		#undef processing
	}
	
	if (dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed) {
		addMessageName("ChargeParameterDiscoveryReq");
		#define m dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq
		sprintf(sTmp, "%d", m.EVRequestedEnergyTransferType); addProperty("EVRequestedEnergyTransferType", sTmp);
		sprintf(sTmp, "%d", m.DC_EVChargeParameter_isUsed); addProperty("DC_EVChargeParameter_isUsed", sTmp);
		if (m.DC_EVChargeParameter_isUsed) {
			sprintf(sTmp, "%d", m.DC_EVChargeParameter.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);
			sprintf(sTmp, "%d", m.DC_EVChargeParameter.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
			// todo EVMaximumCurrentLimit
		}
		#undef m
	}
	if (dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed) {
		addMessageName("ChargeParameterDiscoveryRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.ResponseCode);
		#define processing dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEProcessing
		if (processing==dinEVSEProcessingType_Finished) {
			addProperty("EVSEProcessing", "Finished");
		}
		if (processing==dinEVSEProcessingType_Ongoing) {
			addProperty("EVSEProcessing", "Ongoing");
		}
		#undef processing
		// todo maybe: EVSEChargeParameter_isUsed
		// todo for AC: AC_EVSEChargeParameter_isUsed
		if (dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter_isUsed) {
			//DC_EVSEChargeParameter
			//  DC_EVSEStatus
			#define cp dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter
			#define v1 cp.DC_EVSEStatus.EVSEIsolationStatus
			#define v2 cp.DC_EVSEStatus.EVSEIsolationStatus_isUsed
			#define v3 cp.DC_EVSEStatus.EVSEStatusCode
			#define v4 cp.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
			#define v5 cp.DC_EVSEStatus.EVSENotification
			sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
			sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
			sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
			translatedinDC_EVSEStatusCodeTypeToJson(v3);
			sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
			sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
			#undef v1
			#undef v2
			#undef v3
			#undef v4
			#undef v5
			//  EVSEMaximumCurrentLimit
			sprintf(sTmp, "%d", cp.EVSEMaximumCurrentLimit.Multiplier); addProperty("EVSEMaximumCurrentLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", cp.EVSEMaximumCurrentLimit.Value); addProperty("EVSEMaximumCurrentLimit.Value", sTmp);			
			translateUnitToJson("EVSEMaximumCurrentLimit.Unit", cp.EVSEMaximumCurrentLimit.Unit);
			
			//  EVSEMaximumPowerLimit
			//  EVSEMaximumPowerLimit_isUsed
			sprintf(sTmp, "%d", cp.EVSEMaximumPowerLimit_isUsed); addProperty("EVSEMaximumPowerLimit_isUsed", sTmp);
			sprintf(sTmp, "%d", cp.EVSEMaximumPowerLimit.Multiplier); addProperty("EVSEMaximumPowerLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", cp.EVSEMaximumPowerLimit.Value); addProperty("EVSEMaximumPowerLimit.Value", sTmp);
			translateUnitToJson("EVSEMaximumPowerLimit.Unit", cp.EVSEMaximumPowerLimit.Unit);

			//  EVSEMaximumVoltageLimit
			sprintf(sTmp, "%d", cp.EVSEMaximumVoltageLimit.Multiplier); addProperty("EVSEMaximumVoltageLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", cp.EVSEMaximumVoltageLimit.Value); addProperty("EVSEMaximumVoltageLimit.Value", sTmp);
			translateUnitToJson("EVSEMaximumVoltageLimit.Unit", cp.EVSEMaximumVoltageLimit.Unit);
			//  EVSEMinimumCurrentLimit
			sprintf(sTmp, "%d", cp.EVSEMinimumCurrentLimit.Multiplier); addProperty("EVSEMinimumCurrentLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", cp.EVSEMinimumCurrentLimit.Value); addProperty("EVSEMinimumCurrentLimit.Value", sTmp);
			translateUnitToJson("EVSEMinimumCurrentLimit.Unit", cp.EVSEMinimumCurrentLimit.Unit);
			//  EVSEMinimumVoltageLimit
			sprintf(sTmp, "%d", cp.EVSEMinimumVoltageLimit.Multiplier); addProperty("EVSEMinimumVoltageLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", cp.EVSEMinimumVoltageLimit.Value); addProperty("EVSEMinimumVoltageLimit.Value", sTmp);
			translateUnitToJson("EVSEMinimumVoltageLimit.Unit", cp.EVSEMinimumVoltageLimit.Unit);
			//  EVSECurrentRegulationTolerance
			//  EVSECurrentRegulationTolerance_isUsed
			//  EVSEPeakCurrentRipple
			//  EVSEEnergyToBeDelivered
			//  EVSEEnergyToBeDelivered_isUsed
			//xxx
			#undef cp
		}
	}
	
	if (dinDoc.V2G_Message.Body.CableCheckReq_isUsed) {
		addMessageName("CableCheckReq");
		#define m dinDoc.V2G_Message.Body.CableCheckReq
		sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
		#undef m
	}
	if (dinDoc.V2G_Message.Body.CableCheckRes_isUsed) {
		addMessageName("CableCheckRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.CableCheckRes.ResponseCode);
		#define m dinDoc.V2G_Message.Body.CableCheckRes
		#define v1 m.DC_EVSEStatus.EVSEIsolationStatus
		#define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
		#define v3 m.DC_EVSEStatus.EVSEStatusCode
		#define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
		#define v5 m.DC_EVSEStatus.EVSENotification
		sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
		sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
		sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
		translatedinDC_EVSEStatusCodeTypeToJson(v3);
		sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
		sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
		#undef v1
		#undef v2
		#undef v3
		#undef v4
		#undef v5
		if (m.EVSEProcessing==dinEVSEProcessingType_Finished) {
			addProperty("EVSEProcessing", "Finished");
		}
		if (m.EVSEProcessing==dinEVSEProcessingType_Ongoing) {
			addProperty("EVSEProcessing", "Ongoing");
		}		
		#undef m
	}

	if (dinDoc.V2G_Message.Body.PreChargeReq_isUsed) {
		addMessageName("PreChargeReq");
		#define m dinDoc.V2G_Message.Body.PreChargeReq
		sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVErrorCode); addProperty("DC_EVStatus.EVErrorCode", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);

		sprintf(sTmp, "%d", m.EVTargetVoltage.Multiplier); addProperty("EVTargetVoltage.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVTargetVoltage.Value); addProperty("EVTargetVoltage.Value", sTmp);
		translateUnitToJson("EVTargetVoltage.Unit", m.EVTargetVoltage.Unit);
						
		sprintf(sTmp, "%d", m.EVTargetCurrent.Multiplier); addProperty("EVTargetCurrent.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVTargetCurrent.Value); addProperty("EVTargetCurrent.Value", sTmp);
		translateUnitToJson("EVTargetCurrent.Unit", m.EVTargetCurrent.Unit);

		#undef m
	}
	if (dinDoc.V2G_Message.Body.PreChargeRes_isUsed) {
		addMessageName("PreChargeRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.PreChargeRes.ResponseCode);
		#define m dinDoc.V2G_Message.Body.PreChargeRes
		#define v1 m.DC_EVSEStatus.EVSEIsolationStatus
		#define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
		#define v3 m.DC_EVSEStatus.EVSEStatusCode
		#define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
		#define v5 m.DC_EVSEStatus.EVSENotification
		sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
		sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
		sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
		translatedinDC_EVSEStatusCodeTypeToJson(v3);
		sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
		sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
		
		sprintf(sTmp, "%d", m.EVSEPresentVoltage.Multiplier); addProperty("EVSEPresentVoltage.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVSEPresentVoltage.Value); addProperty("EVSEPresentVoltage.Value", sTmp);
		translateUnitToJson("EVSEPresentVoltage.Unit", m.EVSEPresentVoltage.Unit); /* why is this shown as 0? Because unit is optional, see question2. */

		#undef v1
		#undef v2
		#undef v3
		#undef v4
		#undef v5
		#undef m
	}
	if (dinDoc.V2G_Message.Body.PowerDeliveryReq_isUsed) {
		addMessageName("PowerDeliveryReq");
		sprintf(sTmp, "%d", dinDoc.V2G_Message.Body.PowerDeliveryReq.ReadyToChargeState); addProperty("ReadyToChargeState", sTmp);

		if (dinDoc.V2G_Message.Body.PowerDeliveryReq.ReadyToChargeState==0) { addProperty("ReadyToChargeState_Text", "false"); }
		if (dinDoc.V2G_Message.Body.PowerDeliveryReq.ReadyToChargeState==1) { addProperty("ReadyToChargeState_Text", "true"); }
		/*if (dinDoc.V2G_Message.Body.PowerDeliveryReq.ReadyToChargeState==2) { addProperty("ReadyToChargeState_Text", "Renegotiate"); } */
		
		sprintf(sTmp, "%d", dinDoc.V2G_Message.Body.PowerDeliveryReq.ChargingProfile_isUsed); addProperty("ChargingProfile_isUsed", sTmp);
		sprintf(sTmp, "%d", dinDoc.V2G_Message.Body.PowerDeliveryReq.EVPowerDeliveryParameter_isUsed); addProperty("EVPowerDeliveryParameter_isUsed", sTmp);
		sprintf(sTmp, "%d", dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter_isUsed); addProperty("DC_EVPowerDeliveryParameter_isUsed", sTmp);
		if (dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter_isUsed) {
			#define v1 dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.DC_EVStatus.EVReady
			#define v2 dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.DC_EVStatus.EVErrorCode
			#define v3 dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.DC_EVStatus.EVRESSSOC
			#define v4 dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.BulkChargingComplete
			#define v5 dinDoc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.ChargingComplete
			
			sprintf(sTmp, "%d", v1); addProperty("EVReady", sTmp);
			sprintf(sTmp, "%d", v2); addProperty("EVErrorCode", sTmp);
			
			switch (v2) {
				case dinDC_EVErrorCodeType_NO_ERROR:
					addProperty("EVErrorCodeText", "NO_ERROR");
					break;
				case dinDC_EVErrorCodeType_FAILED_ChargingSystemIncompatibility:
					addProperty("EVErrorCodeText", "FAILED_ChargingSystemIncompatibility");
					break;
				case dinDC_EVErrorCodeType_FAILED_ChargerConnectorLockFault:
					addProperty("EVErrorCodeText", "FAILED_ChargerConnectorLockFault");
					break;
				default:
					addProperty("EVErrorCodeText", "otherError");
					/* todo add more error texts */
			}
			
			sprintf(sTmp, "%d", v3); addProperty("EVRESSSOC", sTmp);
			sprintf(sTmp, "%d", v4); addProperty("BulkChargingComplete", sTmp);
			sprintf(sTmp, "%d", v5); addProperty("ChargingComplete", sTmp);
			#undef v1
			#undef v2
			#undef v3
			#undef v4
			#undef v5
		}

	}
	if (dinDoc.V2G_Message.Body.PowerDeliveryRes_isUsed) {
		addMessageName("PowerDeliveryRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.PowerDeliveryRes.ResponseCode);
		#define m dinDoc.V2G_Message.Body.PowerDeliveryRes
		if (m.DC_EVSEStatus_isUsed) {
			
			#define v1 m.DC_EVSEStatus.EVSEIsolationStatus
			#define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
			#define v3 m.DC_EVSEStatus.EVSEStatusCode
			#define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
			#define v5 m.DC_EVSEStatus.EVSENotification
			sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
			sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
			sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
			translatedinDC_EVSEStatusCodeTypeToJson(v3);
			sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
			sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
			#undef m
			#undef v1
			#undef v2
			#undef v3
			#undef v4
			#undef v5
		}
	}

	if (dinDoc.V2G_Message.Body.CurrentDemandReq_isUsed) {
		addMessageName("CurrentDemandReq");
		#define m dinDoc.V2G_Message.Body.CurrentDemandReq
		sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVErrorCode); addProperty("DC_EVStatus.EVErrorCode", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);

		sprintf(sTmp, "%d", m.EVTargetCurrent.Multiplier); addProperty("EVTargetCurrent.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVTargetCurrent.Value); addProperty("EVTargetCurrent.Value", sTmp);
		translateUnitToJson("EVTargetCurrent.Unit", m.EVTargetCurrent.Unit);

		sprintf(sTmp, "%d", m.EVMaximumVoltageLimit_isUsed); addProperty("EVMaximumVoltageLimit_isUsed", sTmp);
		if (m.EVMaximumVoltageLimit_isUsed) {
		  sprintf(sTmp, "%d", m.EVMaximumVoltageLimit.Multiplier); addProperty("EVMaximumVoltageLimit.Multiplier", sTmp);
		  sprintf(sTmp, "%d", m.EVMaximumVoltageLimit.Value); addProperty("EVMaximumVoltageLimit.Value", sTmp);
		  translateUnitToJson("EVMaximumVoltageLimit.Unit", m.EVMaximumVoltageLimit.Unit);
		}

		sprintf(sTmp, "%d", m.EVMaximumCurrentLimit_isUsed); addProperty("EVMaximumCurrentLimit_isUsed", sTmp);
		if (m.EVMaximumCurrentLimit_isUsed) {
		  sprintf(sTmp, "%d", m.EVMaximumCurrentLimit.Multiplier); addProperty("EVMaximumCurrentLimit.Multiplier", sTmp);
		  sprintf(sTmp, "%d", m.EVMaximumCurrentLimit.Value); addProperty("EVMaximumCurrentLimit.Value", sTmp);
		  translateUnitToJson("EVMaximumCurrentLimit.Unit", m.EVMaximumCurrentLimit.Unit);
		}
		
		sprintf(sTmp, "%d", m.EVMaximumPowerLimit_isUsed); addProperty("EVMaximumPowerLimit_isUsed", sTmp);
		if (m.EVMaximumPowerLimit_isUsed) {
		  sprintf(sTmp, "%d", m.EVMaximumPowerLimit.Multiplier); addProperty("EVMaximumPowerLimit.Multiplier", sTmp);
		  sprintf(sTmp, "%d", m.EVMaximumPowerLimit.Value); addProperty("EVMaximumPowerLimit.Value", sTmp);
		  translateUnitToJson("EVMaximumPowerLimit.Unit", m.EVMaximumPowerLimit.Unit); 
		}
		
		//m.BulkChargingComplete_isUsed
		//m.BulkChargingComplete
		sprintf(sTmp, "%d", m.ChargingComplete); addProperty("ChargingComplete", sTmp);

		sprintf(sTmp, "%d", m.EVTargetVoltage.Multiplier); addProperty("EVTargetVoltage.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVTargetVoltage.Value); addProperty("EVTargetVoltage.Value", sTmp);
		translateUnitToJson("EVTargetVoltage.Unit", m.EVTargetVoltage.Unit); 
		#undef m
	}
	
	if (dinDoc.V2G_Message.Body.CurrentDemandRes_isUsed) {
		addMessageName("CurrentDemandRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.CurrentDemandRes.ResponseCode);
		#define m dinDoc.V2G_Message.Body.CurrentDemandRes
			#define v1 m.DC_EVSEStatus.EVSEIsolationStatus
			#define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
			#define v3 m.DC_EVSEStatus.EVSEStatusCode
			#define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
			#define v5 m.DC_EVSEStatus.EVSENotification
			sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
			sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
			sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
			translatedinDC_EVSEStatusCodeTypeToJson(v3);
			sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
			sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
			#undef v1
			#undef v2
			#undef v3
			#undef v4
			#undef v5
		sprintf(sTmp, "%d", m.EVSEPresentVoltage.Multiplier); addProperty("EVSEPresentVoltage.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVSEPresentVoltage.Value); addProperty("EVSEPresentVoltage.Value", sTmp);
		translateUnitToJson("EVSEPresentVoltage.Unit", m.EVSEPresentVoltage.Unit); 

		sprintf(sTmp, "%d", m.EVSEPresentCurrent.Multiplier); addProperty("EVSEPresentCurrent.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVSEPresentCurrent.Value); addProperty("EVSEPresentCurrent.Value", sTmp);
		translateUnitToJson("EVSEPresentCurrent.Unit", m.EVSEPresentCurrent.Unit); 

		sprintf(sTmp, "%d", m.EVSECurrentLimitAchieved); addProperty("EVSECurrentLimitAchieved", sTmp);
		sprintf(sTmp, "%d", m.EVSEVoltageLimitAchieved); addProperty("EVSEVoltageLimitAchieved", sTmp);
		sprintf(sTmp, "%d", m.EVSEPowerLimitAchieved); addProperty("EVSEPowerLimitAchieved", sTmp);

		sprintf(sTmp, "%d", m.EVSEMaximumVoltageLimit.Multiplier); addProperty("EVSEMaximumVoltageLimit.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVSEMaximumVoltageLimit.Value); addProperty("EVSEMaximumVoltageLimit.Value", sTmp);
		translateUnitToJson("EVSEMaximumVoltageLimit.Unit", m.EVSEMaximumVoltageLimit.Unit); 

		if (m.EVSEMaximumCurrentLimit_isUsed) {
			sprintf(sTmp, "%d", m.EVSEMaximumCurrentLimit.Multiplier); addProperty("EVSEMaximumCurrentLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", m.EVSEMaximumCurrentLimit.Value); addProperty("EVSEMaximumCurrentLimit.Value", sTmp);
			translateUnitToJson("EVSEMaximumCurrentLimit.Unit", m.EVSEMaximumCurrentLimit.Unit); 
		}
		if (m.EVSEMaximumPowerLimit_isUsed) {
			sprintf(sTmp, "%d", m.EVSEMaximumPowerLimit.Multiplier); addProperty("EVSEMaximumPowerLimit.Multiplier", sTmp);
			sprintf(sTmp, "%d", m.EVSEMaximumPowerLimit.Value); addProperty("EVSEMaximumPowerLimit.Value", sTmp);
			translateUnitToJson("EVSEMaximumPowerLimit.Unit", m.EVSEMaximumPowerLimit.Unit); 
		}
		#undef m
	}
	
	if (dinDoc.V2G_Message.Body.SessionStopReq_isUsed) {
		addMessageName("SessionStopReq");
	}
	if (dinDoc.V2G_Message.Body.SessionStopRes_isUsed) {
		addMessageName("SessionStopRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.SessionStopRes.ResponseCode);
	}

	if (dinDoc.V2G_Message.Body.WeldingDetectionReq_isUsed) {
		addMessageName("WeldingDetectionReq");
		#define m dinDoc.V2G_Message.Body.WeldingDetectionReq
		sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVErrorCode); addProperty("DC_EVStatus.EVErrorCode", sTmp);
		sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);	
		#undef m
	}
	if (dinDoc.V2G_Message.Body.WeldingDetectionRes_isUsed) {
		addMessageName("WeldingDetectionRes");
		translateDinResponseCodeToJson(dinDoc.V2G_Message.Body.WeldingDetectionRes.ResponseCode);
		#define m dinDoc.V2G_Message.Body.WeldingDetectionRes		
		#define v1 m.DC_EVSEStatus.EVSEIsolationStatus
		#define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
		#define v3 m.DC_EVSEStatus.EVSEStatusCode
		#define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
		#define v5 m.DC_EVSEStatus.EVSENotification
		sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
		sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
		sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
		translatedinDC_EVSEStatusCodeTypeToJson(v3);
		sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
		sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
		sprintf(sTmp, "%d", m.EVSEPresentVoltage.Multiplier); addProperty("EVSEPresentVoltage.Multiplier", sTmp);
		sprintf(sTmp, "%d", m.EVSEPresentVoltage.Value); addProperty("EVSEPresentVoltage.Value", sTmp);
		translateUnitToJson("EVSEPresentVoltage.Unit", m.EVSEPresentVoltage.Unit); 
		#undef v1
		#undef v2
		#undef v3
		#undef v4
		#undef v5
		#undef m
	}
}


/*********************************************************************************************************
*  Encoder
**********************************************************************************************************
*********************************************************************************************************/
static void encodeSupportedAppProtocolResponse(void) {
	/* The :supportedAppProtocolRes contains only two fields:
	    ResponseCode
		SchemaID (optional) It is not clear, in which cases the SchemaID can be left empty. Maybe if the list has only one enty. Or
		maybe always, to just select the first entry. */		
  init_appHandEXIDocument(&aphsDoc);
  aphsDoc.supportedAppProtocolRes_isUsed = 1u;
  aphsDoc.supportedAppProtocolRes.ResponseCode = appHandresponseCodeType_OK_SuccessfulNegotiation;
  aphsDoc.supportedAppProtocolRes.SchemaID = 1; /* todo: fill with one of the SchemaIDs of the request. The Ioniq uses schema 1 as one-and-only. */
  aphsDoc.supportedAppProtocolRes.SchemaID_isUsed = 1u; /* todo: shall we try without SchemaID? */

  prepareGlobalStream();
  g_errn = encode_appHandExiDocument(&global_stream1, &aphsDoc);
  printGlobalStream();
  sprintf(gInfoString, "encodeSupportedAppProtocolResponse finished");
}

static void encodeSessionSetupRequest(void) {
    uint8_t i;
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.SessionSetupReq_isUsed = 1u;
	init_dinSessionSetupReqType(&dinDoc.V2G_Message.Body.SessionSetupReq);
	/* In the session setup request, the session ID zero means: create a new session.
	   The format (len 8, all zero) is taken from the original Ioniq behavior. */
	dinDoc.V2G_Message.Header.SessionID.bytes[0] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[1] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[2] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[3] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[4] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[5] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[6] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytes[7] = 0;
	dinDoc.V2G_Message.Header.SessionID.bytesLen = 8;
    /* The EVCCID. In the ISO they write, that this shall be the EVCC MAC. But the DIN
    reserves 8 bytes (dinSessionSetupReqType_EVCCID_BYTES_SIZE is 8). This does not match.
    The Ioniq (DIN) sets the bytesLen=6 and fills the 6 bytes with its own MAC. Let's assume this
    is the best way. */
    useEVCCIDFromCommandLine();
    for (i=0; i<LEN_OF_EVCCID; i++) {
        dinDoc.V2G_Message.Body.SessionSetupReq.EVCCID.bytes[i] = EVCCID[i];
    }
    dinDoc.V2G_Message.Body.SessionSetupReq.EVCCID.bytesLen = LEN_OF_EVCCID; 
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeSessionSetupRequest finished");
}

static void init_dinMessageHeaderWithSessionID(void) {
	int i;
	dinDoc.V2G_Message_isUsed = 1u;
	/* generate an "unique" sessionID */
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	/* When receiving the SessionSetupReq with the parameter SessionID equal to zero (0), the 
	SECC shall generate a new (not stored) SessionID value different from zero (0) and return this 
	value in the SessionSetupRes message header.
	We can use the following simplification if we are SECC/EVSE: We set always the same SessionID, with non-zero value. */
	for (i=0; i<gLenOfSessionId; i++) {  
		dinDoc.V2G_Message.Header.SessionID.bytes[i] = gSessionID[i];
	}
	dinDoc.V2G_Message.Header.SessionID.bytesLen = gLenOfSessionId;
}

static void encodeSessionSetupResponse(void) {
	 /* This is the place, where we, as charger, decide about the new session ID. */
	 /* As simplification, we always use the same session ID, so we have no need to transfer
	    the number via command line interface to the upper layers in case we are the charger.
		On the other hand, if we are the car, then we need to use the sessionID which was decided
		by the charger, and we need to transfer it to and from the upper layers. */
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.SessionSetupRes_isUsed = 1u;
	init_dinSessionSetupResType(&dinDoc.V2G_Message.Body.SessionSetupRes);
	/* If the SECC receives a SessionSetupReq including a SessionID value which is not equal to 
	zero (0) and not equal to the SessionID value stored from the preceding V2G Communication 
	Session, it shall send a SessionID value in the SessionSetupRes message that is unequal to 
	"0" and unequal to the SessionID value stored from the preceding V2G Communication 
	Session and indicate the new V2G Communication Session with the ResponseCode set to 
	"OK_NewSessionEstablished"
	*/
	dinDoc.V2G_Message.Body.SessionSetupRes.ResponseCode = dinresponseCodeType_OK_NewSessionEstablished;
	/* EVSEID has min length 7, max length 37 for ISO. In DIN decoder we find maxsize 32. */
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[0] = 'Z';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[1] = 'Z';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[2] = '0';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[3] = '0';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[4] = '0';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[5] = '0';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytes[6] = '0';
	dinDoc.V2G_Message.Body.SessionSetupRes.EVSEID.bytesLen = 7;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSETimeStamp_isUsed = 0u;
	//dinDoc.V2G_Message.Body.SessionSetupRes.EVSETimeStamp = 123456789;
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeSessionSetupResponse finished");
}

static void encodeServiceDiscoveryRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ServiceDiscoveryReq_isUsed = 1u;
	init_dinServiceDiscoveryReqType(&dinDoc.V2G_Message.Body.ServiceDiscoveryReq);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeServiceDiscoveryRequest finished");
}

void encodeServiceDiscoveryResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes_isUsed = 1u;
	init_dinServiceDiscoveryResType(&dinDoc.V2G_Message.Body.ServiceDiscoveryRes);
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ResponseCode = dinresponseCodeType_OK;
	/* the mandatory fields in the ISO are PaymentOptionList and ChargeService.
	   But in the DIN, this is different, we find PaymentOptions, ChargeService and optional ServiceList */
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.PaymentOptions.PaymentOption.array[0] = dinpaymentOptionType_ExternalPayment; /* EVSE handles the payment */
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.PaymentOptions.PaymentOption.arrayLen = 1; /* just one single payment option in the table */
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.ServiceTag.ServiceID = 1; /* todo: not clear what this means  */
	//dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.ServiceTag.ServiceName
	//dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.ServiceTag.ServiceName_isUsed
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.ServiceTag.ServiceCategory = dinserviceCategoryType_EVCharging;
	//dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.ServiceTag.ServiceScope
	//dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.ServiceTag.ServiceScope_isUsed
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.FreeService = 0; /* what ever this means. Just from example. */
	/* dinEVSESupportedEnergyTransferType, e.g.
								dinEVSESupportedEnergyTransferType_DC_combo_core or
								dinEVSESupportedEnergyTransferType_DC_core or
								dinEVSESupportedEnergyTransferType_DC_extended
								dinEVSESupportedEnergyTransferType_AC_single_phase_core.
		DC_extended means "extended pins of an IEC 62196-3 Configuration FF connector", which is
        the normal CCS connector https://en.wikipedia.org/wiki/IEC_62196#FF) */
	dinDoc.V2G_Message.Body.ServiceDiscoveryRes.ChargeService.EnergyTransferType = dinEVSESupportedEnergyTransferType_DC_extended;
	
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeServiceDiscoveryResponse finished");
}

static void encodeServicePaymentSelectionRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ServicePaymentSelectionReq_isUsed = 1u;
	init_dinServicePaymentSelectionReqType(&dinDoc.V2G_Message.Body.ServicePaymentSelectionReq);
	/* the mandatory fields in ISO are SelectedPaymentOption and SelectedServiceList. Same in DIN. */
	dinDoc.V2G_Message.Body.ServicePaymentSelectionReq.SelectedPaymentOption = dinpaymentOptionType_ExternalPayment; /* not paying per car */
	dinDoc.V2G_Message.Body.ServicePaymentSelectionReq.SelectedServiceList.SelectedService.array[0].ServiceID = 1; /* todo: what ever this means. The Ioniq uses 1. */
	dinDoc.V2G_Message.Body.ServicePaymentSelectionReq.SelectedServiceList.SelectedService.arrayLen = 1; /* just one element in the array */ 
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeServicePaymentSelectionRequest finished");
}


void encodeServicePaymentSelectionResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ServicePaymentSelectionRes_isUsed = 1u;
	init_dinServicePaymentSelectionResType(&dinDoc.V2G_Message.Body.ServicePaymentSelectionRes);
	/* The ServicePaymentSelectionRes has only one element: The ResponseCode. */
	dinDoc.V2G_Message.Body.ServicePaymentSelectionRes.ResponseCode = dinresponseCodeType_OK;
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeServicePaymentSelectionResponse finished");
}


static void encodeChargeParameterDiscoveryRequest(void) {
	struct dinDC_EVChargeParameterType *cp;
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed = 1u;
	init_dinChargeParameterDiscoveryReqType(&dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq);
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq.EVRequestedEnergyTransferType = dinEVRequestedEnergyTransferType_DC_extended;
	//dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq.EVChargeParameter
	//dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq.EVChargeParameter_isUsed = 1;
	cp = &dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter;
	cp->DC_EVStatus.EVReady = 1; /* todo: what ever this means */
	//cp->DC_EVStatus.EVCabinConditioning
	//cp->DC_EVStatus.EVCabinConditioning_isUsed
	cp->DC_EVStatus.EVRESSSOC = getIntParam(1); /* Take the SOC from the command line parameter. Scaling is 1%. */
	cp->EVMaximumCurrentLimit.Multiplier = 0; /* -3 to 3. The exponent for base of 10. */
	cp->EVMaximumCurrentLimit.Unit = dinunitSymbolType_A;
	cp->EVMaximumCurrentLimit.Value = 100; 
	//cp->EVMaximumPowerLimit ;
	//cp->EVMaximumPowerLimit_isUsed:1;
	cp->EVMaximumVoltageLimit.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cp->EVMaximumVoltageLimit.Unit = dinunitSymbolType_V;
	cp->EVMaximumVoltageLimit.Value = 398;
	//cp->EVEnergyCapacity
	//cp->EVEnergyCapacity_isUsed
	//cp->EVEnergyRequest
	//cp->EVEnergyRequest_isUsed
	//cp->FullSOC
	//cp->FullSOC_isUsed
	//cp->BulkSOC
	//cp->BulkSOC_isUsed
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter_isUsed = 1;
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeChargeParameterDiscoveryRequest finished");
}

void encodeChargeParameterDiscoveryResponse(void) {
	struct dinEVSEChargeParameterType *cp;
	struct dinDC_EVSEChargeParameterType *cpdc;
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed = 1u;
	init_dinChargeParameterDiscoveryResType(&dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes);
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.ResponseCode = dinresponseCodeType_OK;
	/*
		dinEVSEProcessingType_Finished = 0,
	    dinEVSEProcessingType_Ongoing = 1
	*/
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEProcessing = dinEVSEProcessingType_Finished;
	/* The encoder wants either SASchedules or SAScheduleList. If both are missing, it fails. (around line 3993 in dinEXIDatatypesEncoder.c).
	   The content is not used at all, but we just set it, to satisfy the encoder. */
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.SASchedules.noContent = 0;
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.SASchedules_isUsed = 1;
	
	cp = &dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter;
	cp->noContent = 0;
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter_isUsed=0;
	
	//dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter
	//dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter_isUsed
	cpdc = &dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter;
	cpdc->DC_EVSEStatus.EVSEIsolationStatus = dinisolationLevelType_Valid;
	cpdc->DC_EVSEStatus.EVSEIsolationStatus_isUsed = 1;
	cpdc->DC_EVSEStatus.EVSEStatusCode = dinDC_EVSEStatusCodeType_EVSE_Ready;
	cpdc->DC_EVSEStatus.NotificationMaxDelay = 0; /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
	cpdc->DC_EVSEStatus.EVSENotification = dinEVSENotificationType_None; /* could also be dinEVSENotificationType_StopCharging */


	cpdc->EVSEMaximumCurrentLimit.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSEMaximumCurrentLimit.Unit = dinunitSymbolType_A;
	cpdc->EVSEMaximumCurrentLimit.Value = 200;
	
	cpdc->EVSEMaximumPowerLimit.Multiplier = 3;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSEMaximumPowerLimit.Unit = dinunitSymbolType_W;
	cpdc->EVSEMaximumPowerLimit.Value = 10;
	cpdc->EVSEMaximumPowerLimit_isUsed = 1;
	
	cpdc->EVSEMaximumVoltageLimit.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSEMaximumVoltageLimit.Unit = dinunitSymbolType_V;
	cpdc->EVSEMaximumVoltageLimit.Value = 450;
	
	cpdc->EVSEMinimumCurrentLimit.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSEMinimumCurrentLimit.Unit = dinunitSymbolType_A;
	cpdc->EVSEMinimumCurrentLimit.Value = 1;
	
	cpdc->EVSEMinimumVoltageLimit.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSEMinimumVoltageLimit.Unit = dinunitSymbolType_V;
	cpdc->EVSEMinimumVoltageLimit.Value = 200;
	
	cpdc->EVSECurrentRegulationTolerance.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSECurrentRegulationTolerance.Unit = dinunitSymbolType_A;
	cpdc->EVSECurrentRegulationTolerance.Value = 5;
	cpdc->EVSECurrentRegulationTolerance_isUsed=1;
	
	cpdc->EVSEPeakCurrentRipple.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	cpdc->EVSEPeakCurrentRipple.Unit = dinunitSymbolType_A;
	cpdc->EVSEPeakCurrentRipple.Value = 5;	
	//cpdc->EVSEEnergyToBeDelivered ;
	//cpdc->EVSEEnergyToBeDelivered_isUsed:1;
	dinDoc.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter_isUsed = 1;
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeChargeParameterDiscoveryResponse finished");
}

static void encodeCableCheckRequest(void) {
	dinDoc.V2G_Message_isUsed = 1u;
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.CableCheckReq_isUsed = 1u;
	init_dinCableCheckReqType(&dinDoc.V2G_Message.Body.CableCheckReq);
	#define st dinDoc.V2G_Message.Body.CableCheckReq.DC_EVStatus
	  st.EVReady = 1; /* 1 means true. We are ready. */
	  st.EVErrorCode = dinDC_EVErrorCodeType_NO_ERROR;
	  st.EVRESSSOC = getIntParam(1); /* Take the SOC from the command line parameter. Scaling is 1%. */
	#undef st
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeCableCheckRequest finished");
}

void encodeCableCheckResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.CableCheckRes_isUsed = 1u;
	init_dinCableCheckResType(&dinDoc.V2G_Message.Body.CableCheckRes);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeCableCheckResponse finished");
}

static void encodePreChargeRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.PreChargeReq_isUsed = 1u;
	init_dinPreChargeReqType(&dinDoc.V2G_Message.Body.PreChargeReq);
	#define st dinDoc.V2G_Message.Body.PreChargeReq.DC_EVStatus
	  st.EVReady = 1; /* 1 means true. We are ready. */
	  st.EVErrorCode = dinDC_EVErrorCodeType_NO_ERROR;
	  st.EVRESSSOC = getIntParam(1); /* Take the SOC from the command line parameter. Scaling is 1%. */
	#undef st
	#define tvolt dinDoc.V2G_Message.Body.PreChargeReq.EVTargetVoltage
	  tvolt.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	  tvolt.Unit = dinunitSymbolType_V;
	  tvolt.Unit_isUsed = 1;
	  tvolt.Value = getIntParam(2); /* Take the precharge target voltage from the command line. Scaling is 1V. */
	#undef tvolt
	#define tcurr dinDoc.V2G_Message.Body.PreChargeReq.EVTargetCurrent
	  tcurr.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	  tcurr.Unit = dinunitSymbolType_A;
	  tcurr.Unit_isUsed = 1;
	  tcurr.Value = 1; /* 1A for precharging */
	#undef tcurr
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodePreChargeRequest finished");
}

void encodePreChargeResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.PreChargeRes_isUsed = 1u;
	init_dinPreChargeResType(&dinDoc.V2G_Message.Body.PreChargeRes);
	dinDoc.V2G_Message.Body.PreChargeRes.DC_EVSEStatus.EVSEIsolationStatus = 1;
	dinDoc.V2G_Message.Body.PreChargeRes.DC_EVSEStatus.EVSEIsolationStatus_isUsed = 1;
	dinDoc.V2G_Message.Body.PreChargeRes.EVSEPresentVoltage.Multiplier = 0; /* 10 ^ 0 */
	dinDoc.V2G_Message.Body.PreChargeRes.EVSEPresentVoltage.Unit = dinunitSymbolType_V; /* why is this shown as 0? Because unit is optional, see question2. */
	dinDoc.V2G_Message.Body.PreChargeRes.EVSEPresentVoltage.Value = getIntParam(0); /* Take from command line */
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodePreChargeResponse finished");
}

static void encodePowerDeliveryRequest(void) {
	int x;
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.PowerDeliveryReq_isUsed = 1u;
	init_dinPowerDeliveryReqType(&dinDoc.V2G_Message.Body.PowerDeliveryReq);
	#define m dinDoc.V2G_Message.Body.PowerDeliveryReq
	// ReadyToChargeState
	x = getIntParam(2); /* on command line, we use 0 for STOP and 1 for START */
	if (x==1) {
		/* START */
		m.ReadyToChargeState = 1; /* in ISO the name is ChargeProgress, with values 0=Start, 1=Stop, 2=Renegotiate. Not sure, 
                             whether the meaning is the same.
							Todo: There are hints, that the meaning of this value in the DIN is different: boolean, maybe true==START. */
	} else {
		/* everything else we interpret at STOP */
		m.ReadyToChargeState = 0; 		
	}
	// todo? ChargingProfile
	// todo? ChargingProfile_isUsed
	// DC_EVPowerDeliveryParameter
	m.DC_EVPowerDeliveryParameter_isUsed = 1;
	#define st m.DC_EVPowerDeliveryParameter.DC_EVStatus
	  st.EVReady = 1; /* 1 means true. We are ready. */
	  st.EVErrorCode = dinDC_EVErrorCodeType_NO_ERROR;
	  st.EVRESSSOC = getIntParam(1); /* Take the SOC from the command line parameter. Scaling is 1%. */
	#undef st
	m.DC_EVPowerDeliveryParameter.ChargingComplete = 0; /* boolean. Charging not finished. */
	#undef m
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodePowerDeliveryRequest finished");
}

void encodePowerDeliveryResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.PowerDeliveryRes_isUsed = 1u;
	init_dinPowerDeliveryResType(&dinDoc.V2G_Message.Body.PowerDeliveryRes);
	dinDoc.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus_isUsed = 1;
	dinDoc.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus.EVSEIsolationStatus = dinisolationLevelType_Valid;
	dinDoc.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus.EVSEIsolationStatus_isUsed = 1;
	dinDoc.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus.EVSEStatusCode = dinDC_EVSEStatusCodeType_EVSE_Ready;
	dinDoc.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus.NotificationMaxDelay = 0; /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
	dinDoc.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus.EVSENotification = dinEVSENotificationType_None; /* could also be dinEVSENotificationType_StopCharging */
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodePowerDeliveryResponse finished");
}


static void encodeCurrentDemandRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.CurrentDemandReq_isUsed = 1u;
	init_dinCurrentDemandReqType(&dinDoc.V2G_Message.Body.CurrentDemandReq);
	// DC_EVStatus
	#define st dinDoc.V2G_Message.Body.CurrentDemandReq.DC_EVStatus
	  st.EVReady = 1; /* 1 means true. We are ready. */
	  st.EVErrorCode = dinDC_EVErrorCodeType_NO_ERROR;
	  st.EVRESSSOC = getIntParam(1); /* Take the SOC from the command line parameter. Scaling is 1%. */
	#undef st	
	// EVTargetVoltage
	#define tvolt dinDoc.V2G_Message.Body.CurrentDemandReq.EVTargetVoltage
	  tvolt.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	  tvolt.Unit = dinunitSymbolType_V;
	  tvolt.Unit_isUsed = 1;
	  tvolt.Value = getIntParam(3); /* Take the charging target voltage from the command line. Scaling is 1V. */
	#undef tvolt
	// EVTargetCurrent
	#define tcurr dinDoc.V2G_Message.Body.CurrentDemandReq.EVTargetCurrent
	  tcurr.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	  tcurr.Unit = dinunitSymbolType_A;
	  tcurr.Unit_isUsed = 1;
	  tcurr.Value = getIntParam(2); /* Take the charging target current from the command line. Scaling is 1A. */
	#undef tcurr
	dinDoc.V2G_Message.Body.CurrentDemandReq.ChargingComplete = 0; /* boolean. Todo: Do we need to take this from command line? Or is it fine
    that the PEV just sends a PowerDeliveryReq with STOP, if it decides to stop the charging? */
	dinDoc.V2G_Message.Body.CurrentDemandReq.BulkChargingComplete_isUsed = 1u;
	dinDoc.V2G_Message.Body.CurrentDemandReq.BulkChargingComplete = 0u; /* not complete */
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC_isUsed = 1u;
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC.Unit = dinunitSymbolType_s;
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC.Unit_isUsed = 1;
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC.Value = 1200; /* seconds */
	
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC_isUsed = 1u;
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC.Multiplier = 0;  /* -3 to 3. The exponent for base of 10. */
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC.Unit = dinunitSymbolType_s;
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC.Unit_isUsed = 1;
	dinDoc.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC.Value = 600; /* seconds */
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeCurrentDemandRequest finished");
}

void encodeCurrentDemandResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.CurrentDemandRes_isUsed = 1u;
	init_dinCurrentDemandResType(&dinDoc.V2G_Message.Body.CurrentDemandRes);
	#define m dinDoc.V2G_Message.Body.CurrentDemandRes
	m.DC_EVSEStatus.EVSEIsolationStatus = dinisolationLevelType_Valid;
	m.DC_EVSEStatus.EVSEIsolationStatus_isUsed = 1;
	m.DC_EVSEStatus.EVSEStatusCode = dinDC_EVSEStatusCodeType_EVSE_Ready;
	m.DC_EVSEStatus.NotificationMaxDelay = 0; /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
	m.DC_EVSEStatus.EVSENotification = dinEVSENotificationType_None; /* could also be dinEVSENotificationType_StopCharging */
	m.EVSEPresentVoltage.Multiplier = 0;
	m.EVSEPresentVoltage.Unit = dinunitSymbolType_V;
	m.EVSEPresentVoltage.Unit_isUsed = 1;
	m.EVSEPresentVoltage.Value = getIntParam(0); /* Take from command line */
	m.EVSEPresentCurrent.Multiplier = 0;
	m.EVSEPresentCurrent.Unit = dinunitSymbolType_A;
	m.EVSEPresentCurrent.Unit_isUsed = 1;
	m.EVSEPresentCurrent.Value = getIntParam(1); /* Take from command line */
	m.EVSECurrentLimitAchieved = 0;
	m.EVSEVoltageLimitAchieved = 0;
	m.EVSEPowerLimitAchieved = 0;
	m.EVSEMaximumVoltageLimit_isUsed = 0;
	//m.EVSEMaximumVoltageLimit
	m.EVSEMaximumCurrentLimit_isUsed = 0;
	//m.EVSEMaximumCurrentLimit
	m.EVSEMaximumPowerLimit_isUsed = 0;
	//m.EVSEMaximumPowerLimit

	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeCurrentDemandResponse finished");
}

static void encodeWeldingDetectionRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.WeldingDetectionReq_isUsed = 1u;
	init_dinWeldingDetectionReqType(&dinDoc.V2G_Message.Body.WeldingDetectionReq);
	prepareGlobalStream();
	#define st dinDoc.V2G_Message.Body.WeldingDetectionReq.DC_EVStatus
	  st.EVReady = 1; /* 1 means true. We are ready. */
	  st.EVErrorCode = dinDC_EVErrorCodeType_NO_ERROR;
	  st.EVRESSSOC = getIntParam(1); /* Take the SOC from the command line parameter. Scaling is 1%. */
	#undef st	
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeWeldingDetectionRequest finished");
}

void encodeWeldingDetectionResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.WeldingDetectionRes_isUsed = 1u;
	init_dinWeldingDetectionResType(&dinDoc.V2G_Message.Body.WeldingDetectionRes);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeWeldingDetectionResponse finished");
}
				
static void encodeSessionStopRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.SessionStopReq_isUsed = 1u;
	init_dinSessionStopType(&dinDoc.V2G_Message.Body.SessionStopReq);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeSessionStopRequest finished");
}

void encodeSessionStopResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.SessionStopRes_isUsed = 1u;
	init_dinSessionStopResType(&dinDoc.V2G_Message.Body.SessionStopRes);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeSessionStopResponse finished");
}


static void encodeContractAuthenticationRequest(void) {
	useSessionIdFromCommandLine();
	init_dinMessageHeaderWithSessionID();
	dinDoc.V2G_Message_isUsed = 1u;
	init_dinMessageHeaderType(&dinDoc.V2G_Message.Header);
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ContractAuthenticationReq_isUsed = 1u;
	init_dinContractAuthenticationReqType(&dinDoc.V2G_Message.Body.ContractAuthenticationReq);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeContractAuthenticationRequest finished");
}

void encodeContractAuthenticationResponse(void) {
	init_dinMessageHeaderWithSessionID();
	init_dinBodyType(&dinDoc.V2G_Message.Body);
	dinDoc.V2G_Message.Body.ContractAuthenticationRes_isUsed = 1u;
	init_dinContractAuthenticationResType(&dinDoc.V2G_Message.Body.ContractAuthenticationRes);
	prepareGlobalStream();
	g_errn = encode_dinExiDocument(&global_stream1, &dinDoc);
    printGlobalStream();
    sprintf(gInfoString, "encodeContractAuthenticationResponse finished");
}



/* Converting parameters to an EXI stream */
static void runTheEncoder(char* parameterStream) {
  //printf("runTheEncoder\n");
  /* Parameter description: Three letters:
      - First letter: E=Encode
	  - Second letter: Schema selection H=Handshake, D=DIN, 1=ISO1, 2=ISO2
	  - Third letter: A to Z for requests, a to z for responses.
	  - afterwards: parameter list, without blanks, separated by underlines
  */
  if (strlen(parameterStream)<2) {
	  sprintf(gErrorString, "ERROR: runTheEncoder: parameter list too short");
	  return;
  }
  nNumberOfFoundAdditionalParameters = 0;
  if (strlen(parameterStream)>3) {
	  /* we found additional parameters. Parse them into an array of strings. */
	  strcpy(gAdditionalParamList, &parameterStream[3]);
	  parseAdditionalParameters();
  }
  
  switch (parameterStream[1]) { /* H=HandshakeRequest, h=HandshakeResponse, D=DIN, 1=ISO1, 2=ISO2 */
	case 'H':
		//encodeSupportedAppProtocolRequest();
		sprintf(gErrorString, "encodeSupportedAppProtocolRequest not yet implemented.");
		break;
	case 'h':
		encodeSupportedAppProtocolResponse();
		break;
	case 'D':
		switch (parameterStream[2]) {
			case 'A':
				encodeSessionSetupRequest();
				break;
			case 'a':
				encodeSessionSetupResponse();
				break;
			case 'B':
				encodeServiceDiscoveryRequest();
				break;
			case 'b':
				encodeServiceDiscoveryResponse();
				break;
			case 'C':
				encodeServicePaymentSelectionRequest(); /* DIN name is ServicePaymentSelection, but ISO name is PaymentServiceSelection */
				break;
			case 'c':
				encodeServicePaymentSelectionResponse(); /* DIN name is ServicePaymentSelection, but ISO name is PaymentServiceSelection */
				break;
			case 'D':
				sprintf(gErrorString, "AuthorizationRequest not specified for DIN.");
				break;
			case 'd':
				sprintf(gErrorString, "AuthorizationResponse not specified for DIN.");
				//encodeAuthorizationResponse();
				break;
			case 'E':
				encodeChargeParameterDiscoveryRequest();
				break;
			case 'e':
				encodeChargeParameterDiscoveryResponse();
				break;
			case 'F':
				encodeCableCheckRequest();
				break;
			case 'f':
				encodeCableCheckResponse();
				break;
			case 'G':
				encodePreChargeRequest();
				break;
			case 'g':
				encodePreChargeResponse();
				break;
			case 'H':
				encodePowerDeliveryRequest();
				break;
			case 'h':
				encodePowerDeliveryResponse();
				break;
			case 'I':
				encodeCurrentDemandRequest();
				break;
			case 'i':
				encodeCurrentDemandResponse();
				break;
			case 'J':
				encodeWeldingDetectionRequest();
				break;
			case 'j':
				encodeWeldingDetectionResponse();
				break;
			case 'K':
				encodeSessionStopRequest();
				break;
			case 'k':
				encodeSessionStopResponse();
				break;
			case 'L':
				encodeContractAuthenticationRequest();
				break;
			case 'l':
				encodeContractAuthenticationResponse();
				break;
			default:
				sprintf(gErrorString, "invalid message in DIN encoder requested");
		}
		break;
	case '1':
		sprintf(gErrorString, "ISO1 encoder not yet implemented");
		break;
	case '2':
		sprintf(gErrorString, "ISO2 encoder not yet implemented");
		break;
	default:
		sprintf(gErrorString, "invalid encoder requested");
  }
}

/** Converting EXI stream to parameters  */
static void runTheDecoder(char* parameterStream) {
	int i;
	int numBytes;
	char strOneByteHex[3];

	if (strlen(parameterStream)<4) {
		/* minimum is 4 characters, e.g. DH01 */
		sprintf(gErrorString, "parameter too short");
		return;
	}
	/*** step 1: convert the hex string into an array of bytes ***/
	global_stream1.size = BUFFER_SIZE;
	global_stream1.data = mybuffer;
	global_stream1.pos = &global_pos1;
	numBytes=strlen(parameterStream)/2; /* contains one "virtual byte e.g. DH" at the beginning, which does not belong to the payload. */
	global_pos1 = 0;
	strOneByteHex[2]=0;
	/* convert the hex stream into array of bytes: */
	for (i=1; i<numBytes; i++) { /* starting at 1, means the first two characters (the direction-and-schema-selectors) are jumped-over. */
		strOneByteHex[0] = parameterStream[2*i];
		strOneByteHex[1] = parameterStream[2*i+1];
		mybuffer[global_pos1++] = strtol(strOneByteHex, NULL, 16); /* convert the hex representation into a byte value */
	}
	sprintf(gInfoString, "%d bytes to convert", global_pos1);
	/*
	printf("size = %d\n", global_stream1.size);
	printf("pos  = %d\n", *(global_stream1.pos));
	for (i=0; i<(*global_stream1.pos); i++) {
		printf("%02x ", global_stream1.data[i]);
	}
	printf("\n");
	*/
	*(global_stream1.pos) = 0; /* the decoder shall start at the byte 0 */	
	
	/*** step 2: decide about which schema to use, and call the related decoder ***/
	/* The second character selects the schema. */
	/* The OpenV2G supports 4 different decoders:
	    decode_appHandExiDocument
		decode_iso1ExiDocument
		decode_iso2ExiDocument
		decode_dinExiDocument
		The caller needs to choose, depending on its context-knowledge, the correct decoder.
		The first step in a session is always to use the decode_appHandExiDocument for finding out, which specification/decoder
		is used in the next steps. */
	g_errn = 0;
	switch (parameterStream[1]) {
		case 'H': /* for the decoder, it does not matter whether it is a handshake request (H) or handshake response (h).
		             The same decoder schema is used. */
		case 'h':
			g_errn = decode_appHandExiDocument(&global_stream1, &aphsDoc);
			translateDocAppHandToJson();
			break;
		case 'D': /* The DIN schema decoder */
			g_errn = decode_dinExiDocument(&global_stream1, &dinDoc);
			translateDocDinToJson();
			break;
		case '1': /* The ISO1 schema decoder */
			g_errn = decode_iso1ExiDocument(&global_stream1, &iso1Doc);
			//translateDocIso1ToJson();
			break;
		case '2': /* The ISO2 schema decoder */
			g_errn = decode_iso2ExiDocument(&global_stream1, &iso2Doc);
			//translateDocIso2ToJson();
			break;
		default:
			sprintf(gErrorString, "The second character of the parameter must be H for applicationHandshake, D for DIN, 1 for ISO1 or 2 for ISO2.");
			g_errn = -1;
	}
			
	if(g_errn) {
			/* an error occured */
			sprintf(gErrorString, "runTheDecoder error%d", g_errn);
	}		
}

/* The entry point */
int main_commandline(int argc, char *argv[]) {
	strcpy(gInfoString, "");
	strcpy(gErrorString, "");
	strcpy(gResultString, "");
	strcpy(gPropertiesString, "");
	strcpy(gDebugString, "");
	strcpy(gMessageName, "");
	if (argc>=2) {
		//printf("OpenV2G will process %s\n", argv[1]);
		/* The first char of the parameter decides over Encoding or Decoding. */
		if (argv[1][0]=='E') {
			runTheEncoder(argv[1]);
		} else if (argv[1][0]=='D') {
			runTheDecoder(argv[1]);
		} else {
			sprintf(gErrorString, "The first character of the parameter must be D for decoding or E for encoding.");
		}
	} else {
		sprintf(gErrorString, "OpenV2G: Error: To few parameters.");
	}
	addProperty("debug", gDebugString);
	/* compose a JSON string out of all the elements: */
	printf("{\n\"msgName\": \"%s\",\n\"info\": \"%s\", \n\"error\": \"%s\",\n\"result\": \"%s\"%s\n}",
		gMessageName,
		gInfoString,
		gErrorString,
		gResultString,
		gPropertiesString);
	return 0;
}


