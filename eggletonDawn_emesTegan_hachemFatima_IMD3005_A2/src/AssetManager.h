#pragma once

#include "ofMain.h"

namespace AssetManager_Assets
{
    //obstacles
    static const string ASSET_LOC_ASTEROID_L = "obstacles/asteroid_large.png";
    static const string ASSET_LOC_ASTEROID_S = "obstacles/asteroid_small.png";
    static const string ASSET_LOC_SPACEJUNK = "obstacles/spacejunk.png";

    //collectibles
    static const string ASSET_LOC_MOUSE = "items/mouse.png";
    static const string ASSET_LOC_FISH = "items/fish.png";
    static const string ASSET_LOC_PIZZA = "items/pizza.png";
    static const string ASSET_LOC_POPTART = "items/poptart.png";

    //player controlled character
    static const string ASSET_LOC_SPACECAT = "spaceCat.png";
    static const string ASSET_LOC_LASERBEAM = "laserBeam.png";

};

class AssetManager
{
private:

    // vector is found in the std C++ library
    // vector is a dynamic array in C++
    // < > are like a template

    vector<ofImage>      m_images;
    bool                 m_loaded;

    // private + the singleton so that we only create one instance of an Asset Manager
    AssetManager() {
        m_loaded = false;
    }
public:

    // type def is strongly defined
    typedef enum {
        IMAGE_ASTEROID_L,
        IMAGE_ASTEROID_S,
        IMAGE_SPACEJUNK,
        IMAGE_MOUSE,
        IMAGE_FISH,
        IMAGE_PIZZA,
        IMAGE_POPTART,
        IMAGE_SPACECAT,
        IMAGE_LASERBEAM,
        NUM_IMAGES
    } ASSET_IMAGE;


    // singleton - class that is only created once
    static AssetManager * getInstance() {
        static AssetManager instance;
        return &instance;
    }

    void setup()
    {
        if (!m_loaded) {

            //load in ASSETS
            for (int i = 0; i < ASSET_IMAGE::NUM_IMAGES; ++i) {
                m_images.push_back(ofImage());
            }

            //obstacles
            m_images[IMAGE_ASTEROID_L].load(AssetManager_Assets::ASSET_LOC_ASTEROID_L);
            m_images[IMAGE_ASTEROID_S].load(AssetManager_Assets::ASSET_LOC_ASTEROID_S);
            m_images[IMAGE_SPACEJUNK].load(AssetManager_Assets::ASSET_LOC_SPACEJUNK);

            //items
            m_images[IMAGE_MOUSE].load(AssetManager_Assets::ASSET_LOC_MOUSE);
            m_images[IMAGE_FISH].load(AssetManager_Assets::ASSET_LOC_FISH);
            m_images[IMAGE_PIZZA].load(AssetManager_Assets::ASSET_LOC_PIZZA);
            m_images[IMAGE_POPTART].load(AssetManager_Assets::ASSET_LOC_POPTART);

            //player
            m_images[IMAGE_SPACECAT].load(AssetManager_Assets::ASSET_LOC_SPACECAT);
            m_images[IMAGE_LASERBEAM].load(AssetManager_Assets::ASSET_LOC_LASERBEAM);

            // state that all assets have been loaded
            m_loaded = true;
        }
    }

    // returns a pointer to the image because you don't want multiple copies
    ofImage * getImage(ASSET_IMAGE index)
    {
        return &m_images[(int)index];
    }

};

// singletons are not good for multithreaded performances
#pragma once
