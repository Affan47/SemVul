knh_generateCallbackFunc64(CTX ctx, void *tmpl, void *dest, kFunc *fo)
{
	kchar_t *function = NULL;
#if !defined(K_USING_WINDOWS) && !defined(K_USING_BTRON)
	function = (kchar_t*)tmpl;

	int i, marker = -1, jmp_pos = -1;
	enum last_inst lastInst = call_leave_ret;
	for (i = 0; i < FUNC_SIZE; i++) {
		if (*(intptr_t*)&function[i] == 0xfffffff0fffffff0 && marker == -1) {
			marker = i;
			i += 8;
		}


		if (function[i] == 0xe8 ) {
			jmp_pos = i;
		}


		if(function[i] == 0xc9 && function[i + 1] == 0xe9) {
			lastInst = leave_jmp;
			jmp_pos = i + 1;
			i += 4;
			break;
		}

		if (function[i] == 0xe9 && *(int*)&function[i+1] < 0) {
			lastInst = jmp_only;
			jmp_pos = i;
			i += 5 + 4;
			break;
		}


		if (function[i] == 0xc9 && function[i+1] == 0xc3) {
			i += 2;
			break;
		}
	}

	size_t funcsize = i;
	function = (kchar_t*)knh_xmalloc(ctx, funcsize);
	memcpy(function, tmpl, i);
	if (marker > 0) {
		memcpy(&function[marker], &fo, sizeof(void*));
	}

	if (jmp_pos > 0) {


		function[jmp_pos+0] = 0x48;
		function[jmp_pos+1] = 0xb8;
		union {
			unsigned char code[sizeof(intptr_t)];
			intptr_t v;
		} code;
		code.v = (intptr_t) dest;
		memcpy(function+(jmp_pos+2), code.code, sizeof(code));

		size_t seekidx = jmp_pos + 2 + sizeof(intptr_t);

		switch (lastInst) {
		case leave_jmp:


		case jmp_only:

			function[seekidx+0] = 0xff;
			function[seekidx+1] = 0xe0;
			break;
		case call_leave_ret:

			function[seekidx+0] = 0xff;
			function[seekidx+1] = 0xd0;

			function[seekidx+2] = 0xc9;

			function[seekidx+3] = 0xc3;
			break;
		}
	}

#endif
	return function;
}
