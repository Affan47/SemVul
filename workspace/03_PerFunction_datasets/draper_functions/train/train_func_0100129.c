SP_func_wall (edict_t * self)
{
  self->movetype = MOVETYPE_PUSH;
  gi.setmodel (self, self->model);

  if (self->spawnflags & 8)
    self->s.effects |= EF_ANIM_ALL;
  if (self->spawnflags & 16)
    self->s.effects |= EF_ANIM_ALLFAST;


  if ((self->spawnflags & 7) == 0)
    {
      self->solid = SOLID_BSP;
      gi.linkentity (self);
      return;
    }


  if (!(self->spawnflags & 1))
    {

      self->spawnflags |= 1;
    }


  if (self->spawnflags & 4)
    {
      if (!(self->spawnflags & 2))
	{
	  gi.dprintf ("func_wall START_ON without TOGGLE\n");
	  self->spawnflags |= 2;
	}
    }

  self->use = func_wall_use;
  if (self->spawnflags & 4)
    {
      self->solid = SOLID_BSP;
    }
  else
    {
      self->solid = SOLID_NOT;
      self->svflags |= SVF_NOCLIENT;
    }
  gi.linkentity (self);
}
