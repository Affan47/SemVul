filepos_t EbmlElement::Render(IOCallback & output, bool bWithDefault, bool bKeepPosition, bool bForceRender)
{
  assert(bValueIsSet || (bWithDefault && DefaultISset()));

  if (!bWithDefault && IsDefaultValue()) {
    return 0;
  }
#if defined(LIBEBML_DEBUG)
  uint64 SupposedSize = UpdateSize(bWithDefault, bForceRender);
#endif
  filepos_t result = RenderHead(output, bForceRender, bWithDefault, bKeepPosition);
  uint64 WrittenSize = RenderData(output, bForceRender, bWithDefault);
#if defined(LIBEBML_DEBUG)
  if (static_cast<int64>(SupposedSize) != (0-1))
    assert(WrittenSize == SupposedSize);
#endif
  result += WrittenSize;
  return result;
}
