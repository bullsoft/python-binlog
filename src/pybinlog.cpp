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

PyTypeObject *p_Binlog_Type = NULL;

PyObject *binlogobject_constants = NULL;

static PyObject *BinlogError = NULL;

static PyMethodDef BinlogMethods[] = {
    {"version_info", (PyCFunction)version_info, METH_VARARGS, "Return version info."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3
static PyModuleDef binlogmodule = {
    PyModuleDef_HEAD_INIT,
    "binlog",             /* m_name */
    pybinlog_module_doc,  /* m_doc */
    -1,                   /* m_size */
    BinlogMethods         /* m_methods */
};
#endif

PyObject *version_info(PyObject *dummy, PyObject *args)
{
    UNUSED(dummy);
    UNUSED(args);

    return PyText_FromString("dummy");
}

#if PY_MAJOR_VERSION >= 3
# define BINLOG_RETURN_NULL return NULL
  PyMODINIT_FUNC PyInit_binlog(void)
#else
# define BINLOG_RETURN_NULL return
# ifdef __cplusplus
  extern "C"
# endif
  DL_EXPORT(void) initbinlog(void)
#endif
{
    PyObject *m, *d;

#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&binlogmodule);
#else
    m = Py_InitModule3("binlog", BinlogMethods, pybinlog_module_doc);
#endif
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

#if PY_MAJOR_VERSION >= 3
    return m;
#else
    BINLOG_RETURN_NULL;
#endif

error:
    Py_XDECREF(BinlogError);
    Py_XDECREF(binlogobject_constants);
    BINLOG_RETURN_NULL;
}
