inc_ds(struct cache *cache, struct bio *bio,
		   struct dm_bio_prison_cell *cell)
{
	size_t pb_data_size = get_per_bio_data_size(cache);
	struct per_bio_data *pb = get_per_bio_data(bio, pb_data_size);

	BUG_ON(!cell);
	BUG_ON(pb->all_io_entry);

	pb->all_io_entry = dm_deferred_entry_inc(cache->all_io_ds);
}
