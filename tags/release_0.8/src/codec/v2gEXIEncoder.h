/*
 * Copyright (C) 2007-2013 Siemens AG
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
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.8 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer.com</p>
 * <p>Schema: input/test_v2g/V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXI_v2g_ENCODER_H
#define EXI_v2g_ENCODER_H

/**
* \file 	EXIEncoder.h
* \brief 	EXI Encoder
*
*/

#include "EXITypes.h"
#include "v2gEXIEncoder.h"

/**
 * \brief 	Initialize EXI encoder
 *
 *         	Resets & initializes the EXI encoder.
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       runtimeTable   	Runtime name-tables
 * \param       stringTable   	String table
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gInitEncoder(bitstream_t* stream, exi_state_t* state,
		exi_name_table_runtime_t runtimeTable, exi_value_table_t stringTable);

/**
 * \brief  	Reports the beginning of a set of XML events
 *
 *			see EXI StartDocument (SD) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeStartDocument(bitstream_t* stream,
		exi_state_t* state);

/**
 * \brief  	Reports the end of a set of XML events
 *
 *			see EXI EndDocument (ED) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeEndDocument(bitstream_t* stream,
		exi_state_t* state);

/**
 * \brief  	Supplies the start of a known element
 *
 *			Provides access to the namespace URI and local name of the start tag by providing qnameID.
 *			Note: Both, namespace URI and local name are known (schema-informed) or have been encoded before.
 *			see EXI StartElement (SE) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       qnameID   		qualified name ID
 * \return                  	Error-Code <> 0
 *
 */
int
exiv2gEncodeStartElement(bitstream_t* stream,
		exi_state_t* state, uint16_t qnameID);

/**
 * \brief  	Supplies the start of an element where the namespace is known
 *
 *			Note: Namespace URI is known (schema-informed) or has been encoded before while local name is unknown.
 *			see EXI StartElement (SE) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       namespaceUriID  namespace URI ID
 * \param       localName  		local name as string
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeStartElementNS(bitstream_t* stream,
		exi_state_t* state, uint16_t namespaceUriID,
		exi_string_ucs_t* localName);

/**
 * \brief  	Supplies the start of an element where the namespace and the local name is unknown
 *
 *			Note: Neither namespace URI nor local name is known.
 *			see EXI StartElement (SE) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       namespaceUri  	namespace URI as string
 * \param       localName  		local name as string
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeStartElementGeneric(bitstream_t* stream,
		exi_state_t* state, exi_string_ucs_t* namespaceUri,
		exi_string_ucs_t* localName);

/**
 * \brief  	Supplies the end tag of an element
 *
 *			see EXI EndElement (EE) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeEndElement(bitstream_t* stream,
		exi_state_t* state);

/**
 * \brief  	Supplies characters value
 *
 *			Note: Special handling for list value.
 *			see EXI Characters (CH) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       val   			Characters value
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeCharacters(bitstream_t* stream,
		exi_state_t* state, exi_value_t* val);

/**
 * \brief  	Supplies an attribute qname and value
 *
 *			Note: Special handling for list value.
 *			see EXI Attribute (AT) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       qnameID   		qualified name ID
 * \param       val   			Attribute value
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeAttribute(bitstream_t* stream,
		exi_state_t* state, uint16_t qnameID, exi_value_t* val);




/**
 * \brief  	Supplies an attribute qname and value where the namespace is known
 *
 *			Note: Special handling for list value.
 *			see EXI Attribute (AT) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       namespaceUriID  Qualified namespace URI ID
 * \param       localName  		Qualified localname as String
 * \param       val   			Attribute value
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeAttributeNS(bitstream_t* stream,
		exi_state_t* state, uint16_t namespaceUriID,
		exi_string_ucs_t* localName, exi_value_t* val);


/**
 * \brief  	Supplies an attribute qname and value where the namespace and the local name is unknown
 *
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       namespaceUri  	namespace URI as string
 * \param       localName  		local name as string
 * \param       val   			Attribute value
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeAttributeGeneric(bitstream_t* stream,
		exi_state_t* state, exi_string_ucs_t* namespaceUri,
		exi_string_ucs_t* localName, exi_value_t* val);



/**
 * \brief  	Supplies an xsi:nil attribute
 *
 *			see EXI Attribute (AT) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       val   			Attribute value
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeAttributeXsiNil(bitstream_t* stream,
		exi_state_t* state, exi_value_t* val);

/**
 * \brief  	Supplies an xsi:type attribute
 *
 *			see EXI Attribute (AT) event
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       val   			Attribute value
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeAttributeXsiType(bitstream_t* stream,
		exi_state_t* state, exi_value_t* val);

/**
 * \brief  	Supplies list value for characters and attribute event
 *
 *			List values are special given that first the number and type of entry needs to be passed (element/attribute event) and then one by one the actual values.
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       qnameID   		qualified name ID
 * \param       val   			one list value
 * \param       lt   			list type
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gEncodeListValue(bitstream_t* stream,
		exi_state_t* state, uint16_t qnameID, exi_value_t* val, exi_list_t lt);

#endif

#ifdef __cplusplus
}
#endif

