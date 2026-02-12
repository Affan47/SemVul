S_ssc_init(pTHX_ const RExC_state_t *pRExC_state, regnode_ssc *ssc)
{


    PERL_ARGS_ASSERT_SSC_INIT;

    Zero(ssc, 1, regnode_ssc);
    set_ANYOF_SYNTHETIC(ssc);
    ARG_SET(ssc, ANYOF_ONLY_HAS_BITMAP);
    ssc_anything(ssc);


    if (RExC_contains_locale) {
	ANYOF_POSIXL_SETALL(ssc);
    }
    else {
	ANYOF_POSIXL_ZERO(ssc);
    }
}
