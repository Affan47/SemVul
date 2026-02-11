DebugString() const {
  string contents;
  int depth = 0;
  if (is_extension()) {
    strings::SubstituteAndAppend(&contents, "extend .$0 {\n",
                                 containing_type()->full_name());
    depth = 1;
  }
  DebugString(depth, &contents);
  if (is_extension()) {
     contents.append("}\n");
  }
  return contents;
}
