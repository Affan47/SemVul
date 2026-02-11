addIdLinkRule(const StringC &id,
			   IdLinkRule &rule)
{
  IdLinkRuleGroup *group = defComplexLpd().lookupCreateIdLink(id);
  size_t nRules = group->nLinkRules();
  if ((nRules == 1 && group->linkRule(0).attributes().nSpec() == 0)
      || nRules >= 1 && rule.attributes().nSpec() == 0)
    message(ParserMessages::multipleIdLinkRuleAttribute,
	    StringMessageArg(id));
  group->addLinkRule(rule);
}
