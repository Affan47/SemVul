int af_set_pagesize(AFFILE *af,uint32_t pagesize)
{


    struct af_vnode_info vni;

    af_vstat(af,&vni);

    if(vni.changable_pagesize==0 && af->image_size>0){
	if(pagesize==af->image_pagesize) return 0;
	errno = EINVAL;
	return -1;
    }
    if(pagesize % af->image_sectorsize != 0){
	(*af->error_reporter)("Cannot set pagesize to %d (sectorsize=%d)\n",
			      pagesize,af->image_sectorsize);
	errno = EINVAL;
	return -1;
    }

    af->image_pagesize = pagesize;
    if(af_update_seg(af,AF_PAGESIZE,pagesize,0,0)){
	if(errno != ENOTSUP) return -1;
    }
    return 0;
}
