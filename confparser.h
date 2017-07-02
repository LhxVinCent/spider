#include<stdio.h>
#include<string>
#include<list>
using namespace std;
class ConfigParser
{
   public:
	   //加载配置文件
	   int loder(char* conf_filepath);
	   //单例
	   static ConfigParser* instance();
	   static void release();
       //主要操作
	   int getJobNum();//
	   char getUrlSeed();//获取种子
	   int getDeep();//爬取的深度
       int getLogLevel();//获取日志等级
	   char* getModulePath();//获取模块的路径
	   list<string> getModules();
	   list<string> getFileTypes();
   private:
	   ConfigParser();
	   static ConfigParser* _self;
   private:
	   int job_num;
	   char* seed;
	   int depth;
	   int log_level;
	   char* module_path;
	   list<string> modules;
	   list<string> file_types;

};

ConfigParser::_self=NULL;
