//  Copyright (C) 2018-2022  SEIKO EPSON CORPORATION
//
//  License: LGPL-2.1+
//  Author : SEIKO EPSON CORPORATION
//
//  This file is part of the 'Epson Scan 2' package.
//	 This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.

//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  ESCANLIB.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#ifndef WIN32
#define ESCANLIB 
#include <stdint.h>
#define WINAPI 
#define APIENTRY 
#define CALLBACK 
typedef uint32_t DWORD;
typedef int BOOL;
typedef int INT;
#define WCHAR char
#define LPCWSTR const WCHAR*
typedef unsigned short WORD;
typedef void* PVOID;
typedef long LONG;
typedef void* HANDLE;
typedef const char* LPCSTR;
typedef LPCSTR LPCTSTR;
#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#define ESL_STAT_READY 0x00030001
#define ESL_STAT_ERR_COVER_OPEN 0x00030002
#define ESL_STAT_ERR_PAPER_JAM 0x00030003
#define ESL_STAT_ERR_PAPER_EMPTY 0x00030004
#define ESL_STAT_ERR_FATAL 0x00030005
#define ESL_STAT_ERR_LAMP_TIME_FATAL 0x00030006
#define ESL_STAT_ERR_CR_LOCK 0x00030007
#define ESL_STAT_ERR_DOUBLE_FEED 0x00030008
#define ESL_STAT_ERR_DOCUMENT_TRAY_CLOSE 0x00030009
#define ESL_STAT_ERR_LOW_BATTERY 0x00030010
#define ESL_STAT_ERR_CARRIER_SHEET_SENSOR 0x00030011
#define ESL_STAT_ERR_EDGE_TRACKING_SENSOR 0x00030012
#define ESL_STAT_ERR_PAPER_PROTECTION 0x00030013
#define ESL_STAT_ERR_SEPARATION_LEVER 0x00030014
#define ESL_STAT_ERR_POSE 0x00030015
#define ESL_STAT_ERR_GAP_SENSOR 0x00030016
#define ESL_STAT_ERR_UNKNOWN 0x00030017
typedef struct tagRECT
{
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT;
#endif
typedef enum _eConnectType{
 CT_DEFAULT = 0,
 CT_LOCAL = 1,
 CT_NET_IPV4 = 2,
 CT_NET_IPV6 = 3
} eConnectType;
typedef struct _ConnectInfo {
 eConnectType connectType;
 WCHAR deviceName[64];
 WCHAR networkAddress[64];
} ConnectInfo;
typedef enum _eParamOpType{
 POT_SET = 0,
 POT_GET_CURRENT,
 POT_GET_DEFAULT,
} eParamOpType;
#define ESL_PARAM_SCAN_BASIC 0x00000001
#define ESL_PARAM_SCAN_EX_V1 0x00000002
#define ESL_PARAM_SAVE_BASIC 0x00000011
#define ESL_PARAM_SAVE_EX_V1 0x00000012
#define ESL_PARAM_SAVE_JPEG 0x00000021
#define ESL_PARAM_SAVE_TIFF 0x00000022
#define ESL_PARAM_SAVE_PDF 0x00000023
#define ESL_PARAM_OBR_BASIC 0x00010001
#define ESL_PARAM_OCR_BASIC 0x00020002
#define ESL_PARAM_OCR_EX_V1 0x00020003
#define ESL_PARAM_INFO_BASIC 0x00000101
typedef struct _EslParamHdr {
 DWORD type;
 DWORD size;
} EslParamHdr, *pEslParamHdr;
typedef enum _eDocSource {
 SRC_AUTO = -1,
 SRC_FLATBED = 0,
 SRC_FEEDER_SIMPLEX = 1,
 SRC_FEEDER_DUPLEX = 2,
} eDocSource;
typedef enum _eImageType {
 IT_AUTO = -1,
 IT_COLOR = 0,
 IT_GRAY = 1,
 IT_MONO = 2,
} eImageType;
typedef enum _eDocSize {
 DS_AUTO = -1,
 DS_USER = 0,
 DS_A3 = 0x01,
 DS_A4 = 0x02,
 DS_A5 = 0x03,
 DS_B4 = 0x11,
 DS_B5 = 0x12,
 DS_US_LEDGER = 0x21,
 DS_US_LEGAL = 0x22,
 DS_US_LETTER = 0x23,
} eDocSize;
typedef enum _eSizeUnit {
 SU_INCH = 0,
 SU_MILLIMETER = 1,
 SU_PIXEL = 2,
} eSizeUnit;
typedef enum _eDocRotate {
 DR_AUTO = -1,
 DR_NONE = 0,
 DR_R90 = 1,
 DR_R180 = 2,
 DR_R270 = 3,
} eDocRotate;
typedef enum _eColorFilter {
 CF_NONE = 0x00000000,
 CF_DROPOUT_RED = 0x00000001,
 CF_DROPOUT_GREEN = 0x00000002,
 CF_DROPOUT_BLUE = 0x00000003,
 CF_DROPOUT_PINK = 0x00000004,
 CF_DROPOUT_PURPLE = 0x00000005,
 CF_DROPOUT_YELLOW = 0x00000006,
 CF_DROPOUT_ORANGE = 0x00000007,
 CF_DROPOUT_EXPBLACK = 0x00000008,
 CF_ENHANCE_RED = 0x00000011,
 CF_ENHANCE_GREEN = 0x00000012,
 CF_ENHANCE_BLUE = 0x00000013,
 CF_ENHANCE_PINK = 0x00000014,
 CF_ENHANCE_PURPLE = 0x00000015,
 CF_ENHANCE_YELLOW = 0x00000016,
 CF_ENHANCE_ORANGE = 0x00000017,
 CF_ENHANCE_EXPBLACK = 0x00000018,
} eColorFilter;
typedef enum _eDocEnhance {
 DE_NONE = 0x00000000,
 DE_TET_STD = 0x00000001,
 DE_TET_HIGH = 0x00000002,
 DE_AAS = 0x00000011,
} eDocEnhance;
#define ESL_IMGFILTER_USM 0x00000001
#define ESL_IMGFILTER_DESCREENING 0x00000002
typedef enum _eDFDetect {
 DFD_NONE = 0,
 DFD_LOW = 1,
 DFD_HIGH = 2,
} eDFDetect;
typedef enum _eBPSkip {
 BPS_NONE = 0,
 BPS_VERY_LOW = 1,
 BPS_LOW = 2,
 BPS_MEDIUM = 3,
 BPS_HIGH = 4,
} eBPSkip;
typedef enum _ePHRemove {
 PHR_NONE = 0,
 PHR_ON = 1,
} ePHRemove;
typedef enum _eSkewCorrect {
 SC_NONE = 0,
 SC_EDGE = 1,
 SC_CONTENTS = 2,
 SC_BOTH = 3,
} eSkewCorrect;
typedef struct _EslParamScanBasic {
 DWORD type;
 DWORD size;
 eDocSource docSource;
 eImageType imgType;
 WORD resolution;
 eDocSize docSize;
 eSizeUnit sizeUnit;
 RECT sizeUser;
 eDocRotate docRotate;
 LONG brightness;
 LONG contrast;
 LONG threshold;
 eColorFilter colorFilter;
 WORD numScan;
} EslParamScanBasic;
typedef struct _EslParamScanExV1 {
 DWORD type;
 DWORD size;
 eDocSource docSource;
 eImageType imgType;
 WORD resolution;
 eDocSize docSize;
 eSizeUnit sizeUnit;
 RECT sizeUser;
 eDocRotate docRotate;
 LONG brightness;
 LONG contrast;
 LONG threshold;
 eColorFilter colorFilter;
 WORD numScan;
 eDocEnhance docEnhance;
 DWORD imgFilter;
 eDFDetect optDoubleFeedDetect;
 eBPSkip optBlankPageSkip;
 ePHRemove optPunchHoleRemove;
 eSkewCorrect skewCorrect;
} EslParamScanExV1;
typedef enum _eFileFormat {
 FF_BMP = 0,
 FF_JPEG = 1,
 FF_TIFF = 2,
 FF_MULTITIFF = 3,
 FF_PDF = 4,
 FF_PNG = 5,
 FF_OFD = 6,
} eFileFormat;
typedef enum _eFileName {
 FN_PREFIX = 0,
 FN_BARCODE = 1,
 FN_OCR = 2,
} eFileName;
typedef enum _eTimeFormat {
 TF_NONE = 0,
 TF_YYYYMMDD = 1,
 TF_MMDDYYYY = 2,
 TF_DDMMYYYY = 3,
 TF_YYYYMMDD_HHMMSS = 4,
 TF_MMDDYYYY_HHMMSS = 5,
 TF_DDMMYYYY_HHMMSS = 6,
} eTimeFormat;
#define ESL_SYMBOL_UPC_EAN_JAN 0x00000001
#define ESL_SYMBOL_ITF 0x00000002
#define ESL_SYMBOL_CODE39 0x00000004
#define ESL_SYMBOL_CODABAR 0x00000008
#define ESL_SYMBOL_CODE128 0x00000010
#define ESL_SYMBOL_QR 0x00000020
#define ESL_SYMBOL_PDF417 0x00000040
#define ESL_SYMBOL_DM 0x00000080
typedef enum _eBCOrientation {
 BCO_BOTH = 0,
 BCO_HORIZONTAL = 1,
 BCO_VERTICAL = 2,
} eBCOrientation;
typedef enum _eOCRLanguage {
 OL_NONE = 0,
 OL_OCR_A = 1,
 OL_OCR_B = 2,
 OL_EN = 0x10,
 OL_JA = 0x11,
 OL_ZH_TW = 0x12,
 OL_ZH_CN = 0x13,
 OL_KO = 0x14,
 OL_FR = 0x15,
 OL_IT = 0x16,
 OL_DE = 0x17,
 OL_ES = 0x18,
 OL_PT = 0x19,
 OL_NL = 0x1A,
 OL_RU = 0x1B,
 OL_UK = 0x1C,
} eOCRLanguage;
typedef enum _eAssortType {
 AT_NONE = 0,
 AT_PAGECOUNT = 1,
 AT_BLANKPAGE = 2,
 AT_BARCODE = 3,
 AT_OCR = 4,
} eAssortType;
#define ESL_REMOVE_SEPARATOR 0x00000001
#define ESL_REMOVE_SEPARATOR_BACK 0x00000002
#define ESL_DETECT_BLANKPAGE_BACK 0x00000004
typedef enum _eBPLevel {
 BPL_LOW = 0,
 BPL_MEDIUM = 1,
 BPL_HIGH = 2,
} eBPLevel;
typedef enum _eFolderName {
 FON_NONE = 0,
 FON_PREFIX = 1,
 FON_TIMESTAMP = 2,
 FON_BARCODE_OCR = 3,
} eFolderName;
typedef enum _eSpecifiedParameter {
 SP_SLEEP_TIMER = 0,
 SP_POWER_OFF_TIME = 1,
} eSpecifiedParameter;
typedef struct _EslParamSaveBasic {
 DWORD type;
 DWORD size;
 DWORD numPageStart;
 DWORD numPageEnd;
 eFileFormat fileFormat;
 WCHAR filePath[MAX_PATH];
 eFileName fileNameType;
 WCHAR fileNamePrefix[40];
 eTimeFormat fileTimeFormat;
 WORD fileNumCounterDigits;
 WORD fileNumStartCount;
} EslParamSaveBasic;
typedef struct _EslParamSaveExV1 {
 DWORD type;
 DWORD size;
 DWORD numPageStart;
 DWORD numPageEnd;
 eFileFormat fileFormat;
 WCHAR filePath[MAX_PATH];
 eFileName fileNameType;
 WCHAR fileNamePrefix[40];
 eTimeFormat fileTimeFormat;
 WORD fileNumCounterDigits;
 WORD fileNumStartCount;
 DWORD fileBCType;
 eBCOrientation fileBCOrientation;
 eOCRLanguage fileOcrLanguage;
 eSizeUnit fileDetectUnit;
 RECT fileDetectRect;
 eAssortType assortType;
 DWORD assortOption;
 DWORD assortDivPageCount;
 eBPLevel assortBlankPageLevel;
 DWORD assortBCType;
 eBCOrientation assortBCOrientation;
 eOCRLanguage assortOcrLanguage;
 eSizeUnit assortDetectUnit;
 RECT assortDetectRect;
 eFolderName folderNameType;
 WCHAR folderNamePrefix[40];
 eTimeFormat folderTimeFormat;
 WORD folderNumCounterDigits;
 WORD folderNumStartCount;
} EslParamSaveExV1;
typedef struct _EslParamSaveJPEG {
 DWORD type;
 DWORD size;
 WORD imgQuality;
 BOOL encProgressive;
} EslParamSaveJPEG;
typedef enum _eByteOrder {
 BO_WINDOWS = 0,
 BO_MACINTOSH = 1,
} eByteOrder;
typedef enum _eTiffComp {
 TC_NONE = 0,
 TC_LZW = 1,
 TC_JPEG = 2,
 TC_CCITT_G4 = 3,
} eTiffComp;
typedef struct _EslParamSaveTIFF {
 DWORD type;
 DWORD size;
 eByteOrder byteOrder;
 eTiffComp compColorGray;
 eTiffComp compMono;
 WORD imgQuality;
} EslParamSaveTIFF;
typedef enum _ePdfType {
 PT_NORMAL = 0,
 PT_PDF_A = 1,
 PT_HIGHCOMP = 2,
} ePdfType;
typedef struct _EslParamSavePDF {
 DWORD type;
 DWORD size;
 ePdfType pdfType;
 BOOL addOcrText;
 eOCRLanguage ocrLanguage;
} EslParamSavePDF;
typedef struct _EslParamOBRBasic {
 DWORD type;
 DWORD size;
 DWORD numPageStart;
 DWORD numPageEnd;
 DWORD numDecode;
 DWORD symbolType;
 eBCOrientation orientation;
 eSizeUnit detectUnit;
 RECT detectRect;
} EslParamOBRBasic;
typedef struct _EslParamOCRBasic {
 DWORD type;
 DWORD size;
 DWORD numPageStart;
 DWORD numPageEnd;
 eOCRLanguage ocrLanguage;
 eSizeUnit detectUnit;
 RECT detectRect;
} EslParamOCRBasic;
#define ESL_OCRFONT_ALL 0x00000000
#define ESL_OCRFONT_NUM 0x00000001
#define ESL_OCRFONT_ALPHA_CAP 0x00000002
#define ESL_OCRFONT_ALPHA_SML 0x00000004
#define ESL_OCRFONT_ALPHA (ESL_OCRFONT_ALPHA_CAP | ESL_OCRFONT_ALPHA_SML)
#define ESL_OCRFONT_SYMBOL 0x00000008
typedef struct _EslParamOCRExV1 {
 DWORD type;
 DWORD size;
 DWORD numPageStart;
 DWORD numPageEnd;
 eOCRLanguage ocrLanguage;
 eSizeUnit detectUnit;
 RECT detectRect;
 DWORD ocrCharType;
} EslParamOCRExV1;
typedef struct _EslParamInfoBasic {
 DWORD type;
 DWORD size;
 WCHAR serialNumber[256];
 WCHAR reserved1[256];
 DWORD reserved2[3];
} EslParamInfoBasic;
typedef enum _eExecType{
 ET_SCAN_AND_SAVE = 0,
 ET_SCAN_AND_STORE,
 ET_SAVE_STORED_IMAGE,
 ET_GET_STORED_IMAGE,
 ET_GET_OBR_DATA,
 ET_GET_OCR_DATA,
} eExecType;
#define CBDT_STATUS_SCAN 0x00000001
#define CBDT_IMAGE_FILE 0x00000011
#define CBDT_IMAGE_MEMORY 0x00000012
#define CBDT_DATA_OBR 0x00010001
#define CBDT_DATA_OCR 0x00010002
typedef struct _EslCBDataHdr {
 DWORD type;
 DWORD size;
} EslCBDataHdr;
typedef BOOL (CALLBACK *peslCallback)(EslCBDataHdr* pData, PVOID pPrivate);
#define STATUS_SCAN_UPDATE_PROGRESS 0x00000001
#define STATUS_SCAN_PAGE_END 0x00000002
typedef struct _EslCBDataScanStatus {
 DWORD type;
 DWORD size;
 DWORD status;
 DWORD count;
 DWORD progress;
} EslCBDataScanStatus;
#define STATUS_IMAGE_FILE_INFO 0x00000011
typedef struct _EslCBDataImageFile {
 DWORD type;
 DWORD size;
 DWORD status;
 WCHAR filename[MAX_PATH];
} EslCBDImageFile;
#define STATUS_IMAGE_MEMORY_INFO 0x00000021
typedef struct _EslCBDataImageMemory {
 DWORD type;
 DWORD size;
 DWORD status;
 DWORD count;
 LONG img_width;
 LONG img_height;
 DWORD img_resolution;
 WORD img_channel_per_pixel;
 WORD img_bits_per_channel;
 DWORD img_data_size;
 HANDLE img_handle;
} EslCBDataImageMemory;
#define STATUS_DATA_OBR_RESULT 0x00000031
typedef struct _EslCBDataOBRData {
 DWORD type;
 DWORD size;
 DWORD status;
 DWORD count;
 DWORD index;
 DWORD symbolType;
 LONG dataLength;
 LPCWSTR dataString;
 LONG orientation;
} EslCBDataOBRData;
#define STATUS_DATA_OCR_RESULT 0x00000041
typedef struct _EslCBDataOCRData {
 DWORD type;
 DWORD size;
 DWORD status;
 DWORD count;
 LONG dataLength;
 LPCWSTR dataString;
} EslCBDataOCRData;
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI eslInit(DWORD* pInstance, LPCSTR pszKey, DWORD* pErrCode);
BOOL WINAPI eslFree(const DWORD Instance, DWORD* pErrCode);
BOOL WINAPI eslOpenScanner(const DWORD Instance, const ConnectInfo* pScanner, DWORD* pErrCode);
BOOL WINAPI eslCtrlParameter(const DWORD Instance, const eParamOpType OpType, EslParamHdr* pParam, DWORD* pErrCode);
BOOL WINAPI eslExecute(const DWORD Instance, const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate, DWORD* pErrCode);
BOOL WINAPI eslCloseScanner(const DWORD Instance, DWORD* pErrCode);
BOOL WINAPI eslGetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, INT* select);
BOOL WINAPI eslSetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, const INT setparam);
#ifndef WIN32
BOOL WINAPI eslGetDeviceStatus(const DWORD Instance, DWORD* pStatusCode, DWORD* pErrCode);
#endif
#ifdef __cplusplus
}
#endif
#define ESL_SUCCESS 0x00000000
#define ESL_CANCEL 0x00000001
#define ESL_ERR_PAPERJAM 0x40000020
#define ESL_ERR_PAPERDOUBLEFEED 0x40000021
#define ESL_ERR_OUTOFPAPER 0x40008002
#define ESL_ERR_ADFCOVEROPEN 0x40008003
#define ESL_ERR_GENERAL 0x80000001
#define ESL_ERR_NOT_INITIALIZED 0x80000002
#define ESL_ERR_FILE_MISSING 0x80000003
#define ESL_ERR_INVALID_PARAM 0x80000004
#define ESL_ERR_LOW_MEMORY 0x80000005
#define ESL_ERR_LOW_DISKSPACE 0x80000006
#define ESL_ERR_WRITE_FAIL 0x80000007
#define ESL_ERR_READ_FAIL 0x80000008
#define ESL_ERR_INVALID_OPERATION 0x80000009
#define ESL_ERR_INVALID_KEY 0x80010001
#define ESL_ERR_NOT_SUPPORTED 0x80020001
#define ESL_ERR_NO_DRIVER 0x80020002
#define ESL_ERR_OPEN_FAIL 0x80020003
#define ESL_ERR_SCAN_GENERAL 0x80030001
