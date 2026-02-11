init()
{
  dtv = update->dt;
  dtf = 0.5 * update->dt * force->ftm2v;

  if (strstr(update->integrate_style,"respa"))
    step_respa = ((Respa *) update->integrate)->step;
}
