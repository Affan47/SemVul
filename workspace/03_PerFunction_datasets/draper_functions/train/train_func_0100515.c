debug_print_vm_field(struct vm_field *field)
{
	if (field) {
		printf(" field : %s %s\n", field->type, field->name);
		if (field->class->name) {
			printf("class->name : %s\n", field->class->name);
		}
		printf("\n");
	} else {
		printf("Unable to print null vm_field!\n");
	}
}
