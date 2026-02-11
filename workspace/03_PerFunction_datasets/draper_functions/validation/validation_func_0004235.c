gen_charattr(Symbol* asym, Bytebuffer* databuf)
{
    Datasrc* src;
    Constant* con;

    if(asym->data == NULL) return;
    src = datalist2src(asym->data);
    while((con=srcnext(src))) {
	switch (con->nctype) {

	case NC_CHAR:
	    bbAppend(databuf,con->value.charv);
	    break;
	case NC_BYTE:
	    bbAppend(databuf,con->value.int8v);
	    break;
	case NC_UBYTE:
	    bbAppend(databuf,con->value.uint8v);
	    break;
	case NC_STRING:
	    bbCat(databuf,con->value.stringv.stringv);
	    bbNull(databuf);
	    break;
	case NC_FILL:
	    bbAppend(databuf,NC_FILL_CHAR);
	    break;
	default:
	    semerror(srcline(src),
		     "Encountered non-string constant in attribute: %s",
		     asym->name);
	    return;
	}
    }
}
