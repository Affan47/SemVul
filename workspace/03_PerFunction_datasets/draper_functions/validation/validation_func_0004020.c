buffer_size_add(struct persistent_ram_zone *prz, size_t a)
{
	size_t old;
	size_t new;
	unsigned long flags = 0;

	if (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_lock_irqsave(&prz->buffer_lock, flags);

	old = atomic_read(&prz->buffer->size);
	if (old == prz->buffer_size)
		goto exit;

	new = old + a;
	if (new > prz->buffer_size)
		new = prz->buffer_size;
	atomic_set(&prz->buffer->size, new);

exit:
	if (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_unlock_irqrestore(&prz->buffer_lock, flags);
}
