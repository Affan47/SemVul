GResourceFindString(char *name) {
    int pos;

    pos = _GResource_FindResName(name);
    if ( pos==-1 )
return( NULL );
    else
return( copy(_GResource_Res[pos].val));
}
