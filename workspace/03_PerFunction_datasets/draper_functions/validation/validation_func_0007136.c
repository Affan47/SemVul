writeAttrValue(OFile *fp, VObject *o)
{
    if (NAME_OF(o)) {
	struct PreDefProp *pi;
	pi = lookupPropInfo(NAME_OF(o));
	if (pi && ((pi->flags & PD_INTERNAL) != 0)) return;
	appendcOFile(fp,';');
	appendsOFile(fp,NAME_OF(o));
	}
    else
	appendcOFile(fp,';');
    if (VALUE_TYPE(o)) {
	appendcOFile(fp,'=');
	writeValue(fp,o,0);
	}
}
