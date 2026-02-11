sm68k_disasm (TCHAR *instrname, TCHAR *instrcode, uaecptr addr, uaecptr *nextpc)
{
	TCHAR *ccpt;
	uae_u32 opcode;
	struct mnemolookup *lookup;
	struct instr *dp;
	int oldpc;

	uaecptr newpc = 0;

	m68kpc_offset = addr - m68k_getpc ();

	oldpc = m68kpc_offset;
	opcode = get_iword_1 (m68kpc_offset);
	if (cpufunctbl[opcode] == op_illg_1) {
		opcode = 0x4AFC;
	}
	dp = table68k + opcode;
	for (lookup = lookuptab;lookup->mnemo != dp->mnemo; lookup++);

	m68kpc_offset += 2;

	_tcscpy (instrname, lookup->name);
	ccpt = _tcsstr (instrname, _T("cc"));
	if (ccpt != 0) {
		_tcsncpy (ccpt, ccnames[dp->cc], 2);
	}
	switch (dp->size){
	case sz_byte: _tcscat (instrname, _T(".B ")); break;
	case sz_word: _tcscat (instrname, _T(".W ")); break;
	case sz_long: _tcscat (instrname, _T(".L ")); break;
	default: _tcscat (instrname, _T("   ")); break;
	}

	if (dp->suse) {
		newpc = m68k_getpc () + m68kpc_offset;
		newpc += ShowEA (0, opcode, dp->sreg, dp->smode, dp->size, instrname, NULL, 0);
	}
	if (dp->suse && dp->duse)
		_tcscat (instrname, _T(","));
	if (dp->duse) {
		newpc = m68k_getpc () + m68kpc_offset;
		newpc += ShowEA (0, opcode, dp->dreg, dp->dmode, dp->size, instrname, NULL, 0);
	}

	if (instrcode)
	{
		int i;
		for (i = 0; i < (m68kpc_offset - oldpc) / 2; i++)
		{
			_stprintf (instrcode, _T("%04x "), get_iword_1 (oldpc + i * 2));
			instrcode += _tcslen (instrcode);
		}
	}

	if (nextpc)
		*nextpc = m68k_getpc () + m68kpc_offset;
}
