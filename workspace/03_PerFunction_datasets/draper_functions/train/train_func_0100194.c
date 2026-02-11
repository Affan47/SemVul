example_helloworld()
{

	IrrlichtDevice *device = startup();
	if (device == 0)
		return 1;

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );


	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
	}


	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	EventReceiver_basic receiver(device);
	device->setEventReceiver(&receiver);

	return run ( device );

}
