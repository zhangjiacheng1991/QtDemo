#ifndef DEFINETYPE_H
#define DEFINETYPE_H
#include <stdint.h>
struct CLogMsg
{
    uint16_t  SN;	//日志编号，由接口内部自增
    uint8_t   logType_;  //日志类型(0:应用日志, 1: logmng日志)
    uint16_t 	funcType_; //业务类型
    uint64_t 	time_;	//毫秒级时间
    char	procName_[64]; //进程名
    char 	file_line_[128];//cpp名称+行号
    char 	msg_[1500];	//日志对象信息

};

#endif // DEFINETYPE_H
