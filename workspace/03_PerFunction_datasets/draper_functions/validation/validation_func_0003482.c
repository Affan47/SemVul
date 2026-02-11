dispatch_random(arc4ctx_t *actx) {
	isc_uint16_t result;

	if (actx->lock != NULL)
		LOCK(actx->lock);

	actx->count -= sizeof(isc_uint16_t);
	if (actx->count <= 0)
		dispatch_arc4stir(actx);
	result = dispatch_arc4get16(actx);

	if (actx->lock != NULL)
		UNLOCK(actx->lock);

	return (result);
}
