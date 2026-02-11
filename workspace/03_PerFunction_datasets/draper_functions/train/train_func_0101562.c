clone()
{
	Environment* env = new Environment(m_outer, m_scoped);

	env->m_ret_val = m_ret_val;
	env->m_ret_addr = m_ret_addr;

	if (m_temp)
		env->m_temp = m_temp->clone();

	env->m_data.reserve(m_data.size());

	for (size_t i = 0, size = m_data.size(); i < size; ++i)
		env->pushValue(m_data[i]->clone());

	return env;
}
