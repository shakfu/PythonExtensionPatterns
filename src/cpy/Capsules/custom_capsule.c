//
// Created by Paul Ross on 18/06/2021.
//
// This takes the Python 3.9 custom3 example and shows how to us Capsules with it.

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#define CUSTOM_CAPSULE
#include "custom_capsule.h"

typedef struct {
    PyObject_HEAD
    PyObject *first; /* first name */
    PyObject *last;  /* last name */
    int number;
} CustomObject;

static void
Custom_dealloc(CustomObject *self) {
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
Custom_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
    CustomObject *self;
    self = (CustomObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->last = PyUnicode_FromString("");
        if (self->last == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->number = 0;
    }
    return (PyObject *) self;
}

static int
Custom_init(CustomObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"first", "last", "number", NULL};
    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|UUi", kwlist,
                                     &first, &last,
                                     &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }
    return 0;
}

static PyMemberDef Custom_members[] = {
        {"number", T_INT, offsetof(CustomObject, number), 0,
                "custom number"},
        {NULL, 0, 0, 0, NULL}  /* Sentinel */
};

static PyObject *
Custom_getfirst(CustomObject *self, void *Py_UNUSED(closure)) {
    Py_INCREF(self->first);
    return self->first;
}

static int
Custom_setfirst(CustomObject *self, PyObject *value, void *Py_UNUSED(closure)) {
    PyObject *tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The first attribute value must be a string");
        return -1;
    }
    tmp = self->first;
    Py_INCREF(value);
    self->first = value;
    Py_DECREF(tmp);
    return 0;
}

static PyObject *
Custom_getlast(CustomObject *self, void *Py_UNUSED(closure)) {
    Py_INCREF(self->last);
    return self->last;
}

static int
Custom_setlast(CustomObject *self, PyObject *value, void *Py_UNUSED(closure)) {
    PyObject *tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The last attribute value must be a string");
        return -1;
    }
    tmp = self->last;
    Py_INCREF(value);
    self->last = value;
    Py_DECREF(tmp);
    return 0;
}

static PyGetSetDef Custom_getsetters[] = {
        {"first", (getter) Custom_getfirst, (setter) Custom_setfirst,
                "first name", NULL},
        {"last", (getter) Custom_getlast, (setter) Custom_setlast,
                "last name", NULL},
        {NULL, NULL, NULL, NULL, NULL}  /* Sentinel */
};

static PyObject *
Custom_name(CustomObject *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Custom_methods[] = {
        {"name", (PyCFunction) Custom_name, METH_NOARGS,
                "Return the name, combining the first and last name"
        },
        {NULL, NULL, 0, NULL}  /* Sentinel */
};

static PyTypeObject CustomType = {
        PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "custom3.Custom",
        .tp_doc = "Custom objects",
        .tp_basicsize = sizeof(CustomObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
        .tp_new = Custom_new,
        .tp_init = (initproc) Custom_init,
        .tp_dealloc = (destructor) Custom_dealloc,
        .tp_members = Custom_members,
        .tp_methods = Custom_methods,
        .tp_getset = Custom_getsetters,
};

static PyModuleDef custommodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "custom_capsule",
        .m_doc = "Example module that creates an extension type.",
        .m_size = -1,
};

/* C API.  Clients get at this via PyDateTime_IMPORT, defined in
 * datetime.h.
 */
static PyCustom_CAPI CAPI = {
        &CustomType
//        &PyDateTime_DateTimeType,
//        &PyDateTime_TimeType,
//        &PyDateTime_DeltaType,
//        &PyDateTime_TZInfoType,
//        NULL,                       // PyDatetime_TimeZone_UTC not initialized yet
//        new_date_ex,
//        new_datetime_ex,
//        new_time_ex,
//        new_delta_ex,
//        new_timezone,
//        datetime_fromtimestamp,
//        datetime_date_fromtimestamp_capi,
//        new_datetime_ex2,
//        new_time_ex2
};


PyMODINIT_FUNC
PyInit_custom_capsule(void)
{
    PyObject *m;
    if (PyType_Ready(&CustomType) < 0)
        return NULL;

    m = PyModule_Create(&custommodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&CustomType);
    if (PyModule_AddObject(m, "Custom", (PyObject *) &CustomType) < 0) {
        Py_DECREF(&CustomType);
        Py_DECREF(m);
        return NULL;
    }

    PyObject *c_api_object = PyCapsule_New(&CAPI, PyCustom_CAPSULE_NAME, NULL);
    if (c_api_object == NULL) {
        return NULL;
    }
    if (PyModule_AddObject(m, "CAPI", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}
