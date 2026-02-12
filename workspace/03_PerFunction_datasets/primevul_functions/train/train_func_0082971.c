mpi_powm( MPI res, MPI base, MPI exponent, MPI mod)
{
    mpi_ptr_t  rp, ep, mp, bp;
    mpi_size_t esize, msize, bsize, rsize;
    int               msign, bsign, rsign;
    int        esec,  msec,  bsec,  rsec;
    mpi_size_t size;
    int mod_shift_cnt;
    int negative_result;
    mpi_ptr_t mp_marker=NULL, bp_marker=NULL, ep_marker=NULL;
    mpi_ptr_t xp_marker=NULL;
    int assign_rp=0;
    mpi_ptr_t tspace = NULL;
    mpi_size_t tsize=0;


    esize = exponent->nlimbs;
    msize = mod->nlimbs;
    size = 2 * msize;
    msign = mod->sign;

    esec = mpi_is_secure(exponent);
    msec = mpi_is_secure(mod);
    bsec = mpi_is_secure(base);
    rsec = mpi_is_secure(res);

    rp = res->d;
    ep = exponent->d;

    if( !msize )
	msize = 1 / msize;

    if( !esize ) {


	rp[0] = 1;
	res->nlimbs = (msize == 1 && mod->d[0] == 1) ? 0 : 1;
	res->sign = 0;
	goto leave;
    }


    mp = mp_marker = mpi_alloc_limb_space(msize, msec);
    count_leading_zeros( mod_shift_cnt, mod->d[msize-1] );
    if( mod_shift_cnt )
	mpihelp_lshift( mp, mod->d, msize, mod_shift_cnt );
    else
	MPN_COPY( mp, mod->d, msize );

    bsize = base->nlimbs;
    bsign = base->sign;
    if( bsize > msize ) {


	bp = bp_marker = mpi_alloc_limb_space( bsize + 1, bsec );
	MPN_COPY( bp, base->d, bsize );


	mpihelp_divrem( bp + msize, 0, bp, bsize, mp, msize );
	bsize = msize;


	MPN_NORMALIZE( bp, bsize );
    }
    else
	bp = base->d;

    if( !bsize ) {
	res->nlimbs = 0;
	res->sign = 0;
	goto leave;
    }

    if( res->alloced < size ) {


	if( rp == ep || rp == mp || rp == bp ) {
	    rp = mpi_alloc_limb_space( size, rsec );
	    assign_rp = 1;
	}
	else {
	    mpi_resize( res, size );
	    rp = res->d;
	}
    }
    else {
	if( rp == bp ) {

	    assert( !bp_marker );
	    bp = bp_marker = mpi_alloc_limb_space( bsize, bsec );
	    MPN_COPY(bp, rp, bsize);
	}
	if( rp == ep ) {


	    ep = ep_marker = mpi_alloc_limb_space( esize, esec );
	    MPN_COPY(ep, rp, esize);
	}
	if( rp == mp ) {

	    assert( !mp_marker );
	    mp = mp_marker = mpi_alloc_limb_space( msize, msec );
	    MPN_COPY(mp, rp, msize);
	}
    }

    MPN_COPY( rp, bp, bsize );
    rsize = bsize;
    rsign = bsign;

    {
	mpi_size_t i;
	mpi_ptr_t xp = xp_marker = mpi_alloc_limb_space( 2 * (msize + 1), msec );
	int c;
	mpi_limb_t e;
	mpi_limb_t carry_limb;
	struct karatsuba_ctx karactx;

	memset( &karactx, 0, sizeof karactx );
	negative_result = (ep[0] & 1) && base->sign;

	i = esize - 1;
	e = ep[i];
	count_leading_zeros (c, e);
	e = (e << c) << 1;
	c = BITS_PER_MPI_LIMB - 1 - c;


	for(;;) {
	    while( c ) {
		mpi_ptr_t tp;
		mpi_size_t xsize;


		if( rsize < KARATSUBA_THRESHOLD )
		    mpih_sqr_n_basecase( xp, rp, rsize );
		else {
		    if( !tspace ) {
			tsize = 2 * rsize;
			tspace = mpi_alloc_limb_space( tsize, 0 );
		    }
		    else if( tsize < (2*rsize) ) {
			mpi_free_limb_space( tspace );
			tsize = 2 * rsize;
			tspace = mpi_alloc_limb_space( tsize, 0 );
		    }
		    mpih_sqr_n( xp, rp, rsize, tspace );
		}

		xsize = 2 * rsize;
		if( xsize > msize ) {
		    mpihelp_divrem(xp + msize, 0, xp, xsize, mp, msize);
		    xsize = msize;
		}

		tp = rp; rp = xp; xp = tp;
		rsize = xsize;

		if( (mpi_limb_signed_t)e < 0 ) {

		    if( bsize < KARATSUBA_THRESHOLD ) {
			mpihelp_mul( xp, rp, rsize, bp, bsize );
		    }
		    else {
			mpihelp_mul_karatsuba_case(
				     xp, rp, rsize, bp, bsize, &karactx );
		    }

		    xsize = rsize + bsize;
		    if( xsize > msize ) {
			mpihelp_divrem(xp + msize, 0, xp, xsize, mp, msize);
			xsize = msize;
		    }

		    tp = rp; rp = xp; xp = tp;
		    rsize = xsize;
		}
		e <<= 1;
		c--;
	    }

	    i--;
	    if( i < 0 )
		break;
	    e = ep[i];
	    c = BITS_PER_MPI_LIMB;
	}


	if( mod_shift_cnt ) {
	    carry_limb = mpihelp_lshift( res->d, rp, rsize, mod_shift_cnt);
	    rp = res->d;
	    if( carry_limb ) {
		rp[rsize] = carry_limb;
		rsize++;
	    }
	}
	else {
	    MPN_COPY( res->d, rp, rsize);
	    rp = res->d;
	}

	if( rsize >= msize ) {
	    mpihelp_divrem(rp + msize, 0, rp, rsize, mp, msize);
	    rsize = msize;
	}


	if( mod_shift_cnt )
	    mpihelp_rshift( rp, rp, rsize, mod_shift_cnt);
	MPN_NORMALIZE (rp, rsize);

	mpihelp_release_karatsuba_ctx( &karactx );
    }

    if( negative_result && rsize ) {
	if( mod_shift_cnt )
	    mpihelp_rshift( mp, mp, msize, mod_shift_cnt);
	mpihelp_sub( rp, mp, msize, rp, rsize);
	rsize = msize;
	rsign = msign;
	MPN_NORMALIZE(rp, rsize);
    }
    res->nlimbs = rsize;
    res->sign = rsign;

  leave:
    if( assign_rp ) mpi_assign_limb_space( res, rp, size );
    if( mp_marker ) mpi_free_limb_space( mp_marker );
    if( bp_marker ) mpi_free_limb_space( bp_marker );
    if( ep_marker ) mpi_free_limb_space( ep_marker );
    if( xp_marker ) mpi_free_limb_space( xp_marker );
    if( tspace )    mpi_free_limb_space( tspace );
}
