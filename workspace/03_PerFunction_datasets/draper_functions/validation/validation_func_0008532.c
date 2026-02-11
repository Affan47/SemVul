normalize(NormalStream & os) const
{
	os << "[diff";
	for (idx_type idx = 0; idx < nargs(); ++idx)
		os << ' ' << cell(idx);
	os << ']';
}
