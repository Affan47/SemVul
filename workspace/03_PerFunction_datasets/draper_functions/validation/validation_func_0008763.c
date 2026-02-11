stackTableTop ( tStackTable* s, typeData** List, typeData** Data) {
	if (stackTableEmpty(s)) {
		if (DEBUG_FLAG) printf("No elements is stack Tables!\n");
			return STACK_EMPTY;
	} else {
		(*List)=s->arrList[s->top];
		(*Data)=s->arrData[s->top];
		return SUCCESS;
	}
}
