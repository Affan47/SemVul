lineCountIndent(FILE *file, struct gcontext *gc) {
    int ch;

    while ( (ch=getc(file))!=EOF && ch!='\n' && ch!='\r' );
    if ( ch!=EOF )
	++gc->lineno;
    if ( ch=='\r' ) {
	ch = getc(file);
	if ( ch!='\n' )
	    ungetc(ch,file);
    }
return( gc->found_indent = countIndent(file));
}
