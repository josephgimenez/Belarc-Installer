// InstallBelarc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>

HWND currentAppWindow;
HWND belarcInstallWindow;
HWND belarcInstallDialog;
HWND belarcLicenseAgreeButton;
HWND belarcAdvisorInstall;
HWND belarcAdvisorInstallDialog;
HWND belarcAdvisorInstallButton;
HWND belarcAnalysis;
HWND belarcAnalysisYesButton;
HWND launcher;

CSendKeys sk;

int main()
{

	FreeConsole();

	printf("Please wait while Belarc installs and runs.\n");

	printf("Attempting to launch advisorinstaller.exe from c:\\belarc\n");

	ShellExecute(NULL, L"open", L"c:\\belarc\\advisorinstaller.exe", NULL, NULL, SW_SHOW);

	while (!IsWindow(belarcInstallWindow))
		belarcInstallWindow = FindWindow(NULL, L"Belarc Advisor");

	if (belarcInstallWindow) 
	{
	
		sk.AppActivate(belarcInstallWindow);
		sk.SendKeys(L"{TAB}{ENTER}");

		while (!IsWindow(belarcAdvisorInstall))
		{
			::Sleep(1000);
			belarcAdvisorInstall = FindWindow(NULL, L"Belarc Advisor Installation");
		}
	
		if (belarcAdvisorInstall)
		{
			while (!IsWindow(belarcAdvisorInstallDialog))
				belarcAdvisorInstallDialog = FindWindowEx(belarcAdvisorInstall, 0, L"#32770", 0);

			if (belarcAdvisorInstallDialog)
			{
				sk.AppActivate(belarcAdvisorInstall);	
				sk.SendKeys(L"{ENTER}");
			}
		}					 
				
		else
			printf("Could not find window for advisor installation window.");
					
		while (!IsWindow(belarcAnalysis))
			belarcAnalysis = FindWindow(L"#32770", L"Belarc Analysis - Check for New Definitions");

		if (belarcAnalysis)
		{
	
			sk.AppActivate(belarcAnalysis);
			sk.SendKeys(L"{TAB}{ENTER}");

			
			::Sleep(5000);

			belarcAnalysis = FindWindow(L"#32770", L"Belarc Analysis");

			while (IsWindow(belarcAnalysis))
			{
				belarcAnalysis = FindWindow(L"#32770", L"Belarc Analysis");
			}

			printf("Application \"Belarc\" has closed.\n");

			::Sleep(5000);

		}

		else
			printf("Could not find new definitions window.\n");
	}
				
	return 0;
}

