R_API const char *r_core_anal_optype_colorfor(RCore *core, ut64 addr, bool verbose) {
	ut64 type;
	if (!(core->print->flags & R_PRINT_FLAGS_COLOR)) {
		return NULL;
	}
	if (!r_config_get_i (core->config, "scr.color")) {
		return NULL;
	}
	type = r_core_anal_address (core, addr);
	if (type & R_ANAL_ADDR_TYPE_EXEC) {
		return core->cons->context->pal.ai_exec;
	}
	if (type & R_ANAL_ADDR_TYPE_WRITE) {
		return core->cons->context->pal.ai_write;
	}
	if (type & R_ANAL_ADDR_TYPE_READ) {
		return core->cons->context->pal.ai_read;
	}
	if (type & R_ANAL_ADDR_TYPE_SEQUENCE) {
		return core->cons->context->pal.ai_seq;
	}
	if (type & R_ANAL_ADDR_TYPE_ASCII) {
		return core->cons->context->pal.ai_ascii;
	}
	return NULL;
}
