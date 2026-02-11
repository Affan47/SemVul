readNodeInstance(QvInput *in, const QvName &className,
			 const QvName &refName, QvNode *&node)
{
    node = createInstance(in, className);
    if (node == NULL)
	return FALSE;

    if (! (! refName))
	in->addReference(refName, node);

    return node->readInstance(in);
}
