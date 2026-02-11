get(const char* str)
{
    unsigned int 			hsh  = calcHashKey(str);
    int 			bckt = hsh % kHashTableSize;
	Symbol*			item = gSymbolTable[bckt];

    while ( item && !item->equiv(hsh,str) ) item = item->fNext;
	Symbol* r = item ? item : gSymbolTable[bckt] = new Symbol(str, hsh, gSymbolTable[bckt]);
	return r;
}
