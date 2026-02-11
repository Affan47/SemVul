zxid_contact_desc(zxid_conf* cf, struct zx_elem_s* father)
{
  struct zx_md_ContactPerson_s* contact = zx_NEW_md_ContactPerson(cf->ctx,father);

  contact->contactType = zx_ref_attr(cf->ctx, &contact->gg, zx_contactType_ATTR, "administrative");

  if (cf->contact_org) {
    if (cf->contact_org[0])
      contact->Company = zx_ref_elem(cf->ctx, &contact->gg, zx_md_Company_ELEM, cf->contact_org);
  } else
    if (cf->org_name && cf->org_name[0])
      contact->Company
	= zx_ref_elem(cf->ctx, &contact->gg, zx_md_Company_ELEM, cf->org_name);
    else
      contact->Company
	= zx_ref_elem(cf->ctx, &contact->gg, zx_md_Company_ELEM, STRNULLCHKQ(cf->nice_name));

  if (cf->contact_name && cf->contact_name[0])
    contact->SurName = zx_ref_elem(cf->ctx, &contact->gg, zx_md_SurName_ELEM, cf->contact_name);
  if (cf->contact_email && cf->contact_email[0])
    contact->EmailAddress = zx_ref_elem(cf->ctx, &contact->gg, zx_md_EmailAddress_ELEM, cf->contact_email);
  if (cf->contact_tel && cf->contact_tel[0])
    contact->TelephoneNumber = zx_ref_elem(cf->ctx, &contact->gg, zx_md_TelephoneNumber_ELEM, cf->contact_tel);

  zx_reverse_elem_lists(&contact->gg);
  return contact;
}
