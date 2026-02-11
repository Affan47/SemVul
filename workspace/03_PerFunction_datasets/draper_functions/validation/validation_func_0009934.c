getnextNetPrefix(VarBind *varbind, Variable *var)
{
  NetPrefixNode *prefix;
  AsnOid *varBindName;

  varBindName = &varbind->name;
  for(prefix = (NetPrefixNode *) var->value;
      prefix != NULL && AsnOidCompare(prefix->name, varBindName) != AsnOidGreater;
      prefix = prefix->next);

  if(prefix == NULL)
    return NOSUCHNAME;

  varbind->name.octs = Asn1Alloc(prefix->name->octetLen);
  AsnOidCopy(varBindName, prefix->name);

  varbind->value = Asn1Alloc(sizeof(struct ObjectSyntax));
  varbind->value->choiceId = OBJECTSYNTAX_SIMPLE;
  varbind->value->a.simple = Asn1Alloc(sizeof(struct SimpleSyntax));
  varbind->value->a.simple->choiceId = SIMPLESYNTAX_NUMBER;
  varbind->value->a.simple->a.number = VALID;

  return NOERROR;
}
