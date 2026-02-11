arbel_create_eq ( struct arbel *arbel ) {
	struct arbel_event_queue *arbel_eq = &arbel->eq;
	struct arbelprm_eqc eqctx;
	struct arbelprm_event_mask mask;
	unsigned int i;
	int rc;


	arbel_eq->eqn = arbel->limits.reserved_eqs;


	arbel_eq->doorbell = ( arbel->eq_ci_doorbells +
			       ARBEL_DB_EQ_OFFSET ( arbel_eq->eqn ) );


	arbel_eq->eqe_size =
		( ARBEL_NUM_EQES * sizeof ( arbel_eq->eqe[0] ) );
	arbel_eq->eqe = malloc_dma ( arbel_eq->eqe_size,
				     sizeof ( arbel_eq->eqe[0] ) );
	if ( ! arbel_eq->eqe ) {
		rc = -ENOMEM;
		goto err_eqe;
	}
	memset ( arbel_eq->eqe, 0, arbel_eq->eqe_size );
	for ( i = 0 ; i < ARBEL_NUM_EQES ; i++ ) {
		MLX_FILL_1 ( &arbel_eq->eqe[i].generic, 7, owner, 1 );
	}
	barrier();


	memset ( &eqctx, 0, sizeof ( eqctx ) );
	MLX_FILL_1 ( &eqctx, 0, st, 0xa  );
	MLX_FILL_1 ( &eqctx, 2,
		     start_address_l, virt_to_phys ( arbel_eq->eqe ) );
	MLX_FILL_1 ( &eqctx, 3, log_eq_size, fls ( ARBEL_NUM_EQES - 1 ) );
	MLX_FILL_1 ( &eqctx, 6, pd, ARBEL_GLOBAL_PD );
	MLX_FILL_1 ( &eqctx, 7, lkey, arbel->reserved_lkey );
	if ( ( rc = arbel_cmd_sw2hw_eq ( arbel, arbel_eq->eqn,
					 &eqctx ) ) != 0 ) {
		DBGC ( arbel, "Arbel %p SW2HW_EQ failed: %s\n",
		       arbel, strerror ( rc ) );
		goto err_sw2hw_eq;
	}


	memset ( &mask, 0, sizeof ( mask ) );
	MLX_FILL_1 ( &mask, 1, port_state_change, 1 );
	if ( ( rc = arbel_cmd_map_eq ( arbel,
				       ( ARBEL_MAP_EQ | arbel_eq->eqn ),
				       &mask ) ) != 0 ) {
		DBGC ( arbel, "Arbel %p MAP_EQ failed: %s\n",
		       arbel, strerror ( rc )  );
		goto err_map_eq;
	}

	DBGC ( arbel, "Arbel %p EQN %#lx ring at [%p,%p])\n",
	       arbel, arbel_eq->eqn, arbel_eq->eqe,
	       ( ( ( void * ) arbel_eq->eqe ) + arbel_eq->eqe_size ) );
	return 0;

 err_map_eq:
	arbel_cmd_hw2sw_eq ( arbel, arbel_eq->eqn, &eqctx );
 err_sw2hw_eq:
	free_dma ( arbel_eq->eqe, arbel_eq->eqe_size );
 err_eqe:
	memset ( arbel_eq, 0, sizeof ( *arbel_eq ) );
	return rc;
}
