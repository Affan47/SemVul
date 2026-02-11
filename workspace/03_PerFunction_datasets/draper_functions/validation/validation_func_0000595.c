getSquaredViewDepth(const Camera* cam) const
    {

        if (mParentNode)
            return (cam->getDerivedPosition()
                - mParentNode->_getDerivedPosition()).squaredLength();
        else
            return 0;
    }
