makerequest (int request, const char *name, struct tftphdr *tp,
	     const char *mode)
{
  register char *cp;
  size_t arglen, len;

  tp->th_opcode = htons ((unsigned short) request);
#if HAVE_STRUCT_TFTPHDR_TH_U


  cp = (char *) tp + (tp->th_stuff - (char *) tp);
#else
  cp = (char *) &(tp->th_stuff);
#endif


  len = PKTSIZE - sizeof (struct tftphdr) - sizeof ("netascii");
  arglen = strlen (name);

  strncpy (cp, name, len);

  cp += (arglen < len) ? arglen : len;
  *cp++ = '\0';


  strcpy (cp, mode);
  cp += strlen (mode);
  *cp++ = '\0';
  return cp - (char *) tp;
}
