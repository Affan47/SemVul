void CopyToString(const tstring& src, tstring* dst) {
  if (src.type() == tstring::SMALL) {
    *dst = src;
  } else {
    dst->assign_as_view(src);
  }
}
