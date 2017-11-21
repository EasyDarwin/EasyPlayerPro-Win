#pragma once

#define	XML_CONFIG_FILENAME "EasyPlayerPro.xml"


typedef struct __CHANNEL_INFO_T
{
	char		url[256];
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

