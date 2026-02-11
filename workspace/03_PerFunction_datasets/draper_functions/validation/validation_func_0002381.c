get(std::list<PluginDesc>& descs) {
      for(std::list<ARCPluginDescriptor>::const_iterator desc =
                descriptors.begin(); desc != descriptors.end(); ++desc) {
        PluginDesc pd;
        pd.name = desc->name;
        pd.kind = desc->kind;
        pd.description = desc->description;
        pd.version = desc->version;
        pd.priority = desc->priority;
        descs.push_back(pd);
      };
    }
