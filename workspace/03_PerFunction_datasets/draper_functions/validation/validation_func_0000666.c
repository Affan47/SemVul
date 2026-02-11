handleDelAttr (action, arg)
     char *action, *arg;
{
  char *attrNamePtr;
  if (!arg || !(*arg)) {
    sprintf (stMessage, "No attribute name specified -- '%s' ignored.\n", action);
    stLog (stMessage, ST_LOG_WARNING);
    return (0);
  }

  attrNamePtr = atAttrName (arg);
  if ((delAttrs[delAttrCount] = malloc (strlen (attrNamePtr)+1)) == NULL) {
    stLog ("Not enough memory", ST_LOG_ERROR);
    return (1);
  }
  strcpy (delAttrs[delAttrCount++], attrNamePtr);
  return (addToActionList (action, VADM_DELATTR));
}
