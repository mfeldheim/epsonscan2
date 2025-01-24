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
//  TransferMgr.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "TransferEvent.hpp"
#include <boost/optional.hpp>
#include <queue>
#include <../CommonUtility/utils/CritSec.h>
namespace epsonscan
{
class TransferMgr
{
public :
 TransferMgr() ;
 virtual ~TransferMgr() ;
 bool CanDequeue() ;
 bool CanDequeueWithoutWait() ;
 void Open() ;
 void Close() ;
 void Abort() ;
 void EnqueEvent(TransferEvent event) ;
 boost::optional<TransferEvent> DequeueEvent() ;
 size_t GetQueueCount() {
  return m_Queue.size();
 }
 void Reset();
 void SetDrained(bool bDrained) {
  m_bDrained = bDrained;
 }
 bool GetDrained() const {
  return m_bDrained;
 }
private :
 void EnterCriticalSection_local()
 {
  m_stCritSec.Lock();
 }
 void LeaveCriticalSection_local()
 {
  m_stCritSec.Unlock();
 }
 bool isOpened() ;
 boost::optional<TransferEvent> lastEventWithDequeue(bool dequeue) ;
public :
 void wait();
private :
 CritSec m_stCritSec ;
 bool m_bOpend ;
 std::deque<TransferEvent> m_Queue ;
 bool m_bDrained;
 int m_nCurrentPageNumber;
} ;
}
