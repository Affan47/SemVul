infecthull(struct mesh *m, struct behavior *b)
#else
void infecthull(m, b)
struct mesh *m;
struct behavior *b;
#endif

{
  struct otri hulltri;
  struct otri nexttri;
  struct otri starttri;
  struct osub hullsubseg;
  triangle **deadtriangle;
  vertex horg, hdest;
  triangle ptr;
  subseg sptr;

  if (b->verbose) {
    printf("  Marking concavities (external triangles) for elimination.\n");
  }

  hulltri.tri = m->dummytri;
  hulltri.orient = 0;
  symself(hulltri);

  otricopy(hulltri, starttri);

  do {

    if (!infected(hulltri)) {

      tspivot(hulltri, hullsubseg);
      if (hullsubseg.ss == m->dummysub) {

        if (!infected(hulltri)) {
          infect(hulltri);
          deadtriangle = (triangle **) poolalloc(&m->viri);
          *deadtriangle = hulltri.tri;
        }
      } else {

        if (mark(hullsubseg) == 0) {
          setmark(hullsubseg, 1);
          org(hulltri, horg);
          dest(hulltri, hdest);
          if (vertexmark(horg) == 0) {
            setvertexmark(horg, 1);
          }
          if (vertexmark(hdest) == 0) {
            setvertexmark(hdest, 1);
          }
        }
      }
    }

    lnextself(hulltri);
    oprev(hulltri, nexttri);
    while (nexttri.tri != m->dummytri) {
      otricopy(nexttri, hulltri);
      oprev(hulltri, nexttri);
    }
  } while (!otriequal(hulltri, starttri));
}
