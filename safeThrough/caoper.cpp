#include "caoper.h"
#include <tchar.h>
#include <Windows.h>
#include <string>
#include <comutil.h>
#include <atlcomcli.h>

#import "JITComVCTK_S.dll"

using namespace std;

CAOper::CAOper(QObject *parent) :
    QObject(parent)
{
    m_InitializeHandle = NULL;
    m_SetCert = NULL;
    m_SetCertChooseType = NULL;
    m_AttachSignBase64 = NULL;
    m_DetachSignBase64 = NULL;
    m_ReleaseHandle = NULL;
}
QString CAOper::getOrigin()
{
    char table[] = {'0','1','2','3','4','5','6','7','8','9'};
    char ret[7] = {0};
    int i = 0;
    while (i < 6)
    {
        ret[i] = table[ rand()%10 ];
        ++i;
    }
    ret[i] = '\0';
    return QString::fromAscii(ret);
}

QString CAOper::getCode()
{
    char table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                    'a','b','c','d','e','f','g','h','i','j','k','l','m',
                    'n','o','p','q','r','s','t','u','v','w','x','y','z',
                    '0','1','2','3','4','5','6','7','8','9'};
    int len = 16 , i = 0;
    const int codelen = 17;
    char cret[codelen] = {0};
    while ( i < len)
    {
        cret[i] = table[ rand()%sizeof(table) ];
        ++i;
    }
    cret[i] = '\0';
    QString sret = QString::fromAscii(cret);
    return sret;
}

QString CAOper::buildAuthRequest(const QString strRootDN, const QString strorigin)
{
    QString sAuthRequest = QString::fromWCharArray(TEXT(""));
    HINSTANCE hDll;
    long lReturn;
    hDll = LoadLibrary(_T("JITVCTK_SDll.dll"));
    if (FAILED(hDll))
    {
        return sAuthRequest;
    }
    m_InitializeHandle = (lpInit)GetProcAddress(hDll,"InitializeHandle_C");
    m_SetCert = (lpSetCert)GetProcAddress(hDll,"SetCert_C");
    m_SetCertChooseType = (lpSetCertChooseType)GetProcAddress(hDll,"SetCertChooseType_C");
    m_AttachSignBase64 = (lpAttachSignBase64)GetProcAddress(hDll,"AttachSignBase64_C");
    m_DetachSignBase64 = (lpDetachSignBase64)GetProcAddress(hDll,"DetachSignBase64_C");
    m_ReleaseHandle = (lpReleaseHandle)GetProcAddress(hDll,"ReleaseHandle_C");
    if (NULL==m_InitializeHandle || NULL==m_SetCert || NULL==m_SetCertChooseType || NULL==m_AttachSignBase64 || NULL==m_DetachSignBase64 || NULL==m_ReleaseHandle)
    {
        return sAuthRequest;
    }

    QString strtmp = QString::fromWCharArray(_T("<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SERfR01DQUlTLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U2h1dHRsZUNzcDExXzMwMDBHTS5kbGw=\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U0tGQVBJLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>"));
    string strtmpSource((const char*)_bstr_t(strtmp.toStdWString().c_str()));
        //const char* lpstrtmp =  (const char*)_bstr_t(strtmp);
        HANDLE hReturn = m_InitializeHandle(strtmpSource.c_str());
        if (NULL == hReturn)
        {
            m_ReleaseHandle(hReturn);
            return sAuthRequest;
        }
        // 根据根证书主题过滤证书
       lReturn = m_SetCertChooseType(hReturn,1);
       if (0 != lReturn)
       {
           m_ReleaseHandle(hReturn);
           return sAuthRequest;
       }
        if (strRootDN.isEmpty())
        {
           lReturn = m_SetCert(hReturn,_bstr_t(_T("SC")), _bstr_t((LPCTSTR)NULL), _bstr_t((LPCTSTR)NULL), _bstr_t((LPCTSTR)NULL), _bstr_t((LPCTSTR)NULL), _bstr_t((LPCTSTR)NULL));
        }
        else
        {
          lReturn = m_SetCert(hReturn,_bstr_t(_T("SC")), _bstr_t((LPCTSTR)NULL), _bstr_t((LPCTSTR)NULL), _bstr_t((LPCTSTR)NULL), _bstr_t(strRootDN.toStdWString().c_str()), _bstr_t((LPCTSTR)NULL));
        }
        if (0 != lReturn)
        {
            //MessageBox(_T("选择认证证书失败。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
            m_ReleaseHandle(hReturn);
            return sAuthRequest;
        }
        // 生成认证原文认证请求信息
        string strSource = strorigin.toStdString();

        long nOutLen=0;
        lReturn = m_DetachSignBase64(hReturn,_bstr_t((LPCTSTR)NULL),strSource.c_str(),  NULL, &nOutLen);
        if(0 != lReturn)
        {
            //MessageBox(_T("生成认证原文认证请求信息失败。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
            m_ReleaseHandle(hReturn);
            return sAuthRequest;
        }
        char* pOutData = new char[nOutLen + 1];
        memset(pOutData, 0, nOutLen + 1);
        lReturn = m_DetachSignBase64(hReturn,_bstr_t((LPCTSTR)NULL),strSource.c_str(),  pOutData, &nOutLen);
        if(0 != lReturn)
        {
            //MessageBox(_T("生成认证原文认证请求信息失败。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
            m_ReleaseHandle(hReturn);
            return sAuthRequest;
        }
        QString str1= QString::fromAscii(pOutData);
        sAuthRequest = str1;
        delete[] pOutData;
        pOutData=NULL;
        m_ReleaseHandle(hReturn);
        return sAuthRequest;
}

