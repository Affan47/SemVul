mkpair(Type type1, Type type2)
{ Type type = (Type)malloc(strlen(type1) + strlen(type2) + 1);
  if (!type)
    error("Out of memory");
  strcpy(type, type1);
  strcat(type, type2);
  return type;
}
