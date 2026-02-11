p_class_def2(void)
#else
void p_class_def2()
#endif
{
	int i, m;
	if ( class_stream == NULL ) return;
	fprintf(class_stream, "public:\n");
	fprintf(class_stream, "\tstatic const int MAX_MODE;\n");
	fprintf(class_stream, "\tstatic const int DfaStates;\n");
	for (i=0; i<cur_mode; i++) {
		fprintf(class_stream, "\tstatic const int %s;\n", mode_name[i]);
	}

	fprintf(class_stream, "\ttypedef %s DfaState;\n\n", minsize(dfa_allocated));
	fprintf(class_stream, "\t%s(DLGInputStream *in,\n",ClassName(""));
	fprintf(class_stream, "\t\tunsigned bufsize=2000)\n");
	fprintf(class_stream, "\t\t: DLGLexerBase(in, bufsize, %d)\n", interactive);
	fprintf(class_stream, "\t{\n");
	fprintf(class_stream, "\t;\n");
	fprintf(class_stream, "\t}\n");
	fprintf(class_stream, "\tvoid	  mode(int);\n");
	fprintf(class_stream, "\tANTLRTokenType nextTokenType(void);\n");
	fprintf(class_stream, "\tvoid     advance(void);\n");
	fprintf(class_stream, "protected:\n");
	for (i=1; i<=action_no; ++i) {
		fprintf(class_stream, "\tANTLRTokenType act%d();\n", i);
	}

	for(m=0; m<(mode_counter-1); ++m){
		for(i=dfa_basep[m]; i<dfa_basep[m+1]; ++i)
			fprintf(class_stream, "\tstatic DfaState st%d[%d];\n", i-1, dfa_class_nop[m]+1);
	}
	for(i=dfa_basep[m]; i<=dfa_allocated; ++i)
		fprintf(class_stream, "\tstatic DfaState st%d[%d];\n", i-1, dfa_class_nop[m]+1);

	fprintf(class_stream, "\tstatic DfaState *dfa[%d];\n", dfa_allocated);
	fprintf(class_stream, "\tstatic DfaState dfa_base[];\n");

	fprintf(class_stream, "\tstatic unsigned char *b_class_no[];\n");
	fprintf(class_stream, "\tstatic DfaState accepts[%d];\n",dfa_allocated+1);
	fprintf(class_stream, "\tstatic DLGChar alternatives[%d];\n",dfa_allocated+1);

	fprintf(class_stream, "\tstatic ANTLRTokenType (%s::*actions[%d])();\n", ClassName(""), action_no+1);
	for(m=0; m<mode_counter; ++m) {
		fprintf(class_stream, "\tstatic unsigned char shift%d[%d];\n",
			m, CHAR_RANGE);
	}
	if (comp_level)
		fprintf(class_stream, "\tint ZZSHIFT(int c) { return b_class_no[automaton][1+c]; }\n");
	else
		fprintf(class_stream, "\tint ZZSHIFT(int c) { return 1+c; }\n");


	fprintf(class_stream,"//\n");
	fprintf(class_stream,
	   "// 133MR1 Deprecated feature to allow inclusion of ");
	fprintf(class_stream,
	   "user-defined code in DLG class header\n");
	fprintf(class_stream,"//\n");

	fprintf(class_stream,"#ifdef DLGLexerIncludeFile\n");
	fprintf(class_stream,"#include DLGLexerIncludeFile\n");
	fprintf(class_stream,"#endif\n");

	fprintf(class_stream, "};\n");

	fprintf(class_stream, "typedef ANTLRTokenType (%s::*Ptr%sMemberFunc)();\n",
			ClassName(""), ClassName(""));

	fprintf(class_stream, "#endif\n");
}
