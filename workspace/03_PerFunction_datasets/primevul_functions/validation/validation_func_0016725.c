static void cil_reset_user(struct cil_user *user)
{

	user->bounds = NULL;
	user->dftlevel = NULL;
	user->range = NULL;
}
