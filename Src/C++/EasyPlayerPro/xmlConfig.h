#pragma once

#define	XML_CONFIG_FILENAME "EasyPlayerPro.xml"

#define URL_LENGTH 256


typedef struct __CHANNEL_INFO_T
{
	char		url[URL_LENGTH];
	int			showOSD;
	int			protocol;	//1:tcp  other:udp
	int			cache;
	int			showToolbar;
	int			autoPlay;
}CHANNEL_INFO_T;

typedef struct __PRO_CONFIG_T
{
	int			splitWindow;
	//int			renderFormat;
	int			scale;
	int			multiple;
	int			fullScreen;
	int			recordingFileSize;
	int			recordingDuration;
	int			recordingFileAutoSegmentation;	//Â¼ÏñÎÄ¼þ×Ô¶¯·Ö¸î

	CHANNEL_INFO_T	channel[16];
}PRO_CONFIG_T;

class XMLConfig
{
public:
	XMLConfig(void);
	~XMLConfig(void);

	int		LoadConfig(char *filename, PRO_CONFIG_T *pConfig);
	void	SaveConfig(char *filename, PRO_CONFIG_T *pConfig);

	PRO_CONFIG_T	*GetConfig()	{return &proConfig;}
protected:

	PRO_CONFIG_T		proConfig;
};

