// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#ifndef DEMO_CONFIG_H
#define DEMO_CONFIG_H

/* FreeRTOS config include. */
#include "FreeRTOSConfig.h"

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Include logging header files and define logging macros in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define the LIBRARY_LOG_NAME and LIBRARY_LOG_LEVEL macros depending on
 * the logging configuration for DEMO.
 * 3. Include the header file "logging_stack.h", if logging is enabled for DEMO.
 */

#include "logging_levels.h"

/* Logging configuration for the Demo. */
#ifndef LIBRARY_LOG_NAME
    #define LIBRARY_LOG_NAME    "MQTTDemo"
#endif

#ifndef LIBRARY_LOG_LEVEL
    #define LIBRARY_LOG_LEVEL    LOG_INFO
#endif

/* Prototype for the function used to print to console on Windows simulator
 * of FreeRTOS.
 * The function prints to the console before the network is connected;
 * then a UDP port after the network has connected. */
extern void vLoggingPrintf( const char * pcFormatString,
                            ... );

/* Map the SdkLog macro to the logging function to enable logging
 * on Windows simulator. */
#ifndef SdkLog
    #define SdkLog( message )    vLoggingPrintf message
#endif

#include "logging_stack.h"

/************ End of logging configuration ****************/

/************ WiFi Configuration **************************/
/* Define the default wifi ssid and password. The user can override this 
   via -D command line option or via project settings.  */

#ifndef WIFI_SSID
//#error "Symbol WIFI_SSID must be defined."
#define WIFI_SSID                           "<YOUR WIFI SSID>"
#endif /* WIFI_SSID  */

#ifndef WIFI_PASSWORD
//#error "Symbol WIFI_PASSWORD must be defined."
#define WIFI_PASSWORD                       "<YOUR WIFI PASSWORD>"
#endif /* WIFI_PASSWORD  */

/* WIFI Security type, the security types are defined in wifi.h.
  WIFI_ECN_OPEN = 0x00,         
  WIFI_ECN_WEP = 0x01,          
  WIFI_ECN_WPA_PSK = 0x02,      
  WIFI_ECN_WPA2_PSK = 0x03,     
  WIFI_ECN_WPA_WPA2_PSK = 0x04, 
*/
#ifndef WIFI_SECURITY_TYPE
//#error "Symbol WIFI_SECURITY_TYPE must be defined."
#define WIFI_SECURITY_TYPE WIFI_ECN_WPA2_PSK
#endif /* WIFI_SECURITY_TYPE  */

/************ End of WiFi Configuration ********************/

/**
 * @brief Enable Device Provisioning
 * 
 * @note To disable Device Provisioning undef this macro
 *
 */
#define democonfigENABLE_DPS_SAMPLE

#ifdef democonfigENABLE_DPS_SAMPLE

/**
 * @brief Provisioning service endpoint.
 *
 * @note https://docs.microsoft.com/en-us/azure/iot-dps/concepts-service#service-operations-endpoint
 * 
 */
#define democonfigENDPOINT                  "<YOUR DPS ENDPOINT HERE>"

/**
 * @brief Id scope of provisioning service.
 * 
 * @note https://docs.microsoft.com/en-us/azure/iot-dps/concepts-service#id-scope
 * 
 */
#define democonfigID_SCOPE                  "<YOUR ID SCOPE HERE>"

/**
 * @brief Registration Id of provisioning service
 * 
 * @warning If using X509 authentication, this MUST match the Common Name of the cert.
 *
 *  @note https://docs.microsoft.com/en-us/azure/iot-dps/concepts-service#registration-id
 */
#define democonfigREGISTRATION_ID           "<YOUR REGISTRATION ID HERE>"

#endif // democonfigENABLE_DPS_SAMPLE

/**
 * @brief IoTHub device Id.
 *
 */
#define democonfigDEVICE_ID                 "<YOUR DEVICE ID HERE>"

/**
 * @brief IoTHub module Id.
 *
 */
#define democonfigMODULE_ID                 ""
/**
 * @brief IoTHub hostname.
 *
 */
#define democonfigHOSTNAME                  "<YOUR IOT HUB HOSTNAME HERE>"

/**
 * @brief Device symmetric key
 *
 */
#define democonfigDEVICE_SYMMETRIC_KEY      "<Symmetric key>"

/**
 * @brief Client's X509 Certificate.
 *
 */
// #define democonfigCLIENT_CERTIFICATE_PEM    "<YOUR DEVICE CERT HERE>"

/**
 * @brief Client's private key.
 * 
 */
// #define democonfigCLIENT_PRIVATE_KEY_PEM    "<YOUR DEVICE PRIVATE KEY HERE>"

/**
 * @brief Baltimore Trusted RooT CA.
 *
 */
#define democonfigROOT_CA_PEM "-----BEGIN CERTIFICATE-----\r\n" \
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\r\n" \
"RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\r\n" \
"VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\r\n" \
"DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\r\n" \
"ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\r\n" \
"VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\r\n" \
"mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\r\n" \
"IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\r\n" \
"mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\r\n" \
"XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\r\n" \
"dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\r\n" \
"jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\r\n" \
"BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\r\n" \
"DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\r\n" \
"9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\r\n" \
"jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\r\n" \
"Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\r\n" \
"ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\r\n" \
"R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\r\n" \
"-----END CERTIFICATE-----\r\n"

/**
 * @brief An option to disable Server Name Indication.
 *
 * @note When using a local Mosquitto server setup, SNI needs to be disabled
 * for an MQTT broker that only has an IP address but no hostname. However,
 * SNI should be enabled whenever possible.
 */
#define democonfigDISABLE_SNI              ( pdFALSE )

/**
 * @brief The name of the operating system that the application is running on.
 * The current value is given as an example. Please update for your specific
 * operating system.
 */
#define democonfigOS_NAME                   "FreeRTOS"

/**
 * @brief The version of the operating system that the application is running
 * on. The current value is given as an example. Please update for your specific
 * operating system version.
 */
#define democonfigOS_VERSION                tskKERNEL_VERSION_NUMBER

/**
 * @brief Set the stack size of the main demo task.
 *
 * In the Windows port, this stack only holds a structure. The actual
 * stack is created by an operating system thread.
 */
#define democonfigDEMO_STACKSIZE            ( 2 * 1024U)

/**
 * @brief Size of the network buffer for MQTT packets.
 */
#define democonfigNETWORK_BUFFER_SIZE       ( 5 * 1024U )

/**
 * @brief IoTHub endpoint port.
 */
#define democonfigIOTHUB_PORT          ( 8883 )

#endif /* DEMO_CONFIG_H */
