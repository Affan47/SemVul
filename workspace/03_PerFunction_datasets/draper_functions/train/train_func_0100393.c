sinfo_new_cube_getvig(
        cpl_imagelist *        cube_in,
        int             loleft_x,
        int             loleft_y,
        int             upright_x,
        int             upright_y)
{
    cpl_imagelist     *        cube_out ;
    int                 i ;
    int                 outlx,
                                        outly ;

    int ilx=0;
    int ily=0;
    int inp=0;
    cpl_image* i_img=NULL;
    cpl_image* o_img=NULL;

    if (cube_in==NULL) return NULL ;

    ilx=cpl_image_get_size_x(cpl_imagelist_get(cube_in,0));
    ily=cpl_image_get_size_y(cpl_imagelist_get(cube_in,0));
    inp=cpl_imagelist_get_size(cube_in);

        if ((loleft_x>upright_x) ||
            (loleft_y>upright_y)) {
            sinfo_msg_error("ill-defined slit for extraction: aborting");
            return NULL ;
        }


    outlx = upright_x - loleft_x + 1 ;
    outly = upright_y - loleft_y + 1 ;


    cube_out = cpl_imagelist_new() ;

    for (i=0 ; i<cpl_imagelist_get_size(cube_in) ; i++) {

      i_img=cpl_imagelist_get(cube_in,i);

                o_img = sinfo_new_image_getvig(i_img,
                        loleft_x, loleft_y,
                        upright_x, upright_y) ;
        cpl_imagelist_set(cube_out,o_img,i);
    }
    return cube_out ;
}
