write_sync_reduction_volatile(fsbe_context *cx, Module_table *module)
{
    Reduction_table *rpt;
    Reduction_element *rept;
    int *count = NULL;
    int i;
    if((count = (int *)calloc(NUM_OF_STR_TYPE, sizeof(int))) == NULL)
	fatal("count allocation error\n");
    for (rpt = module->red_head; rpt != NULL; rpt = rpt->next) {
	for (rept = rpt->element_head; rept != NULL; rept = rept->next) {
	    count[(int)rept->type]++;
	}
    }
    for (i = 0; i < NUM_OF_STR_TYPE; i++) {
	if (count[i] != 0){
	    switch (i) {
	    case TYPE_INT:
		ompfbe_iprintf(cx, "VOLATILE RED_INT\n");
		break;
	    case TYPE_REAL:
		ompfbe_iprintf(cx, "VOLATILE RED_REAL\n");
		break;
	    case TYPE_DOUBLE:
		ompfbe_iprintf(cx, "VOLATILE RED_DOUBLE\n");
		break;
	    case TYPE_LOGICAL:
		ompfbe_iprintf(cx, "VOLATILE RED_LOGICAL\n");
		break;
	    default:
		break;
	    }
	}
    }
    free(count);
}
