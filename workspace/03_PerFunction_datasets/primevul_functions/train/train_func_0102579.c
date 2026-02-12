static bool uid_entry_in_group( canon_ace *uid_ace, canon_ace *group_ace )
{
	const char *u_name = NULL;


	if (sid_equal(&group_ace->trustee, &global_sid_World))
		return True;


	if (uid_ace->unix_ug.uid == current_user.ut.uid) {
		size_t i;

		if (group_ace->unix_ug.gid == current_user.ut.gid) {
			return True;
		}

		for (i=0; i < current_user.ut.ngroups; i++) {
			if (group_ace->unix_ug.gid == current_user.ut.groups[i]) {
				return True;
			}
		}
	}


	u_name = uidtoname(uid_ace->unix_ug.uid);
	if (!u_name) {
		return False;
	}


	return user_in_group_sid(u_name, &group_ace->trustee);
}
