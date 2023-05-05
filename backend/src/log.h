#ifndef __LOG_H__
#define __LOG_H__

#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/PatternLayout.hh"

extern log4cpp::Category &category;

void log4cpp_init();




#endif