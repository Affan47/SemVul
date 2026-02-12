runInputModules(void)
{
	modInfo_t *pMod;

	BEGINfunc

	pMod = module.GetNxtType(NULL, eMOD_IN);
	while(pMod != NULL) {
		if(pMod->mod.im.bCanRun) {

			thrdCreate(pMod->mod.im.runInput, pMod->mod.im.afterRun);
		}
	pMod = module.GetNxtType(pMod, eMOD_IN);
	}

	ENDfunc
	return RS_RET_OK;
}
