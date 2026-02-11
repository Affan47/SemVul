shk_chat(shkp)
struct monst *shkp;
{
	struct eshk *eshk;
#ifdef GOLDOBJ
	long shkmoney;
#endif
	if (!shkp->isshk) {


		pline("%s asks whether you've seen any untended shops recently.",
		      Monnam(shkp));


		return;
	}

	eshk = ESHK(shkp);
	if (ANGRY(shkp))
		pline("%s mentions how much %s dislikes %s customers.",
			shkname(shkp), mhe(shkp),
			eshk->robbed ? "non-paying" : "rude");
	else if (eshk->following) {
		if (strncmp(eshk->customer, plname, PL_NSIZ)) {
		    verbalize("%s %s!  I was looking for %s.",
			    Hello(shkp), plname, eshk->customer);
		    eshk->following = 0;
		} else {
		    verbalize("%s %s!  Didn't you forget to pay?",
			      Hello(shkp), plname);
		}
	} else if (eshk->billct) {
		register long total = addupbill(shkp) + eshk->debit;
		pline("%s says that your bill comes to %ld %s.",
		      shkname(shkp), total, currency(total));
	} else if (eshk->debit)
		pline("%s reminds you that you owe %s %ld %s.",
		      shkname(shkp), mhim(shkp),
		      eshk->debit, currency(eshk->debit));
	else if (eshk->credit)
		pline("%s encourages you to use your %ld %s of credit.",
		      shkname(shkp), eshk->credit, currency(eshk->credit));
	else if (eshk->robbed)
		pline("%s complains about a recent robbery.", shkname(shkp));
#ifndef GOLDOBJ
	else if (shkp->mgold < 50)
#else
	else if ((shkmoney = money_cnt(shkp->minvent)) < 50)
#endif
		pline("%s complains that business is bad.", shkname(shkp));
#ifndef GOLDOBJ
	else if (shkp->mgold > 4000)
#else
	else if (shkmoney > 4000)
#endif
		pline("%s says that business is good.", shkname(shkp));
	else if (strcmp(shkname(shkp), "Izchak") == 0)
		pline(Izchak_speaks[rn2(SIZE(Izchak_speaks))],shkname(shkp));
	else
		pline("%s talks about the problem of shoplifters.",shkname(shkp));
}
