
#ifndef __NGX_CONF_H__
#define __NGX_CONF_H__

#include <vector>

#include "ngx_global.h"  //一些全局/通用定义

//读取配置文件类，单例类
//GetInstance(): 获取单例类
//Load(): 装载配置文件到vector容器
//GetString: 获取配置项的值(字符串)
//GetIntDefault: 获取配置项的值(整数)
class CConfig
{
//---------------------------------------------------
//单例设计模式
private:
	CConfig();
public:
	~CConfig();
private:
	static CConfig *m_instance;

public:	
	//获取单例类
	//第一次调用不应该放在线程中，应该放在主进程中，以免和其他线程调用冲突从而导致同时执行两次new CConfig()
	static CConfig* GetInstance() 
	{	
		if (m_instance == NULL)
		{
			//锁
			if (m_instance == NULL)
			{					
				m_instance = new CConfig();
				static CGarhuishou cl; 
			}
			//放锁		
		}
		return m_instance;
	}	
	class CGarhuishou  //类中套类，用于释放对象
	{
	public:				
		~CGarhuishou()
		{
			if (CConfig::m_instance)
			{						
				delete CConfig::m_instance;				
				CConfig::m_instance = NULL;				
			}
		}
	};
//---------------------------------------------------
public:
	//装载配置文件到vector容器
    bool Load(const char *pconfName);
	//获取配置项的值(字符串)
	const char *GetString(const char *p_itemname); 
	//获取配置项的值(整数)        
	int  GetIntDefault(const char *p_itemname,const int def);

public:
	//存储配置信息的容器
	std::vector<LPCConfItem> m_ConfigItemList; 
};

#endif
