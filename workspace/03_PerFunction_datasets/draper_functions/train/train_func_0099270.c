embPropPyrimidine(char base)
{
    if(strchr(propPyrimidines, (ajint)base))
	return ajTrue;

    return ajFalse;
}
