emit_gev_trace(struct gate_t *gp, struct tev_t *tevp)
{
 char s1[RECLEN], s2[RECLEN], vs1[10];

 __evtr_resume_msg();
 if (gp->gpins[0]->x_multfi) strcpy(s2, "this driver of multiple:");
 else strcpy(s2, "the fi=1 driver:");
 __tr_msg("-- %s gate %s processing store event to output, %s %s\n",
  gp->gmsym->synam, to_evtronam(s1, gp->gsym->synam, tevp->teitp,
  (struct task_t *) NULL), s2, __to_gonam(vs1, gp, __new_gateval));
}
