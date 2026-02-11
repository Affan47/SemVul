gifti_free_image( gifti_image * gim )
{
    if( !gim ) {
        if(G.verb > 2) fprintf(stderr,"** free gifti_image w/NULL pointer\n");
        return 1;
    }

    if( G.verb > 2 ) fprintf(stderr,"-- freeing gifti_image\n");

    if( gim->version ) { free(gim->version);  gim->version = NULL; }

    (void)gifti_free_nvpairs(&gim->meta);
    (void)gifti_free_LabelTable(&gim->labeltable);
    (void)gifti_free_DataArray_list(gim->darray, gim->numDA);
    (void)gifti_free_nvpairs(&gim->ex_atrs);
    free(gim);

    return 0;
}
