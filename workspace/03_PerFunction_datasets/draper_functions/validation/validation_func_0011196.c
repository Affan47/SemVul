read_ascii(FILE *fp, Type t, void *data, int index)
{
    int r, i;
    char string[80];

    switch (t) {
    case TYPE_BYTE:
	r = fscanf(fp,"%d",&i);
	if (i<DXD_MIN_BYTE || i>DXD_MAX_BYTE) {
	    DXSetError(ERROR_DATA_INVALID,"#10905",i,"byte");
	    goto error;
	}
	DREF(byte,data,index) = (byte)i;
	break;
    case TYPE_UBYTE:
	r = fscanf(fp,"%d",&i);
	if (i<0 || i>DXD_MAX_UBYTE) {
	    DXSetError(ERROR_DATA_INVALID,"#10905",i,"ubyte");
	    goto error;
	}
	DREF(ubyte,data,index) = (ubyte)i;
	break;
    case TYPE_SHORT:
	r = fscanf(fp,"%d",&i);
	if (i<DXD_MIN_SHORT || i>DXD_MAX_SHORT) {
	    DXSetError(ERROR_DATA_INVALID,"#10905",i,"short");
	    goto error;
	}
	DREF(short,data,index) = (short)i;
	break;
    case TYPE_USHORT:
	r = fscanf(fp,"%d",&i);
	if (i<0 || i>DXD_MAX_USHORT) {
	    DXSetError(ERROR_DATA_INVALID,"#10905",i,"ushort");
	    goto error;
	}
	DREF(unsigned short,data,index) = (unsigned short)i;
	break;
    case TYPE_INT:
	r = fscanf(fp,"%d",&DREF(int,data,index));
	break;
    case TYPE_UINT:
  	r = fscanf(fp,"%u",&DREF(unsigned int,data,index));
	break;
    case TYPE_FLOAT:
	r = fscanf(fp,"%f",&DREF(float,data,index));
	break;
    case TYPE_DOUBLE:
	r = fscanf(fp,"%lf",&DREF(double,data,index));
	break;
    case TYPE_STRING:
	r = fscanf(fp,"%s",&DREF(char,data,index));
	break;
    default:
	DXErrorGoto(ERROR_INTERNAL,
		"Type not implemented for ascii files");
    }

    if (r == 0){
		fscanf(fp,"%70s",string);
		DXSetError(ERROR_DATA_INVALID, "#10906",string);
        goto error;
    }

    if (r == EOF){
	DXSetError(ERROR_MISSING_DATA, "#10898",_dxd_gi_filename);
        goto error;
    }

    return OK;
error:
    return ERROR;

}
