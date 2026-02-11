GWidgetPostNotice8(const char *title,const char *statement,...) {
    va_list ap;


    if ( title==NULL ) {
	if ( last!=NULL )
	    GDrawDestroyWindow(last);
return;
    }

    va_start(ap,statement);
    _GWidgetPostNotice8(title,statement,ap,40);
    va_end(ap);
}
