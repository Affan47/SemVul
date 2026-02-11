zx_DEC_ATTR_wsse_BinarySecurityToken(struct zx_ctx* c, struct zx_wsse_BinarySecurityToken_s* x)
{
  switch (x->gg.attr->g.tok) {
    case zx_EncodingType_ATTR:  x->EncodingType = x->gg.attr; return 1;
    case zx_ValueType_ATTR:  x->ValueType = x->gg.attr; return 1;
    case zx_Id_ATTR|zx_wsu_NS:  x->Id = x->gg.attr; return 1;

  default: return 0;
  }
}
