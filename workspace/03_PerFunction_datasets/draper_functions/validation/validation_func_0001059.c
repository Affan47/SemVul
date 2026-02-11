checkParameterArgumentInteger(
	const char *argument, int *dest, bool *wasReallySet, bool returnFirst)
{
  char *param;
  char *endPtr;
  int intVal;

  param = checkParameterArgument(argument, returnFirst);

  if (param == NULL)
  {
    if (wasReallySet)
      *wasReallySet = false;
    return true;
  }
  else if (param[0] != '\0')
  {
    intVal = strtol(param, &endPtr, 10);
    if (endPtr[0] == '\0')
    {
      *dest = intVal;
      if (wasReallySet)
	*wasReallySet = true;
      return true;
    }
    else
    {
      ArLog::log(ArLog::Normal,
		"Argument given to %s was not an integer it was the string %s",
		 argument, param);
      return false;
    }

  }
  else
  {
    ArLog::log(ArLog::Normal, "No argument given to %s", argument);
    return false;
  }

}
