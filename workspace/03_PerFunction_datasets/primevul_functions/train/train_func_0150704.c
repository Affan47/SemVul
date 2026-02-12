add_points_edwards (mpi_point_t result,
                    mpi_point_t p1, mpi_point_t p2,
                    mpi_ec_t ctx)
{
#define X1 (p1->x)
#define Y1 (p1->y)
#define Z1 (p1->z)
#define X2 (p2->x)
#define Y2 (p2->y)
#define Z2 (p2->z)
#define X3 (result->x)
#define Y3 (result->y)
#define Z3 (result->z)
#define A (ctx->t.scratch[0])
#define B (ctx->t.scratch[1])
#define C (ctx->t.scratch[2])
#define D (ctx->t.scratch[3])
#define E (ctx->t.scratch[4])
#define F (ctx->t.scratch[5])
#define G (ctx->t.scratch[6])
#define tmp (ctx->t.scratch[7])


  ec_mulm (A, Z1, Z2, ctx);


  ec_pow2 (B, A, ctx);


  ec_mulm (C, X1, X2, ctx);


  ec_mulm (D, Y1, Y2, ctx);


  ec_mulm (E, ctx->b, C, ctx);
  ec_mulm (E, E, D, ctx);


  ec_subm (F, B, E, ctx);


  ec_addm (G, B, E, ctx);


  ec_addm (tmp, X1, Y1, ctx);
  ec_addm (X3, X2, Y2, ctx);
  ec_mulm (X3, X3, tmp, ctx);
  ec_subm (X3, X3, C, ctx);
  ec_subm (X3, X3, D, ctx);
  ec_mulm (X3, X3, F, ctx);
  ec_mulm (X3, X3, A, ctx);


  if (ctx->dialect == ECC_DIALECT_ED25519)
    {


      mpi_set (Y3, C);
      _gcry_mpi_neg (Y3, Y3);
      ec_subm (Y3, D, Y3, ctx);
    }
  else
    {
      ec_mulm (Y3, ctx->a, C, ctx);
      ec_subm (Y3, D, Y3, ctx);
    }
  ec_mulm (Y3, Y3, G, ctx);
  ec_mulm (Y3, Y3, A, ctx);


  ec_mulm (Z3, F, G, ctx);


#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef Z2
#undef X3
#undef Y3
#undef Z3
#undef A
#undef B
#undef C
#undef D
#undef E
#undef F
#undef G
#undef tmp
}
