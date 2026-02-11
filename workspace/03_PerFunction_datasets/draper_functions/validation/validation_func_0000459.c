mob_getid(struct atomid *id,struct mobatom *atom)
{ int idpos,links,flags,inscodealtloc;

  links=mob_links(atom);
  flags=int32le(atom->link[links]);
  idpos=links+1;
  id->atom=atom->link[idpos++];
  id->resnamechain=atom->link[idpos++];
  id->resno=atom->link[idpos++];
  if (flags&MOB_INSCODEALTLOCFLAG)
  { inscodealtloc=int32le(atom->link[idpos++]);
    id->inscode=inscodealtloc&0xffff;
    id->altloc=inscodealtloc&0xffff; }
  else id->inscode=id->altloc=0;
  if (flags&MOB_OCCUPANCYFLAG) id->occupancy=((float*)atom->link)[idpos++];
  else id->occupancy=1.0f;
  if (flags&MOB_TEMPFACFLAG) id->bfactor=((float*)atom->link)[idpos++];
  else id->bfactor=0;
  if (flags&MOB_SEGMENTFLAG) id->segment=atom->link[idpos++];
  else id->segment=0;
  if (flags&MOB_PROPERTYFLAG) id->property=((float*)atom->link)[idpos++];
  else id->property=0;
  id->flags=flags&(MOB_SURFENVFLAG|MOB_DOTFLAG); }
