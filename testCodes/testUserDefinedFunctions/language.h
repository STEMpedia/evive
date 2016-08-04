#ifndef LANGUAGE_H
#define LANGUAGE_H

#define LANGUAGE_CONCAT(M)       #M
#define GENERATE_LANGUAGE_INCLUDE(M)  LANGUAGE_CONCAT(language_##M.h)

//Languages supported:
//En: English

#ifndef LANGUAGE_INCLUDE
  #define LANGUAGE_INCLUDE GENERATE_LANGUAGE_INCLUDE(en)
#endif

#ifndef SOURCE_CODE_URL
#define SOURCE_CODE_URL http://github.com/evivetoolkit/
#endif

//Serial console message list comes here:

#include LANGUAGE_INCLUDE
#include "language_en.h"

#endif

