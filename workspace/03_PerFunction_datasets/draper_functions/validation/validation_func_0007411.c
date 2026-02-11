dof_xpay(REAL alpha, const DOF_REAL_VEC *x, DOF_REAL_VEC *y)
{
  FUNCNAME("dof_axpy");
  REAL      *xvec, *yvec;
  const DOF_ADMIN *admin;

  TEST_EXIT(x && y, "pointer is nil: %p, %p\n", x,y);
  TEST_EXIT(x->fe_space && y->fe_space,
	    "fe_space is nil: %p, %p\n", x->fe_space,y->fe_space);
  TEST_EXIT((admin = x->fe_space->admin) && (admin == y->fe_space->admin),
	    "no admin or different admins: %p, %p\n",
	    x->fe_space->admin, y->fe_space->admin);
  TEST_EXIT(x->size >= admin->size_used,
	    "x->size = %d too small: admin->size_used = %d\n",
	    x->size, admin->size_used);
  TEST_EXIT(y->size >= admin->size_used,
	    "y->size = %d too small: admin->size_used = %d\n",
	    y->size, admin->size_used);

  xvec = x->vec;
  yvec = y->vec;

  FOR_ALL_DOFS(admin, yvec[dof] = xvec[dof] + alpha*yvec[dof]);
}
