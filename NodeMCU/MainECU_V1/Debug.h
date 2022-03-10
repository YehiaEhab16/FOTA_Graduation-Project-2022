#ifndef DEBUG_H_
#define DEBUG_H_


#define DEBUG_FLAG            0

#if DEBUG_FLAG == 1
#define debug(x)              Serial.print(x)
#define debugf(x,y)           Serial.printf(x,y)
#define debugln(x)            Serial.println(x)
#else
#define debug(x)
#define debugf(x,y)
#define debugln(x)
#endif


#endif
