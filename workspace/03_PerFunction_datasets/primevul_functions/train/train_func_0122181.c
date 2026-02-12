static void stbi__rewind(stbi__context *s)
{


   s->img_buffer = s->img_buffer_original;
   s->img_buffer_end = s->img_buffer_original_end;
}
