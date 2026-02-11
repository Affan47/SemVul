convert_to(const Glib::ustring& in, std::string& out, int enc) {
  std::string err;
  if (in.validate()) {
    out = in;
    return utf8();
  }
  else {
    if (convert(in, out, enc, utf8(), err)) {
      return enc;
    }
    out = err;
    return -1;
  }
}
