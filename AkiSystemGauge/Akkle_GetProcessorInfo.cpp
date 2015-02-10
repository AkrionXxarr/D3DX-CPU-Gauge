#include "Akkle.hpp"

// Memory leak in here somewhere..
bool Akkle::GetProcessorInfo(double* checkVal)
{
    HRESULT hResult;
    int cpuCheck = (m_cpuCount + 1) * 2;

    IEnumWbemClassObject* pEnumerator = NULL;
    hResult = m_pSvc->ExecQuery(
                            bstr_t("WQL"),
                            bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor"),
                            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                            NULL,
                            &pEnumerator
                            );

    if (FAILED(hResult))
    {
        HandleErrorMsg("ExecQuery Failed", "Error!", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    IWbemClassObject* pClsObj = NULL;
    ULONG uReturn = 0;

    for (int i = 0; i < cpuCheck; i += 2)
    {
        hResult = pEnumerator->Next(WBEM_INFINITE, 1, &pClsObj, &uReturn);
        if (uReturn == 0)
            break;

        VARIANT vtProp;
        VariantInit(&vtProp);

        hResult = pClsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);
        if (FAILED(hResult))
        {
            HandleErrorMsg("pClsObj->Get failed", "Error!", DEFAULT_ERROR, m_hwnd);
            return false;
        }
        checkVal[i] = _wtof(vtProp.bstrVal);
        VariantClear(&vtProp);
        hResult = pClsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
        if (FAILED(hResult))
        {
            HandleErrorMsg("pClsObj->Get failed", "Error!", DEFAULT_ERROR, m_hwnd);
            return false;
        }
        checkVal[i + 1] = _wtof(vtProp.bstrVal);
        VariantClear(&vtProp);

        pClsObj->Release();
        pClsObj = NULL;
    }

    if (pClsObj != NULL)
        pClsObj->Release();
    pEnumerator->Release();

    return true;
}