PreviewPropertiesList PreviewManager::getPreviewProperties() const
    {
        PreviewPropertiesList list;

        for (PreviewId id = 0; id < Loader::getNumLoaders(); ++id) {
            Loader::UniquePtr loader = Loader::create(id, image_);
            if (loader.get() && loader->readDimensions()) {
                PreviewProperties props = loader->getProperties();
                DataBuf buf             = loader->getData();
                props.size_             = (uint32_t)buf.size_;
                list.push_back(props) ;
            }
        }
        std::sort(list.begin(), list.end(), cmpPreviewProperties);
        return list;
    }
