#ifndef _UML_MANAGER_H_
#define _UML_MANAGER_H_
#include<stdio.h>
#include<list>
#include<queue>
#include<map>
#include<string>
#include"url.h"
using namespace std;

class UrlManager
{
  public://外部接口
	  int addUrl(string urlStr);//添加一个全新的URL加入到list and quque中,同时生成索引
	  int addUrlList(list<string> urlStrs);//批量添加
	  URL* getUrlForQuque();//取一个未处理的URL对象指针
	  int setUrlState(URL*url);//设置URL处理状态
	  //setUrlValue();
  private://内部接口
	  URL* findUrl(string urlStr);
	  int removeUrlForQuque(string urlStr);
  private:
	  list<Url> m_urls;//所有的url
	  map<string,m_url*> UrlMap;//所有URL的索引
	  queue<URL*> m_urlquque;//维护等待抓取的URL
};
#endif
