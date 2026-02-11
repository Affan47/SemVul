ike_mobike_create(ike_sa_t *ike_sa, bool initiator)
{
	private_ike_mobike_t *this;

	INIT(this,
		.public = {
			.task = {
				.get_type = _get_type,
				.migrate = _migrate,
				.destroy = _destroy,
			},
			.addresses = _addresses,
			.roam = _roam,
			.dpd = _dpd,
			.transmit = _transmit,
			.is_probing = _is_probing,
			.enable_probing = _enable_probing,
		},
		.ike_sa = ike_sa,
		.initiator = initiator,
	);

	if (initiator)
	{
		this->public.task.build = _build_i;
		this->public.task.process = _process_i;
	}
	else
	{
		this->public.task.build = _build_r;
		this->public.task.process = _process_r;
	}

	return &this->public;
}
