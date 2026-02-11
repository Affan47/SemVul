osd_req_read_kern(struct osd_request *or,
	const struct osd_obj_id *obj, u64 offset, void* buff, u64 len)
{
	struct request_queue *req_q = osd_request_queue(or->osd_dev);
	struct bio *bio = bio_map_kern(req_q, buff, len, GFP_KERNEL);

	if (IS_ERR(bio))
		return PTR_ERR(bio);

	osd_req_read(or, obj, offset, bio, len);
	return 0;
}
