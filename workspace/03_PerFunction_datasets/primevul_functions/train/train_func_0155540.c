string t_cpp_generator::namespace_prefix(string ns) {


  string result = " ::";

  if (ns.size() == 0) {
    return result;
  }
  string::size_type loc;
  while ((loc = ns.find(".")) != string::npos) {
    result += ns.substr(0, loc);
    result += "::";
    ns = ns.substr(loc + 1);
  }
  if (ns.size() > 0) {
    result += ns + "::";
  }
  return result;
}
