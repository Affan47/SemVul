func_jacob_expe_e(
		const CArrayDouble<6> &x,
		const double &dummy, CArrayDouble<12> &Y)
	{
		MRPT_UNUSED_PARAM(dummy);
		const CPose3D p = CPose3D::exp(x);

		p.getAs12Vector(Y);
	}
