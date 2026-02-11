dbcb_resp_entry(const char *fld, size_t fldlen)
{
  if (fld != 0) {
    cstate.writebuf.append_literal("\t");
    escape_string(cstate.writebuf, fld, fld + fldlen);
  } else {
    static const char t[] = "\t\0";
    cstate.writebuf.append(t, t + 2);
  }
}
