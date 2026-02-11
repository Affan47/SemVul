FormatStatus(xstring& buf,int,const char *prefix)
{
   if(repeat)
      buf.appendf(_("\tRepeat count: %d\n"),repeat_count);
   const char *s=Status();
   if(s[0])
      buf.appendf("\t%s\n",s);
   return buf;
}
