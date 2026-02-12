check_location(png_const_structrp png_ptr, int location)
{
   location &= (PNG_HAVE_IHDR|PNG_HAVE_PLTE|PNG_AFTER_IDAT);


   if (location == 0 && (png_ptr->mode & PNG_IS_READ_STRUCT) == 0)
   {

      png_app_warning(png_ptr,
         "png_set_unknown_chunks now expects a valid location");

      location = (png_byte)(png_ptr->mode &
         (PNG_HAVE_IHDR|PNG_HAVE_PLTE|PNG_AFTER_IDAT));
   }


   if (location == 0)
      png_error(png_ptr, "invalid location in png_set_unknown_chunks");


   while (location != (location & -location))
      location &= ~(location & -location);


   return (png_byte)location;
}
