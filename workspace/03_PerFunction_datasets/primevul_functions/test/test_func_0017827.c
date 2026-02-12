R_API bool r_core_anal_fcn(RCore *core, ut64 at, ut64 from, int reftype, int depth) {
	if (depth < 0) {
		if (core->anal->verbose) {
			eprintf ("Message: Early deepness at 0x%08"PFMT64x"\n", at);
		}
		return false;
	}
	if (from == UT64_MAX && is_skippable_addr (core, at)) {
		if (core->anal->verbose) {
			eprintf ("Message: Invalid address for function 0x%08"PFMT64x"\n", at);
		}
		return false;
	}

	const bool use_esil = r_config_get_i (core->config, "anal.esil");
	RAnalFunction *fcn;


	r_core_seek_arch_bits (core, at);

	if (core->io->va) {
		if (!r_io_is_valid_offset (core->io, at, !core->anal->opt.noncode)) {
			if (core->anal->verbose) {
				eprintf ("Warning: Address not mapped or not executable at 0x%08"PFMT64x"\n", at);
			}
			return false;
		}
	}
	if (r_config_get_i (core->config, "anal.a2f")) {
		r_core_cmd0 (core, ".a2f");
		return 0;
	}
	if (use_esil) {
		return r_core_anal_esil_fcn (core, at, from, reftype, depth);
	}

	if ((from != UT64_MAX && !at) || at == UT64_MAX) {
		eprintf ("Invalid address from 0x%08"PFMT64x"\n", from);
		return false;
	}
	if (r_cons_is_breaked ()) {
		return false;
	}
	fcn = r_anal_get_fcn_in (core->anal, at, 0);
	if (fcn) {
		if (fcn->addr == at) {


			if (reftype == R_ANAL_REF_TYPE_CALL && fcn->type == R_ANAL_FCN_TYPE_LOC) {
				function_rename (core->flags, fcn);
			}
			return 0;
		}
		if (r_anal_function_contains (fcn, from)) {
			RList *l = r_anal_xrefs_get (core->anal, from);
			if (l && !r_list_empty (l)) {
				r_list_free (l);
				return true;
			}
			r_list_free (l);


			if (from != UT64_MAX) {
				r_anal_xrefs_set (core->anal, from, at, reftype);
			}
			return true;
		}
	}
	if (__core_anal_fcn (core, at, from, reftype, depth - 1)) {

		if (fcn) {
			r_anal_function_resize (fcn, at - fcn->addr);
		}
		return true;
	}
	return false;
}
