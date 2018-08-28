#include "SaveManager.h"

#include "ostream"
#include "fstream"

#include "iostream"
using namespace std;

#include "tinyxml2.h"
using namespace tinyxml2;

bool SaveManager::init() {
    XMLDocument file;

    bool defaultSave = false;

    // Loads save.xml file
    // If there isn't save.xml, load save_default.xml and create
    // new save.xml based on save_default
    if( file.LoadFile( "media/data/save.xml" ) != XML_NO_ERROR ) {
        if( file.LoadFile( "media/data/save_default.xml" ) != XML_NO_ERROR ) {
            cout << "Loading save file failed" << endl;
            return false;
        }
        else {
            defaultSave = true;

            cout << "Creating save file from default." << endl;

            // Duplicate save_default.xml file
            ifstream src( "media/data/save_default.xml", ios::binary );
            ofstream dst( "media/data/save.xml", ios::binary );

            dst << src.rdbuf();
        }
    }

    // If new save.xml was created, load it
    if( defaultSave ) {
        if( file.LoadFile( "media/data/save.xml" ) != XML_NO_ERROR ) {

            // In case something went wrong, return false
            cout << "Creating save file failed." << endl;
            return false;
        }
    }


    XMLElement* setElement = file.FirstChildElement( "settings" );

    if( setElement == NULL ) {
        cout << "Settings element is missing." << endl;
        return false;
    }
    else {
        XMLElement* resElement = setElement->FirstChildElement( "resolution" );

        if( resElement == NULL ) {
            m_svData.res_w = 1280;
            m_svData.res_h = 720;
        }
        else {
            m_svData.res_w = resElement->IntAttribute( "w" );
            m_svData.res_h = resElement->IntAttribute( "h" );
        }

        XMLElement* vscElement = setElement->FirstChildElement( "vsync" );

        if( vscElement == NULL ) {
            m_svData.vsync = true;
        }
        else {
            m_svData.vsync = vscElement->BoolAttribute( "on" );
        }
    }

    XMLElement* gmElement = file.FirstChildElement( "game" );

    if( gmElement == NULL ) {
        cout << "Game element is missing" << endl;
        return false;
    }
    else {
        XMLElement* plElement = gmElement->FirstChildElement( "player" );

        if( plElement == NULL ) {
            m_pLv = 0;
            m_exp = 0;
        }
        else {
            m_pLv = plElement->IntAttribute( "lv" );
            m_exp = plElement->IntAttribute( "exp" );
        }

        XMLElement* lvElement = gmElement->FirstChildElement( "levels" )->FirstChildElement();

        if( lvElement == NULL ) {
            cout << "There are no level elements" << endl;
            return false;
        }
        else {
            while( lvElement != NULL ) {
                m_lvData.push_back( Level_data() );
                m_lvData.back().id          = lvElement->IntAttribute( "id" );
                m_lvData.back().path        = lvElement->Attribute( "path" );
                m_lvData.back().unlocked    = lvElement->BoolAttribute( "unlocked" );
                m_lvData.back().defeated    = lvElement->BoolAttribute( "defeated" );

                lvElement = lvElement->NextSiblingElement();
            }
        }

        XMLElement* tlElement = gmElement->FirstChildElement( "talents" )->FirstChildElement();

        if( tlElement == NULL ) {
            cout << "There are no talent elements" << endl;
            return false;
        }
        else {
            while( tlElement != NULL ) {
                m_tlData.push_back( Talent_data() );
                m_tlData.back().amount = tlElement->IntAttribute( "amount" );

                tlElement = tlElement->NextSiblingElement();
            }
        }
    }

    return true;
}

bool SaveManager::saveSettings() {
    XMLDocument file;

    if( file.LoadFile( "media/data/save.xml" ) != XML_NO_ERROR ) {
        cout << "Saving settings failed" << endl;
        return false;
    }

    XMLElement* setElement = file.FirstChildElement( "settings" );

    XMLElement* resElement = setElement->FirstChildElement( "resolution" );
    resElement->SetAttribute( "w", m_svData.res_w );
    resElement->SetAttribute( "h", m_svData.res_h );

    XMLElement* vscElement = setElement->FirstChildElement( "vsync" );
    vscElement->SetAttribute( "on", m_svData.vsync );

    file.SaveFile( "media/data/save.xml" );

    return true;
}

bool SaveManager::saveGame() {
    XMLDocument file;

    if( file.LoadFile( "media/data/save.xml" ) != XML_NO_ERROR ) {
        cout << "Saving game failed" << endl;
        return false;
    }

    XMLElement* gmElement = file.FirstChildElement( "game" );

    XMLElement* plElement = gmElement->FirstChildElement( "player" );
    plElement->SetAttribute( "lv", m_pLv );
    plElement->SetAttribute( "exp", m_exp );

    XMLElement* lvElement = gmElement->FirstChildElement( "levels" )->FirstChildElement();
    while( lvElement != NULL ) {
        int index = lvElement->UnsignedAttribute( "id" );

        lvElement->SetAttribute( "unlocked", m_lvData[ index ].unlocked );
        lvElement->SetAttribute( "defeated", m_lvData[ index ].defeated );

        lvElement = lvElement->NextSiblingElement();
    }

    file.SaveFile( "media/data/save.xml" );

    return true;
}

bool SaveManager::saveTalents() {
    XMLDocument file;

    if( file.LoadFile( "media/data/save.xml" ) != XML_NO_ERROR ) {
        cout << "Saving talents failed" << endl;
        return false;
    }

    XMLElement* gmElement = file.FirstChildElement( "game" );

    XMLElement* tlElement = gmElement->FirstChildElement( "talents" )->FirstChildElement();
    while( tlElement != NULL ) {
        int index = tlElement->UnsignedAttribute( "id" );
        tlElement->SetAttribute( "amount", m_tlData[ index ].amount );

        tlElement = tlElement->NextSiblingElement();
    }

    file.SaveFile( "media/data/save.xml" );

    return true;
}
