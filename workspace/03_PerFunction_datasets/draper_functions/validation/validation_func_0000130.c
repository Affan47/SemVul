isCompatible(const GeometryInfo& gi) const
	{
		bool res=true;


		res=res && (m_pImpl->m_periodicDimensions[0]==gi.m_pImpl->m_periodicDimensions[0])
			&& (m_pImpl->m_periodicDimensions[1]==gi.m_pImpl->m_periodicDimensions[1])
			&& (m_pImpl->m_periodicDimensions[2]==gi.m_pImpl->m_periodicDimensions[2]);


		if(m_pImpl->m_periodicDimensions[0]) {
			res = res && (m_pImpl->m_bBoxMin[0]==gi.m_pImpl->m_bBoxMin[0])
				&& (m_pImpl->m_bBoxMax[0]==gi.m_pImpl->m_bBoxMax[0]);
		} else {
			res = res && (m_pImpl->m_bBoxMin[0]<=gi.m_pImpl->m_bBoxMin[0])
				&& (m_pImpl->m_bBoxMax[0]>=gi.m_pImpl->m_bBoxMax[0]);
		}

 		if(m_pImpl->m_periodicDimensions[1]) {
			res = res && (m_pImpl->m_bBoxMin[1]==gi.m_pImpl->m_bBoxMin[1])
				&& (m_pImpl->m_bBoxMax[1]==gi.m_pImpl->m_bBoxMax[1]);
		} else {
			res = res && (m_pImpl->m_bBoxMin[1]<=gi.m_pImpl->m_bBoxMin[1])
				&& (m_pImpl->m_bBoxMax[1]>=gi.m_pImpl->m_bBoxMax[1]);
		}

		if(m_pImpl->m_periodicDimensions[2]) {
			res = res && (m_pImpl->m_bBoxMin[2]==gi.m_pImpl->m_bBoxMin[2])
				&& (m_pImpl->m_bBoxMax[2]==gi.m_pImpl->m_bBoxMax[2]);
		} else {
			res = res && (m_pImpl->m_bBoxMin[2]<=gi.m_pImpl->m_bBoxMin[2])
				&& (m_pImpl->m_bBoxMax[2]>=gi.m_pImpl->m_bBoxMax[2]);
		}

		return res;
	}
