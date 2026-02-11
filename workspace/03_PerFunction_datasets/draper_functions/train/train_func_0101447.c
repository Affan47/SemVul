mlx4_en_init_affinity_hint(struct mlx4_en_priv *priv, int ring_idx)
{
	struct mlx4_en_rx_ring *ring = priv->rx_ring[ring_idx];
	int numa_node = priv->mdev->dev->numa_node;

	if (!zalloc_cpumask_var(&ring->affinity_mask, GFP_KERNEL))
		return -ENOMEM;

	cpumask_set_cpu(cpumask_local_spread(ring_idx, numa_node),
			ring->affinity_mask);
	return 0;
}
