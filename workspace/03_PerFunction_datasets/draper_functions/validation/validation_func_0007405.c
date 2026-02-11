write_tag(v5dstruct * v, int tag, int length, int newfile)
{
    if (!newfile) {

	if (v->CurPos + 8 + length > v->FirstGridPos) {
	    printf("Error: out of header space!\n");

	    return 0;
	}
    }

    if (write_int4(v->FileDesc, tag) == 0)
	return 0;
    if (write_int4(v->FileDesc, length) == 0)
	return 0;
    v->CurPos += 8 + length;
    return 1;
}
