gifti_clear_gifti_image(gifti_image * gim)
{
    if(!gim) { fprintf(stderr,"** NULL in clear_gifti_image\n"); return 1; }

    if( G.verb > 5 ) fprintf(stderr,"-- clearing gifti_image\n");


    memset(gim, 0, sizeof(gim));

    gim->version = NULL;
    gifti_clear_nvpairs(&gim->meta);
    gifti_clear_LabelTable(&gim->labeltable);
    gim->darray = NULL;
    gifti_clear_nvpairs(&gim->ex_atrs);

    return 0;
}
