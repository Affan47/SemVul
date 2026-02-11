wrap_qpol_default_policy_find() {
		char *path;
		int retv;
		BEGIN_EXCEPTION
		retv = qpol_default_policy_find(&path);
		if (retv < 0) {
			SWIG_exception(SWIG_IOError, "Error searching for default policy");
		} else if (retv > 0) {
			SWIG_exception(SWIG_RuntimeError, "Could not find default policy");
		} else {
			return path;
		}
		END_EXCEPTION
	fail:
		return NULL;
	}
