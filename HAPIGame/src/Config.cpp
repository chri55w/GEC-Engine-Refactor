#include "pugixml.hpp"
#include "Config.h"
#include <HAPI_lib.h>


CConfig *CConfig::instance_ = NULL;

CConfig &CConfig::getInstance() {
	if (instance_ == NULL) {
		instance_ = new CConfig();
	}
	return *instance_;
}