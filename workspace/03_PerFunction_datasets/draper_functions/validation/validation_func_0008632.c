getPfaEditGroups(void) {
    static char *groupname=NULL;
    char buffer[1025];

    if ( groupname!=NULL )
return( groupname );
    if ( getPfaEditDir(buffer)==NULL )
return( NULL );
    sprintf(buffer,"%s/groups", getPfaEditDir(buffer));
    groupname = copy(buffer);
return( groupname );
}
