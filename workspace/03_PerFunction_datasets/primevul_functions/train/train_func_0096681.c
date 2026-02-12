uipbuf_clear_attr(void)
{

  memcpy(uipbuf_attrs, uipbuf_default_attrs, sizeof(uipbuf_attrs));
}
