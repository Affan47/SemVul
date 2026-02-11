aead_sndbuf(struct sock *sk)
{
	struct alg_sock *ask = alg_sk(sk);
	struct aead_ctx *ctx = ask->private;

	return max_t(int, max_t(int, sk->sk_sndbuf & PAGE_MASK, PAGE_SIZE) -
			  ctx->used, 0);
}
