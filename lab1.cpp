#include <windows.h>
#include <iostream>
#include <string>

int main()
{
    HKEY hServicesKey = NULL;
    // Deschidem cheia: HKLM\SYSTEM\CurrentControlSet\Services
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

    // Enumerăm toate subcheile (serviciile)
    DWORD index = 0;
    const DWORD MAX_KEY_LENGTH = 255;
    char subKeyName[MAX_KEY_LENGTH + 1];
    DWORD subKeyNameSize = MAX_KEY_LENGTH + 1;
    FILETIME ftLastWriteTime;

    while (true)
    {
        subKeyNameSize = MAX_KEY_LENGTH + 1;
        // Enumerăm subcheia cu indexul curent
        LONG enumRes = RegEnumKeyExA(
            hServicesKey,
            index,
            subKeyName,
            &subKeyNameSize,
            NULL,   // rezervat
            NULL,   // buffer pentru class (nu avem nevoie)
            NULL,   // dimensiunea buffer-ului class
            &ftLastWriteTime
        );

        if (enumRes == ERROR_NO_MORE_ITEMS)
        {
            // Am terminat enumerarea
            break;
        }
        else if (enumRes == ERROR_SUCCESS)
        {
            // Deschidem subcheia pentru a citi "ImagePath"
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
                // Citim valoarea "ImagePath"
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
                    // Afișăm doar dacă este un tip de date de tip șir
                    std::cout << subKeyName << " -> " << imagePath << std::endl;
                }

                RegCloseKey(hSubKey);
            }
            ++index;
        }
        else
        {
            // În caz de altă eroare, ne oprim
            std::cerr << "Eroare la enumerare subchei: " << enumRes << std::endl;
            break;
        }
    }

    // Închidem cheia principală
    RegCloseKey(hServicesKey);

    std::cout << "Apăsați Enter pentru a închide...";
    std::cin.get();
    return 0;
}
