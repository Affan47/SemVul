static inline void finalise_ac(gfp_t gfp_mask,
		unsigned int order, struct alloc_context *ac)
{

	ac->spread_dirty_pages = (gfp_mask & __GFP_WRITE);


	ac->preferred_zoneref = first_zones_zonelist(ac->zonelist,
					ac->high_zoneidx, ac->nodemask);
}
