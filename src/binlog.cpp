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

#include "pybinlog.h"

/*
 * constructor
 */
static BinlogObject *do_binlog_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds)
{
    return NULL;
}

static void do_binlog_dealloc(BinlogObject *self)
{
    PyObject_GC_UnTrack(self);

    Py_TRASHCAN_SAFE_BEGIN(self);
    Py_CLEAR(self->dict);
    Binlog_Type.tp_free(self);
    Py_TRASHCAN_SAFE_END(self);
}

static PyObject *do_binlog_connect(BinlogObject *self, PyObject *args)
{
    Py_RETURN_NONE;
}

static PyObject *do_binlog_get_next_event(BinlogObject *self, PyObject *args)
{
    Py_RETURN_NONE;
}

static PyObject *do_binlog_close(BinlogObject *self)
{
    Py_RETURN_NONE;
}

static int do_binlog_clear(BinlogObject *self)
{
    return 0;
}

static int do_binlog_traverse(BinlogObject *self, visitproc visit, void *arg)
{
    return 0;
}

#if PY_MAJOR_VERSION >= 3

static PyObject *do_binlog_getattro(PyObject *o, PyObject *name)
{
    return NULL;
}

static int do_binlog_setattro(PyObject *o, PyObject *name, PyObject *v)
{
    return 0;
}

#else

static PyObject * do_binlog_getattr(BinlogObject *bo, char *name)
{
    return NULL;
}

static int do_binlog_setattr(BinlogObject *bo, char *name, PyObject *v)
{
    return 0;
}

#endif /* PY_MAJOR_VERSION >= 3 */

static PyMethodDef binlogobject_methods[] = {
    {"connect",        (PyCFunction)do_binlog_connect,        METH_VARARGS, NULL},
    {"get_next_event", (PyCFunction)do_binlog_get_next_event, METH_NOARGS,  NULL},
    {"close",          (PyCFunction)do_binlog_close,          METH_NOARGS,  NULL},
    {NULL, NULL, 0, NULL}
};

PyTypeObject Binlog_Type = {
#if PY_MAJOR_VERSION >= 3
    PyVarObject_HEAD_INIT(NULL, 0)
#else
    PyObject_HEAD_INIT(NULL)
    0,                               /* ob_size */
#endif
    "binlog.Binlog",                 /* tp_name */
    sizeof(BinlogObject),            /* tp_basicsize */
    0,                               /* tp_itemsize */
    (destructor)do_binlog_dealloc,   /* tp_dealloc */
    0,                               /* tp_print */
#if PY_MAJOR_VERSION >= 3
    0,                               /* tp_getattr */
    0,                               /* tp_setattr */
#else
    (getattrfunc)do_binlog_getattr,  /* tp_getattr */
    (setattrfunc)do_binlog_setattr,  /* tp_setattr */
#endif
    0,                               /* tp_reserved */
    0,                               /* tp_repr */
    0,                               /* tp_as_number */
    0,                               /* tp_as_sequence */
    0,                               /* tp_as_mapping */
    0,                               /* tp_hash  */
    0,                               /* tp_call */
    0,                               /* tp_str */
#if PY_MAJOR_VERSION >= 3
    (getattrofunc)do_binlog_getattro, /* tp_getattro */
    (setattrofunc)do_binlog_setattro, /* tp_setattro */
#else
    0,                               /* tp_getattro */
    0,                               /* tp_setattro */
#endif
    0,                               /* tp_as_buffer */
    Py_TPFLAGS_HAVE_GC,              /* tp_flags */
    NULL,                            /* tp_doc */
    (traverseproc)do_binlog_traverse, /* tp_traverse */
    (inquiry)do_binlog_clear,        /* tp_clear */
    0,                               /* tp_richcompare */
    0,                               /* tp_weaklistoffset */
    0,                               /* tp_iter */
    0,                               /* tp_iternext */
    binlogobject_methods,            /* tp_methods */
    0,                               /* tp_members */
    0,                               /* tp_getset */
    0,                               /* tp_base */
    0,                               /* tp_dict */
    0,                               /* tp_descr_get */
    0,                               /* tp_descr_set */
    0,                               /* tp_dictoffset */
    0,                               /* tp_init */
    PyType_GenericAlloc,             /* tp_alloc */
    (newfunc)do_binlog_new,          /* tp_new */
    PyObject_GC_Del,                 /* tp_free */
};

