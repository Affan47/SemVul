operator== (Atom& caAtom)
{

	return ((fabs (x() - caAtom.x()) < PREC) &&
			(fabs (y() - caAtom.y()) < PREC) &&
			(fabs (z() - caAtom.z()) < PREC) &&
			((GetZ () > 0)? GetZ () == caAtom.GetZ (): GetZ () == caAtom.GetZ () &&
			 m_fRed == caAtom.m_fRed && m_fGreen == caAtom.m_fGreen && m_fBlue == caAtom.m_fBlue && m_fAlpha == caAtom.m_fAlpha
			 && GetSize () == caAtom.GetSize ()) &&
			(GetCharge () == caAtom.GetCharge ()));
}
