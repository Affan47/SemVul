row_create_index_for_mysql(

	dict_index_t*	index,

	trx_t*		trx,
	const ulint*	field_lengths)


{
	ind_node_t*	node;
	mem_heap_t*	heap;
	que_thr_t*	thr;
	ulint		err;
	ulint		i;
	ulint		len;
	char*		table_name;
	dict_table_t*	table;

#ifdef UNIV_SYNC_DEBUG
	ut_ad(rw_lock_own(&dict_operation_lock, RW_LOCK_EX));
#endif
	ut_ad(mutex_own(&(dict_sys->mutex)));

	trx->op_info = "creating index";


	table_name = mem_strdup(index->table_name);

	table = dict_table_get_low(table_name, DICT_ERR_IGNORE_NONE);

	trx_start_if_not_started(trx);

	for (i = 0; i < index->n_def; i++) {


		len = dict_index_get_nth_field(index, i)->prefix_len;

		if (field_lengths && field_lengths[i]) {
			len = ut_max(len, field_lengths[i]);
		}


		if (len > (ulint) DICT_MAX_FIELD_LEN_BY_FORMAT(table)) {
			err = DB_TOO_BIG_INDEX_COL;

			dict_mem_index_free(index);
			goto error_handling;
		}
	}

	heap = mem_heap_create(512);

	trx_set_dict_operation(trx, TRX_DICT_OP_TABLE);


	node = ind_create_graph_create(index, heap);

	thr = pars_complete_graph_for_exec(node, trx, heap);

	ut_a(thr == que_fork_start_command(que_node_get_parent(thr)));
	que_run_threads(thr);

	err = trx->error_state;

	que_graph_free((que_t*) que_node_get_parent(thr));

error_handling:

	if (err != DB_SUCCESS) {


		trx->error_state = DB_SUCCESS;

		trx_general_rollback_for_mysql(trx, NULL);

		row_drop_table_for_mysql(table_name, trx, FALSE);

		trx_commit_for_mysql(trx);

		trx->error_state = DB_SUCCESS;
	}

	trx->op_info = "";

	mem_free(table_name);

	return((int) err);
}
