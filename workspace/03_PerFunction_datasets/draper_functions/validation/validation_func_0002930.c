setCatalogAttributes(ParsedSystemId &parsedSysid)
{
  Boolean hadPublic = 0;
  parsedSysid.maps.resize(parsedSysid.maps.size() + 1);
  parsedSysid.maps.back().type = ParsedSystemId::Map::catalogDocument;
  for (;;) {
    StringC token, value;
    Boolean gotValue;
    if (!parseAttribute(token, gotValue, value)) {
      mgr_.message(EntityManagerMessages::fsiSyntax, StringMessageArg(str_));
      return 0;
    }
    if (token.size() == 0)
      break;
    if (matchKey(token, "PUBLIC")) {
      if (hadPublic)
	mgr_.message(EntityManagerMessages::fsiDuplicateAttribute,
		     StringMessageArg(idCharset_.execToDesc("PUBLIC")));
      else if (gotValue) {
	convertMinimumLiteral(value, parsedSysid.maps.back().publicId);
	parsedSysid.maps.back().type = ParsedSystemId::Map::catalogPublic;
      }
      else
	mgr_.message(EntityManagerMessages::fsiMissingValue,
		     StringMessageArg(token));
      hadPublic = 1;
    }
    else
      mgr_.message(gotValue
		   ? EntityManagerMessages::fsiUnsupportedAttribute
		   : EntityManagerMessages::fsiUnsupportedAttributeToken,
		   StringMessageArg(token));
  }
  return 1;
}
