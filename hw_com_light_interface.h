/***********************************************************************************
 *  Copyright (C) 2026 by STAR COOPERATION GmbH. All rights reserved.
 *
 *  This file is part of the Hw Com Light module.
 *
 ***********************************************************************************/

 /**
  * @file 	hw_com_light_interface.h
  * @author 	STAR COOPERATION GmbH
  * @date 	21 Jan 2026
  *
  * This file contains data type declarations for Hw Com Light module.
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
  * (C) 2026 by STAR COOPERATION GmbH. All Rights Reserved. <br>
  * No part of this document may be reproduced in any form (photocopy, microfilm or another procedure) <br>
  * without prior written consent from STAR COOPERATION.
  */

#ifndef HW_COM_LIGHT_INTERFACE_H_
#define HW_COM_LIGHT_INTERFACE_H_

/* Export macros: */
#if defined(_WIN32) || defined(_WIN64)
  #if defined(_HW_COM_LIGHT_EXPORTS)
    #define HW_COM_LIGHT_EXPORTDLL __declspec(dllexport)
  #elif defined(_HW_COM_LIGHT_STATIC_LIB)
    #define HW_COM_LIGHT_EXPORTDLL /* static lib: no import/export */
  #else
    #define HW_COM_LIGHT_EXPORTDLL __declspec(dllimport)
  #endif
#else
  /* Linux/GCC: use visibility attribute for shared library */
  #if defined(_HW_COM_LIGHT_EXPORTS)
    #define HW_COM_LIGHT_EXPORTDLL __attribute__ ((visibility ("default")))
  #else
    #define HW_COM_LIGHT_EXPORTDLL /* static lib or import: no attribute needed */
  #endif
#endif


#include "cai_typedefs.h"

/* Ensure C linkage when compiling with a C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

  /**
   * Create new instance of Hw Com Light module.
   * 
   * Backend selection is automatic based on address format:
   * - IPv4 addresses (e.g., "192.168.1.100") -> UDP network backend
   * - Device paths (e.g., "/dev/device") -> Direct device I/O backend. 
   *   Linux: The first FL3X PCIe device is accessible via the device path /dev/flexcard_ng-dt0. Requires kernel_ng driver version >= 6.12.1.2.
   *          Appending "/raw" to the device path (e.g., "/dev/flexcard_ng-dt0/raw") enables raw mode which bypasses the internal network stack of the embedded device.
   *   Windows: Direct device I/O backend currently not supported
   *
   * @param handle			Returned opaque handle to new instance (must call hw_com_light_destroy to cleanup)
   * @param ipv4_dst			Address string: IPv4 address for network communication or device path for direct access
   * @param port_dst			Destination port number (typically 3333)
   * @param rcv_timeout_ms	Response timeout in milliseconds. Value '0' means wait infinitely.
   *
   * @return 					t_hw_com_light_error - HW_COM_LIGHT_ERROR_OK on success, error code on failure
   */
  HW_COM_LIGHT_EXPORTDLL t_hw_com_light_error hw_com_light_create(HANDLE* handle, char* ipv4_dst, u16 port_dst, u32 rcv_timeout_ms);

  /**
   * Destroy an instance of Hw Com Light module.
   *
   * @param handle		Handle of an instance to destroy
   *
   * @return 				t_hw_com_light_error
   */
  HW_COM_LIGHT_EXPORTDLL t_hw_com_light_error hw_com_light_destroy(HANDLE handle);

  /**
   * Set values of signals or/and pdus.
   *
   * @param handle		Handle of Hw Com Light instance
   * @param values		Array of values to be set
   * @param count			Count of values in the array.
   * @param wait			Wait for response with timeout: 0 - no response required, 1 - wait for response.
   *
   * @return 				t_hw_com_light_error
   */
  HW_COM_LIGHT_EXPORTDLL t_hw_com_light_error hw_com_light_values_set(HANDLE handle, t_hw_com_light_value* values, u16 count, u08 wait);

  /**
   * Set values of signals or/and pdus.
   *
   * @param handle		Handle of Hw Com Light instance
   * @param values		Array of values to be get
   * @param count			Count of values in the array.
   *
   * @return 				t_hw_com_light_error
   */
  HW_COM_LIGHT_EXPORTDLL t_hw_com_light_error hw_com_light_values_get(HANDLE handle, t_hw_com_light_value* values, u16 count);

  /**
   * @brief Retrieves the version information of the HwComLight library.
   *
   * @param[out] version Pointer to a t_hw_com_light_version structure that will
   *                     be filled with the version information. Must not be NULL.
   *
   * @return t_hw_com_light_error Error code indicating the result of the operation.
   *         - Returns success code if version information was retrieved successfully.
   *         - Returns error code if the operation failed (e.g., invalid parameter).
   *
   * @note The caller must ensure that the version parameter points to valid memory.
   */
  HW_COM_LIGHT_EXPORTDLL t_hw_com_light_error hw_com_light_version_get(t_hw_com_light_version* version);

  /**
  * Get timestamp of application.
  *
  * @param handle			Handle of Hw Com Light instance
  * @param date_time_low		Returned lower part of timestamp
  * @param date_time_high	Returned higher part of timestamp.
  *
  * @return 				t_hw_com_light_error
  */
  HW_COM_LIGHT_EXPORTDLL t_hw_com_light_error hw_com_light_timestamp_get(HANDLE handle, u32* date_time_low, u32* date_time_high);

#ifdef __cplusplus
}
#endif

#endif /* HW_COM_LIGHT_INTERFACE_H_ */
