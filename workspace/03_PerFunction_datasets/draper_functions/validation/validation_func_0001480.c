call_gnuplot(double *par, double *data)
{
    int i, j;
    struct value v;


    for (i = 0; i < num_params; i++) {
	(void) Gcomplex(&v, par[i], 0.0);
	setvar(par_name[i], v);
    }

    for (i = 0; i < num_data; i++) {


      for (j=0; j<5; j++) {
	struct udvt_entry *udv = add_udv_by_name(c_dummy_var[j]);
	(void) Gcomplex(&func.dummy_values[j],
			udv->udv_undef ? 0 : getdvar(c_dummy_var[j]),
			0.0);
      }

      for (j=0; j<num_indep; j++)
	(void) Gcomplex(&func.dummy_values[j],
			fit_x[i*num_indep+j], 0.0);
      evaluate_at(func.at, &v);
      if (undefined)
	Eex("Undefined value during function evaluation");
      data[i] = real(&v);
    }
}
