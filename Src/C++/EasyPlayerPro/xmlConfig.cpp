#include "xmlConfig.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

XMLConfig::XMLConfig(void)
{
	memset(&proConfig, 0x00, sizeof(PRO_CONFIG_T));
}


XMLConfig::~XMLConfig(void)
{
}


int		XMLConfig::LoadConfig(char *filename, PRO_CONFIG_T *pConfig)
{
	if (NULL == filename)			return -1;

	int ret = -1;
	TiXmlDocument m_DocR;
	if (! m_DocR.LoadFile(filename))
	{
		memset(&proConfig, 0x00, sizeof(PRO_CONFIG_T));

		proConfig.splitWindow = 4;
		//proConfig.renderFormat = 24;
		proConfig.scale	=	0;
		proConfig.multiple = 1;
		proConfig.fullScreen = 0;
		proConfig.recordingFileSize = 512;

		int channel_num = sizeof(proConfig.channel)/sizeof(proConfig.channel[0]);
		for (int i=0; i<channel_num; i++)		
		{
			proConfig.channel[i].cache = 3;
			proConfig.channel[i].protocol = 1;
			proConfig.channel[i].showOSD = 1;
			proConfig.channel[i].showToolbar = 1;
			proConfig.channel[i].autoPlay = 0;
		}

		SaveConfig(filename, &proConfig);			//不存在配置文件, 生成一个新的配置文件
		if (NULL != pConfig)		memcpy(pConfig, &proConfig, sizeof(PRO_CONFIG_T));
		return ret;
	}

	TiXmlHandle hDoc(&m_DocR);
	TiXmlHandle hRoot(0);

	TiXmlElement *pConfigXML = hDoc.FirstChild("XMLConfig").ToElement();
	if (NULL != pConfigXML)
	{
		TiXmlElement *pE;

		pE = pConfigXML->FirstChildElement("SplitWindow");
		if (pE && pE->GetText())		proConfig.splitWindow = atoi(pE->GetText());
		/*
		pE = pConfigXML->FirstChildElement("RenderFormat");
		if (pE && pE->GetText())		proConfig.renderFormat = atoi(pE->GetText());
		*/

		pE = pConfigXML->FirstChildElement("Scale");
		if (pE && pE->GetText())		proConfig.scale = atoi(pE->GetText());

		pE = pConfigXML->FirstChildElement("Multiple");
		if (pE && pE->GetText())		proConfig.multiple = atoi(pE->GetText());

		pE = pConfigXML->FirstChildElement("FullScreen");
		if (pE && pE->GetText())		proConfig.fullScreen = atoi(pE->GetText());

		pE = pConfigXML->FirstChildElement("RecordingFileSize");
		if (pE && pE->GetText())		proConfig.recordingFileSize = atoi(pE->GetText());

		pE = pConfigXML->FirstChildElement("RecordingDuration");
		if (pE && pE->GetText())		proConfig.recordingDuration = atoi(pE->GetText());

		pE = pConfigXML->FirstChildElement("AutoSegmentation");
		if (pE && pE->GetText())		proConfig.recordingFileAutoSegmentation = atoi(pE->GetText());
		

		TiXmlNode *pNode = pConfigXML->FirstChild("Channel");
		if (NULL != pNode)
		{
			TiXmlElement *pChannel = pNode->ToElement();
			if (NULL != pChannel)
			{
				int chIdx = 0;
				TiXmlElement *pCh = pChannel->FirstChild("CH")->ToElement();
				while (NULL != pCh)
				{
					TiXmlAttribute *pAttr = pCh->FirstAttribute();
					while (NULL != pAttr)
					{
						if (0 == strcmp(pAttr->Name(), "URL"))				strncpy(proConfig.channel[chIdx].url, pAttr->Value(), URL_LENGTH);
						else if (0 == strcmp(pAttr->Name(), "OSD"))			proConfig.channel[chIdx].showOSD =  atoi(pAttr->Value());
						else if (0 == strcmp(pAttr->Name(), "Protocol"))	proConfig.channel[chIdx].protocol =  atoi(pAttr->Value());
						else if (0 == strcmp(pAttr->Name(), "Cache"))		proConfig.channel[chIdx].cache =  atoi(pAttr->Value());
						else if (0 == strcmp(pAttr->Name(), "ShowToolbar"))		proConfig.channel[chIdx].showToolbar =  atoi(pAttr->Value());
						else if (0 == strcmp(pAttr->Name(), "AutoPlay"))	proConfig.channel[chIdx].autoPlay =  atoi(pAttr->Value());

						pAttr = pAttr->Next();
					}

					chIdx ++;
					pCh = pCh->NextSiblingElement();
				}
				//pChannel = pChannel->NextSiblingElement();
			}
		}


		if (NULL != pConfig)		memcpy(pConfig, &proConfig, sizeof(PRO_CONFIG_T));

		ret = 0;
	}

	return ret;
}


int	AddElement(char *propertyName, char *propertyValue, TiXmlElement *pParent)
{
	TiXmlElement *pProperty = new TiXmlElement(propertyName);
	TiXmlText* pValue = new TiXmlText(propertyValue);
	pProperty->InsertEndChild(*pValue);
	pParent->InsertEndChild(*pProperty);
	delete pValue;
	delete pProperty;

	return 0;
}

int	AddElement(char *propertyName, int value, TiXmlElement *pParent)
{
	char sztmp[16] = {0};
	sprintf(sztmp, "%d", value);

	TiXmlElement *pProperty = new TiXmlElement(propertyName);
	TiXmlText* pValue = new TiXmlText(sztmp);
	pProperty->InsertEndChild(*pValue);
	pParent->InsertEndChild(*pProperty);
	delete pValue;
	delete pProperty;

	return 0;
}
void	XMLConfig::SaveConfig(char *filename, PRO_CONFIG_T *pConfig)
{
	if (NULL == filename)		return;
	if (NULL != pConfig)
	{
		memcpy(&proConfig, pConfig, sizeof(PRO_CONFIG_T));
	}

	TiXmlDocument xmlDoc( filename );
	TiXmlDeclaration Declaration( "1.0", "UTF-8", "yes" );
	xmlDoc.InsertEndChild( Declaration );

	TiXmlElement* pRootElm = NULL;
	pRootElm = new TiXmlElement( "XMLConfig" );

	AddElement("SplitWindow",		proConfig.splitWindow,		pRootElm);
	//AddElement("RenderFormat",		proConfig.renderFormat,		pRootElm);
	AddElement("Scale",				proConfig.scale,			pRootElm);
	AddElement("Multiple",			proConfig.multiple,			pRootElm);
	AddElement("FullScreen",		proConfig.fullScreen,		pRootElm);
	AddElement("RecordingFileSize",	proConfig.recordingFileSize,pRootElm);
	AddElement("RecordingDuration",	proConfig.recordingDuration,pRootElm);
	AddElement("AutoSegmentation",	proConfig.recordingFileAutoSegmentation,pRootElm);

	TiXmlElement* pChannel = NULL;
	pChannel = new TiXmlElement( "Channel" );

	int channel_num = sizeof(proConfig.channel)/sizeof(proConfig.channel[0]);
	for (int i=0; i<channel_num; i++)
	{
		TiXmlElement *pCh = new TiXmlElement("CH");
		pChannel->LinkEndChild(pCh);

		pCh->SetAttribute("No", i+1);
		pCh->SetAttribute("URL", proConfig.channel[i].url);
		pCh->SetAttribute("OSD", proConfig.channel[i].showOSD);
		pCh->SetAttribute("Protocol", proConfig.channel[i].protocol);
		pCh->SetAttribute("Cache", proConfig.channel[i].cache);
		pCh->SetAttribute("ShowToolbar", proConfig.channel[i].showToolbar);
		pCh->SetAttribute("AutoPlay", proConfig.channel[i].autoPlay);
	}
	pRootElm->LinkEndChild(pChannel);                          //链接到节点RootLv1下  

	xmlDoc.InsertEndChild(*pRootElm) ;

	//xmlDoc.Print() ;
	if (xmlDoc.SaveFile())
	{
	}
	delete pRootElm;
}
