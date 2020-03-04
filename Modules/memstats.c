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

static PyMethodDef memstats_methods[] = {
    {"get_arenas_n", memstats_get_arenas_n, METH_NOARGS,
     "Return the number of arenas."},
     {"get_arenas_usage", memstats_get_arenas_usage, METH_NOARGS,
     "Return the percentage of bytes used in arenas."},
    {NULL, NULL} /* sentinel */
};

void initmemstats(void)
{
    PyImport_AddModule("memstats");
    Py_InitModule("memstats", memstats_methods);
}
