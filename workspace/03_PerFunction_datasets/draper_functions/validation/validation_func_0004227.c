ParseLookupFlags(SplineFont *sf,PyObject *flagtuple) {
    int i, flags=0, cnt, temp;

    if ( PyInt_Check(flagtuple))
return( PyInt_AsLong(flagtuple));
    if ( STRING_CHECK(flagtuple))
return( ParseLookupFlagsItem(sf,flagtuple));
    cnt = PySequence_Size(flagtuple);
    if ( cnt==-1 )
return( -1 );
    for ( i=0; i<cnt; ++i ) {
	temp = ParseLookupFlagsItem(sf,PySequence_GetItem(flagtuple,i));
	if ( temp==-1 )
return( -1 );
	flags |= temp;
    }
return( flags );
}
