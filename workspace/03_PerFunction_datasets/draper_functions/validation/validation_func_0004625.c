train_use (edict_t * self, edict_t * other, edict_t * activator)
{
  self->activator = activator;

  if (self->spawnflags & TRAIN_START_ON)
    {
      if (!(self->spawnflags & TRAIN_TOGGLE))
	return;
      self->spawnflags &= ~TRAIN_START_ON;
      VectorClear (self->velocity);
      self->nextthink = 0;
    }
  else
    {
      if (self->target_ent)
	train_resume (self);
      else
	train_next (self);
    }
}
