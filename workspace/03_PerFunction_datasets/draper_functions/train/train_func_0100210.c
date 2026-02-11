get_pkcs7_from_part(long msgno,const char *section)
{
    STORE_S *store = NULL;
    PKCS7   *p7 = NULL;
    BIO	   *in = NULL;

    store = get_part_contents(msgno, section);

    if(store){
	if(store->src == CharStar){
	    int len;


	    len = (int) (store->eod - store->dp);
	    in = BIO_new_mem_buf(store->txt, len);
	}
	else{
	    unsigned char c;

	    in = BIO_new(BIO_s_mem());
	    (void) BIO_reset(in);

	    so_seek(store, 0L, 0);
	    while(so_readc(&c, store)){
		BIO_write(in, &c, 1);
	    }
	}

        if(in){

            if((p7=d2i_PKCS7_bio(in,NULL)) == NULL){

	    }

	    BIO_free(in);
        }

	so_give(&store);
    }

    return p7;
}
