create_ordered_vertex_list(std::vector<CL_DelauneyTriangulator_Vertex *> &vertices)
{
	std::vector<CL_DelauneyTriangulator_Vertex>::size_type index_vertices, num_vertices;
	num_vertices = input_vertices.size();
	for (index_vertices = 0; index_vertices < num_vertices; index_vertices++)
	{
		vertices.push_back(&input_vertices[index_vertices]);
	}


	std::sort(vertices.begin(), vertices.end(), CL_CompareVertices());


	std::vector<CL_DelauneyTriangulator_Vertex *>::iterator it = vertices.begin();
	if (it == vertices.end()) return;
	double last_x = (*it)->x;
	double last_y = (*it)->y;
	++it;
	while (it != vertices.end())
	{
		if (last_x == (*it)->x && last_y == (*it)->y)
		{
			it = vertices.erase(it);
		}
		else
		{
			last_x = (*it)->x;
			last_y = (*it)->y;
			++it;
		}
	}
}
