trunc_Q_list(int i)
{
	while (last_Qs.size() > 0 && i--)
		last_Qs.pop_back();
}
