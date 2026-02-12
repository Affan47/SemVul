pk_transaction_set_state (PkTransaction *transaction, PkTransactionState state)
{
	PkTransactionPrivate *priv = transaction->priv;


	if (priv->state != PK_TRANSACTION_STATE_UNKNOWN &&
	    priv->state > state) {
		g_warning ("cannot set %s, as already %s",
			   pk_transaction_state_to_string (state),
			   pk_transaction_state_to_string (priv->state));
	}

	g_debug ("transaction now %s", pk_transaction_state_to_string (state));
	priv->state = state;
	g_signal_emit (transaction, signals[SIGNAL_STATE_CHANGED], 0, state);


	if (state == PK_TRANSACTION_STATE_READY &&
	    (priv->role == PK_ROLE_ENUM_REMOVE_PACKAGES ||
	     priv->role == PK_ROLE_ENUM_INSTALL_PACKAGES ||
	     priv->role == PK_ROLE_ENUM_UPDATE_PACKAGES)) {


		pk_transaction_db_add (priv->transaction_db, priv->tid);


		pk_transaction_db_set_role (priv->transaction_db, priv->tid, priv->role);


		pk_transaction_db_set_uid (priv->transaction_db, priv->tid, priv->uid);


		if (priv->cmdline != NULL)
			pk_transaction_db_set_cmdline (priv->transaction_db, priv->tid, priv->cmdline);


		syslog (LOG_DAEMON | LOG_DEBUG,
			"new %s transaction %s scheduled from uid %i",
			pk_role_enum_to_string (priv->role),
			priv->tid, priv->uid);
	}


	if (state == PK_TRANSACTION_STATE_WAITING_FOR_AUTH) {
		pk_transaction_status_changed_emit (transaction,
						    PK_STATUS_ENUM_WAITING_FOR_AUTH);
		pk_transaction_progress_changed_emit (transaction,
						      PK_BACKEND_PERCENTAGE_INVALID,
						      0, 0);

	} else if (state == PK_TRANSACTION_STATE_READY) {
		pk_transaction_status_changed_emit (transaction,
						    PK_STATUS_ENUM_WAIT);
		pk_transaction_progress_changed_emit (transaction,
						      PK_BACKEND_PERCENTAGE_INVALID,
						      0, 0);
	}
}
