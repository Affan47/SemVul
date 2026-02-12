int af_get_page(AFFILE *af,int64_t pagenum,unsigned char *data,size_t *bytes)
{
    uint32_t arg=0;
    size_t page_len=0;

    if (af_trace){
	fprintf(af_trace,"af_get_page(%p,pagenum=%" I64d ",buf=%p,bytes=%u)\n",af,pagenum,data,(int)*bytes);
    }


    int r = af_get_page_raw(af,pagenum,&arg,0,&page_len);
    if(r){


	if(data && (af->openmode & AF_BADBLOCK_FILL) && errno == ENOENT)
	{
	    for(size_t i = 0;i <= af->image_pagesize - af->image_sectorsize;
		i+= af->image_sectorsize){
		memcpy(data+i,af->badflag,af->image_sectorsize);
		af->bytes_memcpy += af->image_sectorsize;
	    }

	    r = 0;
	}
	return r;
    }


    uint32_t pageflag = 0;
    if((arg & AF_PAGE_COMPRESSED)==0){
	if(data==0){
	    if(bytes) *bytes = page_len;
	    return 0;
	}
	int ret = af_get_page_raw(af,pagenum,&pageflag,data,bytes);
	if(*bytes > page_len) *bytes = page_len;
	if(ret!=0) return ret;
    }
    else {

	unsigned char *compressed_data = (unsigned char *)malloc(page_len);
	size_t compressed_data_len = page_len;
	if(compressed_data==0){
	    return -2;
	}


	if(af_get_page_raw(af,pagenum,&pageflag,compressed_data,&compressed_data_len)){
	    free(compressed_data);
	    return -3;
	}


	int res = -1;
	bool free_data = false;
	if(data==0){
	    data = (unsigned char *)malloc(af->image_pagesize);
	    free_data = true;
	    *bytes = af->image_pagesize;
	}

	switch((pageflag & AF_PAGE_COMP_ALG_MASK)){
	case AF_PAGE_COMP_ALG_ZERO:
	    if(compressed_data_len != 4){
		(*af->error_reporter)("ALG_ZERO compressed data is %d bytes, expected 4.",compressed_data_len);
		break;
	    }
	    memset(data,0,af->image_pagesize);
	    *bytes = ntohl(*(long *)compressed_data);
	    res = 0;
	    break;

	case AF_PAGE_COMP_ALG_ZLIB:
	    res = uncompress(data,(uLongf *)bytes,compressed_data,compressed_data_len);
	    switch(res){
	    case Z_OK:
		break;
	    case Z_ERRNO:
		(*af->error_reporter)("Z_ERRNOR decompressing segment %" I64d,pagenum);
	    case Z_STREAM_ERROR:
		(*af->error_reporter)("Z_STREAM_ERROR decompressing segment %" I64d,pagenum);
	    case Z_DATA_ERROR:
		(*af->error_reporter)("Z_DATA_ERROR decompressing segment %" I64d,pagenum);
	    case Z_MEM_ERROR:
		(*af->error_reporter)("Z_MEM_ERROR decompressing segment %" I64d,pagenum);
	    case Z_BUF_ERROR:
		(*af->error_reporter)("Z_BUF_ERROR decompressing segment %" I64d,pagenum);
	    case Z_VERSION_ERROR:
		(*af->error_reporter)("Z_VERSION_ERROR decompressing segment %" I64d,pagenum);
	    default:
		(*af->error_reporter)("uncompress returned an invalid value in get_segment");
	    }
	    break;

#ifdef USE_LZMA
	case AF_PAGE_COMP_ALG_LZMA:
	    res = lzma_uncompress(data,bytes,compressed_data,compressed_data_len);
	    if (af_trace) fprintf(af_trace,"   LZMA decompressed page %" I64d ". %d bytes => %u bytes\n",
				  pagenum,(int)compressed_data_len,(int)*bytes);
	    switch(res){
	    case 0:break;
	    case 1:(*af->error_reporter)("LZMA header error decompressing segment %" I64d "\n",pagenum);
		break;
	    case 2:(*af->error_reporter)("LZMA memory error decompressing segment %" I64d "\n",pagenum);
		break;
	    }
	    break;
#endif

	default:
	    (*af->error_reporter)("Unknown compression algorithm 0x%d",
				  pageflag & AF_PAGE_COMP_ALG_MASK);
	    break;
	}

	if(free_data){
	    free(data);
	    data = 0;
	}
	free(compressed_data);
	af->pages_decompressed++;
	if(res!=Z_OK) return -1;
    }


    if(data && (af->image_pagesize > af->image_sectorsize)){
	const int SECTOR_SIZE = af->image_sectorsize;
	size_t bytes_left_in_sector = (SECTOR_SIZE - (*bytes % SECTOR_SIZE)) % SECTOR_SIZE;
	for(size_t i=0;i<bytes_left_in_sector;i++){
	    data[*bytes + i] = 0;
	}
	size_t end_of_data = *bytes + bytes_left_in_sector;


	for(size_t i = end_of_data; i <= af->image_pagesize-SECTOR_SIZE; i+=SECTOR_SIZE){
	    memcpy(data+i,af->badflag,SECTOR_SIZE);
	    af->bytes_memcpy += SECTOR_SIZE;
	}
    }
    return 0;
}
