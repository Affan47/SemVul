LoadEffectParameterMatrix(FCDObject* object, xmlNode* parameterNode)
{
	if (!FArchiveXML::LoadEffectParameter(object, parameterNode)) return false;

	bool status = true;
	FCDEffectParameterMatrix* effectParameterMatrix = (FCDEffectParameterMatrix*)object;
	xmlNode* valueNode = FindChildByType(parameterNode, DAE_FXCMN_FLOAT4X4_ELEMENT);
	if (valueNode == NULL)
	{
		valueNode = FindChildByType(parameterNode, DAE_FXCMN_HALF4X4_ELEMENT);
		effectParameterMatrix->SetFloatType(FCDEffectParameterMatrix::HALF);
	}
	else effectParameterMatrix->SetFloatType(FCDEffectParameterMatrix::FLOAT);

	const char* valueString = ReadNodeContentDirect(valueNode);
	if (valueString == NULL || *valueString == 0)
	{

		FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_BAD_MATRIX, parameterNode->line);
	}
	FUStringConversion::ToMatrix(valueString, effectParameterMatrix->GetValue());
	effectParameterMatrix->SetDirtyFlag();
	return status;
}
