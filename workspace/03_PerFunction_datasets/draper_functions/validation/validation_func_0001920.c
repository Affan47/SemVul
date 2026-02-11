pmsg_ref(pmsg_t *mb)
{
	pmsg_check_consistency(mb);
	g_assert(mb->m_refcnt != 0);

	mb->m_refcnt++;

	g_assert(mb->m_refcnt != 0);

	return mb;
}
