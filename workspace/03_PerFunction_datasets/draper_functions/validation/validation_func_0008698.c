Make_Numeric_Type(va_list * ap)
{
  numericARG *argn = (numericARG *)malloc(sizeof(numericARG));

  if (argn)
    {
      argn->precision = va_arg(*ap,int);
      argn->low       = va_arg(*ap,double);
      argn->high      = va_arg(*ap,double);
#if HAVE_LOCALE_H
      argn->L         = localeconv();
#else
      argn->L         = NULL;
#endif
    }
  return (void *)argn;
}
