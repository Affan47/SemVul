gen_command(int command)
{
    if (command >= Charstring::cEscapeDelta) {
	_ncs.append((char)Charstring::cEscape);
	_ncs.append((char)(command - Charstring::cEscapeDelta));
	if (command != Charstring::cSbw)
	    _state = S_GEN;
    } else {
	_ncs.append((char)command);
	if (command > Charstring::cVmoveto && command != Charstring::cHsbw)
	    _state = S_GEN;
    }
}
