SV_StepDirection (edict_t * ent, float yaw, float dist)
{
  vec3_t move, oldorigin;
  float delta;

  ent->ideal_yaw = yaw;
  M_ChangeYaw (ent);

  yaw = yaw * M_PI * 2 / 360;
  move[0] = cos (yaw) * dist;
  move[1] = sin (yaw) * dist;
  move[2] = 0;

  VectorCopy (ent->s.origin, oldorigin);
  if (SV_movestep (ent, move, false))
    {
      delta = ent->s.angles[YAW] - ent->ideal_yaw;
      if (delta > 45 && delta < 315)
	{
	  VectorCopy (oldorigin, ent->s.origin);
	}
      gi.linkentity (ent);
      G_TouchTriggers (ent);
      return true;
    }
  gi.linkentity (ent);
  G_TouchTriggers (ent);
  return false;
}
