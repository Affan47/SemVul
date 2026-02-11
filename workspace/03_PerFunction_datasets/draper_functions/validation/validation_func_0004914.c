domNodeSerializeToFd(DOM_NODE *node, FILE *fd)
{
	unsigned char elementClosed = 0;
	DOM_NODE *curr;

	if (!node)
		return;

	switch (node->type)
	{
		case DOM_NODE_TYPE_TEXT:
			if (node->value)
				fprintf(fd, "%s", node->value);
			break;
		case DOM_NODE_TYPE_ELEMENT:
			if (node->escapeTags)
				fprintf(fd, "&lt;%s", node->name);
			else
				fprintf(fd, "<%s", node->name);

			for (curr = node->attributes;
					curr;
					curr = curr->nextSibling)
			{
				fprintf(fd, " %s", curr->name);

				if (curr->value && *curr->value)
					fprintf(fd, "=\"%s\"", curr->value);
			}

			if (!node->firstChild)
			{
				if (node->escapeTags)
					fprintf(fd, "/&gt;");
				else
					fprintf(fd, "/>");
				elementClosed = 1;
			}
			else
			{
				if (node->escapeTags)
					fprintf(fd, "&gt;");
				else
					fprintf(fd, ">");
			}

			break;
		case DOM_NODE_TYPE_COMMENT:
			if (node->value)
				fprintf(fd, "<!--%s-->", node->value);
			break;
	}

	for (curr = node->firstChild;
			curr;
			curr = curr->nextSibling)
		domNodeSerializeToFd(curr, fd);

	if ((node->type == DOM_NODE_TYPE_ELEMENT) && (!elementClosed) && (!node->autoclose))
	{
		if (node->escapeTags)
			fprintf(fd, "&lt;/%s&gt;", node->name);
		else
			fprintf(fd, "</%s>", node->name);
	}
}
