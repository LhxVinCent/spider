#ifndef _URL_H_
#define _URL_H_

#include<string>
using namespace std;

#define MAX_LINE_LEN 128
#define TYPE_HTML 0
#define TYPE_IMAGE 1
typedef struct stru_url
{
  string url;
  string protocal;
  string Sitename;
  string Path;
  string Filename;
  int stae;
  int deep;
  string Filetype;

}URL;

class Url
{
   public:
	   Url(string url_str);//构造函数
	   int parserUrl();//解析url,并填充内部URL结构
	   struct stru_url* getUrlData();//获得URL数据描述结构
   private:
	   struct stru_url m_url;

};

#endif
