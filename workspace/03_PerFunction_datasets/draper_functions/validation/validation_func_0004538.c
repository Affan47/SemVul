removeOptionalNames()
{
  if (!pd_compactTc) {
    pd_compactTc = this;
    pd_name = (const char*)"";
    for (CORBA::ULong i=0; i < pd_members.length(); i++) {
      pd_members[i] = (const char*)"";
    }
  }
}
