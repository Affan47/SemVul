readnode(xmlNodePtr node)
{
    string name, content;
    xmlNodePtr child;
    XMLNode *tmp;
    xmlAttrPtr attr;

    if (node->name)
		name = (char *) node->name;
    else
		name = string();

    tmp = new XMLNode(name);

    for (attr = node->properties; attr; attr = attr->next) {
		name = (char *) attr->name;
		content = "";
		if (attr->children)
		    content = (char *) attr->children->content;
		tmp->add_property(name, content);
    }

    if (node->content)
		tmp->set_content((char *) node->content);
    else
		tmp->set_content(string());

    for (child = node->children; child; child = child->next)
	    tmp->add_child_nocopy (*readnode(child));

    return tmp;
}
