compilePrologModes()
{
  Boolean scopeInstance = sd().scopeInstance();
  Boolean haveSr = syntax().hasShortrefs();
  Mode modes[nModes];
  int n = 0;
  for (size_t i = 0; i < SIZEOF(modeTable); i++) {
    if (scopeInstance) {
      if (modeTable[i].flags & modeUsedInProlog)
	modes[n++] = modeTable[i].mode;
    }
    else if (haveSr) {
      if ((modeTable[i].flags & (modeUsedInInstance|modeUsedInProlog))
	  && !(modeTable[i].flags & modeUsesSr))
	modes[n++] = modeTable[i].mode;
    }
    else {
      if (modeTable[i].flags & (modeUsedInInstance|modeUsedInProlog))
	modes[n++] = modeTable[i].mode;
    }
  }
  compileModes(modes, n, 0);
}
