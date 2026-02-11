solviip(double alpha, double betas,
								  KronVector& d, double& eig_min) const
{

	if (betas < diag_zero_sq) {
		solvi(alpha, d, eig_min);
		solvi(alpha, d, eig_min);
		return;
	}

	if (d.getDepth() == 0) {
		double aspbs = alpha*alpha+betas;
		QuasiTriangular* t= matrixK->clone(2*alpha, aspbs, *matrixKK);
		t->solvePre(d, eig_min);
		delete t;
	} else {
		const_diag_iter di = matrixF->diag_begin();
		const_diag_iter dsi = matrixFF->diag_begin();
		for (; di != matrixF->diag_end(); ++di, ++dsi) {
			if ((*di).isReal()) {
				solviipRealAndEliminate(alpha, betas, di, dsi, d, eig_min);
			} else {
				solviipComplexAndEliminate(alpha, betas, di, dsi, d, eig_min);
			}
		}
	}
}
