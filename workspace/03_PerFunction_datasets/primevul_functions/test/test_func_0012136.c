drill_attribute_merge (gerbv_HID_Attribute *dest, int ndest, gerbv_HID_Attribute *src, int nsrc)
{
    int i, j;


    for (i = 0 ; i < nsrc ; i++) {

	j = 0;
	while (j < ndest && strcmp (src[i].name, dest[j].name) != 0)
	    j++;


	if (j < ndest && src[i].type == dest[j].type) {
	    dest[j].default_val = src[i].default_val;
	} else {
	    GERB_MESSAGE("Ignoring \"%s\" attribute for drill file", src[i].name);
	}
    }
}
