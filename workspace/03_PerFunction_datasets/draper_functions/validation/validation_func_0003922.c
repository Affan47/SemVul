Load(FILE *stream, ReadFunction readFn,void *arg)
{
	BitString tmp,*r;

	if (stream == NULL) {
		NullPtrError("Load");
		return NULL;
	}
	if (fread(&tmp,1,sizeof(BitString),stream) == 0)
		return NULL;
	r = Create(tmp.count);
	if (r == NULL)
		return NULL;
	r->count = tmp.count;
	r->Flags = tmp.Flags;
	if (fread(r->contents,1,BYTES_FROM_BITS(r->count),stream) == 0) {
		iError.RaiseError("Bitstring.Load",CONTAINER_ERROR_FILE_READ);
		return NULL;
	}
	return r;
}
