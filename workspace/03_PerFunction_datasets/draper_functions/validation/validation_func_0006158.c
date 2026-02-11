create_item(
	std::vector<std::string> path,
	std::vector<std::string> labels)
{
	std::string item_name = labels.back();
	CL_MenuNode *parent_node = create_node(path, labels);

	new CL_MenuItem(item_name, parent_node );

	return parent_node;
}
