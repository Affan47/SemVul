unmarshalMultiComponentProfile(const IOP::TaggedProfile& profile,
				     IOP::MultipleComponentProfile& body)
{
  OMNIORB_ASSERT(profile.tag == IOP::TAG_MULTIPLE_COMPONENTS);

  cdrEncapsulationStream s(profile.profile_data.get_buffer(),
			   profile.profile_data.length(),
			   1);

  CORBA::ULong newitems;
  newitems <<= s;
  if (newitems) {
    if (!s.checkInputOverrun(1,newitems))
      OMNIORB_THROW(MARSHAL,MARSHAL_InvalidIOR,CORBA::COMPLETED_NO);

    CORBA::ULong oldlen = body.length();
    body.length(oldlen + newitems);
    for (CORBA::ULong index = oldlen; index < oldlen+newitems; index++) {
      body[index] <<= s;
    }
  }

  if (s.checkInputOverrun(1,1)) {
    if (orbParameters::strictIIOP) {
      omniORB::logs(10, "Multi-component profile has garbage at end");
      OMNIORB_THROW(MARSHAL,MARSHAL_InvalidIOR,CORBA::COMPLETED_NO);
    }
    else
      omniORB::logs(1, "Warning: Multi-component profile has "
		    "garbage at end. Ignoring.");
  }
}
