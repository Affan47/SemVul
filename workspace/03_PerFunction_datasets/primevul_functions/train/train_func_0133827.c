static int lock_sem_sw_reset(struct mlx5_core_dev *dev, bool lock)
{
	enum mlx5_vsc_state state;
	int ret;

	if (!mlx5_core_is_pf(dev))
		return -EBUSY;


	ret = mlx5_vsc_gw_lock(dev);
	if (ret == -EBUSY)
		return -EINVAL;
	if (ret)
		return ret;

	state = lock ? MLX5_VSC_LOCK : MLX5_VSC_UNLOCK;


	ret = mlx5_vsc_sem_set_space(dev, MLX5_SEMAPHORE_SW_RESET, state);
	if (ret)
		mlx5_core_warn(dev, "Failed to lock SW reset semaphore\n");


	mlx5_vsc_gw_unlock(dev);

	return ret;
}
