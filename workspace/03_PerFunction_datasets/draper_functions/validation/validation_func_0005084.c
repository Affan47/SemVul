gkm_object_unlock (GkmObject *self, GkmCredential *cred)
{
	g_return_val_if_fail (GKM_IS_OBJECT (self), CKR_GENERAL_ERROR);
	g_return_val_if_fail (GKM_OBJECT_GET_CLASS (self)->unlock, CKR_GENERAL_ERROR);
	return GKM_OBJECT_GET_CLASS (self)->unlock (self, cred);
}
