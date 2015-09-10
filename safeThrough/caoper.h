#ifndef CAOPER_H
#define CAOPER_H

#include <QObject>
#include <Windows.h>


typedef void* HANDLE;
typedef HANDLE (WINAPI*lpInit)(const char*);
typedef long (WINAPI*lpSetCert)(HANDLE , const char *, const char *, const char *, const char *, const char *, const char *);
typedef long (WINAPI*lpSetCertChooseType)(HANDLE , long);
typedef long (WINAPI*lpAttachSignBase64)(HANDLE , const char *, const char* , char *, long *);
typedef long (WINAPI*lpDetachSignBase64)(HANDLE , const char *, const char* , char *, long *);
typedef long (WINAPI*lpReleaseHandle)(HANDLE);
class CAOper : public QObject
{
    Q_OBJECT
public:
    explicit CAOper(QObject *parent = 0);

    QString buildAuthRequest(const QString rootDN, const QString strorigin);
    static QString  getCode();
    static QString  getOrigin();
signals:

public slots:
private:
    lpInit					m_InitializeHandle;
    lpSetCert				m_SetCert;
    lpSetCertChooseType		m_SetCertChooseType;
    lpAttachSignBase64		m_AttachSignBase64;
    lpDetachSignBase64		m_DetachSignBase64;
    lpReleaseHandle			m_ReleaseHandle;

};

#endif // CAOPER_H
