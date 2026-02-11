addMatrix(const c8* attributeName, const core::matrix4& v)
{
	Attributes.push_back(new CMatrixAttribute(attributeName, v));
}
