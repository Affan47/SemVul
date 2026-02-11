administrativeRoleAttribute (
	Backend *be,
	Entry *e,
	Attribute *attr,
	const char** text,
	char *textbuf, size_t textlen )
{
	*text = textbuf;

	if( !SLAP_SUBENTRIES(be) ) {
		snprintf( textbuf, textlen,
			"attribute \"%s\" not supported in context",
			attr->a_desc->ad_cname.bv_val );
		return LDAP_OBJECT_CLASS_VIOLATION;
	}

	snprintf( textbuf, textlen,
		"attribute \"%s\" not supported!",
		attr->a_desc->ad_cname.bv_val );
	return LDAP_OBJECT_CLASS_VIOLATION;
}
