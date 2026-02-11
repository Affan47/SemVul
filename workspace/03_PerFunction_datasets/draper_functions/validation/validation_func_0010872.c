relay_back_op_bind( Operation *op, SlapReply *rs )
{


	switch ( be_rootdn_bind( op, rs ) ) {
	case SLAP_CB_CONTINUE:
		break;

	default:
		return rs->sr_err;
	}

	return relay_back_op( op, rs, op_bind );
}
