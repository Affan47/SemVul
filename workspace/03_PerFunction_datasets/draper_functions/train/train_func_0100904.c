parse_call(struct vcc *tl)
{

	vcc_NextToken(tl);
	ExpectErr(tl, ID);
	vcc_AddCall(tl, tl->t);
	vcc_AddRef(tl, tl->t, SYM_SUB);
	Fb(tl, 1, "if (VGC_function_%.*s(sp))\n", PF(tl->t));
	Fb(tl, 1, "\treturn (1);\n");
	vcc_NextToken(tl);
	return;
}
