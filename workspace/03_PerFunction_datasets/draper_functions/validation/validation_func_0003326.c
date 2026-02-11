getMappedType(Node *p, const char *map) {
    String *mapattr = NewString("tmap:");
    Append(mapattr, map);

    String *tm = Getattr(p, mapattr);
    if (tm == NIL) {
      Swig_warning(WARN_MODULA3_TYPEMAP_TYPE_UNDEF, input_file, line_number,
		   "No '%s' typemap defined for type '%s'\n", map, SwigType_str(Getattr(p, "type"), 0));
    }
    Delete(mapattr);
    return tm;
  }
