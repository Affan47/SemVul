lwgeom_size(const uchar *serialized_form)
{
	uchar type = lwgeom_getType((uchar) serialized_form[0]);
	int t;
	const uchar *loc;
	uint32 ngeoms;
	int sub_size;
	int result = 1;

	LWDEBUG(2, "lwgeom_size called");

	if (type == POINTTYPE)
	{
		LWDEBUG(3, "lwgeom_size: is a point");

		return lwgeom_size_point(serialized_form);
	}
	else if (type == LINETYPE)
	{
		LWDEBUG(3, "lwgeom_size: is a line");

		return lwgeom_size_line(serialized_form);
	}
        else if(type == CIRCSTRINGTYPE)
        {
                LWDEBUG(3, "lwgeom_size: is a circularstring");

                return lwgeom_size_circstring(serialized_form);
        }
	else if (type == POLYGONTYPE)
	{
		LWDEBUG(3, "lwgeom_size: is a polygon");

		return lwgeom_size_poly(serialized_form);
	}
        else if (type == COMPOUNDTYPE)
        {
                LWDEBUG(3, "lwgeom_size: is a compound curve");
        }

	if ( type == 0 )
	{
		lwerror("lwgeom_size called with unknown-typed serialized geometry");
		return 0;
	}


	LWDEBUGF(3, "lwgeom_size called on a geoemtry with type %d", type);

	loc = serialized_form+1;

	if (lwgeom_hasBBOX((uchar) serialized_form[0]))
	{
		LWDEBUG(3, "lwgeom_size: has bbox");

		loc += sizeof(BOX2DFLOAT4);
		result +=sizeof(BOX2DFLOAT4);
	}

	if (lwgeom_hasSRID( (uchar) serialized_form[0]) )
	{
		LWDEBUG(3, "lwgeom_size: has srid");

		result +=4;
		loc +=4;
	}


	ngeoms = lw_get_uint32(loc);
	loc +=4;
	result += 4;

	LWDEBUGF(3, "lwgeom_size called on a geoemtry with %d elems (result so far: %d)", ngeoms, result);

	for (t=0;t<ngeoms;t++)
	{
		sub_size = lwgeom_size(loc);

		LWDEBUGF(3, " subsize %d", sub_size);

		loc += sub_size;
		result += sub_size;
	}

	LWDEBUGF(3, "lwgeom_size returning %d", result);

	return result;
}
