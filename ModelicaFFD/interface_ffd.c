#include <stdio.h>

#include "interface_ffd.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include "share.h"

#pragma comment(lib, "user32.lib")

#define BUF_SIZE 256
//TCHAR szName[]=TEXT("Global\\MyFileMappingObject");
TCHAR szName[]=TEXT("MyFileMappingObject");

int initiateFFD(){
  int status;

  status = system("start ..\\..\\Fast-Fluid-Dynamics\\Debug\\FFD_SCI.exe"); // Use start to creat a new window for FFD; like fork the process
  printf("Launch FFD with status: %d\n", status);

  return status;
}



int exchangeData()
{
   HANDLE hMapFile;
   LPCTSTR pBuf;

   hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   szName);               // name of mapping object

   if (hMapFile == NULL)
   {
      _tprintf(TEXT("Could not open file mapping object (%d).\n"),
             GetLastError());
      return 1;
   }

   pBuf = (LPTSTR) MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_ALL_ACCESS,  // read/write permission
               0,
               0,
               BUF_SIZE);

   if (pBuf == NULL)
   {
      _tprintf(TEXT("Could not map view of file (%d).\n"),
             GetLastError());

      CloseHandle(hMapFile);

      return 1;
   }

   MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);

   UnmapViewOfFile(pBuf);

   CloseHandle(hMapFile);

   return 0;
}
