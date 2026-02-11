xsh_image_3d_free( xsh_image_3d ** img_3d )
{
  if ( img_3d != NULL && *img_3d != NULL ) {
    XSH_FREE( (*img_3d)->pixels);
    XSH_FREE( *img_3d);
    *img_3d = NULL ;
  }
}
