trustedRewrite(const Expr& expr1, const Expr& expr2) {


	Proof pf;


	if (withProof()) pf = newPf("trustedRewrite", expr1, expr2);


	return newRWTheorem(expr1, expr2, Assumptions::emptyAssump(), pf);

}
