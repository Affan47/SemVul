geo_free_groups( group_t *groups )
{
    group_t *grp;
    int gid = 0;
    char str[64];

    for( ; groups != NULL; gid++ )
    {
        grp = groups->Next;

        sprintf( str, "GroupStatus(%d)", gid );
        Tcl_UnlinkVar( TCLInterp, str );

        free( groups );
        groups = grp;
    }
    Tcl_SetVar( TCLInterp, "NumberOfGroups", "0", TCL_GLOBAL_ONLY );
}
