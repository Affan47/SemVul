UFOGetBits(xmlDocPtr doc,xmlNodePtr value) {
    xmlNodePtr kid;
    long mask=0;

    if ( _xmlStrcmp(value->name,(const xmlChar *) "array")!=0 )
return( 0 );
    for ( kid = value->children; kid!=NULL; kid=kid->next ) {
	if ( _xmlStrcmp(kid->name,(const xmlChar *) "integer")==0 ) {
	    char *valName = (char *) _xmlNodeListGetString(doc,kid->children,true);
	    mask |= 1<<strtol(valName,NULL,10);
	    free(valName);
	}
    }
return( mask );
}
