getText() const {
  std::ostringstream os;
  for (node_vec::const_iterator ni = children.begin();
       ni != children.end(); ni++) {
    os << *ni;
  }
#if !HAVE_SSTREAM
  os << '\0';
#endif
  return os.str();
}
