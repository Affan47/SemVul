nat_t_generate_nat_d_hash(struct message *msg, struct sockaddr *sa,
    size_t *hashlen)
{
	struct ipsec_exch *ie = (struct ipsec_exch *)msg->exchange->data;
	struct hash	 *hash;
	u_int8_t	 *res;
	in_port_t	  port;

	hash = hash_get(ie->hash->type);
	if (hash == NULL) {
		log_print ("nat_t_generate_nat_d_hash: no hash");
		return NULL;
	}

	*hashlen = hash->hashsize;

	res = (u_int8_t *)malloc((unsigned long)*hashlen);
	if (!res) {
		log_print("nat_t_generate_nat_d_hash: malloc (%lu) failed",
		    (unsigned long)*hashlen);
		*hashlen = 0;
		return NULL;
	}

	port = sockaddr_port(sa);
	bzero(res, *hashlen);

	hash->Init(hash->ctx);
	hash->Update(hash->ctx, msg->exchange->cookies,
	    sizeof msg->exchange->cookies);
	hash->Update(hash->ctx, sockaddr_addrdata(sa), sockaddr_addrlen(sa));
	hash->Update(hash->ctx, (unsigned char *)&port, sizeof port);
	hash->Final(res, hash->ctx);
	return res;
}
