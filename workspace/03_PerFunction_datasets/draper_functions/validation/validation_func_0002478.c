match_explicit(struct ref *src, struct ref *dst,
			  struct ref ***dst_tail,
			  struct refspec *rs,
			  int errs)
{
	struct ref *matched_src, *matched_dst;

	const char *dst_value = rs->dst;

	if (rs->pattern)
		return errs;

	matched_src = matched_dst = NULL;
	switch (count_refspec_match(rs->src, src, &matched_src)) {
	case 1:
		break;
	case 0:


		matched_src = try_explicit_object_name(rs->src);
		if (matched_src)
			break;
		error("src refspec %s does not match any.",
		      rs->src);
		break;
	default:
		matched_src = NULL;
		error("src refspec %s matches more than one.",
		      rs->src);
		break;
	}

	if (!matched_src)
		errs = 1;

	if (dst_value == NULL)
		dst_value = matched_src->name;

	switch (count_refspec_match(dst_value, dst, &matched_dst)) {
	case 1:
		break;
	case 0:
		if (!memcmp(dst_value, "refs/", 5))
			matched_dst = make_dst(dst_value, dst_tail);
		else
			error("dst refspec %s does not match any "
			      "existing ref on the remote and does "
			      "not start with refs/.", dst_value);
		break;
	default:
		matched_dst = NULL;
		error("dst refspec %s matches more than one.",
		      dst_value);
		break;
	}
	if (errs || matched_dst == NULL)
		return 1;
	if (matched_dst->peer_ref) {
		errs = 1;
		error("dst ref %s receives from more than one src.",
		      matched_dst->name);
	}
	else {
		matched_dst->peer_ref = matched_src;
		matched_dst->force = rs->force;
	}
	return errs;
}
