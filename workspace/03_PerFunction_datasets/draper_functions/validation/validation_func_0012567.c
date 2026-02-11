iter_get_op_name(int oper)
{
	static char *name = NULL;
	g_free(name);
	name = NULL;

	switch(oper) {
	case GEL_E_SEPAR:
	case GEL_E_EQUALS:
	case GEL_E_DEFEQUALS:
	case GEL_E_SWAPWITH:
	case GEL_E_INCREMENT:
	case GEL_E_INCREMENT_BY:
	case GEL_E_PARAMETER: break;
	case GEL_E_ABS: name = g_strdup(_("Absolute value")); break;
	case GEL_E_PLUS: name = g_strdup(_("Addition")); break;
	case GEL_E_ELTPLUS: name = g_strdup(_("Element by element addition")); break;
	case GEL_E_MINUS: name = g_strdup(_("Subtraction")); break;
	case GEL_E_ELTMINUS: name = g_strdup(_("Element by element subtraction")); break;
	case GEL_E_MUL: name = g_strdup(_("Multiplication")); break;
	case GEL_E_ELTMUL: name = g_strdup(_("Element by element multiplication")); break;
	case GEL_E_DIV: name = g_strdup(_("Division")); break;
	case GEL_E_ELTDIV: name = g_strdup(_("Element by element division")); break;
	case GEL_E_BACK_DIV: name = g_strdup(_("Back division")); break;
	case GEL_E_ELT_BACK_DIV: name = g_strdup(_("Element by element back division")); break;
	case GEL_E_MOD: name = g_strdup(_("Modulo")); break;
	case GEL_E_ELTMOD: name = g_strdup(_("Element by element modulo")); break;
	case GEL_E_NEG: name = g_strdup(_("Negation")); break;
	case GEL_E_EXP: name = g_strdup(_("Power")); break;
	case GEL_E_ELTEXP: name = g_strdup(_("Element by element power")); break;
	case GEL_E_FACT: name = g_strdup(_("Factorial")); break;
	case GEL_E_DBLFACT: name = g_strdup(_("Double factorial")); break;
	case GEL_E_TRANSPOSE: name = g_strdup(_("Transpose")); break;
	case GEL_E_CONJUGATE_TRANSPOSE: name = g_strdup(_("ConjugateTranspose")); break;
	case GEL_E_CMP_CMP: name = g_strdup(_("Comparison (<=>)")); break;
	case GEL_E_LOGICAL_XOR: name = g_strdup(_("XOR")); break;
	case GEL_E_LOGICAL_NOT: name = g_strdup(_("NOT")); break;
	default: break;
	}

	return name;
}
