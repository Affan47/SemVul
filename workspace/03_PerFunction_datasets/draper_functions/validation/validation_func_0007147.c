Prepare(btScalar dt,int iterations)
{
	static const btScalar	maxdrift=SIMD_PI/16;
	m_icontrol->Prepare(this);
	Joint::Prepare(dt,iterations);
	m_axis[0]	=	m_bodies[0].xform().getBasis()*m_refs[0];
	m_axis[1]	=	m_bodies[1].xform().getBasis()*m_refs[1];
	m_drift		=	NormalizeAny(btCross(m_axis[1],m_axis[0]));
	m_drift		*=	btMin(maxdrift,btAcos(Clamp<btScalar>(btDot(m_axis[0],m_axis[1]),-1,+1)));
	m_drift		*=	m_erp/dt;
	m_massmatrix=	AngularImpulseMatrix(m_bodies[0].invWorldInertia(),m_bodies[1].invWorldInertia());
	if(m_split>0)
	{
		m_sdrift	=	m_massmatrix*(m_drift*m_split);
		m_drift		*=	1-m_split;
	}
	m_drift	/=(btScalar)iterations;
}
