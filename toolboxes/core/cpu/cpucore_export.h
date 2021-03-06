/** \file cpucore_export.h
    \brief Required definitions for Windows, importing/exporting dll symbols 
*/

#ifndef CPUCORE_EXPORT_H_
#define CPUCORE_EXPORT_H_

#if defined (WIN32)
    #ifdef BUILD_TOOLBOX_STATIC
        #define EXPORTCPUCORE
    #else
        #if defined (__BUILD_GADGETRON_CPUCORE__) || defined (cpucore_EXPORTS)
            #define EXPORTCPUCORE __declspec(dllexport)
        #else
            #define EXPORTCPUCORE __declspec(dllimport)
        #endif
    #endif
#else
#define EXPORTCPUCORE
#endif

#endif /* CPUCORE_EXPORT_H_ */
