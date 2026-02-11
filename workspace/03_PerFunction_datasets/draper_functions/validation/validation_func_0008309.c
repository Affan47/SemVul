RemoveOpacities(Object o)
{
  int i;
  Object subo;


  switch(DXGetObjectClass(o)) {
  case CLASS_GROUP:

    for (i=0; (subo=DXGetEnumeratedMember((Group)o, i, NULL)); i++){
      if (!RemoveOpacities(subo))
	return ERROR;
    }
    break;
  case CLASS_FIELD:
    if (DXGetComponentValue((Field)o,"opacities"))
       DXDeleteComponent((Field)o,"opacities");
    break;
  default:

    DXSetError(ERROR_BAD_CLASS,"not a group or field");
    return ERROR;
  }
  return OK;
}
