_evas_gl_image_cache_add(Evas_GL_Image *im)
{
   if (im->references == 0)
     {
        im->csize = im->w * im->h * 4;
        im->gc->shared->images_size += im->csize;
        _evas_gl_image_cache_trim(im->gc);
        return EINA_TRUE;
     }
   else
     {
        im->gc->shared->images = eina_list_remove(im->gc->shared->images, im);
        im->cached = 0;
     }
   return EINA_FALSE;
}
