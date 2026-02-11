getWidth() const
{
	vector<Child>::const_iterator b=children.begin(), e=children.end();

	int maxw=0;

	while (b != e)
	{
		const Child &c= *b++;


		int w= c.child->getAlignment() == PARENTCENTER
			? 0:c.child->getColAligned();

		w += c.child->getWidth();

		if (w > maxw)
			maxw=w;
	}
	return maxw;
}
