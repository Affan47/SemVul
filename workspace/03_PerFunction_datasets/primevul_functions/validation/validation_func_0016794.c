static double SFDStartsCorrectly(FILE *sfd,char *tok) {
    real dval;
    int ch;

    if ( getname(sfd,tok)!=1 )
return( -1 );
    if ( strcmp(tok,"SplineFontDB:")!=0 )
return( -1 );
    if ( getreal(sfd,&dval)!=1 )
return( -1 );


    if ( dval!=0 && dval!=1 && dval!=2.0 && dval!=3.0
         && !(dval > 3.09 && dval <= 3.21)
         && dval!=4.0 )
    {
        LogError("Bad SFD Version number %.1f", dval );
return( -1 );
    }
    ch = nlgetc(sfd); ungetc(ch,sfd);
    if ( ch!='\r' && ch!='\n' )
return( -1 );

return( dval );
}
