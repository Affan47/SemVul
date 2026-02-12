static int r_cmd_java_reload_bin_from_buf (RCore *core, RBinJavaObj *obj, ut8* buffer, ut64 len) {
	if (!buffer || len < 10) {
		return false;
	}
	int res = r_bin_java_load_bin (obj, buffer, len);

	if (res == true) {

		RBinPlugin *tmp;
		RListIter *iter;
		r_list_foreach (core->bin->plugins, iter, tmp) {
			if (!strncmp ("java", tmp->name, 4)) {

				break;
			}
		}


	}
	return res;
}
