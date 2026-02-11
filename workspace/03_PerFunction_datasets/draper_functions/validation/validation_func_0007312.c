FindNode(xmlNodePtr kids,char *name) {
    while ( kids!=NULL ) {
	if ( _xmlStrcmp(kids->name,(const xmlChar *) name)== 0 )
return( kids );
	kids = kids->next;
    }
return( NULL );
}
