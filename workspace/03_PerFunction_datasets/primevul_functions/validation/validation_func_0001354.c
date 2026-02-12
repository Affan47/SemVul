_php_image_output_putbuf(struct gdIOCtx* , const void* buf, int len) {
  return php_write((void *)buf, len);
}
