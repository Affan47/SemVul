isCameraInsideLight(Ogre::Camera* camera)
{
    switch (mParentLight->getType())
    {
    case Ogre::Light::LT_DIRECTIONAL:
        return false;
    case Ogre::Light::LT_POINT:
        {
        Ogre::Real distanceFromLight = camera->getDerivedPosition()
            .distance(mParentLight->getDerivedPosition());

        return distanceFromLight <= mRadius + camera->getNearClipDistance() + 0.1;
        }
    case Ogre::Light::LT_SPOTLIGHT:
        {
        Ogre::Vector3 lightPos = mParentLight->getDerivedPosition();
        Ogre::Vector3 lightDir = mParentLight->getDerivedDirection();
        Ogre::Radian attAngle = mParentLight->getSpotlightOuterAngle();


        Ogre::Vector3 clipRangeFix = -lightDir * (camera->getNearClipDistance() / Ogre::Math::Tan(attAngle/2));
        lightPos = lightPos + clipRangeFix;

        Ogre::Vector3 lightToCamDir = camera->getDerivedPosition() - lightPos;
        Ogre::Real distanceFromLight = lightToCamDir.normalise();

        Ogre::Real cosAngle = lightToCamDir.dotProduct(lightDir);
        Ogre::Radian angle = Ogre::Math::ACos(cosAngle);

        return (distanceFromLight <= (mParentLight->getAttenuationRange() / cosAngle + clipRangeFix.length()))
            && (angle <= attAngle);
        }
    default:

        return false;
    }
}
