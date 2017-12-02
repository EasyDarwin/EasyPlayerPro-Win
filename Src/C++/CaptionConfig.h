#pragma once
#include <string>
#include <map>

class CCaptionConfig
{
public:
    static CCaptionConfig* GetInstance();

	virtual ~CCaptionConfig(void);

    void LoadCaption();

    void AddCaption(const std::string& url, const std::string& caption);

    const std::string* GetCaption(const std::string& url);

    void SaveCaption();

protected:
	CCaptionConfig(void);

private:
    static CCaptionConfig* m_thisCap;
    std::map<std::string, std::string> m_mapCaption;
};

