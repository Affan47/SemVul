void af_cache_writethrough(AFFILE *af,int64_t pagenum,const unsigned char *buf,int bufflen)
{
    for(int i=0;i<af->num_pbufs;i++){
	struct aff_pagebuf *p = &af->pbcache[i];
	if(p->pagenum_valid && p->pagenum == pagenum){
	    if(p->pagebuf_dirty){
		(*af->error_reporter)("af_cache_writethrough: overwriting page %" I64u ".\n",pagenum);
		exit(-1);
	    }
	    memcpy(p->pagebuf,buf,bufflen);
	    memset(p->pagebuf+bufflen,0,af->image_pagesize-bufflen);
	    af->bytes_memcpy += bufflen;
	    p->pagebuf_valid = 1;
	    p->pagebuf_dirty = 0;
	    p->last = cachetime++;
	}
    }
}
