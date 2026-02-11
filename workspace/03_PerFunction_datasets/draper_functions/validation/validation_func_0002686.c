check_tune_attr (const char *name, rtx exp)
{
  switch (GET_CODE (exp))
    {
    case AND:
      if (check_tune_attr (name, XEXP (exp, 0)))
	return true;
      return check_tune_attr (name, XEXP (exp, 1));

    case IOR:
      return (check_tune_attr (name, XEXP (exp, 0))
	      && check_tune_attr (name, XEXP (exp, 1)));

    case EQ_ATTR:
      return strcmp (XSTR (exp, 0), name) == 0;

    default:
      return false;
    }
}
