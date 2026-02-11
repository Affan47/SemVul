deregister_factory (Factory* url_factory)
      {
        if (factories_ && url_factory)
          {
            factories_->unbind (url_factory->protocol ());
          };
      }
