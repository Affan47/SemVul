hkl_pseudo_axis_engine_add_mode(HklPseudoAxisEngine *self,
					HklPseudoAxisEngineMode *mode)
{
	HKL_LIST_ADD_VALUE(self->modes, mode);
}
