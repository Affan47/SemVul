uipbuf_init(void)
{
  memset(uipbuf_default_attrs, 0, sizeof(uipbuf_default_attrs));

  uipbuf_set_default_attr(UIPBUF_ATTR_MAX_MAC_TRANSMISSIONS,
                          UIP_MAX_MAC_TRANSMISSIONS_UNDEFINED);


  uipbuf_set_default_attr(UIPBUF_ATTR_LLSEC_LEVEL,
                          UIPBUF_ATTR_LLSEC_LEVEL_MAC_DEFAULT);
}
