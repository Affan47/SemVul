int __sk_mem_schedule(struct sock *sk, int size, int kind)
{
	struct proto *prot = sk->sk_prot;
	int amt = sk_mem_pages(size);
	int allocated;

	sk->sk_forward_alloc += amt * SK_MEM_QUANTUM;
	allocated = atomic_add_return(amt, prot->memory_allocated);


	if (allocated <= prot->sysctl_mem[0]) {
		if (prot->memory_pressure && *prot->memory_pressure)
			*prot->memory_pressure = 0;
		return 1;
	}


	if (allocated > prot->sysctl_mem[1])
		if (prot->enter_memory_pressure)
			prot->enter_memory_pressure(sk);


	if (allocated > prot->sysctl_mem[2])
		goto suppress_allocation;


	if (kind == SK_MEM_RECV) {
		if (atomic_read(&sk->sk_rmem_alloc) < prot->sysctl_rmem[0])
			return 1;
	} else {
		if (sk->sk_type == SOCK_STREAM) {
			if (sk->sk_wmem_queued < prot->sysctl_wmem[0])
				return 1;
		} else if (atomic_read(&sk->sk_wmem_alloc) <
			   prot->sysctl_wmem[0])
				return 1;
	}

	if (prot->memory_pressure) {
		int alloc;

		if (!*prot->memory_pressure)
			return 1;
		alloc = percpu_counter_read_positive(prot->sockets_allocated);
		if (prot->sysctl_mem[2] > alloc *
		    sk_mem_pages(sk->sk_wmem_queued +
				 atomic_read(&sk->sk_rmem_alloc) +
				 sk->sk_forward_alloc))
			return 1;
	}

suppress_allocation:

	if (kind == SK_MEM_SEND && sk->sk_type == SOCK_STREAM) {
		sk_stream_moderate_sndbuf(sk);


		if (sk->sk_wmem_queued + size >= sk->sk_sndbuf)
			return 1;
	}


	sk->sk_forward_alloc -= amt * SK_MEM_QUANTUM;
	atomic_sub(amt, prot->memory_allocated);
	return 0;
}
