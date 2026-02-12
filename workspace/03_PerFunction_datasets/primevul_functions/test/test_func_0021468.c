static int tipc_aead_encrypt(struct tipc_aead *aead, struct sk_buff *skb,
			     struct tipc_bearer *b,
			     struct tipc_media_addr *dst,
			     struct tipc_node *__dnode)
{
	struct crypto_aead *tfm = tipc_aead_tfm_next(aead);
	struct tipc_crypto_tx_ctx *tx_ctx;
	struct aead_request *req;
	struct sk_buff *trailer;
	struct scatterlist *sg;
	struct tipc_ehdr *ehdr;
	int ehsz, len, tailen, nsg, rc;
	void *ctx;
	u32 salt;
	u8 *iv;


	len = ALIGN(skb->len, 4);
	tailen = len - skb->len + aead->authsize;


	SKB_LINEAR_ASSERT(skb);
	if (tailen > skb_tailroom(skb)) {
		pr_debug("TX(): skb tailroom is not enough: %d, requires: %d\n",
			 skb_tailroom(skb), tailen);
	}

	if (unlikely(!skb_cloned(skb) && tailen <= skb_tailroom(skb))) {
		nsg = 1;
		trailer = skb;
	} else {


		nsg = skb_cow_data(skb, tailen, &trailer);
		if (unlikely(nsg < 0)) {
			pr_err("TX: skb_cow_data() returned %d\n", nsg);
			return nsg;
		}
	}

	pskb_put(skb, trailer, tailen);


	ctx = tipc_aead_mem_alloc(tfm, sizeof(*tx_ctx), &iv, &req, &sg, nsg);
	if (unlikely(!ctx))
		return -ENOMEM;
	TIPC_SKB_CB(skb)->crypto_ctx = ctx;


	sg_init_table(sg, nsg);
	rc = skb_to_sgvec(skb, sg, 0, skb->len);
	if (unlikely(rc < 0)) {
		pr_err("TX: skb_to_sgvec() returned %d, nsg %d!\n", rc, nsg);
		goto exit;
	}


	ehdr = (struct tipc_ehdr *)skb->data;
	salt = aead->salt;
	if (aead->mode == CLUSTER_KEY)
		salt ^= __be32_to_cpu(ehdr->addr);
	else if (__dnode)
		salt ^= tipc_node_get_addr(__dnode);
	memcpy(iv, &salt, 4);
	memcpy(iv + 4, (u8 *)&ehdr->seqno, 8);


	ehsz = tipc_ehdr_size(ehdr);
	aead_request_set_tfm(req, tfm);
	aead_request_set_ad(req, ehsz);
	aead_request_set_crypt(req, sg, sg, len - ehsz, iv);


	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  tipc_aead_encrypt_done, skb);
	tx_ctx = (struct tipc_crypto_tx_ctx *)ctx;
	tx_ctx->aead = aead;
	tx_ctx->bearer = b;
	memcpy(&tx_ctx->dst, dst, sizeof(*dst));


	if (unlikely(!tipc_bearer_hold(b))) {
		rc = -ENODEV;
		goto exit;
	}


	rc = crypto_aead_encrypt(req);
	if (rc == -EINPROGRESS || rc == -EBUSY)
		return rc;

	tipc_bearer_put(b);

exit:
	kfree(ctx);
	TIPC_SKB_CB(skb)->crypto_ctx = NULL;
	return rc;
}
