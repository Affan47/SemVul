assignHoleToShell(EdgeRing *holeER,
		vector<EdgeRing*>& shellList)
{
	EdgeRing *shell = EdgeRing::findEdgeRingContaining(holeER, &shellList);

	if (shell!=NULL)
		shell->addHole(holeER->getRingOwnership());
}
