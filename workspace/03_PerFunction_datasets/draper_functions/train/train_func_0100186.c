_notifyAnimationStateEnabled(AnimationState* target, bool enabled)
    {
        OGRE_LOCK_AUTO_MUTEX;

        mEnabledAnimationStates.remove(target);


        if (enabled)
        {
            mEnabledAnimationStates.push_back(target);
        }


        _notifyDirty();
    }
