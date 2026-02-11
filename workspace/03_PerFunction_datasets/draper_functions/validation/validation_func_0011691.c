AddType (std::string TypeName, Object* (*Create) (), TypeId id)
{
	TypeId Id = Object::GetTypeId (TypeName);
	if (Id != NoType)
		id = Id;
	if (id == OtherType) {
		id = NextType;
		NextType = TypeId ((unsigned) NextType + 1);
	}
	if (Object::GetTypeId (TypeName) != id)
		Object::AddAlias (id, TypeName);
	TypeDesc &typedesc = m_Types[id];
	typedesc.Id = id;
	typedesc.Create = Create;
	return typedesc.Id;
}
