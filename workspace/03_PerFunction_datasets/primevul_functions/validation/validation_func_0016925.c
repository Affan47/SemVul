static int SFDGetBitmapReference(FILE *sfd,BDFFont *bdf) {
    BDFChar *bc;
    BDFRefChar *ref, *head;
    int gid, rgid, xoff, yoff;
    char ch;


    if ( getint(sfd,&gid)!=1 || gid<=0 || gid >= bdf->glyphcnt || ( bc = bdf->glyphs[gid] ) == NULL )
return( 0 );
    if ( getint(sfd,&rgid)!=1 || rgid<0 )
return( 0 );
    if ( getint(sfd,&xoff)!=1 )
return( 0 );
    if ( getint(sfd,&yoff)!=1 )
return( 0 );
    while ( isspace( ch=nlgetc( sfd )) && ch!='\r' && ch!='\n' );

    ref = calloc( 1,sizeof( BDFRefChar ));
    ref->gid = rgid; ref->xoff = xoff, ref->yoff = yoff;
    if ( ch == 'S' ) ref->selected = true;
    for ( head = bc->refs; head != NULL && head->next!=NULL; head = head->next );
    if ( head == NULL ) bc->refs = ref;
    else head->next = ref;
return( 1 );
}
