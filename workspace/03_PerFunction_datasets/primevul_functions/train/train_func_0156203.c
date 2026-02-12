void af_read_sizes(AFFILE *af)
{
    af_get_seg(af,AF_SECTORSIZE,&af->image_sectorsize,0,0);
    if(af->image_sectorsize==0) af->image_sectorsize = 512;

    if(af_get_seg(af,AF_PAGESIZE,&af->image_pagesize,0,0)){
	af_get_seg(af,AF_SEGSIZE_D,&af->image_pagesize,0,0);
    }


    if(af->badflag!=0) free(af->badflag);
    af->badflag = (unsigned char *)malloc(af->image_sectorsize);
    size_t sectorsize = af->image_sectorsize;
    if(af_get_seg(af,AF_BADFLAG,0,af->badflag,(size_t *)&sectorsize)==0){
	af->badflag_set = 1;
    }


    if(af_get_segq(af,AF_IMAGESIZE,(int64_t *)&af->image_size)){


	char segname[AF_MAX_NAME_LEN];
	size_t datalen = 0;
	af_rewind_seg(af);
	int64_t highest_page_number = 0;
	while(af_get_next_seg(af,segname,sizeof(segname),0,0,&datalen)==0){
	    if(segname[0]==0) continue;
	    int64_t pagenum = af_segname_page_number(segname);
	    if(pagenum > highest_page_number) highest_page_number = pagenum;
	}
	size_t highest_page_len = 0;
	if(af_get_page(af,highest_page_number,0,&highest_page_len)==0){
	    af->image_size = af->image_pagesize * highest_page_number + highest_page_len;
	}
    }
    af->image_size_in_file = af->image_size;
}
