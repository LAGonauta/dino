#include <shlobj.h>
#include <memory>

#include "shortcutcreator.h"
#include "win32.hpp"
#include "converter.hpp"
#include "ginvoke.hpp"

#ifdef UNICODE
    #define _UNICODE
#endif

#include <tchar.h>        // magic
#include <objbase.h>      // COM stuff
#include <shlobj.h>       // IShellLink
#include <propvarutil.h>  // InitPropVariantFromString
#include <propkey.h>      // PKEY_AppUserModel_ID
#include <cstdio>         // 'cause iostreams are bloat
#include <filesystem>

#include "ComPtr.hpp"

// Not available in MINGW headers for some reason
PSSTDAPI PropVariantToString(_In_ REFPROPVARIANT propvar, _Out_writes_(cch) PWSTR psz, _In_ UINT cch);

int32_t InstallShortcut(const std::wstring& exe_path, const std::wstring& aumid, const std::wstring& shortcut_path)
{
    ComPtr<IShellLink> shellLink;
    auto hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shellLink));

    if (SUCCEEDED(hr))
    {
        hr = shellLink->SetPath(exe_path.c_str());
        if (SUCCEEDED(hr))
        {
            hr = shellLink->SetArguments(TEXT(""));
            if (SUCCEEDED(hr))
            {
                hr = shellLink->SetWorkingDirectory(exe_path.c_str());
                if (SUCCEEDED(hr))
                {
                    ComPtr<IPropertyStore> propertyStore;
                    hr = shellLink.As(&propertyStore);
                    if (SUCCEEDED(hr))
                    {
                        PROPVARIANT appIdPropVar;
                        hr = InitPropVariantFromString(aumid.c_str(), &appIdPropVar);
                        if (SUCCEEDED(hr))
                        {
                            hr = propertyStore->SetValue(PKEY_AppUserModel_ID, appIdPropVar);
                            if (SUCCEEDED(hr))
                            {
                                hr = propertyStore->Commit();
                                if (SUCCEEDED(hr))
                                {
                                    ComPtr<IPersistFile> persistFile;
                                    hr = shellLink.As(&persistFile);
                                    if (SUCCEEDED(hr))
                                    {
                                        hr = persistFile->Save(shortcut_path.c_str(), TRUE);
                                    }
                                }
                            }
                            PropVariantClear(&appIdPropVar);
                        }
                    }
                }
            }
        }
    }
    return hr;
}

int32_t ValidateShortcut(const std::wstring& shortcut_path, const std::wstring& currentAumid)
{
    bool wasChanged = false;

    ComPtr<IShellLink> shellLink;
    auto hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shellLink));

    if (SUCCEEDED(hr))
    {
        ComPtr<IPersistFile> persistFile;
        hr = shellLink.As(&persistFile);
        if (SUCCEEDED(hr))
        {
            hr = persistFile->Load(shortcut_path.c_str(), STGM_READWRITE);
            if (SUCCEEDED(hr))
            {
                ComPtr<IPropertyStore> propertyStore;
                hr = shellLink.As(&propertyStore);
                if (SUCCEEDED(hr))
                {
                    PROPVARIANT appIdPropVar;
                    hr = propertyStore->GetValue(PKEY_AppUserModel_ID, &appIdPropVar);
                    if (SUCCEEDED(hr))
                    {
                        std::array<wchar_t, MAX_PATH> AUMI;
                        hr = PropVariantToString(appIdPropVar, AUMI.data(), AUMI.size());
                        if (FAILED(hr) || currentAumid != std::wstring(AUMI.data()))
                        {
                            // AUMI Changed for the same app, let's update the current value! =)
                            wasChanged = true;
                            PropVariantClear(&appIdPropVar);
                            hr = InitPropVariantFromString(currentAumid.c_str(), &appIdPropVar);
                            if (SUCCEEDED(hr))
                            {
                                hr = propertyStore->SetValue(PKEY_AppUserModel_ID, appIdPropVar);
                                if (SUCCEEDED(hr))
                                {
                                    hr = propertyStore->Commit();
                                    if (SUCCEEDED(hr) && SUCCEEDED(persistFile->IsDirty()))
                                    {
                                        hr = persistFile->Save(shortcut_path.c_str(), TRUE);
                                    }
                                }
                            }
                        }
                        PropVariantClear(&appIdPropVar);
                    }
                }
            }
        }
    }
    return hr;
}

static bool ImplEnsureAumiddedShortcutExists(
    const std::string_view menu_rel_path, const std::string_view aumid)
{
    auto waumid = sview_to_wstr(aumid);
    if (waumid.empty())
    {
        return false;
    }

    auto exePath = GetExePath();

    auto path = GetEnv(L"APPDATA") + LR"(\Microsoft\Windows\Start Menu\)"
        + sview_to_wstr(menu_rel_path) + L".lnk";
    if (!std::filesystem::exists(path))
    {
        return SUCCEEDED(InstallShortcut(exePath, waumid, path));
    }
    else
    {
        return SUCCEEDED(ValidateShortcut(path, waumid));
    }
}

extern "C"
{
    gboolean EnsureAumiddedShortcutExists(const gchar* aumid) noexcept
    {
        return g_try_invoke(
            ImplEnsureAumiddedShortcutExists, R"(Programs\Dino)", aumid);
    }
}
