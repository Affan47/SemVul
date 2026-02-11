mag_v_copy_to_empty(magv_t *dst, const magv_t *src)
{
	memcpy(dst, src, sizeof(magv_t));
	dst->max_len = dst->len + 1;
	kroundup32(dst->max_len);
	dst->seq = calloc(dst->max_len, 1); memcpy(dst->seq, src->seq, src->len);
	dst->cov = calloc(dst->max_len, 1); memcpy(dst->cov, src->cov, src->len);
	kv_init(dst->nei[0]); kv_copy(ku128_t, dst->nei[0], src->nei[0]);
	kv_init(dst->nei[1]); kv_copy(ku128_t, dst->nei[1], src->nei[1]);
}
