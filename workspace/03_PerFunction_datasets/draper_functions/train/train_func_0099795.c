aiSetImportPropertyString(aiPropertyStore* p, const char* szName,
	const C_STRUCT aiString* st)
{
	if (!st) {
		return;
	}
	ASSIMP_BEGIN_EXCEPTION_REGION();
	PropertyMap* pp = reinterpret_cast<PropertyMap*>(p);
	SetGenericProperty<std::string>(pp->strings,szName,std::string(st->C_Str()),NULL);
	ASSIMP_END_EXCEPTION_REGION(void);
}
