general_stack_get_top_ed(struct general_stack *stack)
{
	if (general_stack_empty_ed(stack))
	{
		return NULL;
	}

	return stack->buffer[stack->top + 1];
}
