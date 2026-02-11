wasp_instr_jf( ){


    if( wasp_is_false( WASP_RX ) ){
        WASP_IP = WASP_IP->proc->inst + wasp_imm_fv( WASP_AX );
    }else{
        wasp_next_instr();
    }
}
