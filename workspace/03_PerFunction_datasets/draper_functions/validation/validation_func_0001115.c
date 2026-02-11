feat_supports_lighting(int feat)
{

	if (use_graphics == GRAPHICS_PSEUDO) return FALSE;

	if ((use_graphics != GRAPHICS_DAVID_GERVAIS) &&
	    (feat >= FEAT_TRAP_HEAD) && (feat <= FEAT_TRAP_TAIL))
	{
		return TRUE;
	}

	switch (feat)
	{
		case FEAT_FLOOR:
		case FEAT_INVIS:
		case FEAT_SECRET:
		case FEAT_MAGMA:
		case FEAT_QUARTZ:
		case FEAT_MAGMA_H:
		case FEAT_QUARTZ_H:
		case FEAT_WALL_EXTRA:
		case FEAT_WALL_INNER:
		case FEAT_WALL_OUTER:
		case FEAT_WALL_SOLID:
		case FEAT_PERM_EXTRA:
		case FEAT_PERM_INNER:
		case FEAT_PERM_OUTER:
		case FEAT_PERM_SOLID:
			return TRUE;
		default:
			return FALSE;
	}
}
