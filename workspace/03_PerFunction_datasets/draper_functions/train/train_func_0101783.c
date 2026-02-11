gplp_func_desc_load (GOPluginService *service,
		     char const *name,
		     GnmFuncDescriptor *res)
{
	ServiceLoaderDataFunctionGroup *loader_data;
	PyObject *fn_info_obj;

	g_return_val_if_fail (IS_GNM_PLUGIN_SERVICE_FUNCTION_GROUP (service), FALSE);
	g_return_val_if_fail (name != NULL, FALSE);

	loader_data = g_object_get_data (G_OBJECT (service), "loader_data");
	SWITCH_TO_PLUGIN (go_plugin_service_get_plugin (service));
	fn_info_obj = PyDict_GetItemString (loader_data->python_fn_info_dict,
					    (gchar *) name);
	if (fn_info_obj == NULL) {
		gnm_python_clear_error_if_needed (SERVICE_GET_LOADER (service)->py_object);
		return FALSE;
	}

	if (PyTuple_Check (fn_info_obj)) {
		PyObject *python_args;
		PyObject *python_fn;

		if (PyTuple_Size (fn_info_obj) == 3 &&
		    (python_args = PyTuple_GetItem (fn_info_obj, 0)) != NULL &&
			PyString_Check (python_args) &&
		    (python_fn = PyTuple_GetItem (fn_info_obj, 2)) != NULL &&
		    PyFunction_Check (python_fn)) {
			res->arg_spec	= PyString_AsString (python_args);
			res->help	= python_function_get_gnumeric_help (
				loader_data->python_fn_info_dict, python_fn, name);
			res->fn_args	= &call_python_function_args;
			res->fn_nodes	= NULL;
			res->linker	= NULL;
			res->impl_status = GNM_FUNC_IMPL_STATUS_UNIQUE_TO_GNUMERIC;
			res->test_status = GNM_FUNC_TEST_STATUS_UNKNOWN;
			return TRUE;
		}

		gnm_python_clear_error_if_needed (SERVICE_GET_LOADER (service)->py_object);
		return FALSE;
	}

	if (PyFunction_Check (fn_info_obj)) {
		res->arg_spec	= "";
		res->help	= python_function_get_gnumeric_help (
			loader_data->python_fn_info_dict, fn_info_obj, name);
		res->fn_args	= NULL;
		res->fn_nodes	= &call_python_function_nodes;
		res->linker	= NULL;
		res->impl_status = GNM_FUNC_IMPL_STATUS_UNIQUE_TO_GNUMERIC;
		res->test_status = GNM_FUNC_TEST_STATUS_UNKNOWN;
		return TRUE;
	}

	gnm_python_clear_error_if_needed (SERVICE_GET_LOADER (service)->py_object);
	return FALSE;
}
