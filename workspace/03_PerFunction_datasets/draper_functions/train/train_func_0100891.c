LA(int i)
{
	if ( caseSensitive ) {
		return inputState->getInput().LA(i);
	} else {
		return toLower(inputState->getInput().LA(i));
	}
}
