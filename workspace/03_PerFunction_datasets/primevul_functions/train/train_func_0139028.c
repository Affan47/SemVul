char* trim_quotes( char* instr ) {
	char * result;
	int  instr_len;

	if (instr == NULL) {
		return NULL;
	}

	instr_len = strlen(instr);

	if ((instr_len > 2) && (instr[0] == '"') && (instr[instr_len-1]) == '"') {

		result = (char*)malloc(instr_len - 1);
		strncpy(result, &(instr[1]), instr_len-2);
		result[instr_len-2] = 0;
	} else {
		result = strdup(instr);
	}

	return result;
}
