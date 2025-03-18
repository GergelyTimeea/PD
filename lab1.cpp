#include <windows.h>
#include <iostream>
#include <string>

int main()
{
    HKEY hServicesKey = NULL;
    LONG lRet = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "SYSTEM\\CurrentControlSet\\Services",
        0,
        KEY_READ,
        &hServicesKey
    );

    if (lRet != ERROR_SUCCESS)
    {
        std::cerr << "Nu s-a putut deschide cheia Services! Eroare: " << lRet << std::endl;
        return 1;
    }

    DWORD index = 0;
    const DWORD MAX_KEY_LENGTH = 255;
    char subKeyName[MAX_KEY_LENGTH + 1];
    DWORD subKeyNameSize = MAX_KEY_LENGTH + 1;
    FILETIME ftLastWriteTime;

    while (true)
    {
        subKeyNameSize = MAX_KEY_LENGTH + 1;
        LONG enumRes = RegEnumKeyExA(
            hServicesKey,
            index,
            subKeyName,
            &subKeyNameSize,
            NULL,   
            NULL,   
            NULL,  
            &ftLastWriteTime
        );

        if (enumRes == ERROR_NO_MORE_ITEMS)
        {
            break;
        }
        else if (enumRes == ERROR_SUCCESS)
        {
            HKEY hSubKey = NULL;
            LONG openSubKeyRes = RegOpenKeyExA(
                hServicesKey,
                subKeyName,
                0,
                KEY_READ,
                &hSubKey
            );

            if (openSubKeyRes == ERROR_SUCCESS)
            {
                char imagePath[1024];
                DWORD dataSize = sizeof(imagePath);
                DWORD type = 0;
                LONG queryRes = RegQueryValueExA(
                    hSubKey,
                    "ImagePath",
                    NULL,
                    &type,
                    reinterpret_cast<LPBYTE>(imagePath),
                    &dataSize
                );

                if (queryRes == ERROR_SUCCESS && (type == REG_SZ || type == REG_EXPAND_SZ))
                {
                    std::cout << subKeyName << " -> " << imagePath << std::endl;
                }

                RegCloseKey(hSubKey);
            }
            ++index;
        }
        else
        {
            std::cerr << "Eroare la enumerare subchei: " << enumRes << std::endl;
            break;
        }
    }

    RegCloseKey(hServicesKey);

    std::cout << "Apăsați Enter pentru a închide...";
    std::cin.get();
    return 0;
}
