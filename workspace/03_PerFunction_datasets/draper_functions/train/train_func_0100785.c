GTextInfoGetWidth(GWindow base,GTextInfo *ti,FontInstance *font) {
    int width=0;
    int iwidth=0;
    int skip = 0;

    if ( ti->text!=NULL ) {
	if ( ti->font!=NULL )
	    font = ti->font;

	if ( font!=NULL )
	    GDrawSetFont(base,font);
	width = GDrawGetBiTextWidth(base,ti->text, -1, -1, NULL);
    }
    if ( ti->image!=NULL ) {
	iwidth = GImageGetScaledWidth(base,ti->image);
	if ( ti->text!=NULL )
	    skip = GDrawPointsToPixels(base,6);
    }
return( width+iwidth+skip );
}
