#if defined(_WINDOWS)
#if !defined (_SCL_SECURE_NO_WARNINGS)
#define _SCL_SECURE_NO_WARNINGS
#endif
#if !defined (_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#else
#if defined(__DEPRECATED)
#undef __DEPRECATED
#endif
#endif

#if defined(_WINDOWS) && defined(_GINKGO_DEBUG)
#if defined _GINKGO_CHECK_LEAKS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#endif

#if defined(_WINDOWS)
#include <stdlib.h>
#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>
#else // !_WIN32
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#if !defined(__cplusplus)
#include <stdio.h>
#else

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

#include <vtk_glew.h>

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/xml/xml.h>
#include <wx/filename.h>
#include <wx/file.h>
#include <wx/sstream.h>
#include <wx/tokenzr.h>
#include <wx/thread.h>

#include <vtkInformation.h>
#include <vtkAlgorithmOutput.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>

#include <api/autoptr.h>
#endif
