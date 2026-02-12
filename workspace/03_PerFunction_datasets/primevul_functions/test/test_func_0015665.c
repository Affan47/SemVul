static bool inline valid_var_kind(char kind) {
	switch (kind) {
	case R_ANAL_VAR_KIND_BPV:
	case R_ANAL_VAR_KIND_SPV:
	case R_ANAL_VAR_KIND_REG:
		return true;
	default:
		return false;
	}
}
