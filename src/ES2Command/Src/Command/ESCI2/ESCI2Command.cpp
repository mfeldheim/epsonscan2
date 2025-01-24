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
//  ESCI2Command.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "CommonUtility/utils/stringutils.h"
#include "CommonUtility/utils/ESBuffer.h"
#include "Include/ES2Command/ESPropertyKeys.h"
#include "ESCI2Command.h"
#include "Utils/Endian.h"
#include "ESCI2JSONPerser.h"
#include "../ModelInfo.h"
#include "../Environment.h"
#include "Utils/ESUtils.h"
typedef enum
{
 kParseRuleNone = 0,
 kParseRuleOneValue,
 kParseRuleBoolean,
 kParseRuleBooleanList,
 kParseRuleSize,
 kParseRuleRect,
 kParseRuleString,
 kParseRuleList,
 kParseRuleRange,
 kParseRuleListOrRange,
 kParseRulePaperSize,
 kParseRuleError,
 kParseRulePageStart,
 kParseRulePageEnd,
 kParseRuleBGLevel,
 kParseRuleFocus,
 kParseRuleTerminator,
} ParseRule;
static ESAny ESCI2ParseOneValue(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 ESAny anyValue(cEnumerator.Nextdata());
 if (anyValue.type() == typeid(nullptr))
 {
  return anyValue;
 }
 dicContainer[strKey] = anyValue;
 return cEnumerator.Nextdata();
}
static ESAny ESCI2ParseBoolean(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 dicContainer[strKey] = true;
 return cEnumerator.Nextdata();
}
static ESAny ESCI2ParseBooleanList(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 dicContainer[strKey] = true;
 ESAny anyNextKey(cEnumerator.Nextdata());
 while (anyNextKey.type() != typeid(nullptr))
 {
  ESStringA *pStrNextKey = NULL;
  if ((anyNextKey.type() == typeid(ESStringA)) && ((pStrNextKey = SAFE_ANY_DATA_PTR(anyNextKey, ESStringA)) != NULL))
  {
   if (pStrNextKey->find("#") != ESStringA::npos)
   {
    return anyNextKey;
   }
   else
   {
    dicContainer[*pStrNextKey] = true;
   }
   anyNextKey = cEnumerator.Nextdata();
  }
  else
  {
   return anyNextKey;
  }
 }
 return nullptr;
}
static ESAny ESCI2ParseSize(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 try
 {
  ESNumber nW = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ESNumber nH = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ST_ES_SIZE_F size = MakeSize((float)nW, (float)nH);
  dicContainer[strKey] = size;
  return cEnumerator.Nextdata();
 }
 catch (...)
 {
  return nullptr;
 }
}
static ESAny ESCI2ParseRect(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 try
 {
  ESNumber nX = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ESNumber nY = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ESNumber nW = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ESNumber nH = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ST_ES_RECT_UN32 rc = MakeRect<UInt32>(nX, nY, (nX + nW), (nY + nH));
  dicContainer[strKey] = rc;
  return cEnumerator.Nextdata();
 }
 catch (...)
 {
  return nullptr;
 }
}
static ESAny ESCI2ParseString(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 ESAny anyValue(cEnumerator.Nextdata());
 if (anyValue.type() != typeid(nullptr))
 {
  ESByteData *pDataValue = SAFE_ANY_DATA_PTR(anyValue, ESByteData);
  if (pDataValue != NULL)
  {
   ESStringA strValue;
   strValue.assign(pDataValue->begin(), pDataValue->end());
   if (!strValue.empty())
   {
    dicContainer[strKey] = strValue;
   }
  }
 }
 else
 {
  if (IsEnableDumpCommand())
  {
   ES_INFO_LOG(ES_STRING("%s is empty."), ES_CMN_FUNCS::STRING::ToESString(strKey).c_str());
  }
 }
 return cEnumerator.Nextdata();
}
static ESAny ESCI2ParseList(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 int nCount = (int)dicContainer.count(strKey);
 if ((nCount == 0) ||
  (nCount != 0 && dicContainer[strKey].type() != typeid(ESAnyArray)))
 {
  ESAnyArray arTmp;
  dicContainer[strKey] = arTmp;
 }
 ESAnyArray &array = boost::any_cast<ESAnyArray &>(dicContainer[strKey]);
 ESAny anyNextKey = cEnumerator.Nextdata();
 while (anyNextKey.type() != typeid(nullptr))
 {
  ESStringA *pStrNextKey = NULL;
  if ((anyNextKey.type() == typeid(ESStringA)) && ((pStrNextKey = SAFE_ANY_DATA_PTR(anyNextKey, ESStringA)) != NULL))
  {
   if (pStrNextKey->find("#") != ESStringA::npos)
   {
    return anyNextKey;
   }
  }
  array.push_back(anyNextKey);
  anyNextKey = cEnumerator.Nextdata();
 }
 return nullptr;
}
static ESAny ESCI2ParseRange(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 try
 {
  ESNumber nFirst = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ESNumber nLast = boost::any_cast<ESNumber>(cEnumerator.Nextdata());
  ST_ES_RANGE stRange;
  stRange.nMin = nFirst;
  stRange.nMax = nLast;
  stRange.nStep = 1;
  dicContainer[strKey] = stRange;
  return cEnumerator.Nextdata();
 }
 catch (...)
 {
  return nullptr;
 }
}
static ESAny ESCI2ParseListOrRange(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 ESAny anyValue(cEnumerator.Nextdata());
 if (ESStringA *pStrType = SAFE_ANY_DATA_PTR(anyValue, ESStringA))
 {
  if ((*pStrType) == CESCI2Command::FCCSTR(DATATYPE_LIST))
  {
   return ESCI2ParseList(strKey, cEnumerator, dicContainer);
  }
  else if ((*pStrType) == CESCI2Command::FCCSTR(DATATYPE_RANGE))
  {
   return ESCI2ParseRange(strKey, cEnumerator, dicContainer);
  }
  return cEnumerator.Nextdata();
 }
 else
 {
  return anyValue;
 }
}
static ESAny ESCI2ParsePaperSize(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 try
 {
  ESAny anyOptionType(cEnumerator.Nextdata());
  ESAny anySize(cEnumerator.Nextdata());
  if (anyOptionType.type() != typeid(nullptr) && anySize.type() != typeid(nullptr))
  {
   ESStringA *pStrOptionType = SAFE_ANY_DATA_PTR(anyOptionType, ESStringA);
   if (pStrOptionType != NULL)
   {
    if (dicContainer.count(strKey) == 0)
    {
     ESDictionaryA dicValue;
     dicContainer[strKey] = dicValue;
    }
    ESDictionaryA *pDicValue = SAFE_KEYS_DATA_PTR(dicContainer, strKey.c_str(), ESDictionaryA);
    if (pDicValue != NULL)
    {
     (*pDicValue)[*pStrOptionType] = anySize;
    }
   }
  }
  return cEnumerator.Nextdata();
 }
 catch (...)
 {
  return nullptr;
 }
}
static ESAny ESCI2ParseError(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 try
 {
  ESAny anyPart(cEnumerator.Nextdata());
  ESAny anyFactor(cEnumerator.Nextdata());
  if (anyPart.type() != typeid(nullptr) && anyFactor.type() != typeid(nullptr))
  {
   ESStringA *pStrPart = SAFE_ANY_DATA_PTR(anyPart, ESStringA);
   if (pStrPart != NULL)
   {
    if (dicContainer.count(strKey) == 0)
    {
     ESDictionaryA dicValue;
     dicContainer[strKey] = dicValue;
    }
    ESDictionaryA *pDicValue = SAFE_KEYS_DATA_PTR(dicContainer, strKey.c_str(), ESDictionaryA);
    if (pDicValue != NULL)
    {
     (*pDicValue)[*pStrPart] = anyFactor;
    }
   }
  }
  return cEnumerator.Nextdata();
 }
 catch (...)
 {
  return nullptr;
 }
}
static ESAny ESCI2ParsePageStart(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 ESAny anyWidth(cEnumerator.Nextdata());
 if (anyWidth.type() == typeid(nullptr))
 {
  return anyWidth;
 }
 ESAny anyDummyBytesPerLine(cEnumerator.Nextdata());
 if (anyDummyBytesPerLine.type() == typeid(nullptr))
 {
  return anyDummyBytesPerLine;
 }
 ESAny anyHeight(cEnumerator.Nextdata());
 if (anyHeight.type() == typeid(nullptr))
 {
  return anyHeight;
 }
 ESDictionaryA dicValue;
 dicValue[ESCI2_DIC_KEY_WIDTH] = anyWidth;
 dicValue[ESCI2_DIC_KEY_DUMMY_BYTES_PER_LINE] = anyDummyBytesPerLine;
 dicValue[ESCI2_DIC_KEY_HEIGHT] = anyHeight;
 dicContainer[strKey] = dicValue;
 return cEnumerator.Nextdata();
}
static ESAny ESCI2ParsePageEnd(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 ESAny anyWidth(cEnumerator.Nextdata());
 if (anyWidth.type() == typeid(nullptr))
 {
  return anyWidth;
 }
 ESAny anyHeight(cEnumerator.Nextdata());
 if (anyHeight.type() == typeid(nullptr))
 {
  return anyHeight;
 }
 ESDictionaryA dicValue;
 dicValue[ESCI2_DIC_KEY_WIDTH] = anyWidth;
 dicValue[ESCI2_DIC_KEY_HEIGHT] = anyHeight;
 dicContainer[strKey] = dicValue;
 return cEnumerator.Nextdata();
}
static ESAny ESCI2ParseBGLevel(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 ESDictionary dicValue;
 dicValue[kESBGLevelKeyRed] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyRedWidth] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyGreen] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyGreenWidth] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyBlue] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyBlueWidth] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyMono] = cEnumerator.Nextdata();
 dicValue[kESBGLevelKeyMonoWidth] = cEnumerator.Nextdata();
 dicContainer[strKey] = dicValue;
 return cEnumerator.Nextdata();
}
static ESAny ESCI2ParseFocus(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 try
 {
  ESAny anyPart(cEnumerator.Nextdata());
  if (anyPart.type() != typeid(nullptr))
  {
   ESStringA *pStrPart = SAFE_ANY_DATA_PTR(anyPart, ESStringA);
   if (pStrPart != NULL)
   {
    if (dicContainer.count(strKey) == 0)
    {
     ESDictionaryA dicValue;
     dicContainer[strKey] = dicValue;
    }
    ESDictionaryA *pDicValue = SAFE_KEYS_DATA_PTR(dicContainer, strKey.c_str(), ESDictionaryA);
    if (pDicValue != NULL)
    {
     if (pStrPart->compare(CESCI2Command::FCCSTR(STAT_FOCUS_VALID)) == 0)
     {
      ESAny anyFactor(cEnumerator.Nextdata());
      if (anyFactor.type() != typeid(nullptr))
      {
       (*pDicValue)[*pStrPart] = anyFactor;
      }
     }
     else if (pStrPart->compare(CESCI2Command::FCCSTR(STAT_FOCUS_INVALID)) == 0)
     {
      (*pDicValue)[*pStrPart] = ESNumber(0);
     }
    }
   }
  }
  return cEnumerator.Nextdata();
 }
 catch (...)
 {
  return nullptr;
 }
}
static ESAny ESCI2ParseTerminator(const ESStringA &strKey, CESCI2DataEnumerator &cEnumerator, ESDictionaryA &dicContainer)
{
 cEnumerator.SetDataSource(NULL);
 return nullptr;
}
static ESAny ESCI2ParseElement(const ESAny &anyKey, CESCI2DataEnumerator &cEnumerator, const ESDictionaryA &dicRules, ESDictionaryA &dicContainer)
{
 if (anyKey.type() != typeid(ESStringA))
 {
  return cEnumerator.Nextdata();
 }
 const ESStringA &strKey = boost::any_cast<const ESStringA &>(anyKey);
 auto itr = dicRules.find(strKey);
 if (itr != dicRules.end())
 {
  if (itr->second.type() == typeid(ESDictionaryA))
  {
   ESAny anyNextKey(cEnumerator.Nextdata());
   if (anyNextKey.type() != typeid(nullptr))
   {
    const ESDictionaryA &dicSubRules = boost::any_cast<const ESDictionaryA &>(itr->second);
    if ((dicContainer.count(strKey) == 0) ||
     (dicContainer[strKey].type() != typeid(ESDictionaryA)))
    {
     ESDictionaryA dicAdd;
     dicContainer[strKey] = dicAdd;
    }
    ESDictionaryA &dicSubContainer = boost::any_cast<ESDictionaryA &>(dicContainer[strKey]);
    anyNextKey = ESCI2ParseElement(anyNextKey, cEnumerator, dicSubRules, dicSubContainer);
   }
   return anyNextKey;
  }
  else if (itr->second.type() == typeid(ParseRule))
  {
   const ParseRule eRule = boost::any_cast<ParseRule>(itr->second);
   switch (eRule)
   {
   case kParseRuleOneValue:
    return ESCI2ParseOneValue(strKey, cEnumerator, dicContainer);
   case kParseRuleBoolean:
    return ESCI2ParseBoolean(strKey, cEnumerator, dicContainer);
   case kParseRuleBooleanList:
    return ESCI2ParseBooleanList(strKey, cEnumerator, dicContainer);
   case kParseRuleSize:
    return ESCI2ParseSize(strKey, cEnumerator, dicContainer);
   case kParseRuleRect:
    return ESCI2ParseRect(strKey, cEnumerator, dicContainer);
   case kParseRuleString:
    return ESCI2ParseString(strKey, cEnumerator, dicContainer);
   case kParseRuleList:
    return ESCI2ParseList(strKey, cEnumerator, dicContainer);
   case kParseRuleRange:
    return ESCI2ParseRange(strKey, cEnumerator, dicContainer);
   case kParseRuleListOrRange:
    return ESCI2ParseListOrRange(strKey, cEnumerator, dicContainer);
   case kParseRulePaperSize:
    return ESCI2ParsePaperSize(strKey, cEnumerator, dicContainer);
   case kParseRuleError:
    return ESCI2ParseError(strKey, cEnumerator, dicContainer);
   case kParseRulePageStart:
    return ESCI2ParsePageStart(strKey, cEnumerator, dicContainer);
   case kParseRulePageEnd:
    return ESCI2ParsePageEnd(strKey, cEnumerator, dicContainer);
   case kParseRuleBGLevel:
    return ESCI2ParseBGLevel(strKey, cEnumerator, dicContainer);
   case kParseRuleFocus:
    return ESCI2ParseFocus(strKey, cEnumerator, dicContainer);
   case kParseRuleTerminator:
    return ESCI2ParseTerminator(strKey, cEnumerator, dicContainer);
   default:
    break;
   }
  }
  else
  {
   ;
  }
 }
 return cEnumerator.Nextdata();
}
static ESErrorCode ESCI2Pase(CESCI2DataEnumerator &cEnumerator, const ESDictionaryA &dicRules, ESDictionaryA *pDicOutResult)
{
 ESDictionaryA dicContainer;
 ESAny anyKey = cEnumerator.Nextdata();
 if (anyKey.type() == typeid(nullptr))
 {
  return kESErrorFatalError;
 }
 bool bNext = true;
 while (bNext)
 {
  anyKey = ESCI2ParseElement(anyKey, cEnumerator, dicRules, dicContainer);
  if (anyKey.type() == typeid(nullptr))
  {
   bNext = false;
  }
 }
 if (pDicOutResult != NULL)
 {
  pDicOutResult->swap(dicContainer);
 }
 return kESErrorNoError;
}
CESCI2Command::CESCI2DataEnumeratorDataSource::CESCI2DataEnumeratorDataSource()
 : m_pParent(NULL)
{
}
CESCI2Command::CESCI2DataEnumeratorDataSource::~CESCI2DataEnumeratorDataSource()
{
}
void CESCI2Command::CESCI2DataEnumeratorDataSource::Init(CESCI2Command *pParent)
{
 m_pParent = pParent;
}
UInt32 CESCI2Command::CESCI2DataEnumeratorDataSource::ReadFromEnumerator(CESCI2DataEnumerator *pSender, PESByte pBuffer, UInt32 un32Length)
{
 ES_LOG_TRACE_FUNC();
 if (m_pParent == NULL)
 {
  return 0;
 }
 ESErrorCode err = m_pParent->Read(pBuffer, un32Length);
 if (err != kESErrorNoError)
 {
  return 0;
 }
 return un32Length;
}
CESCI2Command::CESCI2Command()
{
 using namespace epsonscan2::es2command;
 m_bIsRetry = Environment::IsCommandRetry();
 m_bIsAllowAuthError = Environment::IsAllowStatusAuthError();
 m_bIsTransferring = false;
 m_eESCI2Mode = kModeNone;
 m_cEnumeratorDataSource.Init(this);
}
CESCI2Command::~CESCI2Command()
{
}
ESErrorCode CESCI2Command::Initialize()
{
 return kESErrorNoError;
}
ESStringA CESCI2Command::FCCSTR(const UInt32 un32CmdId)
{
 UInt32 un32BigEndian = CFSwapInt32HostToBig(un32CmdId);
 char buf[5] = {0};
 memcpy_s(buf, sizeof(buf), &un32BigEndian, sizeof(un32BigEndian));
 return buf;
}
UInt32 CESCI2Command::FourCharCode(const ESStringA strCode)
{
 UInt32 un32BigEndian = 0;
 if (!strCode.empty())
 {
  memcpy_s(&un32BigEndian, sizeof(un32BigEndian), strCode.c_str(), std::min<size_t>(strCode.length(), 4));
 }
 return CFSwapInt32BigToHost(un32BigEndian);
}
bool CESCI2Command::IsRetry()
{
 return m_bIsRetry;
}
bool CESCI2Command::IsShouldSyncFunctionalUnit()
{
 using namespace epsonscan2::es2command;
 return ModelInfo::Instance().IsShouldSyncFunctionalUnit(GetProductName());
}
bool CESCI2Command::IsShouldKeepControlMode()
{
 using namespace epsonscan2::es2command;
 return ModelInfo::Instance().IsShouldKeepControlMode(GetProductName());
}
bool CESCI2Command::IsShouldZeroClearEdgeFillForFB()
{
 using namespace epsonscan2::es2command;
 return ModelInfo::Instance().IsShouldZeroClearEdgeFillForFB(GetProductName());
}
bool CESCI2Command::IsShouldIgnoreDateAndTime()
{
 using namespace epsonscan2::es2command;
 return ModelInfo::Instance().IsShouldIgnoreDateAndTime(GetProductName());
}
bool CESCI2Command::IsShouldSendStatAfterADFScan()
{
 using namespace epsonscan2::es2command;
 return ModelInfo::Instance().IsShouldSendStatAfterADFScan(GetProductName());
}
ESErrorCode CESCI2Command::SyncFunctionalUnit()
{
 ESErrorCode err = kESErrorNoError;
 ESStringA strKey;
 switch (GetFunctionalUnitType())
 {
 case kESFunctionalUnitFlatbed:
  strKey = FCCSTR(INFO_FB);
  break;
 case kESFunctionalUnitDocumentFeeder:
  strKey = FCCSTR(INFO_ADF);
  break;
 case kESFunctionalUnitTransparent:
  strKey = FCCSTR(INFO_TPU);
  break;
 default:
  break;
 }
 if (!strKey.empty())
 {
  ESDictionaryA dic;
  ESStringSetA strSet;
  dic[strKey] = strSet;
  err = SendParameters(dic);
 }
 return err;
}
static const int DATA_HEADER_SIZE = 64;
ESErrorCode CESCI2Command::SendRequest(__in ESCI2RequestCode eRequestCode, __in_opt ESByteData *pParamData)
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode err = kESErrorNoError;
 CESCI2DataConstructor cReqConstructor;
 cReqConstructor.AppendFourCharString(FCCSTR(eRequestCode));
 int nParamSize = pParamData ? (int)pParamData->size() : 0;
 cReqConstructor.AppendHex(nParamSize);
 const ESByteData &reqData = cReqConstructor.GetData();
 if (IsEnableDumpCommand())
 {
  AfxGetLog()->Dump((PESByte)&reqData[0], (int)reqData.size(), "command.txt");
  if (pParamData != NULL)
  {
   AfxGetLog()->Dump((PESByte) & (*pParamData)[0], (int)pParamData->size(), "command.txt");
  }
 }
 if (pParamData == NULL)
 {
  err = Write((PESByte)&reqData[0], (UInt32)reqData.size(), DATA_HEADER_SIZE);
 }
 else
 {
  err = Write((PESByte)&reqData[0], (UInt32)reqData.size(), 0);
  if (err == kESErrorNoError)
  {
   err = Write((PESByte) & (*pParamData)[0], (UInt32)pParamData->size(), DATA_HEADER_SIZE);
  }
 }
 return err;
}
ESErrorCode CESCI2Command::ReceiveReply(__inout ESCI2RequestCode &eRequestCode, __out_opt ESDictionaryA *pDicOutHeaderInfo, __out_opt ES_CMN_FUNCS::BUFFER::CESHeapBuffer *pOutDataBuffer)
{
 ES_LOG_TRACE_FUNC();
 if (pOutDataBuffer)
 {
  pOutDataBuffer->FreeBuffer();
 }
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer cHeaderBuffer;
 if (!cHeaderBuffer.AllocBuffer(DATA_HEADER_SIZE))
 {
  ES_LOG_MEMORY_ALLOCATE_ERROR();
  return kESErrorMemoryError;
 }
 ESErrorCode err = Read(cHeaderBuffer.GetBufferPtr(), DATA_HEADER_SIZE);
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 if (IsEnableDumpCommand())
 {
  AfxGetLog()->Dump(cHeaderBuffer.GetBufferPtr(), cHeaderBuffer.GetLength(), "command.txt");
 }
 CESCI2DataEnumerator cEnumerator(cHeaderBuffer);
 ESAny anyRepCode = cEnumerator.Nextdata();
 if (anyRepCode.type() != typeid(ESStringA))
 {
  ES_LOG_INVALID_RESPONSE();
  return kESErrorInvalidResponse;
 }
 ESStringA &strRepCode = boost::any_cast<ESStringA &>(anyRepCode);
 ESAny anyDataSize = cEnumerator.Nextdata();
 if (anyDataSize.type() != typeid(ESNumber))
 {
  ES_LOG_INVALID_RESPONSE();
  return kESErrorInvalidResponse;
 }
 ESNumber nDataSize = boost::any_cast<ESNumber>(anyDataSize);
 eRequestCode = (ESCI2RequestCode)FourCharCode(strRepCode);
 if (IsEnableDumpCommand())
 {
#ifdef WIN32
  ES_INFO_LOG(ES_STRING("%s, %s, dataBlock = %d"), __FUNCTIONW__, ES_CMN_FUNCS::STRING::MBStringToUnicode(strRepCode.c_str()).c_str(), nDataSize);
#else
  ES_INFO_LOG(ES_STRING("%s, %s, dataBlock = %d"), __FUNCTION__, strRepCode.c_str(), nDataSize);
#endif
 }
 cEnumerator.SetDataSource(&m_cEnumeratorDataSource);
 err = ESCI2Pase(cEnumerator, HeaderPaseRule(), pDicOutHeaderInfo);
 if (IS_ERR_CODE(err))
 {
  ES_LOG_FAILED_PASE_DATA();
  return err;
 }
 if (nDataSize > 0)
 {
  ES_CMN_FUNCS::BUFFER::CESHeapBuffer cHeapBuffer;
  if (!cHeapBuffer.AllocBuffer(nDataSize))
  {
   ES_LOG_MEMORY_ALLOCATE_ERROR();
   return kESErrorMemoryError;
  }
  err = Read(cHeapBuffer.GetBufferPtr(), nDataSize);
  if (IS_ERR_CODE(err))
  {
   return err;
  }
  if (pOutDataBuffer)
  {
   pOutDataBuffer->Attach(cHeapBuffer);
  }
 }
 return err;
}
const ESDictionaryA &CESCI2Command::HeaderPaseRule()
{
 if (m_dicHeaderPaseRule.empty())
 {
  m_dicHeaderPaseRule[FCCSTR(HEADER_ERROR)] = kParseRuleError;
  m_dicHeaderPaseRule[FCCSTR(HEADER_ATTENTION)] = kParseRuleOneValue;
  m_dicHeaderPaseRule[FCCSTR(HEADER_NOTREADY)] = kParseRuleOneValue;
  m_dicHeaderPaseRule[FCCSTR(HEADER_PARAMETER)] = kParseRuleOneValue;
  m_dicHeaderPaseRule[FCCSTR(HEADER_SURFACETYPE)] = kParseRuleOneValue;
  m_dicHeaderPaseRule[FCCSTR(HEADER_PAGESTART)] = kParseRulePageStart;
  m_dicHeaderPaseRule[FCCSTR(HEADER_PAGEEND)] = kParseRulePageEnd;
  m_dicHeaderPaseRule[FCCSTR(HEADER_LEFTOVER_PAGE)] = kParseRuleOneValue;
  m_dicHeaderPaseRule[FCCSTR(HEADER_DOCUMENTTYPE)] = kParseRuleList;
  m_dicHeaderPaseRule[FCCSTR(HEADER_DOUBLEFEED_INFORMATION)] = kParseRuleOneValue;
  m_dicHeaderPaseRule[FCCSTR(HEADER_SUSPEND_NOTIFY)] = kParseRuleBoolean;
  m_dicHeaderPaseRule[FCCSTR(HEADER_TERMINATOR)] = kParseRuleTerminator;
 }
 return m_dicHeaderPaseRule;
}
ESErrorCode ErrorCodeForHeaderError(ESDictionaryA &dicHeaderError)
{
 ES_LOG_TRACE_FUNC();
 UInt32 un32Factor = 0;
 if (!dicHeaderError.empty())
 {
  ESDictionaryA::iterator it = dicHeaderError.begin();
  if (it->second.type() == typeid(ESStringA))
  {
   ESStringA &strFactor = boost::any_cast<ESStringA &>(it->second);
   un32Factor = CESCI2Command::FourCharCode(strFactor);
  }
 }
 switch (un32Factor)
 {
 case ERROR_FACTOR_COVEROPEN:
  ES_ERROR_LOG(ES_STRING("Error factor : cover open."));
  return kESErrorCoverOpen;
 case ERROR_FACTOR_PAPERJAM:
  ES_ERROR_LOG(ES_STRING("Error factor : paper jam."));
  return kESErrorPaperJam;
 case ERROR_FACTOR_PAPEREMPTY:
  ES_ERROR_LOG(ES_STRING("Error factor : paper empty."));
  return kESErrorPaperEmpty;
 case ERROR_FACTOR_CRLOCK:
  ES_ERROR_LOG(ES_STRING("Error factor : crlock."));
  return kESErrorCRLock;
 case ERROR_FACTOR_DOUBLEFEED:
  ES_ERROR_LOG(ES_STRING("Error factor : double feed."));
  return kESErrorPaperDoubleFeed;
 case ERROR_FACTOR_TRAYCLOSE:
  ES_ERROR_LOG(ES_STRING("Error factor : try close."));
  return kESErrorTrayClose;
 case ERROR_FACTOR_LAMPTIME:
  ES_ERROR_LOG(ES_STRING("Error factor : lamp time."));
  return kESErrorLampTime;
 case ERROR_FACTOR_AUTHFAIL:
  ES_ERROR_LOG(ES_STRING("Error factor : auth fail."));
  return kESErrorAuthFailure;
 case ERROR_FACTOR_NOPERMISSION:
  ES_ERROR_LOG(ES_STRING("Error factor : no permission."));
  return kESErrorNoPermission;
 case ERROR_FACTOR_CRSHEETSENSOR:
  ES_ERROR_LOG(ES_STRING("Error factor : carrier sheet sensor error"));
  return kESErrorCRSheetSensorError;
 case ERROR_FACTOR_STACKER_ERROR:
  ES_ERROR_LOG(L"Error factor : stacker error");
  return kESErrorPrintStackerError;
 case ERROR_FACTOR_PAPER_REMOVE_ERROR:
  ES_ERROR_LOG(L"Error factor : paper remove error");
  return kESErrorPaperRemoveError;
 case ERROR_FACTOR_SKEW_ERROR:
  ES_ERROR_LOG(L"Error factor : skew error");
  return kESErrorSkewDetectError;
 case ERROR_FACTOR_ETSENSOR:
  ES_ERROR_LOG(ES_STRING("Error factor : ET Sensor error"));
  return kESErrorETSensorError;
 case ERROR_FACTOR_PAPERPROTECT:
  ES_ERROR_LOG(ES_STRING("Error factor : paper protection error"));
  return kESErrorPaperProtect;
 case ERROR_FACTOR_SEPARATIONLEVER:
  ES_ERROR_LOG(ES_STRING("Error factor : Separation Lever error"));
  return kESErrorSeparationLeverError;
 case ERROR_FACTOR_POSE:
  ES_ERROR_LOG(ES_STRING("Error factor : Pose error"));
  return kESErrorPoseError;
 case ERROR_FACTOR_GAPSENSOR:
  ES_ERROR_LOG(ES_STRING("Error factor : GAP sensor error"));
  return kESErrorGAPSensorError;
 case ERROR_FACTOR_FATAL:
  ES_ERROR_LOG(ES_STRING("Error factor : fatal"));
  return kESErrorDeviceFatalError;
 case ERROR_FACTOR_PESENSOR:
  ES_ERROR_LOG(L"Error factor : PE sensor error");
  return kESErrorPESensorError;
 default:
  ES_ERROR_LOG(ES_STRING("Error factor : unknown.(0x%lx)"), (unsigned long)un32Factor);
  return kESErrorNoError;
 }
}
ESErrorCode CESCI2Command::RunSequence(
 __in ESCI2RequestCode eRequestCode,
 __in_opt ESByteData *pParamBlock,
 __out_opt ESDictionaryA *pDicOutHeaderInfo,
 __out_opt ES_CMN_FUNCS::BUFFER::CESHeapBuffer *pOutDataBuffer)
{
 ES_LOG_TRACE_FUNC();
 const int SEQ_RETRY_INTERVAL = 100;
 if (GetMode() == kModeNone)
 {
  ES_LOG_INVALID_SEQUENCE();
  return kESErrorSequenceError;
 }
 ESErrorCode err = kESErrorNoError;
 SYNCHRONIZED_START
 {
  while (1)
  {
   err = SendRequest(eRequestCode, pParamBlock);
   if (IS_ERR_CODE(err))
   {
    return err;
   }
   ESCI2RequestCode eReplyCode = eRequestCode;
   ESDictionaryA dicHeader;
   err = ReceiveReply(eReplyCode, &dicHeader, pOutDataBuffer);
   if (IS_ERR_CODE(err))
   {
    return err;
   }
   else if (eReplyCode != eRequestCode)
   {
    ES_LOG_INVALID_RESPONSE();
    err = kESErrorInvalidResponse;
    return err;
   }
   if (pDicOutHeaderInfo != NULL)
   {
    *pDicOutHeaderInfo = dicHeader;
   }
   ESStringA strHeaderError = FCCSTR(HEADER_ERROR);
   if (dicHeader.count(strHeaderError) != 0)
   {
    ES_LOG_INVALID_RESPONSE();
    if (dicHeader[strHeaderError].type() == typeid(ESDictionaryA))
    {
     ESDictionaryA &dicErrorInfo = boost::any_cast<ESDictionaryA &>(dicHeader[strHeaderError]);
     return ErrorCodeForHeaderError(dicErrorInfo);
    }
    return kESErrorInvalidResponse;
   }
   ESStringA strNotReady = FCCSTR(HEADER_NOTREADY);
   if (dicHeader.count(strNotReady) != 0)
   {
    if (dicHeader[strNotReady].type() == typeid(ESStringA))
    {
     ESStringA &strNotReadyStat = boost::any_cast<ESStringA &>(dicHeader[strNotReady]);
     UInt32 un32NotReadyStat = FourCharCode(strNotReadyStat);
     switch (un32NotReadyStat)
     {
     case NOTREADY_BUSY:
     case NOTREADY_WARMINGUP:
      ES_LOG_BUSY();
      if (IsRetry())
      {
       Sleep(SEQ_RETRY_INTERVAL);
       continue;
      }
      break;
     case NOTREADY_RESERVED:
      ES_LOG_NOT_READY();
      return kESErrorDeviceInUse;
     case NOTREADY_USERAUTH:
      ES_LOG_USERAUTH_ENABLED();
      return kESErrorUserAuthEnabled;
     default:
      break;
     }
    }
   }
   break;
  }
 }
 SYNCHRONIZED_END
 return err;
}
ESErrorCode CESCI2Command::RequestScannerControl()
{
 ES_LOG_TRACE_FUNC();
 ESByte buf[] = {FS, FS_REQUEST_CONTROL};
 if (IsEnableDumpCommand())
 {
  AfxGetLog()->Dump(buf, sizeof(buf), "command.txt");
 }
 ESErrorCode err = Write(buf, sizeof(buf), sizeof(ESByte));
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 ESByte byAck = 0;
 err = Read(&byAck, sizeof(ESByte));
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 if (byAck != ACK)
 {
  ES_LOG_INVALID_RESPONSE();
  return kESErrorInvalidResponse;
 }
 return kESErrorNoError;
}
ESErrorCode CESCI2Command::RequestScannerInquiry()
{
 ES_LOG_TRACE_FUNC();
 ESByte buf[] = {FS, FS_REQUEST_INQUIRY};
 if (IsEnableDumpCommand())
 {
  AfxGetLog()->Dump(buf, sizeof(buf), "command.txt");
 }
 ESErrorCode err = Write(buf, sizeof(buf), sizeof(ESByte));
 if (err != kESErrorNoError)
 {
  return err;
 }
 ESByte byAck = 0;
 err = Read(&byAck, sizeof(ESByte));
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 if (byAck != ACK)
 {
  ES_LOG_INVALID_RESPONSE();
  return kESErrorInvalidResponse;
 }
 return kESErrorNoError;
}
ESErrorCode CESCI2Command::RequestScannerMaintenance()
{
 ES_LOG_TRACE_FUNC();
 ESByte buf[] = {FS, FS_REQUEST_MAINTENANCE};
 if (IsEnableDumpCommand())
 {
  AfxGetLog()->Dump(buf, sizeof(buf), "command.txt");
 }
 ESErrorCode err = Write(buf, sizeof(buf), sizeof(ESByte));
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 ESByte byAck = 0;
 err = Read(&byAck, sizeof(ESByte));
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 if (byAck != ACK)
 {
  return kESErrorInvalidResponse;
 }
 return kESErrorNoError;
}
ESErrorCode CESCI2Command::RequestFinalize()
{
 ES_LOG_TRACE_FUNC();
 return RunSequence(REQUEST_FINALIZE, NULL, NULL, NULL);
}
ESErrorCode CESCI2Command::RequestMechanicalControlWithParameter(ESByteData &parameter)
{
 ES_LOG_TRACE_FUNC();
 ESCI2Mode eCurrentMode = GetMode();
 ESErrorCode err = SetMode(kModeControl);
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 err = RunSequence(REQUEST_MECHCONTROL, &parameter, NULL, NULL);
 ESErrorCode err2 = SetMode(eCurrentMode);
 if (IS_ERR_SUCCESS(err) && IS_ERR_CODE(err2))
 {
  err = err2;
 }
 return err;
}
CESCI2Command::ESCI2Mode CESCI2Command::GetMode()
{
 return m_eESCI2Mode;
}
ESErrorCode CESCI2Command::SetMode(ESCI2Mode eMode)
{
 ES_LOG_TRACE_FUNC();
 if (eMode & m_eESCI2Mode)
 {
  return kESErrorNoError;
 }
 if (eMode & kModeInquiry)
 {
  eMode = kModeInquiry;
 }
 else if (eMode & kModeControl)
 {
  eMode = kModeControl;
 }
 else if (eMode & kModeMaintenance)
 {
  eMode = kModeMaintenance;
 }
 else
 {
  eMode = kModeNone;
 }
 ESErrorCode err = kESErrorNoError;
 switch (m_eESCI2Mode)
 {
 case kModeControl:
 case kModeInquiry:
  err = RequestFinalize();
  break;
 case kModeMaintenance:
  err = RequestFinalize();
  {
   if (m_pDevInterface)
   {
    Sleep(m_pDevInterface->WaitTimeAfterFinalize());
   }
  }
  break;
 default:
  break;
 }
 if (IS_ERR_CODE(err))
 {
  goto BAIL;
 }
 switch (eMode)
 {
 case kModeControl:
  err = RequestScannerControl();
  break;
 case kModeInquiry:
  err = RequestScannerInquiry();
  break;
 case kModeMaintenance:
  err = RequestScannerMaintenance();
  break;
 default:
  break;
 }
BAIL:
 if (IS_ERR_SUCCESS(err))
 {
  m_eESCI2Mode = eMode;
 }
 return err;
}
ESByteData CESCI2Command::ParameterDataWithDict(ESDictionaryA &dicParameters, UInt32 un32MaxSize, ESStringArrayA &arOutProcessedKeys)
{
 ES_LOG_TRACE_FUNC();
 ESByteData outParameterData;
 arOutProcessedKeys.clear();
 ESStringArrayA s_arOrderKeys;
 if (s_arOrderKeys.empty())
 {
  s_arOrderKeys.push_back(FCCSTR(CAP_ADF));
  s_arOrderKeys.push_back(FCCSTR(CAP_TPU));
  s_arOrderKeys.push_back(FCCSTR(CAP_FB));
  s_arOrderKeys.push_back(FCCSTR(CAP_RESOLUTION_MAIN));
  s_arOrderKeys.push_back(FCCSTR(CAP_RESOLUTION_SUB));
  s_arOrderKeys.push_back(FCCSTR(CAP_COLORFORMAT));
  s_arOrderKeys.push_back(FCCSTR(CAP_IMAGEFORMAT));
  s_arOrderKeys.push_back(FCCSTR(CAP_JPEGQUALITY));
  s_arOrderKeys.push_back(FCCSTR(CAP_THRESHOLD));
  s_arOrderKeys.push_back(FCCSTR(CAP_DITHER_HALFTONE));
  s_arOrderKeys.push_back(FCCSTR(CAP_GAMMAMODE));
  s_arOrderKeys.push_back(FCCSTR(CAP_GAMMATABLE));
  s_arOrderKeys.push_back(FCCSTR(CAP_COLORMATRIX));
  s_arOrderKeys.push_back(FCCSTR(CAP_SHARPNESSFILTER));
  s_arOrderKeys.push_back(FCCSTR(CAP_DETECTBP));
  s_arOrderKeys.push_back(FCCSTR(CAP_DETECTBPLEVEL));
  s_arOrderKeys.push_back(FCCSTR(CAP_DETECTCT));
  s_arOrderKeys.push_back(FCCSTR(CAP_SKIPIMAGE));
  s_arOrderKeys.push_back(FCCSTR(CAP_MIRRORING));
  s_arOrderKeys.push_back(FCCSTR(CAP_CROPPINGSIZE));
  s_arOrderKeys.push_back(FCCSTR(CAP_FOCUS));
  s_arOrderKeys.push_back(FCCSTR(CAP_EDGEFILL_COLOR));
  s_arOrderKeys.push_back(FCCSTR(CAP_EDGEFILL_AREA));
  s_arOrderKeys.push_back(FCCSTR(CAP_QUIETMODE));
  s_arOrderKeys.push_back(FCCSTR(PAR_LENGTHDOUBLEFEED_LEN));
  s_arOrderKeys.push_back(FCCSTR(PAR_DOUBLEFEED_AREA));
  s_arOrderKeys.push_back(FCCSTR(CAP_LAMINATEDPAPER));
  s_arOrderKeys.push_back(FCCSTR(CAP_COLORCOUNTERTYPE));
  s_arOrderKeys.push_back(FCCSTR(PAR_PAGECOUNT));
  s_arOrderKeys.push_back(FCCSTR(PAR_ACQUISITIONAREA));
  s_arOrderKeys.push_back(FCCSTR(PAR_MAX_BUFFERSIZE));
 }
 for (ESDictionaryA::iterator it = dicParameters.begin(); it != dicParameters.end(); ++it)
 {
  ESStringArrayA::iterator itOrder = std::find(s_arOrderKeys.begin(), s_arOrderKeys.end(), it->first);
  if (itOrder == s_arOrderKeys.end())
  {
   s_arOrderKeys.push_back(it->first);
  }
 }
 for (ESStringArrayA::const_iterator itKey = s_arOrderKeys.begin(); itKey != s_arOrderKeys.end(); ++itKey)
 {
  ESDictionaryA::const_iterator itValue = dicParameters.find(*itKey);
  if (itValue == dicParameters.end())
  {
   continue;
  }
  CESCI2DataConstructor cDataConstructor;
  const ESStringA &strKey = itValue->first;
  const ESAny &anyValue = itValue->second;
  UInt32 un32Code = FourCharCode(strKey);
  switch (un32Code)
  {
  case CAP_ADF:
  case CAP_FB:
  case CAP_TPU:
   cDataConstructor.AppendFourCharString(strKey);
   if (const ESStringSetA *pStrSetValue = SAFE_ANY_DATA_CPTR(anyValue, ESStringSetA))
   {
    for (ESStringSetA::const_iterator it = pStrSetValue->begin(); it != pStrSetValue->end(); ++it)
    {
     cDataConstructor.AppendFourCharString(*it);
    }
   }
   break;
  case CAP_COLORFORMAT:
  case CAP_COLORCOUNTERTYPE:
  case CAP_IMAGEFORMAT:
  case CAP_DITHER_HALFTONE:
  case CAP_GAMMAMODE:
  case CAP_DETECTBP:
  case CAP_DETECTCT:
  case CAP_SKIPIMAGE:
  case CAP_MIRRORING:
  case CAP_EDGEFILL_COLOR:
  case CAP_QUIETMODE:
  case CAP_LAMINATEDPAPER:
  case CAP_CLIENT_APPLICATION:
  case CAP_BG_REMOVAL:
  case CAP_SHARPNESSFILTER:
   if (const ESStringA *pStrValue = SAFE_ANY_DATA_CPTR(anyValue, ESStringA))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendFourCharString(*pStrValue);
   }
   break;
  case PAR_PAGECOUNT:
   if (const ESNumber *pnValue = SAFE_ANY_DATA_CPTR(anyValue, ESNumber))
   {
    ESNumber count = *pnValue;
    if (IsDuplexEnabled())
    {
     count += count % 2;
    }
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendDecimal((unsigned short)count);
   }
   break;
  case CAP_JPEGQUALITY:
  case CAP_THRESHOLD:
  case CAP_GAMMA_SCALE:
  case CAP_DETECTBPLEVEL:
  case PAR_LENGTHDOUBLEFEED_LEN:
   if (const ESNumber *pnValue = SAFE_ANY_DATA_CPTR(anyValue, ESNumber))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendDecimal((unsigned short)*pnValue);
   }
   break;
  case PAR_MAX_BUFFERSIZE:
  case CAP_RESOLUTION_MAIN:
  case CAP_RESOLUTION_SUB:
  case CAP_CROPPINGSIZE:
  case CAP_BRTIGHTNESS:
  case CAP_CONSTRAST:
   if (const ESNumber *pnValue = SAFE_ANY_DATA_CPTR(anyValue, ESNumber))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendInteger((int)*pnValue);
   }
   break;
  case CAP_GAMMATABLE:
  case CAP_COLORMATRIX:
   if (anyValue.type() == typeid(ESDictionaryA))
   {
    const ESDictionaryA *pDicValue = SAFE_ANY_DATA_CPTR(anyValue, ESDictionaryA);
    for (ESDictionaryA::const_iterator it = pDicValue->begin(); it != pDicValue->end(); ++it)
    {
     if (const ESByteData *pData = SAFE_ANY_DATA_CPTR(it->second, ESByteData))
     {
      cDataConstructor.AppendFourCharString(strKey);
      cDataConstructor.AppendFourCharString(it->first);
      cDataConstructor.AppendData(*pData);
     }
    }
   }
   else if (const ESStringA *pStrValue = SAFE_ANY_DATA_CPTR(anyValue, ESStringA))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendFourCharString(*pStrValue);
   }
   break;
  case PAR_ACQUISITIONAREA:
  {
   ST_ES_RECT_UN32 rc = GetScanAreaInPixel();
   cDataConstructor.AppendFourCharString(strKey);
   cDataConstructor.AppendInteger((int)(rc.left));
   cDataConstructor.AppendInteger((int)(rc.top));
   cDataConstructor.AppendInteger((int)(rc.right - rc.left));
   cDataConstructor.AppendInteger((int)(rc.bottom - rc.top));
  }
  break;
  case CAP_EDGEFILL_AREA:
   if (const ESDictionaryA *pDicValue = SAFE_ANY_DATA_CPTR(anyValue, ESDictionaryA))
   {
    const ESNumber *pnLeft = SAFE_KEYS_DATA_CPTR(*pDicValue, ESCI2_DIC_KEY_LEFT, ESNumber);
    const ESNumber *pnRight = SAFE_KEYS_DATA_CPTR(*pDicValue, ESCI2_DIC_KEY_RIGHT, ESNumber);
    const ESNumber *pnTop = SAFE_KEYS_DATA_CPTR(*pDicValue, ESCI2_DIC_KEY_TOP, ESNumber);
    const ESNumber *pnBottom = SAFE_KEYS_DATA_CPTR(*pDicValue, ESCI2_DIC_KEY_BOTTOM, ESNumber);
    if ((pnLeft != NULL) && (pnRight != NULL) && (pnTop != NULL) && (pnBottom != NULL))
    {
     cDataConstructor.AppendFourCharString(strKey);
     cDataConstructor.AppendInteger(*pnLeft);
     cDataConstructor.AppendInteger(*pnRight);
     cDataConstructor.AppendInteger(*pnTop);
     cDataConstructor.AppendInteger(*pnBottom);
    }
   }
   break;
  case PAR_DOUBLEFEED_AREA:
   if (const ESDictionaryA *pDicValue = SAFE_ANY_DATA_CPTR(anyValue, ESDictionaryA))
   {
    const ESNumber *pnOffset = SAFE_KEYS_DATA_CPTR(*pDicValue, ESCI2_DIC_KEY_OFFSET, ESNumber);
    const ESNumber *pnLength = SAFE_KEYS_DATA_CPTR(*pDicValue, ESCI2_DIC_KEY_LENGTH, ESNumber);
    if ((pnOffset != NULL) && (pnLength != NULL))
    {
     cDataConstructor.AppendFourCharString(strKey);
     cDataConstructor.AppendInteger(*pnOffset);
     cDataConstructor.AppendInteger(*pnLength);
    }
   }
   break;
  default:
   break;
  }
  if (un32MaxSize > 0)
  {
   if (outParameterData.size() + cDataConstructor.GetData().size() > un32MaxSize)
   {
    break;
   }
   const ESByteData &data = cDataConstructor.GetData();
   outParameterData.insert(outParameterData.end(), data.begin(), data.end());
   arOutProcessedKeys.push_back(strKey);
  }
 }
 if (IsEnableDumpCommand())
 {
  AfxGetLog()->Dump(&outParameterData[0], (int)outParameterData.size(), "command.txt");
 }
 return outParameterData;
}
ESByteData CESCI2Command::MaintenanceParameterDataWithDict(ESDictionaryA &dicParameters, UInt32 un32MaxSize, ESStringArrayA &arOutProcessedKeys)
{
 ES_LOG_TRACE_FUNC();
 ESByteData outParameterData;
 arOutProcessedKeys.clear();
 for (ESDictionaryA::const_iterator itParam = dicParameters.begin(); itParam != dicParameters.end(); ++itParam)
 {
  CESCI2DataConstructor cDataConstructor;
  const ESStringA &strKey = itParam->first;
  const ESAny &anyValue = itParam->second;
  UInt32 un32Code = FourCharCode(strKey);
  switch (un32Code)
  {
  case CAP_ADF:
  {
   cDataConstructor.AppendFourCharString(strKey);
   const ESDictionaryA *pDicValue = SAFE_ANY_DATA_CPTR(anyValue, ESDictionaryA);
   if (pDicValue != NULL)
   {
    for (ESDictionaryA::const_iterator it = pDicValue->begin(); it != pDicValue->end(); ++it)
    {
     const ESStringA &strValueKey = it->first;
     const ESAny &anyDicValuesData = it->second;
     UInt32 un32DicValuesCode = FourCharCode(strValueKey);
     switch (un32DicValuesCode)
     {
     case CAP_ADF_SIMPLEXSCANCOUNTER:
     case CAP_ADF_DUPLEXSCANCOUNTER:
     case CAP_ADF_SIMPLEXCARDSCANCOUNTER:
     case CAP_ADF_DUPLEXCARDSCANCOUNTER:
     case CAP_ADF_PAPERJAMCOUNTER:
     case CAP_ADF_DFEEDCOUNTER_ULTRASONIC:
     case CAP_ADF_DFEEDCOUNTER_LENGTH:
     case CAP_ADF_DFEEDCOUNTER_SOFTWARE:
     case CAP_ADF_ROLLERKITCOUNTER:
     case CAP_ADF_SPECIALDOCUMENTCOUNTER:
     case CAP_ADF_PASSPORT_CS_COUNTER:
      if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyDicValuesData, ESNumber))
      {
       cDataConstructor.AppendFourCharString(strValueKey);
       cDataConstructor.AppendHex((unsigned long)*pValue);
      }
      break;
     case CAP_ADF_LAMP1COUNTER:
     case CAP_ADF_LAMP2COUNTER:
     case CAP_ADF_PICKUPROLLERCOUNTER:
     case CAP_ADF_SEPARATIONPADCOUNTER:
     case CAP_ADF_RETARDROLLERCOUNTER:
     case CAP_ADF_ORIGINPOINTCORRECTION:
     case CAP_ADF_TOPCORRECTION_FRONT:
     case CAP_ADF_TOPCORRECTION_BACK:
     case CAP_ADF_DOCUMENTDRIVECORRECTION_FRONT:
     case CAP_ADF_DOCUMENTDRIVECORRECTION_BACK:
     case CAP_ADF_LIGHTINTENSITY_BACK:
     case CAP_ADF_CLEANINGWARNING_TH:
     case CAP_ADF_ROLLERKITCOUNTER_TH:
     case CAP_ADF_RETARDROLLERCOUNTER_TH:
     case CAP_ADF_SEPARATIONPADCOUNTER_TH:
     case CAP_ADF_PICKUPROLLERCOUNTER_TH:
     case CAP_ADF_CLEANINGWARNINGCOUNTER:
      if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyDicValuesData, ESNumber))
      {
       cDataConstructor.AppendFourCharString(strValueKey);
       cDataConstructor.AppendInteger((int)*pValue);
      }
      break;
     case CAP_ADF_PAPERPROTECTION:
     case CAP_ADF_BEHAVIORWHEN_DF:
     case CAP_ADF_CLEANINGWARNING:
      if (const ESStringA *pStrValue = SAFE_ANY_DATA_CPTR(anyDicValuesData, ESStringA))
      {
       cDataConstructor.AppendFourCharString(strValueKey);
       cDataConstructor.AppendFourCharString(*pStrValue);
      }
      break;
     default:
      break;
     }
    }
   }
  }
  break;
  case CAP_FB:
  {
   cDataConstructor.AppendFourCharString(strKey);
   const ESDictionaryA *pDicValue = SAFE_ANY_DATA_CPTR(anyValue, ESDictionaryA);
   if (pDicValue != NULL)
   {
    for (ESDictionaryA::const_iterator it = pDicValue->begin(); it != pDicValue->end(); ++it)
    {
     const ESStringA &strValueKey = it->first;
     const ESAny &anyDicValuesData = it->second;
     UInt32 un32DicValuesCode = FourCharCode(strValueKey);
     switch (un32DicValuesCode)
     {
     case CAP_FB_SCANCOUNTER:
      if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyDicValuesData, ESNumber))
      {
       cDataConstructor.AppendFourCharString(strValueKey);
       cDataConstructor.AppendHex((unsigned long)*pValue);
      }
      break;
     case CAP_FB_LAMP1COUNTER:
     case CAP_FB_LAMP2COUNTER:
     case CAP_FB_ORIGINPOINTCORRECTION_MAIN:
     case CAP_FB_ORIGINPOINTCORRECTION_SUB:
     case CAP_FB_CARRIAGEDRIVECORRECTION:
      if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyDicValuesData, ESNumber))
      {
       cDataConstructor.AppendFourCharString(strValueKey);
       cDataConstructor.AppendInteger((int)*pValue);
      }
      break;
     default:
      break;
     }
    }
   }
  }
  break;
  case CAP_POWERSAVE:
  case CAP_POWEROFF:
  case CAP_POWEROFF2ND:
   if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyValue, ESNumber))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendDecimal((unsigned short)*pValue);
   }
   break;
  case CAP_DATEANDTIME:
   if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyValue, ESNumber))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendHex((unsigned long)*pValue);
   }
   break;
  case CAP_SENSORGLASS:
  case CAP_DIRECTPOWERON:
  case CAP_NONCONNECT_POWEROFF:
   if (const ESStringA *pStrValue = SAFE_ANY_DATA_CPTR(anyValue, ESStringA))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendFourCharString(*pStrValue);
   }
   break;
  case PAR_MAX_BUFFERSIZE:
   if (const ESNumber *pValue = SAFE_ANY_DATA_CPTR(anyValue, ESNumber))
   {
    cDataConstructor.AppendFourCharString(strKey);
    cDataConstructor.AppendInteger((int)*pValue);
   }
   break;
  default:
   break;
  }
  if (un32MaxSize > 0)
  {
   if (outParameterData.size() + cDataConstructor.GetData().size() > un32MaxSize)
   {
    break;
   }
   const ESByteData &data = cDataConstructor.GetData();
   outParameterData.insert(outParameterData.end(), data.begin(), data.end());
   arOutProcessedKeys.push_back(strKey);
  }
 }
 return outParameterData;
}
ESErrorCode CESCI2Command::RequestRunSequence(ESCI2RequestCode eRequestCode, ESCI2Mode eMode, ESByteData *pParamBlock, const ESDictionaryA &dicRules, ESDictionaryA &dicOutResult)
{
 ES_LOG_TRACE_FUNC();
 dicOutResult.clear();
 ESCI2Mode eCurrentMode = GetMode();
 ESErrorCode err = SetMode(eMode);
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer cHeapBuffer;
 err = RunSequence(eRequestCode, pParamBlock, NULL, &cHeapBuffer);
 if (IS_ERR_CODE(err))
 {
  goto BAIL;
 }
 if (!cHeapBuffer.IsEmpty())
 {
  CESCI2DataEnumerator cEnumerator(cHeapBuffer);
  if (IsEnableDumpCommand())
  {
   AfxGetLog()->Dump(cHeapBuffer.GetBufferPtr(), cHeapBuffer.GetLength(), "command.txt");
  }
  ESDictionaryA dicResult;
  err = ESCI2Pase(cEnumerator, dicRules, &dicResult);
  if (IS_ERR_CODE(err))
  {
   ES_LOG_FAILED_PASE_DATA();
   goto BAIL;
  }
  dicOutResult.swap(dicResult);
 }
BAIL:
 ESErrorCode err2 = SetMode(eCurrentMode);
 if (IS_ERR_SUCCESS(err) && IS_ERR_CODE(err2))
 {
  err = err2;
 }
 return err;
}
ESErrorCode CESCI2Command::WaitUntilDone()
{
 ESCI2Mode eCurrentMode = GetMode();
 ESErrorCode err = SetMode(kModeControl);
 if (IS_ERR_CODE(err))
 {
  goto BAIL;
 }
 err = RunSequence(REQUEST_STATUS, NULL, NULL, NULL);
 if (IS_ERR_CODE(err))
 {
  goto BAIL;
 }
BAIL:
 ESErrorCode err2 = SetMode(eCurrentMode);
 if (IS_ERR_SUCCESS(err) && IS_ERR_CODE(err2))
 {
  err = err2;
 }
 return err;
}
ESErrorCode CESCI2Command::StartScanning()
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode err = kESErrorNoError;
 ESByteData bdPasswordData, *pParam = NULL;
 if (IsAuthenticationSupported() && IsAuthenticationEnabled())
 {
  ESString strAuthUserName = GetAuthUserName();
  ESString strPassword = GetAuthPassword();
#ifdef WIN32
  ESStringA strAuthUserNameA = ES_CMN_FUNCS::STRING::UnicodeToMBString(strAuthUserName);
  ESStringA strPasswordA = ES_CMN_FUNCS::STRING::UnicodeToMBString(strPassword);
#else
  ESStringA strAuthUserNameA = strAuthUserName;
  ESStringA strPasswordA = strPassword;
#endif
  ESErrorCode err = CreateSha1HashedPasswordData(strAuthUserNameA, strPasswordA, bdPasswordData);
  if (IS_ERR_CODE(err))
  {
   ES_LOG_INVALID_SETTING_PARAM();
   bdPasswordData.clear();
   bdPasswordData.resize((MAX_USERNAME_LENGTH + HASH_DATA_SIZE), 0);
   if (strAuthUserNameA.size() <= MAX_USERNAME_LENGTH)
   {
    ::memcpy_s(&bdPasswordData[0], MAX_USERNAME_LENGTH, strAuthUserNameA.c_str(), strAuthUserNameA.size());
   }
  }
  pParam = &bdPasswordData;
 }
 m_bIsTransferring = true;
 err = RunSequence(REQUEST_TRANSFERDATA, pParam, NULL, NULL);
 if (IS_ERR_CODE(err))
 {
  m_bIsTransferring = false;
 }
 return err;
}
ESErrorCode CESCI2Command::RequestImage(ESDictionaryA &dicHeaderInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer &cOutBuffer)
{
 ES_LOG_TRACE_FUNC();
 return RunSequence(REQUEST_IMAGE, NULL, &dicHeaderInfo, &cOutBuffer);
}
ESErrorCode CESCI2Command::RequestCancel()
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode err = RunSequence(REQUEST_CANCEL, NULL, NULL, NULL);
 m_bIsTransferring = false;
 return err;
}
ESErrorCode CESCI2Command::RequestAdministratorLock(bool bModeOn, const ESString &password)
{
 ES_LOG_TRACE_FUNC();
 ESStringA strAdminLock = bModeOn ? CESCI2Command::FCCSTR(ADMINLOCK_ON) : CESCI2Command::FCCSTR(ADMINLOCK_OFF);
 ESByteData paramData;
 paramData.clear();
 paramData.resize(4, 0);
 ::memcpy_s(&paramData[0], 4, strAdminLock.c_str(), 4);
 if (!bModeOn)
 {
  if (password.length())
  {
   ESStringA strHashPasswordA = password;
   ENUM_ES_HASH_TYPE eHashType = GetMaintenanceHashType();
   if (eHashType == kESHashType1) {
    ESByteData bdSha256Data;
    ESErrorCode err = CreateSha256HashedData(strHashPasswordA, bdSha256Data);
    if (IS_ERR_CODE(err)) {
     ES_LOG_INVALID_SETTING_PARAM();
     bdSha256Data.clear();
     bdSha256Data.resize((HASH_DATA_SIZE_32 + HASH_SOLT_LENGTH), 0);
    }
    paramData.insert(paramData.end(), bdSha256Data.begin(), bdSha256Data.end());
   }else{
    ESByteData bdSha1Data;
    ESErrorCode err = CreateSha1HashedData(strHashPasswordA, bdSha1Data);
    if (IS_ERR_CODE(err)) {
     ES_LOG_INVALID_SETTING_PARAM();
     bdSha1Data.clear();
     bdSha1Data.resize(HASH_DATA_SIZE, 0);
    }
    paramData.insert(paramData.end(), bdSha1Data.begin(), bdSha1Data.end());
   }
  }
  else
  {
   return kESErrorInvalidParameter;
  }
 }
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer cHeapBuffer;
 ESErrorCode err = RunSequence(REQUEST_ADMIN_LOCK, &paramData, NULL, &cHeapBuffer);
 if (IS_ERR_CODE(err))
 {
  goto BAIL;
 }
 if (!cHeapBuffer.IsEmpty())
 {
  if (IsEnableDumpCommand())
  {
   AfxGetLog()->Dump(cHeapBuffer.GetBufferPtr(), cHeapBuffer.GetLength(), "command.txt");
  }
  CESCI2DataEnumerator cEnumerator(cHeapBuffer);
  ESAny anyValue(cEnumerator.Nextdata());
  if (ESStringA *pStrType = SAFE_ANY_DATA_PTR(anyValue, ESStringA))
  {
   if ((*pStrType) == CESCI2Command::FCCSTR(PARAMETER_OK))
   {
    err = kESErrorNoError;
   }
   else if ((*pStrType) == CESCI2Command::FCCSTR(PARAMETER_FAIL))
   {
    ES_LOG_INVALID_SETTING_PARAM();
    err = kESErrorInvalidParameter;
   }
   else
   {
    ES_LOG_INVALID_RESPONSE();
    err = kESErrorInvalidResponse;
   }
  }
 }
BAIL:
 return err;
}
ESErrorCode CESCI2Command::RequestAfmMode(bool bModeOn)
{
 ES_LOG_TRACE_FUNC();
 UInt32 u32AfmMode = (bModeOn ? AFM_ON : AFM_OFF);
 CESCI2DataConstructor param;
 param.AppendFourCharString(FCCSTR(u32AfmMode));
 return RunSequence(REQUEST_AFM, param.GetDataPtr(), NULL, NULL);
}
ESErrorCode CESCI2Command::RequestPanelToPushScanReady(bool bPushScanReady)
{
 ES_LOG_TRACE_FUNC();
 UInt32 u32PushScanReady = (bPushScanReady ? SRDY_ON : SRDY_OFF);
 CESCI2DataConstructor param;
 param.AppendFourCharString(FCCSTR(u32PushScanReady));
 return RunSequence(REQUEST_PUSHSCANREADY, param.GetDataPtr(), NULL, NULL);
}
ESErrorCode CESCI2Command::RequestJobMode(UInt32 un32JobMode)
{
 ES_LOG_TRACE_FUNC();
 CESCI2DataConstructor param;
 param.AppendFourCharString(FCCSTR(un32JobMode));
 return RunSequence(REQUEST_JOB, param.GetDataPtr(), NULL, NULL);
}
ESErrorCode CESCI2Command::GetInfo(__out ESDictionaryA &dicOutInfo)
{
 ES_LOG_TRACE_FUNC();
 return RequestRunSequence(REQUEST_INFO, kModeInquiry | kModeControl, NULL, GetInfoPaseRule(), dicOutInfo);
}
const ESDictionaryA &CESCI2Command::GetInfoPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicInfoPaseRule.empty()){
   ESDictionaryA dicADFInfoRules;
dicADFInfoRules[FCCSTR(INFO_ADF_TYPE)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_DUPLEX)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_ORDER)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_PREFEED)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_WIDTHDETECTION)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_HEIGHTDETECTION)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_GUIDEPOSITION)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_GUIDELESS)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_AUTOSCAN)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_SCANAREA)] = kParseRuleSize;
dicADFInfoRules[FCCSTR(INFO_ADF_MIN_DOCUMENTSIZE)] = kParseRuleSize;
dicADFInfoRules[FCCSTR(INFO_ADF_MAX_DOCUMENTSIZE)] = kParseRuleSize;
dicADFInfoRules[FCCSTR(INFO_ADF_BASIC_RESOLUTION)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_AUTORECOVERY)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_OVERSCAN_SIZE)] = kParseRuleSize;
dicADFInfoRules[FCCSTR(INFO_ADF_CRSHEETDETECTION)] = kParseRuleBoolean;
dicADFInfoRules[FCCSTR(INFO_ADF_LOAD)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_ADF)] = dicADFInfoRules;
ESDictionaryA dicFBInfoRules;
dicFBInfoRules[FCCSTR(INFO_FB_WIDTHDETECTION)] = kParseRuleBoolean;
dicFBInfoRules[FCCSTR(INFO_FB_HEIGHTDETECTION)] = kParseRuleBoolean;
dicFBInfoRules[FCCSTR(INFO_FB_GUIDEPOSITION)] = kParseRuleOneValue;
dicFBInfoRules[FCCSTR(INFO_FB_SCANAREA)] = kParseRuleSize;
dicFBInfoRules[FCCSTR(INFO_FB_BASICRESOLUTION)] = kParseRuleOneValue;
dicFBInfoRules[FCCSTR(INFO_FB_OVERSCAN_SIZE)] = kParseRuleSize;
m_dicInfoPaseRule[FCCSTR(INFO_FB)] = dicFBInfoRules;
ESDictionaryA dicTPUInfoRules;
dicTPUInfoRules[FCCSTR(INFO_TPU_SCANAREA)] = kParseRuleSize;
dicTPUInfoRules[FCCSTR(INFO_TPU_BASICRESOLUTION)] = kParseRuleOneValue;
dicTPUInfoRules[FCCSTR(INFO_TPU_OVERSCAN_SIZE)] = kParseRuleSize;
m_dicInfoPaseRule[FCCSTR(INFO_TPU)] = dicTPUInfoRules;
m_dicInfoPaseRule[FCCSTR(INFO_MAX_IMAGEPIX)] = kParseRuleSize;
m_dicInfoPaseRule[FCCSTR(INFO_PUSHBUTTON)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_PRODUCTNAME)] = kParseRuleString;
m_dicInfoPaseRule[FCCSTR(INFO_SERIALNUMBER)] = kParseRuleString;
m_dicInfoPaseRule[FCCSTR(INFO_VERSION)] = kParseRuleString;
m_dicInfoPaseRule[FCCSTR(INFO_DEV_BUFFERSIZE)] = kParseRuleOneValue;
m_dicInfoPaseRule[FCCSTR(INFO_DUMMYLESS)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_AUTHENTICATION)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_INITIALIZATION)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_AUTOFOCUS)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_MANUALFOCUS)] = kParseRuleListOrRange;
m_dicInfoPaseRule[FCCSTR(INFO_AUTOFEEDINGMODE)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_MIN_DOUBLEFEEDLEN)] = kParseRuleOneValue;
m_dicInfoPaseRule[FCCSTR(INFO_CROPPABLERESOL)] = kParseRuleListOrRange;
m_dicInfoPaseRule[FCCSTR(INFO_PUSHSCANREADY)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_JOB)] = kParseRuleListOrRange;
m_dicInfoPaseRule[FCCSTR(INFO_EXTINFO)] = kParseRuleBoolean;
m_dicInfoPaseRule[FCCSTR(INFO_HASHTYPE)] = kParseRuleOneValue;
}
return m_dicInfoPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::GetMaintenanceInfo(__out ESDictionaryA &dicOutMaintenanceInfo)
{
 ES_LOG_TRACE_FUNC();
 return RequestRunSequence(REQUEST_INFO, kModeMaintenance, NULL, GetMaintenanceInfoPaseRule(), dicOutMaintenanceInfo);
}
const ESDictionaryA &CESCI2Command::GetMaintenanceInfoPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicMaintenanceInfoPaseRule.empty()){
   ESDictionaryA dicADFInfoRules;
dicADFInfoRules[FCCSTR(INFO_ADF_LIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_LAMP1LIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_LAMP2LIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_PICKUPROLLERLIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_PICKUPROLLERLIFENEAREND)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_SEPARATIONPADLIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_SEPARATIONPADLIFENEAREND)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_RETARDROLLERLIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_RETARDROLLERLIFENEAREND)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_ROLLERKITLIFELIMIT)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_ROLLERKITLIFENEAREND)] = kParseRuleOneValue;
dicADFInfoRules[FCCSTR(INFO_ADF_BACKGROUNDGLEVEL_FRONT)] = kParseRuleBGLevel;
dicADFInfoRules[FCCSTR(INFO_ADF_BACKGROUNDGLEVEL_BACK)] = kParseRuleBGLevel;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_ADF)] = dicADFInfoRules;
ESDictionaryA dicFBInfoRules;
dicFBInfoRules[FCCSTR(INFO_FB_LIFELIMIT)] = kParseRuleOneValue;
dicFBInfoRules[FCCSTR(INFO_FB_LMP1LIFELIMIT)] = kParseRuleOneValue;
dicFBInfoRules[FCCSTR(INFO_FB_LMP2LIFELIMIT)] = kParseRuleOneValue;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_FB)] = dicFBInfoRules;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_POWERSAVE)] = kParseRuleBoolean;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_ADMIN_LOCK)] = kParseRuleBoolean;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_DEF_PASSWDTYPE)] = kParseRuleOneValue;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_PRODUCTNAME)] = kParseRuleString;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_SERIALNUMBER)] = kParseRuleString;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_VERSION)] = kParseRuleString;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_DEV_BUFFERSIZE)] = kParseRuleOneValue;
m_dicMaintenanceInfoPaseRule[FCCSTR(INFO_INITIALIZATION)] = kParseRuleBoolean;
m_dicMaintenanceInfoPaseRule[ FCCSTR(INFO_HASHTYPE)] = kParseRuleOneValue;
}
return m_dicMaintenanceInfoPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::GetExtInfo(__out ESDictionaryA &dicOutExtInfo)
{
 ES_LOG_TRACE_FUNC();
 ESCI2Mode eCurrentMode = GetMode();
 ESErrorCode err = SetMode(kModeInquiry | kModeControl);
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer cHeapBuffer;
 err = RunSequence(REQUEST_EXTINFO, NULL, NULL, &cHeapBuffer);
 if (IS_ERR_CODE(err))
 {
  goto BAIL;
 }
 if (!cHeapBuffer.IsEmpty())
 {
  ESDictionaryA dict;
  if (CESCI2JSONPerser::ParseWithData(cHeapBuffer, dict))
  {
   dicOutExtInfo.swap(dict);
  }
 }
BAIL:
 SetMode(eCurrentMode);
 return err;
}
ESErrorCode CESCI2Command::GetCapabilities(__out ESDictionaryA &dicOutCapability)
{
 ES_LOG_TRACE_FUNC();
 return RequestRunSequence(REQUEST_CAP_A, kModeInquiry | kModeControl, NULL, CapabilitiesPaseRule(), dicOutCapability);
}
const ESDictionaryA &CESCI2Command::CapabilitiesPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicCapabilitiesPaseRule.empty()){
   ESDictionaryA dicADFRules;
dicADFRules[FCCSTR(CAP_ADF_DUPLEX)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_PAPEREND_DETECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_DOUBLEFEED_DETECTION0)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_DOUBLEFEED_DETECTION1)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_DOUBLEFEED_DETECTION2)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_DOUBLEFEED_DETECTION3)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_LENGTHDOUBLEFEED_DETECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_SWDOUBLEFEED_DETECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_SWPAPERPROTECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_SCANSPEED_SELECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_BGCOLOR_BLACK)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_BGCOLOR_GRAY)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_BGCOLOR_WHITE)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_PAPERLOAD)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_PAPEREJECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_CROPPING)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_CROPPING_INSCRIBED)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_SKEWCORRECTION)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_OVERSCAN_SIZE)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_OVERSCAN_SIZE_CROPPING)] = kParseRuleBooleanList;
dicADFRules[FCCSTR(CAP_ADF_PASSPORTCRSHEET)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_RESOLUTION)] = kParseRuleListOrRange;
dicADFRules[FCCSTR(CAP_ADF_CLEANING)] = kParseRuleBoolean;
dicADFRules[FCCSTR(CAP_ADF_CALIBRATION)] = kParseRuleBoolean;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_ADF)] = dicADFRules;
ESDictionaryA dicFBRules;
dicFBRules[FCCSTR(CAP_FB_LAMP1)] = kParseRuleBooleanList;
dicFBRules[FCCSTR(CAP_FB_LAMP2)] = kParseRuleBooleanList;
dicFBRules[FCCSTR(CAP_FB_SCANSPEED_SELECTION)] = kParseRuleBoolean;
dicFBRules[FCCSTR(CAP_FB_CROPPING)] = kParseRuleBoolean;
dicFBRules[FCCSTR(CAP_FB_SKEWCORRECTION)] = kParseRuleBoolean;
dicFBRules[FCCSTR(CAP_FB_OVERSCAN_SIZE)] = kParseRuleBoolean;
dicFBRules[FCCSTR(CAP_FB_RESOLUTION)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_FB)] = dicFBRules;
static ESDictionaryA dicTPURules;
dicTPURules[FCCSTR(CAP_TPU_NEGATIVE)] = kParseRuleBoolean;
dicTPURules[FCCSTR(CAP_TPU_MAGNIFICATION_CORRECT)] = kParseRuleBoolean;
dicTPURules[FCCSTR(CAP_TPU_SCANSPEED_SELECTION)] = kParseRuleBoolean;
dicTPURules[FCCSTR(CAP_TPU_CROPPING)] = kParseRuleBoolean;
dicTPURules[FCCSTR(CAP_TPU_SKEWCORRECTION)] = kParseRuleBoolean;
dicTPURules[FCCSTR(CAP_TPU_OVERSCAN_SIZE)] = kParseRuleBoolean;
dicTPURules[FCCSTR(CAP_TPU_RESOLUTION)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_TPU)] = dicTPURules;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_COLORFORMAT)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_IMAGEFORMAT)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_JPEGQUALITY)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_THRESHOLD)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_CONSTRAST)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_BRTIGHTNESS)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_GAMMA_SCALE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_SHARPNESSFILTER)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_BG_REMOVAL)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_COLORCOUNTERTYPE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_DITHER_HALFTONE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_GAMMAMODE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_GAMMATABLE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_COLORMATRIX)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_DETECTBP)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_DETECTBPLEVEL)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_DETECTCT)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_SKIPIMAGE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_SHARPNESSFILTER)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_MIRRORING)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_RESOLUTION_MAIN)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_RESOLUTION_SUB)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_CROPPINGSIZE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_FOCUS)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_EDGEFILL_COLOR)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_EDGEFILL_AREA)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_QUIETMODE)] = kParseRuleListOrRange;
m_dicCapabilitiesPaseRule[FCCSTR(CAP_LAMINATEDPAPER)] = kParseRuleListOrRange;
}
return m_dicCapabilitiesPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::GetMaintenanceCapabilities(__out ESDictionaryA &dicOutMaintenanceCapability)
{
 ES_LOG_TRACE_FUNC();
 return RequestRunSequence(REQUEST_CAP_A, kModeMaintenance, NULL, GetMaintenanceCapabilitiesPaseRule(), dicOutMaintenanceCapability);
}
const ESDictionaryA &CESCI2Command::GetMaintenanceCapabilitiesPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicMaintenanceCapabilitiesPaseRule.empty()){
   ESDictionaryA dicADFRules;
dicADFRules[FCCSTR(CAP_ADF_SIMPLEXSCANCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_SIMPLEXCARDSCANCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DUPLEXSCANCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DUPLEXCARDSCANCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_LAMP1COUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_LAMP2COUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_PAPERJAMCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DFEEDCOUNTER_ULTRASONIC)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DFEEDCOUNTER_LENGTH)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DFEEDCOUNTER_SOFTWARE)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_PAPERPROTECTCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_PICKUPROLLERCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_SEPARATIONPADCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_RETARDROLLERCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_ROLLERKITCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_SPECIALDOCUMENTCOUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_PASSPORT_CS_COUNTER)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_ORIGINPOINTCORRECTION)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_TOPCORRECTION_FRONT)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_TOPCORRECTION_BACK)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DOCUMENTDRIVECORRECTION_FRONT)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_DOCUMENTDRIVECORRECTION_BACK)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_LIGHTINTENSITY_BACK)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_PAPERPROTECTION)] = kParseRuleListOrRange;
dicADFRules[FCCSTR(CAP_ADF_BEHAVIORWHEN_DF)] = kParseRuleListOrRange;
dicADFRules[FCCSTR(CAP_ADF_CLEANINGWARNING)] = kParseRuleListOrRange;
dicADFRules[FCCSTR(CAP_ADF_CLEANINGWARNING_TH)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_ROLLERKITCOUNTER_TH)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_RETARDROLLERCOUNTER_TH)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_SEPARATIONPADCOUNTER_TH)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_PICKUPROLLERCOUNTER_TH)] = kParseRuleRange;
dicADFRules[FCCSTR(CAP_ADF_CLEANINGWARNINGCOUNTER)] = kParseRuleRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_ADF)] = dicADFRules;
ESDictionaryA dicFBRules;
dicFBRules[FCCSTR(CAP_FB_SCANCOUNTER)] = kParseRuleRange;
dicFBRules[FCCSTR(CAP_FB_LAMP1COUNTER)] = kParseRuleRange;
dicFBRules[FCCSTR(CAP_FB_LAMP2COUNTER)] = kParseRuleRange;
dicFBRules[FCCSTR(CAP_FB_ORIGINPOINTCORRECTION_MAIN)] = kParseRuleRange;
dicFBRules[FCCSTR(CAP_FB_ORIGINPOINTCORRECTION_SUB)] = kParseRuleRange;
dicFBRules[FCCSTR(CAP_FB_CARRIAGEDRIVECORRECTION)] = kParseRuleRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_FB)] = dicFBRules;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_POWEROFF)] = kParseRuleListOrRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_POWEROFF2ND)] = kParseRuleListOrRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_POWERSAVE)] = kParseRuleListOrRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_DATEANDTIME)] = kParseRuleListOrRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_SENSORGLASS)] = kParseRuleListOrRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_DIRECTPOWERON)] = kParseRuleListOrRange;
m_dicMaintenanceCapabilitiesPaseRule[FCCSTR(CAP_NONCONNECT_POWEROFF)] = kParseRuleListOrRange;
}
return m_dicMaintenanceCapabilitiesPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::GetStatus(__out ESDictionaryA &dicOutStatus)
{
 ES_LOG_TRACE_FUNC();
 if (m_bIsTransferring)
 {
  return kESErrorNoError;
 }
 ESErrorCode err = kESErrorNoError;
 if (IsShouldSyncFunctionalUnit())
 {
  err = SyncFunctionalUnit();
  if (IS_ERR_CODE(err))
  {
   return err;
  }
 }
 err = RequestRunSequence(REQUEST_STATUS, kModeInquiry | kModeControl, NULL, GetStatusPaseRule(), dicOutStatus);
 if (m_bIsAllowAuthError && err == kESErrorAuthFailure)
 {
  err = kESErrorNoError;
 }
 return err;
}
ESErrorCode CESCI2Command::GetMaintenanceStatus(__out ESDictionaryA &dicOutStatus)
{
 ES_LOG_TRACE_FUNC();
 if (m_bIsTransferring)
 {
  return kESErrorNoError;
 }
 static ESDictionaryA dicRules;
 if (dicRules.empty())
 {
  dicRules[FCCSTR(STAT_ERROR)] = kParseRuleError;
  dicRules[FCCSTR(STAT_BATTERY)] = kParseRuleOneValue;
  dicRules[FCCSTR(STAT_SENSORGLASS)] = kParseRuleOneValue;
  dicRules[FCCSTR(STAT_WARNING)] = kParseRuleError;
  dicRules[FCCSTR(STAT_ADMIN_LOCK)] = kParseRuleOneValue;
 }
 ESErrorCode err = kESErrorNoError;
 if (IsShouldSyncFunctionalUnit())
 {
  err = SyncFunctionalUnit();
  if (IS_ERR_CODE(err))
  {
   return err;
  }
 }
 err = RequestRunSequence(REQUEST_STATUS, kModeMaintenance, NULL, dicRules, dicOutStatus);
 if (m_bIsAllowAuthError && err == kESErrorAuthFailure)
 {
  err = kESErrorNoError;
 }
 return err;
}
const ESDictionaryA &CESCI2Command::GetStatusPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicStatusPaseRule.empty()){
   m_dicStatusPaseRule[FCCSTR(STAT_PAPERSIZE)] = kParseRulePaperSize;
m_dicStatusPaseRule[FCCSTR(STAT_ERROR)] = kParseRuleError;
m_dicStatusPaseRule[FCCSTR(STAT_PUSHBUTTON)] = kParseRuleOneValue;
m_dicStatusPaseRule[FCCSTR(STAT_DOCSEPARATION)] = kParseRuleOneValue;
m_dicStatusPaseRule[FCCSTR(STAT_CARDSCANNING)] = kParseRuleOneValue;
m_dicStatusPaseRule[FCCSTR(STAT_BATTERY)] = kParseRuleOneValue;
m_dicStatusPaseRule[FCCSTR(STAT_SENSORGLASS)] = kParseRuleOneValue;
m_dicStatusPaseRule[FCCSTR(STAT_SCANNERPOSITION)] = kParseRuleOneValue;
m_dicStatusPaseRule[FCCSTR(STAT_WARNING)] = kParseRuleError;
m_dicStatusPaseRule[FCCSTR(STAT_FOCUS)] = kParseRuleFocus;
m_dicStatusPaseRule[FCCSTR(STAT_ERRORCODE)] = kParseRuleOneValue;
ESDictionaryA dicScanParameterRules;
dicScanParameterRules[FCCSTR(STAT_SCANPARAMETER_ALL)] = kParseRuleBoolean;
dicScanParameterRules[FCCSTR(STAT_SCANPARAMETER_AFMC)] = kParseRuleBoolean;
dicScanParameterRules[FCCSTR(STAT_SCANPARAMETER_PCS)] = kParseRuleBoolean;
m_dicStatusPaseRule[FCCSTR(STAT_SCANPARAMETER)] = dicScanParameterRules;
}
return m_dicStatusPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::GetResults(__out ESDictionaryA &dicOutResults, __in_opt ESStringArrayA *pStrarKeys)
{
 ES_LOG_TRACE_FUNC();
 ESByteData *pParamBlock = NULL;
 CESCI2DataConstructor cDataConstructor;
 if (pStrarKeys != NULL)
 {
  for (ESStringArrayA::const_iterator it = pStrarKeys->begin(); it != pStrarKeys->end(); ++it)
  {
   cDataConstructor.AppendFourCharString(*it);
  }
  pParamBlock = cDataConstructor.GetDataPtr();
 }
 return RequestRunSequence(REQUEST_RESULT_A, kModeInquiry | kModeControl, pParamBlock, GetResultsPaseRule(), dicOutResults);
}
const ESDictionaryA &CESCI2Command::GetResultsPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicResultsPaseRule.empty()){
   m_dicResultsPaseRule[FCCSTR(CAP_ADF)] = kParseRuleList;
m_dicResultsPaseRule[FCCSTR(CAP_FB)] = kParseRuleError;
m_dicResultsPaseRule[FCCSTR(CAP_COLORFORMAT)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_IMAGEFORMAT)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_JPEGQUALITY)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_THRESHOLD)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_BRTIGHTNESS)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_CONSTRAST)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_GAMMA_SCALE)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_DITHER_HALFTONE)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_GAMMAMODE)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_SHARPNESSFILTER)] = kParseRuleOneValue;
ESDictionaryA dicGammaTableRules;
dicGammaTableRules[FCCSTR(CAP_GAMMATABLE_RED)] = kParseRuleOneValue;
dicGammaTableRules[FCCSTR(CAP_GAMMATABLE_GREEN)] = kParseRuleOneValue;
dicGammaTableRules[FCCSTR(CAP_GAMMATABLE_BLUE)] = kParseRuleOneValue;
dicGammaTableRules[FCCSTR(CAP_GAMMATABLE_MONO)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_GAMMATABLE)] = dicGammaTableRules;
ESDictionaryA dicColorMatrixRules;
dicColorMatrixRules[FCCSTR(CAP_COLORMATRIX_08)] = kParseRuleOneValue;
dicColorMatrixRules[FCCSTR(CAP_COLORMATRIX_16)] = kParseRuleOneValue;
dicColorMatrixRules[FCCSTR(CAP_COLORMATRIX_UNIT)] = kParseRuleBoolean;
m_dicResultsPaseRule[FCCSTR(CAP_COLORMATRIX)] = dicColorMatrixRules;
m_dicResultsPaseRule[FCCSTR(CAP_DETECTBP)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_DETECTBPLEVEL)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_DETECTCT)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_SKIPIMAGE)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_SHARPNESSFILTER)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_MIRRORING)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_RESOLUTION_MAIN)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_RESOLUTION_SUB)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_CROPPINGSIZE)] = kParseRuleSize;
m_dicResultsPaseRule[FCCSTR(CAP_FOCUS)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_EDGEFILL_COLOR)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_EDGEFILL_AREA)] = kParseRuleList;
m_dicResultsPaseRule[FCCSTR(CAP_QUIETMODE)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(CAP_BG_REMOVAL)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(PAR_PAGECOUNT)] = kParseRuleOneValue;
m_dicResultsPaseRule[FCCSTR(PAR_ACQUISITIONAREA)] = kParseRuleRect;
m_dicResultsPaseRule[FCCSTR(PAR_MAX_BUFFERSIZE)] = kParseRuleOneValue;
}
return m_dicResultsPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::GetMaintenanceResults(__out ESDictionaryA &dicOutResults, __in_opt ESStringArrayA *pStrarKeys)
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode err = kESErrorNoError;
 if (!m_dicMaintenanceResults.empty())
 {
  dicOutResults = m_dicMaintenanceResults;
  return err;
 }
 ESByteData *pParamBlock = NULL;
 CESCI2DataConstructor cDataConstructor;
 if (pStrarKeys != NULL)
 {
  for (ESStringArrayA::const_iterator it = pStrarKeys->begin(); it != pStrarKeys->end(); ++it)
  {
   cDataConstructor.AppendFourCharString(*it);
  }
  pParamBlock = cDataConstructor.GetDataPtr();
 }
 err = RequestRunSequence(REQUEST_RESULT_A, kModeMaintenance, pParamBlock, GetMaintenanceResultsPaseRule(), dicOutResults);
 {
  m_dicMaintenanceResults = dicOutResults;
 }
 return err;
}
const ESDictionaryA &CESCI2Command::GetMaintenanceResultsPaseRule(){
 SYNCHRONIZED_START{
  if (m_dicMaintenanceResultsPaseRule.empty()){
   ESDictionaryA dicADFRules;
dicADFRules[FCCSTR(CAP_ADF_SIMPLEXSCANCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DUPLEXSCANCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_SIMPLEXCARDSCANCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DUPLEXCARDSCANCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_LAMP1COUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_LAMP2COUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_PAPERJAMCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DFEEDCOUNTER_ULTRASONIC)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DFEEDCOUNTER_LENGTH)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DFEEDCOUNTER_SOFTWARE)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_PAPERPROTECTCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_PICKUPROLLERCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_SEPARATIONPADCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_RETARDROLLERCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_ROLLERKITCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_SPECIALDOCUMENTCOUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_PASSPORT_CS_COUNTER)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_ORIGINPOINTCORRECTION)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_TOPCORRECTION_FRONT)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_TOPCORRECTION_BACK)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DOCUMENTDRIVECORRECTION_FRONT)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_DOCUMENTDRIVECORRECTION_BACK)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_LIGHTINTENSITY_BACK)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_PAPERPROTECTION)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_BEHAVIORWHEN_DF)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_CLEANINGWARNING)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_CLEANINGWARNING_TH)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_ROLLERKITCOUNTER_TH)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_RETARDROLLERCOUNTER_TH)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_SEPARATIONPADCOUNTER_TH)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_PICKUPROLLERCOUNTER_TH)] = kParseRuleOneValue;
dicADFRules[FCCSTR(CAP_ADF_CLEANINGWARNINGCOUNTER)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_ADF)] = dicADFRules;
ESDictionaryA dicFBRules;
dicFBRules[FCCSTR(CAP_FB_SCANCOUNTER)] = kParseRuleOneValue;
dicFBRules[FCCSTR(CAP_FB_LAMP1COUNTER)] = kParseRuleOneValue;
dicFBRules[FCCSTR(CAP_FB_LAMP2COUNTER)] = kParseRuleOneValue;
dicFBRules[FCCSTR(CAP_FB_ORIGINPOINTCORRECTION_MAIN)] = kParseRuleOneValue;
dicFBRules[FCCSTR(CAP_FB_ORIGINPOINTCORRECTION_SUB)] = kParseRuleOneValue;
dicFBRules[FCCSTR(CAP_FB_CARRIAGEDRIVECORRECTION)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_FB)] = dicFBRules;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_POWEROFF)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_POWEROFF2ND)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_POWERSAVE)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_DATEANDTIME)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(PAR_MAX_BUFFERSIZE)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_SENSORGLASS)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_DIRECTPOWERON)] = kParseRuleOneValue;
m_dicMaintenanceResultsPaseRule[FCCSTR(CAP_NONCONNECT_POWEROFF)] = kParseRuleOneValue;
}
return m_dicMaintenanceResultsPaseRule;
}
SYNCHRONIZED_END
}
ESErrorCode CESCI2Command::SendParameters(__in ESDictionaryA dicParameters)
{
 ES_LOG_TRACE_FUNC();
 ESCI2Mode eCurrentMode = GetMode();
 ESErrorCode err = SetMode(kModeControl);
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 UInt32 un32MaxBufferSize = GetDeviceMaxBufferSize();
 if (IsFeedTypeADF() && IsAdfLoadSupported())
 {
  if (IsAutoCroppingEnabled() || IsSkewCorrectionEnabled() || GetBackGroundRemoval() != kESBackgroundRemovalLevelOff)
  {
   CESCI2DataConstructor cDataConstructor;
   cDataConstructor.AppendFourCharString(FCCSTR(CAP_ADF));
   cDataConstructor.AppendFourCharString(FCCSTR(CAP_ADF_PAPERLOAD));
   ESByteData *pParamBlock = cDataConstructor.GetDataPtr();
   err = RunSequence(REQUEST_MECHCONTROL, pParamBlock, NULL, NULL);
   if (IS_ERR_CODE(err))
   {
    goto BAIL;
   }
   err = WaitUntilDone();
   if (IS_ERR_CODE(err))
   {
    goto BAIL;
   }
  }
 }
 while (dicParameters.size() > 0)
 {
  ESStringArrayA arProcessedKeys;
  ESDictionaryA dicHeaderInfo;
  ESByteData ParamData = ParameterDataWithDict(dicParameters, un32MaxBufferSize, arProcessedKeys);
  if (arProcessedKeys.size() <= 0)
  {
   ES_LOG_FAILED_CONVERT_DATA();
   err = kESErrorMemoryError;
   goto BAIL;
  }
  for (ESStringArrayA::const_iterator it = arProcessedKeys.begin(); it != arProcessedKeys.end(); ++it)
  {
   if (dicParameters.count(*it) != 0)
   {
    dicParameters.erase(*it);
   }
  }
  err = RunSequence(REQUEST_PARAM_A, &ParamData, &dicHeaderInfo, NULL);
  if (IS_ERR_CODE(err))
  {
   goto BAIL;
  }
  bool bParameterOK = false;
  if (ESStringA *pStrParamResult = SAFE_KEYS_DATA_PTR(dicHeaderInfo, FCCSTR(HEADER_PARAMETER).c_str(), ESStringA))
  {
   if (FourCharCode(*pStrParamResult) == PARAMETER_OK)
   {
    bParameterOK = true;
   }
  }
  else
  {
   ES_LOG_EXCEPTION_ERROR();
  }
  if (!bParameterOK)
  {
   ES_LOG_INVALID_RESPONSE();
   err = kESErrorInvalidResponse;
   goto BAIL;
  }
 }
BAIL:
 ESErrorCode err2 = SetMode(eCurrentMode);
 if (IS_ERR_SUCCESS(err) && IS_ERR_CODE(err2))
 {
  err = err2;
 }
 return err;
}
ESErrorCode CESCI2Command::SendMaintenanceParameters(__in ESDictionaryA dicParameters)
{
 ES_LOG_TRACE_FUNC();
 bool bNeedToUnlockAdminLock = false;
 if (IsAdminLockSupported() && IsAdminLockEnabledWithUnlockTest(false))
 {
  bNeedToUnlockAdminLock = true;
 }
 ESCI2Mode eCurrentMode = GetMode();
 ESErrorCode err = SetMode(kModeMaintenance);
 if (IS_ERR_CODE(err))
 {
  return err;
 }
 bool bUnlockedTempAdminLock = false;
 {
  if (bNeedToUnlockAdminLock && RequestingUnlockAdminLock() && GetAdminLockPassword().length())
  {
   ESErrorCode err2 = RequestAdministratorLock(false, GetAdminLockPassword());
   if (!IS_ERR_CODE(err2))
   {
    bUnlockedTempAdminLock = true;
   }
  }
 }
 UInt32 un32MaxBufferSize = GetDeviceMaxBufferSize();
 while (dicParameters.size() > 0)
 {
  ESStringArrayA arProcessedKeys;
  ESDictionaryA dicHeaderInfo;
  ESByteData ParamData = MaintenanceParameterDataWithDict(dicParameters, un32MaxBufferSize, arProcessedKeys);
  if (arProcessedKeys.size() <= 0)
  {
   ES_LOG_FAILED_CONVERT_DATA();
   err = kESErrorMemoryError;
   goto BAIL;
  }
  for (ESStringArrayA::const_iterator it = arProcessedKeys.begin(); it != arProcessedKeys.end(); ++it)
  {
   if (dicParameters.count(*it) != 0)
   {
    dicParameters.erase(*it);
   }
  }
  err = RunSequence(REQUEST_PARAM_A, &ParamData, &dicHeaderInfo, NULL);
  if (IS_ERR_CODE(err))
  {
   goto BAIL;
  }
  bool bParameterOK = false;
  if (ESStringA *pStrParamResult = SAFE_KEYS_DATA_PTR(dicHeaderInfo, FCCSTR(HEADER_PARAMETER).c_str(), ESStringA))
  {
   if (FourCharCode(*pStrParamResult) == PARAMETER_OK)
   {
    bParameterOK = true;
   }
  }
  else
  {
   ES_LOG_EXCEPTION_ERROR();
  }
  if (!bParameterOK)
  {
   ES_LOG_INVALID_RESPONSE();
   err = kESErrorInvalidResponse;
   goto BAIL;
  }
 }
BAIL:
{
 if (bUnlockedTempAdminLock)
 {
  ESErrorCode err2 = RequestAdministratorLock(true, ESString());
  bUnlockedTempAdminLock = false;
 }
}
 ESErrorCode err2 = SetMode(eCurrentMode);
 if (IS_ERR_SUCCESS(err) && IS_ERR_CODE(err2))
 {
  err = err2;
 }
 {
  m_dicMaintenanceResults.clear();
 }
 return err;
}
