/*
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 2001 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <stdlib.h>

#include "libfilter.h"
#include "filter_gstring.h"


stnode_t* stnode_new(sttype_id_t type_id, gpointer data);
void stnode_set_bracket(stnode_t *node, gboolean bracket);
stnode_t* stnode_dup(const stnode_t *org);
void stnode_init(stnode_t *node, sttype_id_t type_id, gpointer data);
void stnode_init_int(stnode_t *node, sttype_id_t type_id, gint32 value);
void stnode_free(stnode_t *node);
const char* stnode_type_name(stnode_t *node);
sttype_id_t stnode_type_id(stnode_t *node);
gint32 stnode_value(stnode_t *node);
const char* stnode_deprecated(stnode_t *node);

#define assert_magic(obj, mnum) \
	g_assert((obj)); \
	if ((obj)->magic != (mnum)) { \
		printf("\nMagic num is 0x%08x, but should be 0x%08x", \
			(obj)->magic, (mnum)); \
			g_assert((obj)->magic == (mnum)); \
	}

#define STTYPE_ACCESSOR(ret,type,attr,magicnum) \
	ret \
	CONCAT(CONCAT(CONCAT(sttype_,type),_),attr) (stnode_t *node) {\
		CONCAT(type,_t)	*value; \
		value = (CONCAT(type,_t) *)stnode_data(node);\
		assert_magic(value, magicnum); \
		return value->attr; \
	}

#define STTYPE_ACCESSOR_PROTOTYPE(ret,type,attr) \
	ret \
	CONCAT(CONCAT(CONCAT(sttype_,type),_),attr) (stnode_t *node);


#endif
