mem_read(BIO *b, char *out, int outl)
	{
	int ret= -1;
	BUF_MEM *bm;

	bm=(BUF_MEM *)b->ptr;
	BIO_clear_retry_flags(b);
	ret=(outl >=0 && (size_t)outl > bm->length)?(int)bm->length:outl;
	if ((out != NULL) && (ret > 0)) {
		memcpy(out,bm->data,ret);
		bm->length-=ret;
		if(b->flags & BIO_FLAGS_MEM_RDONLY) bm->data += ret;
		else {
			memmove(&(bm->data[0]),&(bm->data[ret]),bm->length);
		}
	} else if (bm->length == 0)
		{
		ret = b->num;
		if (ret != 0)
			BIO_set_retry_read(b);
		}
	return(ret);
	}
