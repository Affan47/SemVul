mpi_set_send_recv_to_block_for_mtg(Block *block_head)
{
    Block *block;
    Quadruple *qr;
    Statement *stm;

    for( block = block_head; block != NULL; block = block->next){

	if( block->pre_head != NULL){
	    for( stm = block->pre_head->stm_head; stm != NULL; stm = stm->next){
		qr = stm->qr_head;
		if( qr->ope == OPE_NT_RECEIVE && qr->op[2]->entry == -1){
		    block->recv_nt_set = qr->op[1]->tbl.n;
		}
	    }
	}


	if( block->inner == NULL){
	    for( stm = block->pre_head->stm_head; stm != NULL; stm = stm->next){
		qr = stm->qr_head;
		if( qr->ope == OPE_NT_SEND && qr->op[2]->entry == -1){
		    block->send_nt_set = qr->op[1]->tbl.n;
		}
	    }
	}else{
	    for( stm = block->post_head->stm_head; stm != NULL; stm = stm->next){
		qr = stm->qr_head;
		if( qr->ope == OPE_NT_SEND && qr->op[2]->entry == -1){
		    block->send_nt_set = qr->op[1]->tbl.n;
		}
	    }
	}
    }
}
