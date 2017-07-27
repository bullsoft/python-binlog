/*
 * Copyright (C) 2017 Shang Yuanchun <idealities@gmail.com>
 *
 *
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * Bitzer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bitzer. If not, write to:
 * The Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301, USA.
 */

#ifndef BINLOG_H
#define BINLOG_H

#include <Python.h>

#include "docstring.h"

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(WIN32)
#  define WIN32 1
#endif

#if PY_MAJOR_VERSION >= 3
# define PyText_FromFormat(format, str) PyUnicode_FromFormat((format), (str))
# define PyText_FromString(str) PyUnicode_FromString(str)
#else
# define PyText_FromFormat(format, str) PyString_FromFormat((format), (str))
# define PyText_FromString(str) PyString_FromString(str)
#endif

#ifndef UNUSED
# define UNUSED(x) ((void)x)
#endif

extern PyObject *binlogobject_constants;

#ifdef __cplusplus
extern "C" {
#endif

static PyObject *version_info(PyObject *dummy, PyObject *args);

#ifdef __cplusplus
}
#endif

#endif
