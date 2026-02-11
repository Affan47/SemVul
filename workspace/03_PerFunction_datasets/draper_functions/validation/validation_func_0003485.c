test_vlstr_alloc_custom(size_t size, void *info)
{
    void *ret_value=NULL;
    size_t *mem_used=(size_t *)info;
    size_t extra;


    extra=MAX(sizeof(void *),sizeof(size_t));

    if((ret_value=HDmalloc(extra+size))!=NULL) {
        *(size_t *)ret_value=size;
        *mem_used+=size;
    }
    ret_value=((unsigned char *)ret_value)+extra;
    return(ret_value);
}
