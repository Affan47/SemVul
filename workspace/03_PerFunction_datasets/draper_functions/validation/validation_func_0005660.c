accept_push(private_mode_config_t *this)
{
	enumerator_t *enumerator;
	peer_cfg_t *config;
	bool vip;
	host_t *host;

	config = this->ike_sa->get_peer_cfg(this->ike_sa);
	enumerator = config->create_virtual_ip_enumerator(config);
	vip = enumerator->enumerate(enumerator, &host);
	enumerator->destroy(enumerator);

	return vip && !config->use_pull_mode(config);
}
