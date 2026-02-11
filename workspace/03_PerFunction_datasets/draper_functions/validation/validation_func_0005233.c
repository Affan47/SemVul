fromobject__fetch(register fromobject_susp_type susp, snd_list_type snd_list)
{
    int cnt = 0;
    int togo;
    int n;
    sample_block_type out;
    register sample_block_values_type out_ptr;

    register sample_block_values_type out_ptr_reg;

    register boolean done_reg;
    register LVAL src_reg;
    falloc_sample_block(out, "fromobject__fetch");
    out_ptr = out->samples;
    snd_list->block = out;

    while (cnt < max_sample_block_len) {


	togo = max_sample_block_len - cnt;

        if (susp->done) {
            togo = 0;
            break;
        }

	n = togo;
	done_reg = susp->done;
	src_reg = susp->src;
	out_ptr_reg = out_ptr;
	if (n) do {
            LVAL rslt = xleval(cons(s_send, cons(src_reg,
                                                 consa(s_next))));
            if (floatp(rslt)) {
                *out_ptr_reg++ = (sample_type) getflonum(rslt);
            } else {
                done_reg = true;

                break;
            };
	} while (--n);

	togo -= n;
	susp->done = done_reg;
	out_ptr += togo;
	cnt += togo;
    }


    if (togo == 0 && cnt == 0) {
	snd_list_terminate(snd_list);
    } else {
	snd_list->block_len = cnt;
	susp->susp.current += cnt;
    }
}
