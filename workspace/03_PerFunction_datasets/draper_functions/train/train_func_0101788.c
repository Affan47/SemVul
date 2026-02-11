findLightsAffectingFrustum(const Camera* camera)
    {


        MovableObjectCollection* lights =
            getMovableObjectCollection(PCZLightFactory::FACTORY_TYPE_NAME);


        {
                    OGRE_LOCK_MUTEX(lights->mutex);


            mTestLightInfos.clear();
            mTestLightInfos.reserve(lights->map.size());

            MovableObjectIterator it(lights->map.begin(), lights->map.end());

            while(it.hasMoreElements())
            {
                PCZLight* l = static_cast<PCZLight*>(it.getNext());
                if (l->isVisible() &&
                    l->affectsVisibleZone())
                {
                    LightInfo lightInfo;
                    lightInfo.light = l;
                    lightInfo.type = l->getType();
                    if (lightInfo.type == Light::LT_DIRECTIONAL)
                    {

                        lightInfo.position = Vector3::ZERO;
                        lightInfo.range = 0;
                        mTestLightInfos.push_back(lightInfo);
                    }
                    else
                    {


                        lightInfo.range = l->getAttenuationRange();
                        lightInfo.position = l->getDerivedPosition();
                        Sphere sphere(lightInfo.position, lightInfo.range);
                        if (camera->isVisible(sphere))
                        {
                            mTestLightInfos.push_back(lightInfo);
                        }
                    }
                }
            }
        }


        if (mCachedLightInfos != mTestLightInfos)
        {
            mLightsAffectingFrustum.resize(mTestLightInfos.size());
            LightInfoList::const_iterator i;
            LightList::iterator j = mLightsAffectingFrustum.begin();
            for (i = mTestLightInfos.begin(); i != mTestLightInfos.end(); ++i, ++j)
            {
                *j = i->light;

                if (isShadowTechniqueTextureBased())
                {
                    (*j)->_calcTempSquareDist(camera->getDerivedPosition());
                }
            }


            if (isShadowTechniqueTextureBased())
            {


                bool overridden = false;
                for (ListenerList::reverse_iterator ri = mListeners.rbegin();
                    ri != mListeners.rend(); ++ri)
                {
                    overridden = (*ri)->sortLightsAffectingFrustum(mLightsAffectingFrustum);
                    if (overridden)
                        break;
                }
                if (!overridden)
                {

                    std::stable_sort(
                        mLightsAffectingFrustum.begin(), mLightsAffectingFrustum.end(),
                        lightsForShadowTextureLess());
                }

            }


            mCachedLightInfos.swap(mTestLightInfos);


            _notifyLightsDirty();
        }

    }
