#include "stdafx.h"
#include "CaptionConfig.h"
#include "tinyxml/tinyxml.h"

#define	XML_CAPTION_CONFIG_FILENAME "CaptionConfig.xml"

CCaptionConfig* CCaptionConfig::m_thisCap = NULL;

CCaptionConfig* CCaptionConfig::GetInstance()
{
    if (NULL == m_thisCap)
    {
        m_thisCap = new CCaptionConfig;
    }
    return m_thisCap;
}
CCaptionConfig::CCaptionConfig(void)
{
}


CCaptionConfig::~CCaptionConfig(void)
{
}

void CCaptionConfig::LoadCaption()
{
    TiXmlDocument rootDoc;
    if (rootDoc.LoadFile(XML_CAPTION_CONFIG_FILENAME, TIXML_ENCODING_LEGACY))
    {
        TiXmlHandle hDoc(&rootDoc);
        TiXmlElement *pCapCfg = hDoc.FirstChild("CaptionConfig").ToElement();
        if (NULL != pCapCfg)
        {
            TiXmlElement *pMap = pCapCfg->FirstChildElement("Map");
            while (NULL != pMap)
            {
                std::string url = pMap->Attribute("URL");
                std::string caption = pMap->Attribute("CAPTION");
                m_mapCaption.insert(std::pair<std::string, std::string>(url, caption));
                pMap = pMap->NextSiblingElement();
            }
        }
    }
}

void CCaptionConfig::AddCaption(const std::string& url, const std::string& caption)
{
    std::map<std::string, std::string>::iterator it = m_mapCaption.find(url);
    if (it != m_mapCaption.end())
    {
        m_mapCaption.erase(it);
    }
    m_mapCaption.insert(std::pair<std::string, std::string>(url, caption));
}

const std::string* CCaptionConfig::GetCaption(const std::string& url)
{
    std::map<std::string, std::string>::iterator it = m_mapCaption.find(url);
    if (it != m_mapCaption.end())
    {
        return &(it->second);
    }
    return NULL;
}

void CCaptionConfig::SaveCaption()
{
    if (m_mapCaption.size() > 0)
    {
        TiXmlDocument xmlDoc(XML_CAPTION_CONFIG_FILENAME);
        TiXmlDeclaration Declaration("1.0", "UTF-8", "yes");
        xmlDoc.InsertEndChild( Declaration );

        TiXmlElement* pRootElm = NULL;
        pRootElm = new TiXmlElement("CaptionConfig");

        for (std::map<std::string, std::string>::iterator it = m_mapCaption.begin(); it != m_mapCaption.end(); ++it)
        {
            TiXmlElement *pMap = new TiXmlElement("Map");
            pMap->SetAttribute("URL", it->first.c_str());
            pMap->SetAttribute("CAPTION", it->second.c_str());
            pRootElm->LinkEndChild(pMap);
        }

        xmlDoc.InsertEndChild(*pRootElm) ;

        //xmlDoc.Print() ;
        xmlDoc.SaveFile();

        delete pRootElm;
    }
}