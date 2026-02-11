tjp_result_type () const {
  stringstream out;
  CTypeInfo *type = _type;
  if (type->isVoid () || type->isUndefined ())
    out << "void";
  else if (type->isAddress ()) {
    if (_use_typedef) {
      if (type->BaseType()->isConst())
        out << "const ";
      out << "TResult";
    }
    else
      type->BaseType ()->TypeText (out, "", true, true);
  }
  else
    if (_use_typedef) {
      if (type->isConst())
        out << "const ";
      out << "TResult";
    }
    else
      type->TypeText (out, "", true, true);
  return out.str ();
}
