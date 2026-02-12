decompile_SWITCH(int n, SWF_ACTION *actions, int maxn, int off1end)
{
	int i,j;
	int start;
	int ccsize=0;
	int cvsize=0;
	int maxoff=0;
	int n_maxoff=0;
	int pend=0;
	int xsize=0;
	int jmpsize=0;
	int lastoff=0;
	int n_firstactions=maxn;
	int lastcasestart=0;
	char *defa="[last]";
	char *tmp=NULL;
	struct strbufinfo origbuf;
	struct _stack *StackSave;
	struct SWF_ACTIONPUSHPARAM *swcopy,*sw=pop();
	struct SWF_ACTIONPUSHPARAM *compare=pop();
	int offSave;
	for (i=0; i<n_firstactions; i++)
	{
		if (actions[i+1].SWF_ACTIONRECORD.Offset==off1end)
		{

			if (OpCode(actions, i, maxn) == SWFACTION_JUMP)
			{
				maxoff=actions[i].SWF_ACTIONJUMP.BranchOffset+actions[i].SWF_ACTIONJUMP.Offset+5;
				j=1;
			}
			else
			{

			}
			break;
		}
	}

	if (!maxoff)
	{
		for (i=maxn-1;i>=0;i--)
		{
			if (OpCode(actions, i, maxn) == SWFACTION_JUMP && !actions[i].SWF_ACTIONJUMP.BranchOffset)
			{
				maxoff=actions[i].SWF_ACTIONRECORD.Offset+5;
				j=2;
				break;
			}
		}
	}

	for (i=0;i<maxn;i++)
	{
		if (actions[i].SWF_ACTIONRECORD.Offset>=maxoff)
		{
			n_maxoff=i;
			break;
		}
	}

	if (!n_maxoff)
		n_maxoff=maxn;

	INDENT
	println("switch( %s ) {			// end switch at %d (index %d) / found via meth %d)",
	        getString(sw), maxoff,n_maxoff,j);

	push(sw);
	push(compare);

	i=1;
	do
	{
		if((OpCode(actions, i, maxn) == SWFACTION_IF
		   && OpCode(actions, i-1, maxn) == SWFACTION_STRICTEQUALS )
		   ||(OpCode(actions, i, maxn) == SWFACTION_JUMP
		   && OpCode(actions, i-1, maxn) == SWFACTION_IF) )
		{
			start=i;
			while (start<maxn
			       && actions[start].SWF_ACTIONRECORD.Offset < actions[i].SWF_ACTIONRECORD.Offset+5+actions[i].SWF_ACTIONJUMP.BranchOffset
)			{
				start++;
			}
			if (n_firstactions==maxn)
			{
				n_firstactions=start;
			}

			for (ccsize=0; ccsize+start<n_maxoff; ccsize++)
			{
#ifdef DEBUGSWITCH
				println("in ccsize: ccsize=%d  off=%d %s",
				        ccsize,actions[ccsize+start].SWF_ACTIONRECORD.Offset,
				        actionName(OpCode(actions, ccsize+start, maxn)));
#endif
				if (OpCode(actions, ccsize+start, maxn) == SWFACTION_JUMP)
				{
					if (maxoff == actions[ccsize+start].SWF_ACTIONJUMP.Offset+5 + actions[ccsize+start].SWF_ACTIONJUMP.BranchOffset)
					{
						jmpsize= actions[ccsize+start].SWF_ACTIONJUMP.BranchOffset;
						lastoff= actions[ccsize+start].SWF_ACTIONJUMP.Offset;
						ccsize++;
						break;
					}
				}
			}

#if USE_LIB
			if (tmp && (start!=pend))
			{
				puts(tmp);
			}

			if (tmp)
			{
				free(tmp);
				tmp=NULL;
			}
			pend=start;
#endif
			if (OpCode(actions, i, maxn) == SWFACTION_JUMP)
			{
				if (ccsize<=1)
					break;
				else
				{
					INDENT
					if (actions[start].SWF_ACTIONRECORD.Offset>lastcasestart)
						xsize+=ccsize;
					else
						defa="[early]";
						println("default:			// at %d %s start=%d ccsize=%d",
						        actions[start].SWF_ACTIONRECORD.Offset,defa, start, ccsize);
				}
			}
			else
			{
				INDENT
				xsize=ccsize;
				lastcasestart=actions[start].SWF_ACTIONRECORD.Offset;
				println("case %s:			// at %d  start=%d ccsize=%d jmp=%d+%d+5",
			        getString(pop()), lastcasestart, start, ccsize, lastoff,jmpsize);
				swcopy=pop();

			}

#if USE_LIB
			origbuf=setTempString();
#endif
			StackSave=Stack;
			offSave=offseoloop;
			offseoloop=maxoff;
			decompileActions( ccsize, &actions[start],gIndent+1);
			offseoloop=offSave;
			Stack=StackSave;
#if USE_LIB
			tmp=switchToOrigString(origbuf);
#endif

			if (OpCode(actions, i, maxn) == SWFACTION_JUMP)
			{
				break;
			}
			else
			{
				if (OpCode(actions, i+1, maxn) != SWFACTION_JUMP)
				{
					i++;
					cvsize=0;
					while (i+cvsize < n_firstactions
					       && OpCode(actions, i+cvsize, maxn) != SWFACTION_STRICTEQUALS)
					{
#ifdef DEBUGSWITCH
						println("in  cvsize=%d  %d %s",
						        cvsize, actions[i+cvsize].SWF_ACTIONRECORD.Offset,
						        actionName(OpCode(actions, i+cvsize, maxn)));
#endif
							cvsize++;
					}
					decompileActions( cvsize, &actions[i],gIndent+1);
					i+=cvsize;
				}
			}
		}
	} while (++i < n_firstactions);

#if USE_LIB
	if (tmp)
	{
		puts(tmp);
		free(tmp);
	}
#endif
	INDENT
	println("}					// switch ret value =%d",xsize);
	return xsize;
}
