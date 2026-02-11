find_option_type(struct option_type *optype, const char *str, int len)
{
     if (len == 0)
	  len = strlen(str);
     for ( ; optype->str; optype++) {
	  if (len >= optype->min_match &&
	      memcmp(str, optype->str, len) == 0) {
	       return optype->type;
	  }
     }
     return 0;
}
