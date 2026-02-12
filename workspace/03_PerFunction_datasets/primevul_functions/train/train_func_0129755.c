bool EbmlMaster::CheckMandatory() const
{
  assert(Context.GetSize() != 0);

  unsigned int EltIdx;
  for (EltIdx = 0; EltIdx < EBML_CTX_SIZE(Context); EltIdx++) {
    if (EBML_CTX_IDX(Context,EltIdx).IsMandatory()) {
      if (FindElt(EBML_CTX_IDX_INFO(Context,EltIdx)) == NULL) {
#if defined(LIBEBML_DEBUG)


#endif
        return false;
      }
    }
  }

  return true;
}
