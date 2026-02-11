GetMemberIndexToSwitchTeams(const DataStructures::List<TeamId> &sourceTeamNumbers, TeamId targetTeamNumber)
{
	DataStructures::List<unsigned int> preferredSwapIndices;
	DataStructures::List<unsigned int> potentialSwapIndices;
	unsigned int i,j;
	for (j=0; j < sourceTeamNumbers.Size(); j++)
	{
		RakAssert(sourceTeamNumbers[j]!=targetTeamNumber);
		for (i=0; i < teamMembers.Size(); i++)
		{
			if (teamMembers[i].currentTeam==sourceTeamNumbers[j])
			{
				if (teamMembers[i].requestedTeam==targetTeamNumber)
					preferredSwapIndices.Push(i,_FILE_AND_LINE_);
				else
					potentialSwapIndices.Push(i,_FILE_AND_LINE_);
			}
		}
	}

	if (preferredSwapIndices.Size()>0)
	{
		return preferredSwapIndices[ randomMT() % preferredSwapIndices.Size() ];
	}
	else if (potentialSwapIndices.Size()>0)
	{
		return potentialSwapIndices[ randomMT() % potentialSwapIndices.Size() ];
	}
	else
	{
		return (unsigned int) -1;
	}
}
