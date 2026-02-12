XMLNode::add_content(const string& c)
{
	if (c.empty ()) {


		return NULL;
	}
	return add_child_copy(XMLNode (string(), c));
}
