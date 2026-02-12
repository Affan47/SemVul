stackswap()
{
#ifdef DEBUG
	printf("*stackswap*\n");
#endif
	struct SWF_ACTIONPUSHPARAM *p = peek();
	char type = Stack->type;

        if (Stack->next == NULL) {
#if DEBUG
		SWF_warn("stackswap: can't swap (stack contains only one element)\n");
#endif
                return;
        }

	Stack->type = Stack->next->type;
	Stack->val  = Stack->next->val;
	Stack->next->type = type;
	Stack->next->val  = p;
}
