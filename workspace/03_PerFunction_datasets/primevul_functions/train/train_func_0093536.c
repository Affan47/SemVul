static int avi_add_chunk(avi_t *AVI, unsigned char *tag, unsigned char *data, u32 length)
{
	unsigned char c[8];
	char p=0;


	memcpy(c,tag,4);
	long2str(c+4,length);


	if( avi_write(AVI->fdes,(char *)c,8) != 8 ||
	        avi_write(AVI->fdes,(char *)data,length) != length ||
	        avi_write(AVI->fdes,&p,length&1) != (length&1))
	{
		gf_fseek(AVI->fdes,AVI->pos,SEEK_SET);
		AVI_errno = AVI_ERR_WRITE;
		return -1;
	}


	AVI->pos += 8 + PAD_EVEN(length);


	return 0;
}
