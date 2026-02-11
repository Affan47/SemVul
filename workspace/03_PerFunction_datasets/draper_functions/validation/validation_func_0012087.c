CL_BubbleTrail (vec3_t start, vec3_t end)
{
	vec3_t		move;
	vec3_t		vec;
	float		len;
	int			i, j;
	particle_t	*p;
	float		dec;

	VectorCopy (start, move);
	VectorSubtract (end, start, vec);
	len = VectorNormalize (vec);

	dec = 32;
	VectorScale (vec, dec, vec);

	for (i=0 ; i<len ; i+=dec)
	{
		if (!(p = new_particle()))
			return;

		VectorClear (p->accel);

		p->alpha = 1.0;
		p->alphavel = -1.0 / (1+frand()*0.2);
		p->color = 4 + (rand()&7);
		p->type = PARTICLE_STANDARD;
		p->image = r_bubbletexture;
		p->scale = 2 + (rand()&2);
		p->blendsrc = GL_SRC_ALPHA;
		p->blenddst = GL_ONE_MINUS_SRC_ALPHA;

		for (j=0 ; j<3 ; j++)
		{
			p->org[j] = move[j] + crand()*2;
			p->vel[j] = crand()*5;
		}
		p->vel[2] += 6;

		VectorAdd (move, vec, move);
	}
}
