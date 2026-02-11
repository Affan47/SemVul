zx_DEC_ELEM_md_AffiliationDescriptor(struct zx_ctx* c, struct zx_md_AffiliationDescriptor_s* x)
{
  struct zx_elem_s* el = x->gg.kids;
  switch (el->g.tok) {
  case zx_ds_Signature_ELEM:
    if (!x->Signature)
      x->Signature = (struct zx_ds_Signature_s*)el;
    return 1;
  case zx_md_Extensions_ELEM:
    if (!x->Extensions)
      x->Extensions = (struct zx_md_Extensions_s*)el;
    return 1;
  case zx_md_AffiliateMember_ELEM:
    if (!x->AffiliateMember)
      x->AffiliateMember = el;
    return 1;
  case zx_md_KeyDescriptor_ELEM:
    if (!x->KeyDescriptor)
      x->KeyDescriptor = (struct zx_md_KeyDescriptor_s*)el;
    return 1;

  default: return 0;
  }
}
