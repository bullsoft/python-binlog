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

PyObject *binlogobject_constants = NULL;

static PyObject *BinlogError = NULL;

static PyMethodDef BinlogMethods[] = {
    {"version_info", (PyCFunction)version_info, METH_VARARGS, "Return version info."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyModuleDef binlogmodule = {
    PyModuleDef_HEAD_INIT,
    "binlog",             /* m_name */
    pybinlog_module_doc,  /* m_doc */
    -1,                   /* m_size */
    BinlogMethods         /* m_methods */
};

static PyObject *version_info(PyObject *dummy, PyObject *args)
{
    UNUSED(dummy);
    UNUSED(args);

    return PyText_FromString("dummy");
}

PyMODINIT_FUNC PyInit_binlog(void)
{
    PyObject *m, *d;

    m = PyModule_Create(&binlogmodule);
    if (!m) {
        goto error;
    }

    BinlogError = PyErr_NewException("binlog.error", NULL, NULL);
    if (!BinlogError) {
        goto error;
    }
    if (PyModule_AddObject(m, "error", BinlogError) < 0) {
        goto error;
    }

    d = PyModule_GetDict(m);

    binlogobject_constants = PyDict_New();
    if (!binlogobject_constants)
        goto error;

    return m;

error:
    Py_XDECREF(BinlogError);
    Py_XDECREF(binlogobject_constants);
    return NULL;
}
