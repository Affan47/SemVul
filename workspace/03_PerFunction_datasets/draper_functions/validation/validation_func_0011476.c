create_dll( )
{
	Dllist *new_dll = (Dllist *) malloc(sizeof(Dllist));
	Vertex *new_vert = create_vertex(0.0, 0.0, 0.0);

	if (new_dll != NULL && new_vert != NULL)
		init_dll(new_dll, new_vert);
	else
		printf("Error in create_dll function\n");

	return new_dll;
}
