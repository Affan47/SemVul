f2fs_submit_page_bio(struct f2fs_io_info *fio)
{
	struct bio *bio;
	struct page *page = fio->encrypted_page ? fio->encrypted_page : fio->page;

	trace_f2fs_submit_page_bio(page, fio);
	f2fs_trace_ios(fio, 0);


	bio = __bio_alloc(fio->sbi, fio->blk_addr, 1, is_read_io(fio->rw));

	if (bio_add_page(bio, page, PAGE_CACHE_SIZE, 0) < PAGE_CACHE_SIZE) {
		bio_put(bio);
		return -EFAULT;
	}

	submit_bio(fio->rw, bio);
	return 0;
}
