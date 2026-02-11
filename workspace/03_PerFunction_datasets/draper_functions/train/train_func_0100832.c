PyFFContour_IndexAssign( PyObject *self, Py_ssize_t pos, PyObject *val ) {
    PyFF_Contour *cont = (PyFF_Contour *) self;
    PyObject *old;

    if ( !PyType_IsSubtype(&PyFF_PointType,((PyObject *)val)->ob_type) ) {
	PyErr_Format(PyExc_TypeError, "Value must be a (FontForge) Point");
return( -1 );
    }
    if ( pos<0 || pos>=cont->pt_cnt ) {
	PyErr_Format(PyExc_TypeError, "Index out of bounds");
return( -1 );
    }
    if ( cont->points[pos]->on_curve != ((PyFF_Point *) val)->on_curve &&
	    !cont->is_quadratic ) {
	PyErr_Format(PyExc_TypeError, "Replacement point must have the same on_curve setting as original in a cubic contour");
return( -1 );
    }

    old = (PyObject *) cont->points[pos];
    cont->points[pos] = (PyFF_Point *) val;
    PyFFContour_ClearSpiros((PyFF_Contour *) self);
    Py_DECREF( old );
return( 0 );
}
