GlyphNamesFromTuple(PyObject *glyphs) {
    int cnt, len;
    char *str, *ret, *pt;
    int i;

    if ( STRING_CHECK(glyphs)) {
#if PY_MAJOR_VERSION >= 3
        PyObject *bytes = PyUnicode_AsUTF8String(glyphs);
        if (bytes == NULL)
return( NULL );
        str = copy( PyBytes_AsString(bytes) );
        Py_DECREF( bytes );
return( str );
#else
return( copy( PyBytes_AsString(glyphs)) );
#endif
    }
    if ( !PySequence_Check(glyphs) ) {
	PyErr_Format(PyExc_TypeError,"Expected tuple of glyph names");
return(NULL );
    }
    cnt = PySequence_Size(glyphs);
    len = 0;
    for ( i=0; i<cnt; ++i ) {
	PyObject *aglyph = PySequence_GetItem(glyphs,i);
	if ( PyType_IsSubtype(&PyFF_GlyphType,((PyObject *)aglyph)->ob_type) ) {
	    SplineChar *sc = ((PyFF_Glyph *) aglyph)->sc;
	    str = sc->name;
	} else
	    str = PyBytes_AsString(aglyph);
	if ( str==NULL ) {
	    PyErr_Format(PyExc_TypeError,"Expected tuple of glyph names");
return( NULL );
	}
	len += strlen(str)+1;
    }

    ret = pt = galloc(len+1);
    for ( i=0; i<cnt; ++i ) {
	PyObject *aglyph = PySequence_GetItem(glyphs,i);
	if ( PyType_IsSubtype(&PyFF_GlyphType,((PyObject *)aglyph)->ob_type) ) {
	    SplineChar *sc = ((PyFF_Glyph *) aglyph)->sc;
	    str = sc->name;
	} else
	    str = PyBytes_AsString(aglyph);
	strcpy(pt,str);
	pt += strlen(pt);
	*pt++ = ' ';
    }
    if ( pt!=ret )
	--pt;
    *pt = '\0';
return( ret );
}
