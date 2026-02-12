is_ICC_signature(png_alloc_size_t it)
{
   return is_ICC_signature_char(it >> 24)  &&
      is_ICC_signature_char((it >> 16) & 0xff) &&
      is_ICC_signature_char((it >> 8) & 0xff) &&
      is_ICC_signature_char(it & 0xff);
}
