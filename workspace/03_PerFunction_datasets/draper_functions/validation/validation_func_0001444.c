deleteMaterialRenders()
{

	for (u32 i=0; i<MaterialRenderers.size(); ++i)
		if (MaterialRenderers[i].Renderer)
			MaterialRenderers[i].Renderer->drop();

	MaterialRenderers.clear();
}
