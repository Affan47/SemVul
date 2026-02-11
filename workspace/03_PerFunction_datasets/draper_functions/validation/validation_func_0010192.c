locate_endpoint (pointf *v, pointf *vo, int r, segment_t* seg, qnode_t* qs)
{
  qnode_t *rptr = &qs[r];

  switch (rptr->nodetype) {
    case T_SINK:
      return rptr->trnum;

    case T_Y:
      if (_greater_than(v, &rptr->yval))
	return locate_endpoint(v, vo, rptr->right, seg, qs);
      else if (_equal_to(v, &rptr->yval))
	{
	  if (_greater_than(vo, &rptr->yval))
	    return locate_endpoint(v, vo, rptr->right, seg, qs);
	  else
	    return locate_endpoint(v, vo, rptr->left, seg, qs);
	}
      else
	return locate_endpoint(v, vo, rptr->left, seg, qs);

    case T_X:
      if (_equal_to(v, &seg[rptr->segnum].v0) ||
	       _equal_to(v, &seg[rptr->segnum].v1))
	{
	  if (FP_EQUAL(v->y, vo->y))
	    {
	      if (vo->x < v->x)
		return locate_endpoint(v, vo, rptr->left, seg, qs);
	      else
		return locate_endpoint(v, vo, rptr->right, seg, qs);
	    }

	  else if (is_left_of(rptr->segnum, seg, vo))
	    return locate_endpoint(v, vo, rptr->left, seg, qs);
	  else
	    return locate_endpoint(v, vo, rptr->right, seg, qs);
	}
      else if (is_left_of(rptr->segnum, seg, v))
	return locate_endpoint(v, vo, rptr->left, seg, qs);
      else
	return locate_endpoint(v, vo, rptr->right, seg, qs);

    default:
      fprintf(stderr, "unexpected case in locate_endpoint\n");
      assert (0);
      break;
    }
    return 1;
}
