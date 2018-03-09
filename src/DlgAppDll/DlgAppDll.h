// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLGAPPDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLGAPPDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLGAPPDLL_EXPORTS
#define DLGAPPDLL_API __declspec(dllexport)
#else
#define DLGAPPDLL_API __declspec(dllimport)
#endif

// This class is exported from the DlgAppDll.dll
class DLGAPPDLL_API CDlgAppDll {
public:
	CDlgAppDll(void);
	// TODO: add your methods here.
};

extern DLGAPPDLL_API int nDlgAppDll;

DLGAPPDLL_API int fnDlgAppDll(void);
