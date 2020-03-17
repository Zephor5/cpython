/* custom module of python 2.7.17m */

#include "Python.h"

/* A static module */

/* 'self' is not used */
static PyObject *
memstats_get_arenas_n(PyObject *self, PyObject *args)
{
    return Py_BuildValue("i", PyObject_GetArenaN());
}

static PyObject *
memstats_get_arenas_usage(PyObject *self, PyObject *args)
{
    return Py_BuildValue("f", PyObject_GetArenaUsage());
}

static PyObject *
memstats_get_user_objects(PyObject *self, PyObject *args)
{
    PyObject *res;
#ifdef WITH_THREAD
    PyGILState_STATE gil;
    gil = PyGILState_Ensure();
#endif
    res = PyGC_Collect_User_Objects();
#ifdef WITH_THREAD
    PyGILState_Release(gil);
#endif
    return res;
}

static PyObject *
memstats_get_exclude_modules(PyObject *self, PyObject *args)
{
    return PyGC_Get_Exclude_Modules();
}

static PyObject *
memstats_set_exclude_modules(PyObject *self, PyObject *args)
{
    return Py_BuildValue("i", PyGC_Set_Exclude_Modules(args));
}

static PyObject *
memstats_get_gc_size(PyObject *self, PyObject *args) {
    return Py_BuildValue("i", PyGC_Get_All_Size());
}

static PyMethodDef memstats_methods[] = {
    {"get_arenas_n", memstats_get_arenas_n, METH_NOARGS,
     "Return the number of arenas."},
     {"get_arenas_usage", memstats_get_arenas_usage, METH_NOARGS,
     "Return the percentage of bytes used in arenas."},
     {"get_user_objects", memstats_get_user_objects, METH_NOARGS,
     "Return all user objects in gc"},
     {"get_exclude_modules", memstats_get_exclude_modules, METH_NOARGS,
     "get exclude modules for user objects"},
     {"set_exclude_modules", memstats_set_exclude_modules, METH_VARARGS,
     "set exclude modules for user objects"},
     {"get_gc_size", memstats_get_gc_size, METH_NOARGS,
     "get total size of all objects in gc"},
    {NULL, NULL} /* sentinel */
};

void initmemstats(void)
{
    PyImport_AddModule("memstats");
    Py_InitModule("memstats", memstats_methods);
}
