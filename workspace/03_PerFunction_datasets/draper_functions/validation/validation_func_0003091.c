at_eof(stbi *s)
{
   if (s->io.read) {
      if (!(s->io.eof)(s->io_user_data)) return 0;


      if (s->read_from_callbacks == 0) return 1;
   }

   return s->img_buffer >= s->img_buffer_end;
}
