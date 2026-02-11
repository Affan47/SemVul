field_cmp_ulong(void *a, void *b, OPERATOR op)
{
	switch (op) {
	case GT:
		return (*(u_long *)a > *(u_long *)b);
	case GTEQ:
		return (*(u_long *)a >= *(u_long *)b);
	case LT:
		return (*(u_long *)a < *(u_long *)b);
	case LTEQ:
		return (*(u_long *)a <= *(u_long *)b);
	case NEQ:
		return (*(u_long *)a != *(u_long *)b);
	case EQ:
		return (*(u_long *)a == *(u_long *)b);
	case WC:
	case NWC:
		break;
	}

	abort();

}
