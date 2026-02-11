findXMLAttValu (XMLEle *ep, const char *name)
{
	XMLAtt *a = findXMLAtt (ep, name);
	return (a ? a->valu.s : "");
}
