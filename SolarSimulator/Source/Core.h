#ifdef WINDOWS
#include <windows.h>
#else
#define LINUX
#endif



#define GLB_MAGIC 0x46546C67

#define PATH "../../../SolarSimulator/Resources/"
#define ASSETS_PARENT_DIR "../../../SolarSimulator/Resources/Assets/Textures/" 
//#define PATH "Resources/"
//#define ASSETS_PARENT_DIR "Resources/Assets/Textures/"


typedef unsigned long int  uint64;
typedef unsigned int       uint32;
typedef unsigned short int uint16;
typedef unsigned char	   uint8;

typedef long int		   int64;
typedef int				   int32;
typedef short int		   int16;
typedef char			   int8;
