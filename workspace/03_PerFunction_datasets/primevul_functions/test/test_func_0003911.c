string EscapeOrigName(const string& orig_name) {

  return absl::StrReplaceAll(orig_name, {{"_", "__"}});
}
