getInt(struct SWF_ACTIONPUSHPARAM *act)
{
	switch( act->Type )
	{
	case PUSH_FLOAT:
		return ((int)act->p.Float);
	case PUSH_NULL:
		return 0;
	case PUSH_REGISTER:
		return getInt(regs[act->p.RegisterNumber]);
	case PUSH_DOUBLE:
		return (int)act->p.Double;
	case PUSH_INT:
		return act->p.Integer;
	default:
		fprintf (stderr,"  Can't get int for type: %d\n", act->Type);
	}
	return 0;
}
