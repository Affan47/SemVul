ProjectAtoms_ (MolComplexS *mol_complexSP, int mol_complexesN,
		      ConfigS *configSP)
{
static size_t		projected_atomsN = 0;
static int		mol_complexI;
static int		imagesN, imageI;
static MolComplexS	*curr_mol_complexSP;
static double		nominator_x, nominator_y, user_atomic_position;
static double		x0, y0, z0, x1, y1;
static int		center_screen_x[2], center_screen_y;
static size_t		atomsN, atomI;
static AtomS		*curr_atomSP;
static double		denominator, reciprocal_denominator;
static double		rationalized_x, rationalized_y = 0;


if (configSP->stereoF == 1) imagesN = 2;
else imagesN = 1;


nominator_x = configSP->user_screen_atomic_distance *
	      configSP->atomic_to_screen_scale_x;
nominator_y = configSP->user_screen_atomic_distance *
	      configSP->atomic_to_screen_scale_y;


user_atomic_position = configSP->user_atomic_position;


x0 = configSP->rationalized_x0;
y0 = configSP->rationalized_y0;
x1 = configSP->rationalized_x1;
y1 = configSP->rationalized_y1;
z0 = configSP->win_atomic_z0;


center_screen_x[0] = configSP->center_screen_x[0];
center_screen_x[1] = configSP->center_screen_x[1];
center_screen_y = configSP->center_screen_y;


for (mol_complexI = 0; mol_complexI < mol_complexesN; mol_complexI++)
	{

	curr_mol_complexSP = mol_complexSP + mol_complexI;


	if (curr_mol_complexSP->position_changedF == 0) continue;


	atomsN = curr_mol_complexSP->atomsN;
	for (atomI = 0; atomI < atomsN; atomI++)
		{

		curr_atomSP = curr_mol_complexSP->atomSP + atomI;


		for (imageI = 0; imageI < imagesN; imageI++)
			{

			denominator = curr_atomSP->raw_atomS.z[imageI] -
				      user_atomic_position;
			if (denominator == 0.0) continue;
			reciprocal_denominator = 1.0 / denominator;


			if (curr_atomSP->raw_atomS.z[imageI] < z0)
				{
				curr_atomSP->inside_windowF = 0;
				break;
				}


			rationalized_x = curr_atomSP->raw_atomS.x[imageI] *
					 nominator_x * reciprocal_denominator;
			rationalized_y = curr_atomSP->raw_atomS.y *
					 nominator_y * reciprocal_denominator;


			if (rationalized_x < x0)
				{
				curr_atomSP->inside_windowF = 0;
				break;
				}
			else if (rationalized_x > x1)
				{
				curr_atomSP->inside_windowF = 0;
				break;
				}
			else if (rationalized_y < y0)
				{
				curr_atomSP->inside_windowF = 0;
				break;
				}
			else if (rationalized_y > y1)
				{
				curr_atomSP->inside_windowF = 0;
				break;
				}
			else curr_atomSP->inside_windowF = 1;


			curr_atomSP->raw_atomS.screen_x[imageI] =
				(int) rationalized_x + center_screen_x[imageI];
			}


		if (curr_atomSP->inside_windowF == 0) continue;


		curr_atomSP->raw_atomS.screen_y =
				(int) rationalized_y + center_screen_y;


		projected_atomsN++;
		}
	}

return projected_atomsN;
}
