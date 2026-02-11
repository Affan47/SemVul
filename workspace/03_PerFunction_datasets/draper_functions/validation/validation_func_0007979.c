armcpu_exec(armcpu_t *armcpu)
{
        u32 c = 1;

#ifdef GDB_STUB
        if ( armcpu->stalled)
          return STALLED_CYCLE_COUNT;


        if ( armcpu->irq_flag) {
          armcpu_irqExeption( armcpu);
        }

        c = armcpu_prefetch(armcpu);

        if ( armcpu->stalled) {
          return c;
        }
#endif

	if(armcpu->CPSR.bits.T == 0)
	{

        if((TEST_COND(CONDITION(armcpu->instruction), CODE(armcpu->instruction), armcpu->CPSR)))
		{
			c += arm_instructions_set[INSTRUCTION_INDEX(armcpu->instruction)](armcpu);
		}
#ifdef GDB_STUB
        if ( armcpu->post_ex_fn != NULL) {

            armcpu->post_ex_fn( armcpu->post_ex_fn_data,
                                armcpu->instruct_adr, 0);
        }
#else
		c += armcpu_prefetch(armcpu);
#endif
		return c;
	}

	c += thumb_instructions_set[armcpu->instruction>>6](armcpu);

#ifdef GDB_STUB
    if ( armcpu->post_ex_fn != NULL) {

        armcpu->post_ex_fn( armcpu->post_ex_fn_data, armcpu->instruct_adr, 1);
    }
#else
	c += armcpu_prefetch(armcpu);
#endif
	return c;
}
