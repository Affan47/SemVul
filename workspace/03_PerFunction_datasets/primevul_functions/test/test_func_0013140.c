int sctp_user_addto_chunk(struct sctp_chunk *chunk, int len,
			  struct iov_iter *from)
{
	void *target;


	target = skb_put(chunk->skb, len);


	if (!copy_from_iter_full(target, len, from))
		return -EFAULT;


	chunk->chunk_hdr->length =
		htons(ntohs(chunk->chunk_hdr->length) + len);
	chunk->chunk_end = skb_tail_pointer(chunk->skb);

	return 0;
}
