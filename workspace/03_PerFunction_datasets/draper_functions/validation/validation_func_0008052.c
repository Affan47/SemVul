reconfigure_bool(e2fsck_t ctx, struct e2fsck_problem *ptr,
			     const char *key, int mask, const char *name)
{
	int	bool;

	bool = (ptr->flags & mask);
	profile_get_boolean(ctx->profile, "problems", key, name, bool, &bool);
	if (bool)
		ptr->flags |= mask;
	else
		ptr->flags &= ~mask;
}
