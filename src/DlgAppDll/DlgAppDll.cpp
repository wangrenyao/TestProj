// DlgAppDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DlgAppDll.h"


// This is an example of an exported variable
DLGAPPDLL_API int nDlgAppDll=0;

// This is an example of an exported function.
DLGAPPDLL_API int fnDlgAppDll(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see DlgAppDll.h for the class definition
CDlgAppDll::CDlgAppDll()
{
    return;
}
