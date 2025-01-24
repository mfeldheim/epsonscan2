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
//  list.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "list.h"
#include <string.h>
list* list_create ()
{
  list* lst = 0;
  lst = t_calloc (1, list);
  return lst;
}
void list_destroy (list* lst, void (*dtor)(void*))
{
  if (!lst) return;
  list_entry* entry = lst->head;
  list_entry* tmp;
  while (entry != NULL)
  {
    if (dtor && entry->data)
      (*dtor) (entry->data);
    tmp = entry->next;
    delete (entry);
    entry = tmp;
  }
  delete (lst);
}
bool list_append (list* lst, void* new_data)
{
  if (!lst) return false;
  list_entry* entry = 0;
  entry = t_calloc (1, list_entry);
  if (!entry) return false;
  entry->data = new_data;
  if (0 == lst->num_entries)
    {
      lst->head = entry;
      lst->tail = entry;
      lst->cur = entry;
    }
  else
    {
      lst->tail->next = entry;
      lst->tail = entry;
    }
  lst->num_entries += 1;
  return true;
}
void** list_normalize (const list *lst)
{
  void **nlst;
  if (!lst) return NULL;
  nlst = t_malloc (lst->num_entries + 1, void *);
  if (nlst)
    {
      list *p = (list *) lst;
      list_entry *cur = p->cur;
      void *entry;
      int i = 0;
      list_reset (p);
      while ((entry = list_next (p)))
        {
          nlst[i++] = entry;
        }
      nlst[i++] = NULL;
      p->cur = cur;
    }
  return nlst;
}
size_t list_size (list* lst)
{
  if (!lst) return 0;
  return lst->num_entries;
}
void list_reset (list* lst)
{
  if (!lst) return;
  lst->cur = lst->head;
}
void* list_next (list* lst)
{
  if (!lst || !lst->cur) return 0;
  void* rv = lst->cur->data;
  lst->cur = lst->cur->next;
  return rv;
}
