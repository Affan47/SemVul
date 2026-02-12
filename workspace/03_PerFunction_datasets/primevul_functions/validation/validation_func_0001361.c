static void _php_image_output_putc(struct gdIOCtx* , int c) {


  unsigned char ch = (unsigned char) c;
  php_write(&ch, 1);
}
