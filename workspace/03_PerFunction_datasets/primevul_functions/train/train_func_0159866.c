nt_lm_owf_gen (char *pwd, uschar nt_p16[16], uschar p16[16])
{
char passwd[130];

memset (passwd, '\0', 130);
safe_strcpy (passwd, pwd, sizeof (passwd) - 1);


memset (nt_p16, '\0', 16);
E_md4hash (US passwd, nt_p16);

#ifdef DEBUG_PASSWORD
DEBUG_X (100, ("nt_lm_owf_gen: pwd, nt#\n"));
dump_data (120, passwd, strlen (passwd));
dump_data (100, CS  nt_p16, 16);
#endif


passwd[14] = '\0';
strupper (passwd);


memset (p16, '\0', 16);
E_P16 (US passwd, US p16);

#ifdef DEBUG_PASSWORD
DEBUG_X (100, ("nt_lm_owf_gen: pwd, lm#\n"));
dump_data (120, passwd, strlen (passwd));
dump_data (100, CS  p16, 16);
#endif

memset (passwd, '\0', sizeof (passwd));
}
