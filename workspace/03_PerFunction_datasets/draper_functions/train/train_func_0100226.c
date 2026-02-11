zend_stack_destroy(zend_stack *stack)
{
	int i;

	if (stack->elements) {
		for (i = 0; i < stack->top; i++) {
			efree(stack->elements[i]);
		}

		efree(stack->elements);
	}

	return SUCCESS;
}
