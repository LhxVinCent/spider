#include<stdio.h>
#include<string>
#include "confparser.h"
#include "qstring.h"
	   //加载配置文件
	   //
 int ConfigParser::loder(char* conf_filepath)
{
    char* filepath=conf_filepath;
    FILE* fp=NULL;
	int linenum=0;
    char buf[MAX_CONF_LEN+1];
	int argc=0;
	char** argv=NULL;
	const char* err=NULL;
	char* line=NULL;
	if((fp=fopen(filepath,"r"))==NULL)
	{
       SPIDER_LOG(SPIDER_LEVEL_ERROR,"Can't load congfile %s",filepath);
	   return 1;
	}
	while(fgets(buf,MAX_CONF_LEN+1,fp)!=NULL)
	{
		linenum++;
		line=strim(buf);
        if(line[0]=='#' || line[0]=='\0')       
			continue;
		argv=strsplit(line,'=',&argc,1);
        if(argc==2){
         if(strcasecmp(argv[0],"max_job_num")==0){
           this->job_num=atoi(argv[1]);
		 }else if(strcasecmp(argv[0],"seeds")==0)
		 {
              this->seeds=strdup(argv[1]);
		 }
		 else if(strcasecmp(argv[0],"module_path")==0)
		 {
                   this->module_path=strdup(argv[1]);
		 }
		 else if(strcasecmp(argv[0],"load_module")==0)
		 {
            this->modules.push_back(strdup(argv[1]));
		 }else if(strcasecmp(argv[0],"log_level")==0)
		 {
            this->log_level=atoi()argv[1];
		 }else if(strcasecmp(argv[0],"max_depth")==0)
		 {
              this->depth=atoi(arg[1]);
		 }else if(strcasecmp(argv[0],"accept_types")==0)
		 {
            this->file_type.push_back(strdup(argv[1]));
		 }else{
           err="Unknown directive";goto conferr;
		 }

		
	}
		else{
                err="directive must be 'key=value'; goto conferr;
		}
conferr:
 return 0;
}
	   //单例
	   ConfigParser* ConfigParser::instance()
{
	if(_self==NULL)
	{
		_self=new ConfigParser();
	}
}
 void ConfigParser::release()
{
    if(_self==NULL)
	{
       return;
	}
	delete _self;
}
       //主要操作
	   int ConfigParser:: getJobNum()//
{
       
}
	   char ConfigParser:: getUrlSeed()//获取种子
{
}
	   int ConfigParser::getDeep()//爬取的深度
{

}
       int ConfigParser::getLogLevel()//获取日志等级
{

}
	   char* ConfigParser::getModulePath()//获取模块的路径
{
}
	   list<string> ConfigParser::getModules()
{

}
	   list<string> ConfigParser::getFileTypes()
{

}
	   ConfigParser:: ConfigParser()
{
    job_num=10;
  seed=NULL;
 depth=0;
log_level=0;
module_path=NULL;
           
}
	   static ConfigParser* _self
  	   int job_num
	   char* seed
	   int depth
	   int log_level
	   char* module_path
	   list<string> modules
	   list<string> file_types


