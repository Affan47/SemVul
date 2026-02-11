exquopos (const cl_I& x, const cl_I& y)
{


  var cl_I_div_t q_r = cl_divide(x,y);
  if (!zerop(q_r.remainder)) { throw exquo_exception(x,y); }
  return q_r.quotient;
}

}
