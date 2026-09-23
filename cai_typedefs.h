/***********************************************************************************
 *  Copyright (C) 2022 by STAR COOPERATION GmbH. All rights reserved.
 *
 *  This file is part of the Hw Com Light module.
 *
 ***********************************************************************************/

/**
 * @file 	hw_com_light_interface.h
 * @author 	STAR COOPERATION GmbH
 * @date 	04 Jan 2022
 *
 * This file contains interface declarations for Hw Com Light module.
 *
 *
 *
 * @mainpage Documentation of Hw Com Light Interface
 *
 * @section use_case Features
 *
 * With this module implements Hw Com Communication. <br>
 *
 *
 * The following features are supported:
 *
 * - Setting of Signal and PDU values 
 * - Getting of Signal and PDU values
 *
 * @section contact_info Contact Information
 * STAR ELECTRONICS GmbH & Co. KG A Company of the STAR COOPERATION Group <br>
 * Jahnstrasse 86 <br>
 * 73037 Goeppingen <br>
 * Phone: +49 (0)7031 6288-300 <br>
 * Phone: +49 (0)7031 6288-5330 (Support) <br>
 * Fax: +49 (0)7031 6288-5349 <br>
 * Sales: sales-ee@star-cooperation.com <br>
 * Support: support-ee@star-cooperation.com <br>
 * <a href="http://www.star-cooperation.com/ee-solutions">www.star-cooperation.com/ee-solutions</a>
 *
 * @section company_data Company Data
 * STAR ELECTRONICS GmbH & Co. KG, registered offices: Goeppingen, register court Ulm, HRA 721096 <br>
 * Partner liable to unlimited extent: STAR ELECTRONICS Verwaltungs-GmbH, registered offices: <br>
 * Goeppingen, register court Ulm, HRB 722565 <br>
 * Represented by the executive board: Rolf Wittig, Henning Lange <br>
 *
 * >>STAR ELECTRONICS<< represents STAR COOPERATION GmbH.
 *
 * @section copyright_notice Copyright Notice
 * (C) 2022 by STAR COOPERATION GmbH. All Rights Reserved. <br>
 * No part of this document may be reproduced in any form (photocopy, microfilm or another procedure) <br>
 * without prior written consent from STAR COOPERATION.
 */
#ifndef _CAI_TYPEDEFS_H_
#define _CAI_TYPEDEFS_H_

#ifndef HANDLE
typedef void* HANDLE;
#endif

#ifndef s08
typedef signed char s08;
#endif
#ifndef u08
typedef unsigned char u08;
#endif
#ifndef vs08
typedef volatile signed char vs08;
#endif
#ifndef vu08
typedef volatile unsigned char vu08;
#endif

#ifndef s16
typedef signed short s16;
#endif
#ifndef u16
typedef unsigned short u16;
#endif
#ifndef vs16
typedef volatile signed short vs16;
#endif
#ifndef vu16
typedef volatile unsigned short vu16;
#endif

#ifndef s32
typedef signed int s32;
#endif
#ifndef u32
typedef unsigned int u32;
#endif
#ifndef vs32
typedef volatile signed int vs32;
#endif
#ifndef vu32
typedef volatile unsigned int vu32;
#endif
#ifndef f32
typedef float f32;
#endif
#ifndef vf32
typedef volatile float vf32;
#endif

/**
 * Enumeration which describes possible error states
 */
typedef enum e_hw_com_light_error
{
	HW_COM_LIGHT_ERROR_OK = 0,
	HW_COM_LIGHT_ERROR_BAD_PARAMETER,
	HW_COM_LIGHT_ERROR_BAD_HANDLE,
	HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST,
	HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE,
	HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE,
	HW_COM_LIGHT_ERROR_OUT_OF_MEMORY,
	HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK,
	HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT,
	HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN,
	HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE,
	HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER,
	HW_COM_LIGHT_ERROR_RESPONSE_NACK,
	HW_COM_LIGHT_ERROR_FAILED,
	HW_COM_LIGHT_ERROR_SOCKET_FAILED,
	HW_COM_LIGHT_ERROR_SOCKET_BIND_FAILED,
	HW_COM_LIGHT_ERROR_RECEIVE_TIMEOUT,
	HW_COM_LIGHT_ERROR_SEND_TIMEOUT,
}t_hw_com_light_error;

/**
 * Structure which describes a value to be set or get
 */
typedef struct s_hw_com_light_value
{
	/**
	 * Address of the value (ID_Defienes.xml)
	 */
	u32 address;
	/**
	 * Length of the value in bytes (ID_Defienes.xml)
	 */
	u16 length;
	/**
	 * Buffer to store the value. 
	 * For data length <= 4 bytes -> use 'value' to store data.
	 * For data length > 4 bytes -> initialize 'buffer' with the address of allocated memory big enough to hold data to be set or get.
	 */
	 union
	 {
	 	/**
		 * For data length > 4 bytes -> initialize 'buffer' with the address of allocated memory big enough to hold data to be set or get.
		 */
	 	void* buf;
	 	/**
		 * For data length <= 4 bytes -> use 'value' to store data.
		 */
	 	u32 value;
	 }data;
} t_hw_com_light_value;
		

/// \brief Represents a version number.
typedef struct t_hw_com_light_version
{
    u08 Major;      ///< Major version number
    u08 Minor;      ///< Minor version number
    u08 Patch;      ///< Patch number (normally '0')
    u08 Build;      ///< Build number (normally '0')
} t_hw_com_light_version;

typedef struct S_HW_COM_LIGHT_PHS_DATA
{
	uint32_t address;
	uint16_t length;
	uint64_t physData;
} HW_COM_LIGHT_PHYS_DATA;

#endif /*_CAI_TYPEDEFS_H_ */



