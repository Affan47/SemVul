gen_attr (attr)
     rtx attr;
{
  const char *p, *tag;
  int is_const = GET_CODE (XEXP (attr, 2)) == CONST;

  printf ("#define HAVE_ATTR_%s\n", XSTR (attr, 0));


  p = XSTR (attr, 1);
  if (*p == '\0')
    printf ("extern int get_attr_%s PARAMS ((%s));\n", XSTR (attr, 0),
	    (is_const ? "void" : "rtx"));
  else
    {
      printf ("enum attr_%s {", XSTR (attr, 0));

      while ((tag = scan_comma_elt (&p)) != 0)
	{
	  write_upcase (XSTR (attr, 0));
	  putchar ('_');
	  while (tag != p)
	    putchar (TOUPPER (*tag++));
	  if (*p == ',')
	    fputs (", ", stdout);
	}

      fputs ("};\n", stdout);
      printf ("extern enum attr_%s get_attr_%s PARAMS ((%s));\n\n",
	      XSTR (attr, 0), XSTR (attr, 0), (is_const ? "void" : "rtx"));
    }


  if (! strcmp (XSTR (attr, 0), "length"))
    {
      puts ("\
extern void shorten_branches PARAMS ((rtx));\n\
extern int insn_default_length PARAMS ((rtx));\n\
extern int insn_variable_length_p PARAMS ((rtx));\n\
extern int insn_current_length PARAMS ((rtx));\n\n\
#include \"insn-addr.h\"\n");
    }
}
