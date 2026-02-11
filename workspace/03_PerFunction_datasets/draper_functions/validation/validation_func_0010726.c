fastUnmarshalWString(cdrStream&          stream,
				  omniCodeSet::NCS_W* ncs,
				  _CORBA_ULong        bound,
				  _CORBA_ULong&       len,
				  _CORBA_WChar*&      ws)
{
  if (ncs->id() == id()) {

    _CORBA_ULong mlen; mlen <<= stream;

    if (mlen % 4)
      OMNIORB_THROW(MARSHAL, MARSHAL_InvalidWCharSize,
		    (CORBA::CompletionStatus)stream.completion());

    len = mlen / 4;

    if (bound && len > bound)
      OMNIORB_THROW(MARSHAL, MARSHAL_WStringIsTooLong,
		    (CORBA::CompletionStatus)stream.completion());

    if (!stream.checkInputOverrun(1, mlen))
      OMNIORB_THROW(MARSHAL, MARSHAL_PassEndOfMessage,
		    (CORBA::CompletionStatus)stream.completion());

    ws = omniCodeSetUtil::allocW(len + 1);
    omniCodeSetUtil::HolderW wh(ws);

    stream.unmarshalArrayULong((_CORBA_ULong*)ws, len);

    ws[len] = 0;

    wh.drop();
    return 1;
  }
  return 0;
}
