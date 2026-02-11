powerLogScale(float yval)
{

	if (yval <= _minCutoff) {
		return _dbAbsMin;
	}


	float nval = (10.0 * FTutils::fast_log10(yval)) + _dbAdjust;

	return nval;

}
