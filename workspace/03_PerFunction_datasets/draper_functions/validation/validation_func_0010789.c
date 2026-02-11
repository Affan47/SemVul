InitPositionInterpolator(M_PositionInterpolator *node)
{
	node->on_set_fraction = PosInt_SetFraction;
	if (node->keyValue.count) node->value_changed = node->keyValue.vals[0];
	return 1;
}
