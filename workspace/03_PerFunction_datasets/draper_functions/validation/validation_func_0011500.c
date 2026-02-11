xi1_to_gi1(GXDisplay *gdisp,XImage *xi) {
    GImage *gi;
    struct _GImage *base;

    gi = gcalloc(1,sizeof(GImage));
    base = galloc(sizeof(struct _GImage));
    if ( gi==NULL || base==NULL )
return( NULL );
    gi->u.image = base;
    base->image_type = it_mono;
    base->width = xi->width;
    base->height = xi->height;
    base->bytes_per_line = xi->bytes_per_line;
    base->data = (uint8 *) (xi->data);
    base->clut = NULL;
    base->trans = COLOR_UNKNOWN;

    if ( xi->bitmap_bit_order==LSBFirst ) {

	int len = base->height*base->bytes_per_line;
	uint8 *newdata = galloc(len), *pt, *ipt, *end;
	int m1,m2,val;

	for ( ipt = (uint8 *) xi->data, pt=newdata, end=pt+len; pt<end; ++pt, ++ipt ) {
	    val = 0;
	    for ( m1=1, m2=0x80; m2!=0; m1<<=1, m2>>=1 )
		if ( *ipt&m1 ) val|=m2;
	    *pt = val;
	}
	base->data = newdata;
    } else
	xi->data = NULL;
return( gi );
}
