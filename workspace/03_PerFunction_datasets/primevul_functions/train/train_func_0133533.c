OPJ_UINT32 opj_j2k_get_num_tp(opj_cp_t *cp, OPJ_UINT32 pino, OPJ_UINT32 tileno)
{
        const OPJ_CHAR *prog = 00;
        OPJ_INT32 i;
        OPJ_UINT32 tpnum = 1;
        opj_tcp_t *tcp = 00;
        opj_poc_t * l_current_poc = 00;


        assert(tileno < (cp->tw * cp->th));
        assert(pino < (cp->tcps[tileno].numpocs + 1));


        tcp = &cp->tcps[tileno];
        assert(tcp != 00);

        l_current_poc = &(tcp->pocs[pino]);
        assert(l_current_poc != 0);


        prog = opj_j2k_convert_progression_order(tcp->prg);
        assert(strlen(prog) > 0);

        if (cp->m_specific_param.m_enc.m_tp_on == 1) {
                for (i=0;i<4;++i) {
                        switch (prog[i])
                        {

                                case 'C':
                                        tpnum *= l_current_poc->compE;
                                        break;

                                case 'R':
                                        tpnum *= l_current_poc->resE;
                                        break;

                                case 'P':
                                        tpnum *= l_current_poc->prcE;
                                        break;

                                case 'L':
                                        tpnum *= l_current_poc->layE;
                                        break;
                        }

                        if ( cp->m_specific_param.m_enc.m_tp_flag == prog[i] ) {
                                cp->m_specific_param.m_enc.m_tp_pos=i;
                                break;
                        }
                }
        }
        else {
                tpnum=1;
        }

        return tpnum;
}
