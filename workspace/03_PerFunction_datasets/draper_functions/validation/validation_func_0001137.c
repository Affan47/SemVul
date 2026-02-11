ArgusPrintSrcAddrLabel (char *buf)
{
   if (ArgusInput->ArgusManStart.ahdr.type & ARGUS_RMON)
      sprintf (&buf[strlen(buf)], "%*s Addr%*s ",   (hfield - 5)/2, " ", (hfield - 5)/2, " ");
   else
      sprintf (&buf[strlen(buf)], "%*sSrcAddr%*s ", (hfield - 7)/2, " ", (hfield - 7)/2, " ");

   if (!(hfield & 0x01)) sprintf (&buf[strlen(buf)], " ");
}
