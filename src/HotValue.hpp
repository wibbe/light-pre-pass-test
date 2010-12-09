
#ifndef HOT_VALUE_HPP
#define HOT_VALUE_HPP

#ifdef NDEBUG || DEBUG

#define H(val) val
#define HC(count, val) val

#define updateHotValues()

#else

#define H(val) hotValue(__FILE__, __LINE__, 0, val)
#define HC(count, val) hotValue(__FILE__, __LINE__, count, val)

int hotValue(const char * file, unsigned int line, unsigned int count, int value);
float hotValue(const char * file, unsigned int line, unsigned int count, float value);

void updateHotValues();

#endif
#endif
