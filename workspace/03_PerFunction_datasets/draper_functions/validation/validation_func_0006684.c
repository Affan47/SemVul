intel_dup_image(__DRIimage *orig_image, void *loaderPrivate)
{
   __DRIimage *image;

   image = calloc(1, sizeof *image);
   if (image == NULL)
      return NULL;

   intel_region_reference(&image->region, orig_image->region);
   if (image->region == NULL) {
      free(image);
      return NULL;
   }

   image->internal_format = orig_image->internal_format;
   image->planar_format   = orig_image->planar_format;
   image->dri_format      = orig_image->dri_format;
   image->format          = orig_image->format;
   image->offset          = orig_image->offset;
   image->width           = orig_image->width;
   image->height          = orig_image->height;
   image->tile_x          = orig_image->tile_x;
   image->tile_y          = orig_image->tile_y;
   image->has_depthstencil = orig_image->has_depthstencil;
   image->data            = loaderPrivate;

   memcpy(image->strides, orig_image->strides, sizeof(image->strides));
   memcpy(image->offsets, orig_image->offsets, sizeof(image->offsets));

   return image;
}
