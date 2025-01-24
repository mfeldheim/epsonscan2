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
//  list.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef list_h_included
#define list_h_included 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "defines.h"
#ifdef __cplusplus
extern "C"
{
#endif
typedef struct list_entry
{
  void* data;
  struct list_entry* next;
} list_entry;
typedef struct list
{
  list_entry* head;
  list_entry* tail;
  list_entry* cur;
  size_t num_entries;
} list;
list* list_create ();
void list_destroy (list* lst, void (*dtor)(void*));
bool list_append (list* lst, void* new_data);
void** list_normalize (const list* lst);
size_t list_size (list* lst);
void list_reset (list* lst);
void* list_next (list* lst);
#ifdef __cplusplus
}
#endif
#endif
