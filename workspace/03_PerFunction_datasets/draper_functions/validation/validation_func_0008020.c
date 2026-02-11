IsUnsignedBDFKey(char *key) {


    int i;

    for ( i=0; StandardProps[i].name!=NULL; ++i )
	if ( strcmp(key,StandardProps[i].name)==0 )
return(( StandardProps[i].type&~prt_property)==prt_uint );

return( false );
}
