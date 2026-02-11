unmarshalRepoId(cdrStream& stream, InputValueTracker* tracker)
{


  CORBA::ULong len; len <<= stream;
  CORBA::Long  pos = stream.currentInputPtr();

  if (len == 0xffffffff) {
    CORBA::Long offset;
    offset <<= stream;
    if (offset >= -4) {
      OMNIORB_THROW(MARSHAL, MARSHAL_InvalidIndirection,
		    (CORBA::CompletionStatus)stream.completion());
    }
    return tracker->lookupRepoId(pos + offset, pos - 4,
			   (CORBA::CompletionStatus)stream.completion());
  }
  if (!stream.checkInputOverrun(1, len))
    OMNIORB_THROW(MARSHAL, MARSHAL_PassEndOfMessage,
		  (CORBA::CompletionStatus)stream.completion());

  char* s = _CORBA_String_helper::alloc(len - 1);
  stream.get_octet_array((_CORBA_Octet*)s, len);

  if (s[len-1] != '\0')
    OMNIORB_THROW(MARSHAL,MARSHAL_StringNotEndWithNull,
		  (CORBA::CompletionStatus)stream.completion());

  tracker->addRepoId(s, pos-4);


  return s;
}
