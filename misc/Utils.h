
#ifndef __UTILS_H__
#define __UTILS_H__

#include <cmath>
#include <sstream>
#include <cstdlib>

#define ITEM_NUM(array) (sizeof(array) / sizeof(array[0]))

#define GET_DICT_VALUE(dict, key, typeValue, defaultVal) \
    (dict->valueForKey(key)->length() > 0 ? dict->valueForKey(key)->typeValue() : defaultVal)

#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Max(a, b) ((a) > (b) ? (a) : (b))

#ifdef WIN32
#define M_PI       (3.14159265358979323846)

inline int round(float x) {
	return ((int)(x + 0.5f));
}
#endif

//#define interface struct
#define INTERFACE_BEGIN(type)   class type { \
public: \
virtual ~type() {}
#define INTERFACE_END };

#define EPSILON     (1e-6)

namespace Utils {
    static inline float toDegrees(float rad) {
        return rad * 180.0 / M_PI;
    }

    static inline float toRadians(float deg) {
        return deg * M_PI / 180.0;
    }

    template<typename T> 
        static inline std::string convertToString(T v) {
            std::ostringstream ss;
            ss << v;
            return ss.str();
        }

    template<typename T>
        static inline void shuffleArray(T* array, size_t len) {
            int j = 0;
            T temp;

            if (NULL == array || 0 == len) return;
            while ( --len ) {
                j = rand() % (len + 1);
                temp = array[len];
                array[len] = array[j];
                array[j] = temp;
            }
        }
}
#endif
