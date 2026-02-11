evaluatePDF_parzen(
	const double &	x,
	const double &	y,
	const double &	phi,
	const double &	stdXY,
	const double &	stdPhi ) const
{
	double	ret = 0;

	for (CParticleList::const_iterator	it=m_particles.begin();it!=m_particles.end();++it)
	{
		double difPhi = math::wrapToPi( phi - it->d->phi() );

		ret += exp(it->log_w) *
			   math::normalPDF( it->d->distance2DTo(x,y), 0, stdXY ) *
			   math::normalPDF( fabs( difPhi ), 0, stdPhi );
	}

	return ret;
}
