derivative(const symbol & s) const
{
	ex result;
	for (size_t i=0; i<seq.size(); i++) {
		ex arg_diff = seq[i].diff(s);
		if (!arg_diff.is_zero()) {
			paramset ps = parameter_set;
			ps.insert(i);
			result += arg_diff * fderivative(serial, ps, seq);
		}
	}
	return result;
}
