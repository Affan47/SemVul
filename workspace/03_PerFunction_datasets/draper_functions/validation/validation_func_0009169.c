slapu_next_attribute( LDAP* ld, LDAPMessage* entry, BerElement* iter)
{
    Slapi_Attr** attr = (Slapi_Attr**)iter;
    if (ld != internal_ld) {
	return ldap_next_attribute (ld, entry, iter);
    }
    if (attr && slapi_entry_next_attr (*(Slapi_Entry**)entry, *attr, attr) == LDAP_SUCCESS) {
	return slapu_attr_get_desc (*attr);
    }
    return NULL;
}
