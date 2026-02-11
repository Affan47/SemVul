_initAnimationState(AnimationStateSet* animSet)
    {
        animSet->removeAllAnimationStates();

        AnimationList::iterator i;
        for (i = mAnimationsList.begin(); i != mAnimationsList.end(); ++i)
        {
            Animation* anim = i->second;

            const String& animName = anim->getName();
            animSet->createAnimationState(animName, 0.0, anim->getLength());
        }


        LinkedSkeletonAnimSourceList::iterator li;
        for (li = mLinkedSkeletonAnimSourceList.begin();
            li != mLinkedSkeletonAnimSourceList.end(); ++li)
        {
            if (!li->pSkeleton.isNull())
            {
                li->pSkeleton->_refreshAnimationState(animSet);
            }
        }

    }
