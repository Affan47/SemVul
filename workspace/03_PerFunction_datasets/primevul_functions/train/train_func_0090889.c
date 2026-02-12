__releases(&idprv->handler_mutex)
{
	enum rdma_cm_state state;
	unsigned long flags;

	trace_cm_id_destroy(id_priv);


	lockdep_assert_held(&id_priv->handler_mutex);
	spin_lock_irqsave(&id_priv->lock, flags);
	state = id_priv->state;
	id_priv->state = RDMA_CM_DESTROYING;
	spin_unlock_irqrestore(&id_priv->lock, flags);
	mutex_unlock(&id_priv->handler_mutex);
	_destroy_id(id_priv, state);
}
