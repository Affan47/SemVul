StripAccelerators(const wxString &s)
{
   wxString result;
   result.Alloc(s.Length());
   for(size_t i = 0; i < s.Length(); i++) {
      if (s[i] == '\t')
         break;
      if (s[i] != '&' && s[i] != '.')
         result += s[i];
   }
   return result;
}
