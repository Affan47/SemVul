LSR_AttachScene(GF_SceneDecoder *plug, GF_Scene *scene, Bool is_scene_decoder)
{
	LSRPriv *priv = (LSRPriv *)plug->privateStack;
	if (priv->codec) return GF_BAD_PARAM;
	priv->pScene = scene;
	priv->app = scene->root_od->term;

	priv->codec = gf_laser_decoder_new(scene->graph);

	gf_laser_decoder_set_clock(priv->codec, gf_scene_get_time, scene);
	return GF_OK;
}
