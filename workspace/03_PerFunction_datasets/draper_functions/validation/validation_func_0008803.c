checkContext(const MemberData& mdata) const
{
	if (mdata.flags == MemberData::PUBLIC) {
		return true;
	}
	const Function* curr_func =  m_call_stack.top().func;

	if (curr_func) {
		return curr_func->getContext() != mdata.value->getType();
	}
	return false;
}
