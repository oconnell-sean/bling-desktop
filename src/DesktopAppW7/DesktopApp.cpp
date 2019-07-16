#include "stdafx.h"

#include "DesktopApp.h"
#include "DesktopAppDlg.h"

#include "DesktopCore\DesktopCore.h"
#include "DesktopCore\Upgrade\Agents\UpgradeViewerAgent.h"
#include "DesktopCore\Upgrade\Agents\UpgradeDesktopAgent.h"
#include "DesktopCore\Blink\Agents\SyncVideoAgent.h"
#include "DesktopCore\Blink\Agents\SyncThumbnailAgent.h"
#include "DesktopCore\Blink\Agents\SaveTokenAgent.h"
#include "DesktopCore\Blink\Agents\ActivityAgent.h"
#include "DesktopCore\System\Services\ApplicationDataService.h"
#include "DesktopCore\System\Services\CrashReportService.h"
#include "Services\DownloadViewerService.h"
#include <boost/optional.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(DesktopApp, CWinApp)
END_MESSAGE_MAP()

DesktopApp::DesktopApp() : m_nExitCode(ERROR_SUCCESS)
{

}

DesktopApp theApp;

BOOL DesktopApp::InitInstance()
{
	desktop::core::service::CrashReportService service;
	service.initialize({});

	// Enable High-DPI support on Windows 7 or newer.
	CefEnableHighDPISupport();

	void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
	// Manage the life span of the sandbox information object. This is necessary
	// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif

	// Provide CEF with command-line arguments.
	CefMainArgs main_args(GetModuleHandle(NULL));

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	int exit_code = CefExecuteProcess(main_args, NULL, sandbox_info);
	if (exit_code >= 0)
	{
		// The sub-process has completed so return here.
		return exit_code;
	}

	m_core = std::make_unique<desktop::core::DesktopCore>();

	std::string reason;

	m_cefApp = new desktop::ui::BrowserApp();
	m_cefApp->initialize();

    //Bring up the main dialog
    DesktopAppDlg mainDlg;
    m_pMainWnd = &mainDlg;
    mainDlg.DoModal();

	CefShutdown();

  return FALSE;
}

int DesktopApp::ExitInstance()
{
  __super::ExitInstance();
  return m_nExitCode;
}

BOOL DesktopApp::CreateBrowser(CefRefPtr<desktop::ui::BrowserClientHandler> client_handler, HWND hWnd, CRect rect, LPCTSTR pszURL)
{
	return m_cefApp->CreateBrowser(client_handler, hWnd, rect, pszURL);
}

std::string DesktopApp::onBrowserCreated(CefRefPtr<CefBrowser> browser)
{
	m_core->initialize();

	m_core->addAgent(std::make_unique<desktop::core::agent::UpgradeViewerAgent>(std::make_unique<desktop::ui::service::DownloadViewerService>(browser)));
	m_core->addAgent(std::make_unique<desktop::core::agent::SyncVideoAgent>());
	m_core->addAgent(std::make_unique<desktop::core::agent::SyncThumbnailAgent>());
	m_core->addAgent(std::make_unique<desktop::core::agent::SaveTokenAgent>());

	desktop::core::service::ApplicationDataService service;
	auto documents = service.getMyDocuments();
	return documents + "Download\\Versions\\";
}