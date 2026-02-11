rtree_next_node(struct memory_bitmap *bm)
{
	if (!list_is_last(&bm->cur.node->list, &bm->cur.zone->leaves)) {
		bm->cur.node = list_entry(bm->cur.node->list.next,
					  struct rtree_node, list);
		bm->cur.node_pfn += BM_BITS_PER_BLOCK;
		bm->cur.node_bit  = 0;
		touch_softlockup_watchdog();
		return true;
	}


	if (!list_is_last(&bm->cur.zone->list, &bm->zones)) {
		bm->cur.zone = list_entry(bm->cur.zone->list.next,
				  struct mem_zone_bm_rtree, list);
		bm->cur.node = list_entry(bm->cur.zone->leaves.next,
					  struct rtree_node, list);
		bm->cur.node_pfn = 0;
		bm->cur.node_bit = 0;
		return true;
	}


	return false;
}
