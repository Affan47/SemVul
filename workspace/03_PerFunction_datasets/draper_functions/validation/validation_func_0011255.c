pk11_FindAttrInTemplate(CK_ATTRIBUTE *attr, unsigned int numAttrs,
						CK_ATTRIBUTE_TYPE target)
{
    for (; numAttrs > 0; ++attr, --numAttrs) {
    	if (attr->type == target)
	    return PR_TRUE;
    }
    return PR_FALSE;
}
