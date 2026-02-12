bool ParseAttrValue(StringPiece type, StringPiece text, AttrValue* out) {

  string field_name;
  bool is_list = absl::ConsumePrefix(&type, "list(");
  if (absl::ConsumePrefix(&type, "string")) {
    field_name = "s";
  } else if (absl::ConsumePrefix(&type, "int")) {
    field_name = "i";
  } else if (absl::ConsumePrefix(&type, "float")) {
    field_name = "f";
  } else if (absl::ConsumePrefix(&type, "bool")) {
    field_name = "b";
  } else if (absl::ConsumePrefix(&type, "type")) {
    field_name = "type";
  } else if (absl::ConsumePrefix(&type, "shape")) {
    field_name = "shape";
  } else if (absl::ConsumePrefix(&type, "tensor")) {
    field_name = "tensor";
  } else if (absl::ConsumePrefix(&type, "func")) {
    field_name = "func";
  } else if (absl::ConsumePrefix(&type, "placeholder")) {
    field_name = "placeholder";
  } else {
    return false;
  }
  if (is_list && !absl::ConsumePrefix(&type, ")")) {
    return false;
  }


  string to_parse;
  if (is_list) {


    StringPiece cleaned = text;
    str_util::RemoveLeadingWhitespace(&cleaned);
    str_util::RemoveTrailingWhitespace(&cleaned);
    if (cleaned.size() < 2 || cleaned[0] != '[' ||
        cleaned[cleaned.size() - 1] != ']') {
      return false;
    }
    cleaned.remove_prefix(1);
    str_util::RemoveLeadingWhitespace(&cleaned);
    if (cleaned.size() == 1) {


      out->Clear();
      out->mutable_list();
      return true;
    }
    to_parse = strings::StrCat("list { ", field_name, ": ", text, " }");
  } else {
    to_parse = strings::StrCat(field_name, ": ", text);
  }

  return ProtoParseFromString(to_parse, out);
}
