smt_fill_echo(struct s_smc *smc, struct smt_p_echo *echo, u_long seed,
			  int len)
{
	u_char	*p ;

	SK_UNUSED(smc) ;
	SMTSETPARA(echo,SMT_P_ECHODATA) ;
	echo->para.p_len = len ;
	for (p = echo->ec_data ; len ; len--) {
		*p++ = (u_char) seed ;
		seed += 13 ;
	}
}
