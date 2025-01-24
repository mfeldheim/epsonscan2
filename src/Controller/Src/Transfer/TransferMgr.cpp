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
//  TransferMgr.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Utility.hpp"
#include "TransferMgr.hpp"
namespace epsonscan
{
TransferMgr::TransferMgr()
{
 m_bOpend = false ;
 EnterCriticalSection_local() ;
 m_Queue.clear() ;
 LeaveCriticalSection_local() ;
 SetDrained(false);
 m_nCurrentPageNumber = 0;
}
TransferMgr::~TransferMgr()
{
 EnterCriticalSection_local() ;
 for (auto itr = m_Queue.begin() ; itr != m_Queue.end() ; itr ++) {
  (*itr).Release() ;
 }
 m_Queue.clear() ;
 LeaveCriticalSection_local() ;
}
void TransferMgr::wait()
{
 usleep(10);
}
boost::optional<TransferEvent> TransferMgr::lastEventWithDequeue(bool dequeue)
{
 SDI_TRACE_LOG("TransferMgr::lastEventWithDequeue in");
 if (GetDrained()) {
  SDI_TRACE_LOG("TransferMgr::lastEventWithDequeue out NULL");
  return boost::none;
 }
 boost::optional<TransferEvent> obj = boost::none;
 for (;;) {
  EnterCriticalSection_local();
  {
   if (this->m_Queue.size() > 0) {
    obj = this->m_Queue.at(0);
    if (dequeue) {
     this->m_Queue.pop_front();
    }
   }
  }
  LeaveCriticalSection_local();
  if (obj) {
   if (obj->GetType() == kEventTypeComplete)
   {
    usleep(100*1000);
   }
   break;
  }
  if (!this->isOpened()) {
   SDI_TRACE_LOG("TransferMgr::lastEventWithDequeue break");
   break;
  }
  this->wait();
 }
 if (!obj) {
  SetDrained(true);
 }
 if (dequeue && obj)
 {
  auto image = obj->GetImage();
  if (image)
  {
   image->WaitUntilFinishImageProc();
   obj->SetError(image->GetLastError());
  }
 }
 SDI_TRACE_LOG("TransferMgr::lastEventWithDequeue out deque = %d", dequeue);
 if (obj)
 {
  SDI_TRACE_LOG("obj->GetType() == %d", obj->GetType());
 }else{
  SDI_TRACE_LOG("obj is null");
 }
 return obj;
}
bool TransferMgr::CanDequeue()
{
 SDI_TRACE_LOG("TransferMgr::CanDequeue()");
 boost::optional<TransferEvent> event = lastEventWithDequeue(false);
 if (event)
 {
  SDI_TRACE_LOG("TransferMgr::event exists");
  if(event->GetType() == kEventTypeImage)
  {
   SDI_TRACE_LOG("TransferMgr::kEventTypeImage");
   auto image = event->GetImage();
   if (image)
   {
    SDI_TRACE_LOG("TransferMgr::image exists  ");
    image->WaitUntilFinishImageProc();
    if (image->IsBlankPage())
    {
     SDI_TRACE_LOG("TransferMgr::image is blankpage");
      for (;;) {
       EnterCriticalSection_local();
       if (this->m_Queue.size() > 0) {
        for (int i = 0; i < this->m_Queue.size(); i++)
        {
         auto event = this->m_Queue.at(i);
         if (event.GetType() == kEventTypeImage)
         {
           auto image = event.GetImage();
           if (image)
           {
            image->WaitUntilFinishImageProc();
            if (image->IsBlankPage() == false)
            {
             SDI_TRACE_LOG("TransferMgr::image is not blankpage ");
             LeaveCriticalSection_local();
             return true;
            }
           }
         }
         if (event.GetType() == kEventTypeComplete)
         {
          SDI_TRACE_LOG("TransferMgr::kEventTypeComplete ");
          LeaveCriticalSection_local();
          return false;
         }
        }
       }
       LeaveCriticalSection_local();
           this->wait();
         }
    }else{
     SDI_TRACE_LOG("TransferMgr::image is not blankpage");
     return true;
    }
   }
  }
  if(event->GetType() == kEventTypeComplete)
  {
   return false;
  }
 }
 return true;
}
bool TransferMgr::CanDequeueWithoutWait()
{
 EnterCriticalSection_local();
 if (m_Queue.size() > 0)
 {
  LeaveCriticalSection_local() ;
  return true;
 }
 LeaveCriticalSection_local() ;
 return false;
}
void TransferMgr::Open()
{
 SDI_TRACE_LOG("Enter");
 EnterCriticalSection_local();
 m_bOpend = true ;
 m_nCurrentPageNumber = 0;
 LeaveCriticalSection_local() ;
 SetDrained(false);
 SDI_TRACE_LOG("Leave");
}
void TransferMgr::Close()
{
 SDI_TRACE_LOG("Enter");
 EnterCriticalSection_local();
 m_bOpend = false ;
 m_nCurrentPageNumber = 0;
 LeaveCriticalSection_local() ;
 SDI_TRACE_LOG("Leave");
}
void TransferMgr::Abort()
{
 SDI_TRACE_LOG("Enter");
 EnterCriticalSection_local() ;
 for (auto itr = m_Queue.begin() ; itr != m_Queue.end() ; itr ++) {
  (*itr).Release();
 }
 m_Queue.clear();
 LeaveCriticalSection_local();
 this->Close() ;
 SetDrained(true);
 SDI_TRACE_LOG("Leave");
}
void TransferMgr::EnqueEvent(TransferEvent event)
{
 SDI_TRACE_LOG("Enter");
 if (!this->isOpened()) {
  return ;
 }
 EnterCriticalSection_local() ;
 m_Queue.push_back(event);
 LeaveCriticalSection_local() ;
 SDI_TRACE_LOG("Leave");
}
boost::optional<TransferEvent> TransferMgr::DequeueEvent()
{
 return lastEventWithDequeue(TRUE) ;
}
void TransferMgr::Reset()
{
 SDI_TRACE_LOG("Enter");
 EnterCriticalSection_local();
 for (auto itr = m_Queue.begin(); itr != m_Queue.end(); itr++) {
  (*itr).Release();
 }
 m_Queue.clear();
 LeaveCriticalSection_local();
 SDI_TRACE_LOG("Leave");
}
bool TransferMgr::isOpened()
{
 bool bOpened = false ;
 {
  EnterCriticalSection_local() ;
  bOpened = this->m_bOpend ;
  LeaveCriticalSection_local() ;
 }
 return bOpened ;
}
}
