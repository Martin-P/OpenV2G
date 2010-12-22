



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

 
 
 #ifdef __cplusplus
extern "C" {
#endif

#ifndef SERVICECLIENTSTUBS_H
#define SERVICECLIENTSTUBS_H

 #include "v2g_service.h"
 #include "v2g_serviceDataTypes.h"
 #include "v2g_serviceClientStubs.h"
 
/**  
 * \brief   Calls the remote sessionSetup method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct SessionSetupReqType* Request data for the server (has to be set up before)
 * \param	result   struct SessionSetupResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_sessionSetup(struct EXIService* service, struct HeaderType* header, struct SessionSetupReqType* params, struct SessionSetupResType* result);

 

	
/**  
 * \brief   Calls the remote serviceDiscovery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct ServiceDiscoveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct ServiceDiscoveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_serviceDiscovery(struct EXIService* service, struct HeaderType* header, struct ServiceDiscoveryReqType* params, struct ServiceDiscoveryResType* result);

 

	
/**  
 * \brief   Calls the remote selectedServicePayment method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct ServicePaymentSelectionReqType* Request data for the server (has to be set up before)
 * \param	result   struct ServicePaymentSelectionResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_selectedServicePayment(struct EXIService* service, struct HeaderType* header, struct ServicePaymentSelectionReqType* params, struct ServicePaymentSelectionResType* result);

 

	
/**  
 * \brief   Calls the remote paymentDetails method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PaymentDetailsReqType* Request data for the server (has to be set up before)
 * \param	result   struct PaymentDetailsResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_paymentDetails(struct EXIService* service, struct HeaderType* header, struct PaymentDetailsReqType* params, struct PaymentDetailsResType* result);

 

	
/**  
 * \brief   Calls the remote powerDiscovery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PowerDiscoveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct PowerDiscoveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_powerDiscovery(struct EXIService* service, struct HeaderType* header, struct PowerDiscoveryReqType* params, struct PowerDiscoveryResType* result);

 

	
/**  
 * \brief   Calls the remote lineLock method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct LineLockReqType* Request data for the server (has to be set up before)
 * \param	result   struct LineLockResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_lineLock(struct EXIService* service, struct HeaderType* header, struct LineLockReqType* params, struct LineLockResType* result);

 

	
/**  
 * \brief   Calls the remote powerDelivery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PowerDeliveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct PowerDeliveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_powerDelivery(struct EXIService* service, struct HeaderType* header, struct PowerDeliveryReqType* params, struct PowerDeliveryResType* result);

 

	
/**  
 * \brief   Calls the remote meteringStatus method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
  * \param	result   struct MeteringStatusResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_meteringStatus(struct EXIService* service, struct HeaderType* header, struct MeteringStatusResType* result);

 

	
/**  
 * \brief   Calls the remote meteringReceipt method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct MeteringReceiptReqType* Request data for the server (has to be set up before)
 * \param	result   struct MeteringReceiptResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
	int call_meteringReceipt(struct EXIService* service, struct HeaderType* header, struct MeteringReceiptReqType* params, struct MeteringReceiptResType* result);

 

	

	/* Initialize the v2g client */
	int init_v2gServiceClient(struct EXIService* service, bytes_t bytes, string_ucs_t string, uint8_t* inStream, size_t max_inStream_size, uint8_t* outStream, size_t max_outStream_size, uint16_t transportHeaderOffset);
 
#endif

#ifdef __cplusplus
}
#endif
