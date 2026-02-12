decompilePUSHPARAM (struct SWF_ACTIONPUSHPARAM *act, int wantstring)
{
	char *t;
	switch( act->Type )
	{
	case PUSH_STRING:
		if( wantstring ) printf ("'%s'", act->p.String);
		else printf ("%s", act->p.String);
		break;
	case PUSH_FLOAT:
		printf ("%f", act->p.Float);
		break;
	case PUSH_NULL:
		printf ("NULL" );
		break;
	case PUSH_UNDEF:
		printf ("undefined" );
		break;
	case PUSH_REGISTER:
		if( regs[act->p.RegisterNumber] ) {
			printf ("%s", getName(act));
		} else {
			printf ("R%d", (int)act->p.RegisterNumber);
		}
		break;
	case PUSH_BOOLEAN:
		printf ("%s", act->p.Boolean?"true":"false");
		break;
	case PUSH_DOUBLE:
		printf ("%g", act->p.Double);
		break;
	case PUSH_INT:
		printf ("%ld", act->p.Integer);
		break;

	case PUSH_CONSTANT:
	case PUSH_CONSTANT16:
		if( wantstring ) t=getString(act);
	  	else t=getName(act);
	  	puts(t);
	  	free(t);
	  	break;

#if 0
	  case 8:
		if (act->p.Constant8 > poolcounter)
		{
		        SWF_warn("WARNING: retrieving constants not present in the pool.\n");
		        break;
		}
		if( wantstring )
  		  printf ("'%s'", pool[act->p.Constant8]);
		else
  		  printf ("%s", pool[act->p.Constant8]);
		break;
	  case 9:
		if (act->p.Constant16 > poolcounter)
		{
		        SWF_warn("WARNING: retrieving constants not present in the pool.\n");
		        break;
		}
		if( wantstring )
  		  printf ("'%s'", pool[act->p.Constant16]);
		else
  		  printf ("%s", pool[act->p.Constant16]);
		break;
#endif
	case 12:
	case 11:
	case PUSH_VARIABLE:
		printf ("%s", act->p.String);
		break;
	default:
		printf ("  Unknown type: %d\n", act->Type);
	}
}
