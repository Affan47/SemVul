getDepth(const Coordinate& p)
{
	vector<DepthSegment*> stabbedSegments;
	findStabbedSegments(p, stabbedSegments);


	if (stabbedSegments.size()==0) return 0;

	sort(stabbedSegments.begin(), stabbedSegments.end(), DepthSegmentLessThen());

	DepthSegment *ds=stabbedSegments[0];
	int ret = ds->leftDepth;

#if GEOS_DEBUG
	cerr<<"SubgraphDepthLocater::getDepth("<<p.toString()<<"): "<<ret<<endl;
#endif

	for (vector<DepthSegment *>::iterator
		it=stabbedSegments.begin(), itEnd=stabbedSegments.end();
		it != itEnd;
		++it)
	{
		delete *it;
	}

	return ret;
}
