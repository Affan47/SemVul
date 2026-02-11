wl3501_esbq_req(struct wl3501_card *this, u16 *ptr)
{
	u16 tmp = 0;

	wl3501_set_to_wla(this, this->esbq_req_head, ptr, 2);
	wl3501_set_to_wla(this, this->esbq_req_head + 2, &tmp, sizeof(tmp));
	this->esbq_req_head += 4;
	if (this->esbq_req_head >= this->esbq_req_end)
		this->esbq_req_head = this->esbq_req_start;
}
