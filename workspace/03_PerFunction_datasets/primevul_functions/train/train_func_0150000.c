GlobalClassExit(void)
{
	DEFiRet;


	objRelease(net,      LM_NET_FILENAME);
	objRelease(prop,     CORE_COMPONENT);
	objRelease(conf,     CORE_COMPONENT);
	objRelease(ruleset,  CORE_COMPONENT);
	objRelease(rule,     CORE_COMPONENT);
	objRelease(expr,     CORE_COMPONENT);
	vmClassExit();
	objRelease(datetime, CORE_COMPONENT);


	strExit();

#if 0
	CHKiRet(objGetObjInterface(&obj));

	CHKiRet(objUse(errmsg,   CORE_COMPONENT));
	CHKiRet(objUse(module,   CORE_COMPONENT));
#endif
	rsrtExit();

	RETiRet;
}
