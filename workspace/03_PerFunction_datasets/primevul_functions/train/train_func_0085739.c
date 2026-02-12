tcp_sack_partialack(struct tcpcb *tp, struct tcphdr *th)
{

	TCP_TIMER_DISARM(tp, TCPT_REXMT);
	tp->t_rtttime = 0;


	if (tp->snd_cwnd > (th->th_ack - tp->snd_una)) {
		tp->snd_cwnd -= th->th_ack - tp->snd_una;
		tp->snd_cwnd += tp->t_maxseg;
	} else
		tp->snd_cwnd = tp->t_maxseg;
	tp->snd_cwnd += tp->t_maxseg;
	tp->t_flags |= TF_NEEDOUTPUT;
}
