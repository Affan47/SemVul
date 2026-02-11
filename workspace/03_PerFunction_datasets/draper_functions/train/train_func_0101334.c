gather_ornaments_on_point (struct Bond *list, struct Ornament orns[],
	                   const unsigned int max, const LLINT x,
			   const LLINT y)
{
  struct Ornament * orn;
  struct Bond * current = list;
  unsigned int found = 0;
  int end;

  if (current == NULL)
    return 0;

  while (current != NULL)
  {
    if (current->type == BOND_GROUP)
    {
      found += gather_ornaments_on_point (current->group_members,
                                       	  &(orns[found]),
	                                  max - found, x, y);
      current = current->next;
      continue;
    }


    end = -1;
    if (BOND_HAS_TEXT (current))
    {
      if (IS_SMALL (current->x3 - x) && IS_SMALL (current->y3 - y))
        end = 0;
    }
    else
    {
      if (IS_SMALL (current->x1 - x) && IS_SMALL (current->y1 - y))
        end = 0;
      if (IS_SMALL (current->x2 - x) && IS_SMALL (current->y2 - y))
        end = 1;
    }


    if (end >= 0)
    {
      orn = current->ornaments[end];

      while (orn != NULL && found < max)
      {
	orns[found] = *orn;
	found++;
	orn = orn->next;
      }
    }

    current = current->next;
  }

  return found;
}
