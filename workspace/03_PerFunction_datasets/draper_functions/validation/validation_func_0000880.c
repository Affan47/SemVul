Custom600Headers()
{
   struct stat Buf;
   if (stat(LastGoodSig.c_str(),&Buf) != 0)
      return "\nIndex-File: true";

   return "\nIndex-File: true\nLast-Modified: " + TimeRFC1123(Buf.st_mtime);
}
