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

static int insert_obj(PyObject *d, PyObject *extra, const char *name, PyObject *value)
{
    PyObject *key;

    if (!d) {
        return -1;
    }

    key = PyText_FromString(name);
    if (!key) {
        return -1;
    }

    if (PyDict_SetItem(d, key, value) < 0) {
        goto error;
    }
    if (extra && PyDict_SetItem(extra, key, value) < 0) {
        goto error;
    }

    Py_DECREF(key);
    Py_DECREF(value);
    return 0;

error:
    Py_DECREF(key);
    return -1;
}

static int insert_int(PyObject *d, PyObject *extra, const char *name, long value)
{
    PyObject *v = PyInt_FromLong(value);

    if (!v) {
        return -1;
    }

    if (insert_obj(d, extra, name, v) < 0) {
        Py_DECREF(v);
        return -1;
    }
    return 0;
}

#define insert_obj_helper(d, extra, name, value)     \
    do {                                             \
        if (insert_obj(d, extra, name, value) < 0)   \
            goto error;                              \
    } while (0)

#define insert_int_helper(d, extra, name, value)     \
    do {                                             \
        if (insert_int(d, extra, name, value) < 0)   \
            goto error;                              \
    } while (0)

#define define_const(value) \
    insert_int_helper(d, binlogobject_constants, #value, value)

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

    p_Binlog_Type = &Binlog_Type;
    Py_TYPE(&Binlog_Type) = &PyType_Type;

    insert_obj_helper(d, NULL, "Binlog", (PyObject *)p_Binlog_Type);

    {
        using namespace binary_log;
        define_const(UNKNOWN_EVENT);
        define_const(START_EVENT_V3);
        define_const(QUERY_EVENT);
        define_const(STOP_EVENT);
        define_const(ROTATE_EVENT);
        define_const(INTVAR_EVENT);
        define_const(LOAD_EVENT);
        define_const(SLAVE_EVENT);
        define_const(CREATE_FILE_EVENT);
        define_const(APPEND_BLOCK_EVENT);
        define_const(EXEC_LOAD_EVENT);
        define_const(DELETE_FILE_EVENT);
        define_const(NEW_LOAD_EVENT);
        define_const(RAND_EVENT);
        define_const(USER_VAR_EVENT);
        define_const(FORMAT_DESCRIPTION_EVENT);
        define_const(XID_EVENT);
        define_const(BEGIN_LOAD_QUERY_EVENT);
        define_const(EXECUTE_LOAD_QUERY_EVENT);
        define_const(TABLE_MAP_EVENT);
        define_const(PRE_GA_WRITE_ROWS_EVENT);
        define_const(PRE_GA_UPDATE_ROWS_EVENT);
        define_const(PRE_GA_DELETE_ROWS_EVENT);
        define_const(WRITE_ROWS_EVENT_V1);
        define_const(UPDATE_ROWS_EVENT_V1);
        define_const(DELETE_ROWS_EVENT_V1);
        define_const(INCIDENT_EVENT);
        define_const(HEARTBEAT_LOG_EVENT);
        define_const(IGNORABLE_LOG_EVENT);
        define_const(ROWS_QUERY_LOG_EVENT);
        define_const(WRITE_ROWS_EVENT);
        define_const(UPDATE_ROWS_EVENT);
        define_const(DELETE_ROWS_EVENT);
        define_const(GTID_LOG_EVENT);
        define_const(ANONYMOUS_GTID_LOG_EVENT);
        define_const(PREVIOUS_GTIDS_LOG_EVENT);
        define_const(TRANSACTION_CONTEXT_EVENT);
        define_const(VIEW_CHANGE_EVENT);
    }

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
