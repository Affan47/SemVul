stack_initialize(const size_t element_size
    ,void (*release_function)(void *))
{
	stack_t *stack = malloc(sizeof(stack_t));
	if(!stack){
		return NULL;
	}
	stack->array = NULL;
	stack->size = 0;
	stack->element_size = element_size;
	stack->array_size = 0;
	stack->release_function = release_function;
	return stack;
}
