GetExtraAttribute(const char* profile, const char* key) const
{
	FUAssert(GetParent() != NULL, return NULL);
	const FCDETechnique * extraTech = GetParent()->GetExtra()->GetDefaultType()->FindTechnique(profile);
	if (extraTech == NULL) return NULL;
	const FCDENode * enode = extraTech->FindParameter(key);
	if (enode == NULL) return NULL;
	return enode->GetContent();
}
