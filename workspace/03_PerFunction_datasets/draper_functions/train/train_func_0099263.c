dCollideSpherePlane (dxGeom *o1, dxGeom *o2, int flags,
			 dContactGeom *contact, int skip)
{
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dSphereClass);
  dIASSERT (o2->type == dPlaneClass);
  dIASSERT ((flags & NUMC_MASK) >= 1);

  dxSphere *sphere = (dxSphere*) o1;
  dxPlane *plane = (dxPlane*) o2;

  contact->g1 = o1;
  contact->g2 = o2;
  contact->side1 = -1;
  contact->side2 = -1;

  dReal k = dDOT (o1->final_posr->pos,plane->p);
  dReal depth = plane->p[3] - k + sphere->radius;
  if (depth >= 0) {
    contact->normal[0] = plane->p[0];
    contact->normal[1] = plane->p[1];
    contact->normal[2] = plane->p[2];
    contact->pos[0] = o1->final_posr->pos[0] - plane->p[0] * sphere->radius;
    contact->pos[1] = o1->final_posr->pos[1] - plane->p[1] * sphere->radius;
    contact->pos[2] = o1->final_posr->pos[2] - plane->p[2] * sphere->radius;
    contact->depth = depth;
    return 1;
  }
  else return 0;
}
