visit(Try* node)
{
	node->getBlock()->accept(*this);

	node->getCatches()->accept(*this);

	if (node->hasFinally()) {
		node->getFinally()->accept(*this);
	}
}
