main(int argc, char **argv)
{
	int i, len;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filter_length>\n", argv[0]);
		return 1;
	}

	len = atoi(argv[1]);

#if 0
	puts("#ifndef _FILTER_I386_H");
	puts("#define _FILTER_I386_H");
	puts("#define __HAVE_ARCH_MAC");

	puts("extern inline float mac(const float *a, const float *b)");
	puts("{");
	puts("\tfloat f;");
#endif

	puts("\tasm volatile (");

	asmline("flds (%1)");
	asmline("fmuls (%2)");
	asmline("flds 4(%1)");
	asmline("fmuls 4(%2)");

	for (i = 2; i < len; i++) {
		asmline2("flds ", i * 4, "(%1)");
		asmline2("fmuls ", i * 4, "(%2)");
		asmline("fxch %%st(2)");
		asmline("faddp");
	}

	asmline("faddp");

	puts("\t\t: \"=t\" (f) : \"r\" (a) , \"r\" (b) : \"memory\");");

#if 0
	puts("\treturn f;");
	puts("}");

	puts("#endif");
#endif

	return 0;
}
