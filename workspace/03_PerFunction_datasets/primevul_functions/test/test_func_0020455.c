static bool tcf_chain_held_by_acts_only(struct tcf_chain *chain)
{
	ASSERT_BLOCK_LOCKED(chain->block);


	return chain->refcnt == chain->action_refcnt;
}
