Status ValidateSignatureWithAttrs(const OpDef& sig, AttrSlice attr_values) {


  for (const auto& attr : sig.attr()) {
    const AttrValue* attr_value = attr_values.Find(attr.name());
    if (attr_value) {
      Status status = AttrValueHasType(*attr_value, attr.type());
      if (!status.ok()) {
        errors::AppendToMessage(&status, "for attr '", attr.name(), "'");
        return status;
      }
    } else if (!attr.has_default_value()) {
      return errors::NotFound("Attr ", attr.name(), " is not found from ",
                              SummarizeOpDef(sig));
    }
  }


#if 0
  if (attr_values.size() != sig.attr_size()) {
    for (const auto& a : attr_values) {

      bool found = false;
      for (const auto& s : sig.attr()) {
        if (a.first == s.name()) {
          found = true;
          break;
        }
      }
      if (!found) {
        return errors::NotFound("Attr ", a.first, " is not found in ",
                                SummarizeOpDef(sig));
      }
    }
  }
#endif

  return Status::OK();
}
