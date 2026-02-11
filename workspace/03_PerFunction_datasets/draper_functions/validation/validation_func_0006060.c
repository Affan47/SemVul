Trace(std::ostream & strmOut, const char * s, int level)
{


	AST * pAST = this;
	while (pAST)
	{
		for (int i = 0; i < level * 3; i++)
			strmOut << " ";

		if (s != 0)
			strmOut << s;

		GrpASTNode * grNode = dynamic_cast<GrpASTNode *>(getNode());
		Assert(grNode);

		strmOut << debugString() << "(" << getType() << ")";
		if (getText() != "")
			strmOut << ": '" << getText().c_str() << "'";
		int line = grNode->LineAndFile().PreProcessedLine();
		if (line > 0)
			strmOut << "  [line #" << line << "]";
		strmOut << "\n";

		AST * pASTChild = getFirstChild();
		if (pASTChild)
			pASTChild->Trace(strmOut, 0, level + 1);

		pAST = pAST->getNextSibling();
	}
}
