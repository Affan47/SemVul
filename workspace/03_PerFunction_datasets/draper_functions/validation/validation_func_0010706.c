least_square(vector<double>* x,vector<double>* y,double* slope, double* offset, double* rsquared) {


	double sum_x=0, sum_y=0, sum_xy=0, sum_xx=0, delta=0, y_avg = 0, n = static_cast<double>(x->size());
	for (size_t i = 0; i < x->size(); i++) {

		sum_x += (*x)[i];
		sum_y += (*y)[i];
		sum_xy += (*x)[i]*(*y)[i];
		sum_xx += (*x)[i]*(*x)[i];
	}
	delta = n*sum_xx - sum_x*sum_x;
	*slope = (n*sum_xy - sum_x*sum_y)/delta;
	*offset = (sum_xx*sum_y - sum_x*sum_xy)/delta;
	y_avg = sum_y / n;


	*rsquared = 0;
	double residue = 0.0,syy=0.0;

	for (int i = 0; i < n; i++) {
		residue += pow((*y)[i] - (*slope) * (*x)[i] - *offset,2.0);
		syy += pow((*y)[i] - y_avg,2.0);
	}

	*rsquared = 1 - residue/syy;
}
