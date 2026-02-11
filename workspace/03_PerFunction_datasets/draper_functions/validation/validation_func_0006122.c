RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
								const b2Transform& xf, int32 childIndex) const
{
	B2_NOT_USED(childIndex);


	b2Vec2 p1 = b2MulT(xf.R, input.p1 - xf.position);
	b2Vec2 p2 = b2MulT(xf.R, input.p2 - xf.position);
	b2Vec2 d = p2 - p1;

	qreal lower = 0.0f, upper = input.maxFraction;

	int32 index = -1;

	for (int32 i = 0; i < m_vertexCount; ++i)
	{


		qreal numerator = b2Dot(m_normals[i], m_vertices[i] - p1);
		qreal denominator = b2Dot(m_normals[i], d);

		if (denominator == 0.0f)
		{
			if (numerator < 0.0f)
			{
				return false;
			}
		}
		else
		{


			if (denominator < 0.0f && numerator < lower * denominator)
			{


				lower = numerator / denominator;
				index = i;
			}
			else if (denominator > 0.0f && numerator < upper * denominator)
			{


				upper = numerator / denominator;
			}
		}


		if (upper < lower)
		{
			return false;
		}
	}

	b2Assert(0.0f <= lower && lower <= input.maxFraction);

	if (index >= 0)
	{
		output->fraction = lower;
		output->normal = b2Mul(xf.R, m_normals[index]);
		return true;
	}

	return false;
}
