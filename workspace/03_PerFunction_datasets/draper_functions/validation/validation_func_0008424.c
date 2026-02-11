insert_internal_object_declaration(pIIR_DeclarationList *listp, pIIR_DeclarativeRegion region,
				   pIIR_PosInfo pos, const string &name, const string &type_str,
				   pIIR_Expression initial, int flags)
{


  if (listp == NULL)
    listp = get_last_rest_address(&extended_declarations(region));

  pV2CC_InternalObjectDeclaration obj =
    new V2CC_InternalObjectDeclaration(pos ,
				       to_TextLiteral(name) ,
				       region ,
				       NULL ,
				       0  ,
				       NULL  ,
				       initial ,
				       NULL ,
				       (string)type_str ,
				       "" ,
				       flags );
  *listp = new IIR_DeclarationList(obj->pos, obj, *listp);

  return obj;
}
