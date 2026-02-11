applicable ( const TBox::TSimpleRule& rule )
{
	BipolarPointer bp = curConcept.bp();
	const CWDArray& lab = curNode->label().getLabel(dtPConcept);

	DepSet loc = curConcept.getDep();

	for ( TBox::TSimpleRule::const_iterator p = rule.Body.begin(), p_end = rule.Body.end(); p < p_end; ++p )
	{
		if ( (*p)->pName == bp )
			continue;
		if ( findConceptClash ( lab, (*p)->pName, loc ) )
			loc = getClashSet();
		else
			return false;
	}


	setClashSet(loc);
	return true;
}
