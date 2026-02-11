typemap_locals(DOHString * s, ParmList *l, Wrapper *f, int argnum) {
  Parm *p;
  char *new_name;

  p = l;
  while (p) {
    SwigType *pt = Getattr(p, "type");
    SwigType *at = SwigType_alttype(pt, 1);
    String *pn = Getattr(p, "name");
    String *value = Getattr(p, "value");
    if (at)
      pt = at;
    if (pn) {
      if (Len(pn) > 0) {
	String *str;
	int isglobal = 0;

	str = NewStringEmpty();

	if (strncmp(Char(pn), "_global_", 8) == 0) {
	  isglobal = 1;
	}


	if ((argnum >= 0) && (!isglobal)) {
	  Printf(str, "%s%d", pn, argnum);
	} else {
	  Append(str, pn);
	}
	if (isglobal && Wrapper_check_local(f, str)) {
	  p = nextSibling(p);
	  Delete(str);
	  if (at)
	    Delete(at);
	  continue;
	}
	if (value) {
	  String *pstr = SwigType_str(pt, str);
	  new_name = Wrapper_new_localv(f, str, pstr, "=", value, NIL);
	  Delete(pstr);
	} else {
	  String *pstr = SwigType_str(pt, str);
	  new_name = Wrapper_new_localv(f, str, pstr, NIL);
	  Delete(pstr);
	}
	if (!isglobal) {

	  Replace(s, pn, new_name, DOH_REPLACE_ID | DOH_REPLACE_NOQUOTE);
	}
	Delete(str);
      }
    }
    p = nextSibling(p);
    if (at)
      Delete(at);
  }
}
