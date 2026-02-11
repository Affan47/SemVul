update(struct command *cmd)
{
	const char *name = cmd->ref_name;
	unsigned char *old_sha1 = cmd->old_sha1;
	unsigned char *new_sha1 = cmd->new_sha1;
	struct ref_lock *lock;


	if (prefixcmp(name, "refs/") || check_ref_format(name + 5)) {
		error("refusing to create funny ref '%s' remotely", name);
		return "funny refname";
	}

	if (!is_null_sha1(new_sha1) && !has_sha1_file(new_sha1)) {
		error("unpack should have generated %s, "
		      "but I can't find it!", sha1_to_hex(new_sha1));
		return "bad pack";
	}
	if (deny_non_fast_forwards && !is_null_sha1(new_sha1) &&
	    !is_null_sha1(old_sha1) &&
	    !prefixcmp(name, "refs/heads/")) {
		struct object *old_object, *new_object;
		struct commit *old_commit, *new_commit;
		struct commit_list *bases, *ent;

		old_object = parse_object(old_sha1);
		new_object = parse_object(new_sha1);

		if (!old_object || !new_object ||
		    old_object->type != OBJ_COMMIT ||
		    new_object->type != OBJ_COMMIT) {
			error("bad sha1 objects for %s", name);
			return "bad ref";
		}
		old_commit = (struct commit *)old_object;
		new_commit = (struct commit *)new_object;
		bases = get_merge_bases(old_commit, new_commit, 1);
		for (ent = bases; ent; ent = ent->next)
			if (!hashcmp(old_sha1, ent->item->object.sha1))
				break;
		free_commit_list(bases);
		if (!ent) {
			error("denying non-fast forward %s"
			      " (you should pull first)", name);
			return "non-fast forward";
		}
	}
	if (run_update_hook(cmd)) {
		error("hook declined to update %s", name);
		return "hook declined";
	}

	if (is_null_sha1(new_sha1)) {
		if (!parse_object(old_sha1)) {
			warning ("Allowing deletion of corrupt ref.");
			old_sha1 = NULL;
		}
		if (delete_ref(name, old_sha1, 0)) {
			error("failed to delete %s", name);
			return "failed to delete";
		}
		return NULL;
	}
	else {
		lock = lock_any_ref_for_update(name, old_sha1, 0);
		if (!lock) {
			error("failed to lock %s", name);
			return "failed to lock";
		}
		if (write_ref_sha1(lock, new_sha1, "push")) {
			return "failed to write";
		}
		return NULL;
	}
}
