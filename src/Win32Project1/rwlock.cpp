#include "stdafx.h"

class CSRWLock
{
public:
    CSRWLock()
    {
        ::InitializeSRWLock(&m_lock);
    }

    //
    VOID EnterReaderLock()
    {
        ::AcquireSRWLockShared(&m_lock);
    }
    VOID LeaveReaderLock()
    {
        ::ReleaseSRWLockShared(&m_lock);
    }

    //
    VOID EnterWriterLock()
    {
        ::AcquireSRWLockExclusive(&m_lock);
    }
    VOID LeaveWriterLock()
    {
        ::ReleaseSRWLockExclusive(&m_lock);
    }

private:
    SRWLOCK  m_lock;
};


class CAutoReleaseSRWLock
{
public:
    typedef BOOL(*RelaseLockFuncPtr)(IN SRWLOCK lock, IN DWORD dwTlsIndex);

    CAutoReleaseSRWLock(IN SRWLOCK lock, IN DWORD dwTlsIndex, IN RelaseLockFuncPtr funcPtr)
    {
        m_bLockReleased = FALSE;

        m_releaseLockFunc = funcPtr;
        m_lock = lock;
        m_dwTlsIndex = dwTlsIndex;

    }

    ~CAutoReleaseSRWLock()
    {
        if (!m_bLockReleased)
        {
            ReleaseLock();
        }
    }

    VOID ReleaseLock()
    {
        if (!m_bLockReleased)
        {
            m_releaseLockFunc(m_lock, m_dwTlsIndex);
            m_bLockReleased = TRUE;
        }
    }

private:
    BOOL m_bLockReleased;
    RelaseLockFuncPtr m_releaseLockFunc;
    SRWLOCK m_lock;
    DWORD m_dwTlsIndex;
};

class CReentrantSRWLock
{
public:
    CReentrantSRWLock()
    {
        m_dwTlsIndex = TlsAlloc();
        ::InitializeSRWLock(&m_lock);
    }

    ~CReentrantSRWLock()
    {
        TlsFree(m_dwTlsIndex);
        m_dwTlsIndex = TLS_OUT_OF_INDEXES;
    }

    CAutoReleaseSRWLock EnterReaderLock()
    {
        DWORD	dwLockStatus;
        BOOL	bReaderLocked;
        BOOL	bWriterLocked;

        dwLockStatus	= 0;
        bReaderLocked	= FALSE;
        bWriterLocked	= FALSE;

        dwLockStatus = (DWORD)TlsGetValue(m_dwTlsIndex);
        bReaderLocked = IsReaderLocked(dwLockStatus);
        bWriterLocked = IsWriterLocked(dwLockStatus);

        if (bReaderLocked || bWriterLocked)
        {
            return CAutoReleaseSRWLock(m_lock, m_dwTlsIndex, ReleaseLockDummy);
        }

        ::AcquireSRWLockShared(&m_lock);
        ::TlsSetValue(m_dwTlsIndex, (LPVOID)MakeLockStatus(TRUE, FALSE));
        return CAutoReleaseSRWLock(m_lock, m_dwTlsIndex, ReleaseReaderLock);
    }

    CAutoReleaseSRWLock EnterWriterLock()
    {
        DWORD	dwLockStatus;
        BOOL	bReaderLocked;
        BOOL	bWriterLocked;

        dwLockStatus = 0;
        bReaderLocked = FALSE;
        bWriterLocked = FALSE;

        dwLockStatus = (DWORD)TlsGetValue(m_dwTlsIndex);
        bReaderLocked = IsReaderLocked(dwLockStatus);
        bWriterLocked = IsWriterLocked(dwLockStatus);

        if (bWriterLocked > 0)
        {
            return CAutoReleaseSRWLock(m_lock, m_dwTlsIndex, ReleaseLockDummy);
        }
        else if (bReaderLocked > 0)
        {
            ::ReleaseSRWLockShared(&m_lock);
            ::AcquireSRWLockExclusive(&m_lock);
            ::TlsSetValue(m_dwTlsIndex, (LPVOID)MakeLockStatus(TRUE, FALSE));
            return CAutoReleaseSRWLock(m_lock, m_dwTlsIndex, ReleaseWriterAndAcquireReader);
        }

        ::AcquireSRWLockExclusive(&m_lock);
        ::TlsSetValue(m_dwTlsIndex, (LPVOID)MakeLockStatus(TRUE, FALSE));
        return CAutoReleaseSRWLock(m_lock, m_dwTlsIndex, ReleaseWriterLock);
    }

private:
    DWORD		m_dwTlsIndex;
    SRWLOCK		m_lock;


public:
    static __forceinline DWORD MakeLockStatus(IN BOOL bReaderLock, IN BOOL bWriterLock)
    {
        return MAKELONG(bReaderLock, bWriterLock);
    }

    static __forceinline BOOL IsReaderLocked(IN DWORD dwLock)
    {
        return LOWORD(dwLock);
    }

    static __forceinline BOOL IsWriterLocked(IN DWORD dwLock)
    {
        return HIWORD(dwLock);
    }

    static __forceinline BOOL ReleaseLockDummy(IN SRWLOCK /*lock*/, IN DWORD /*dwTlsIndex*/)
    {
        return TRUE;
    }

    static BOOL ReleaseReaderLock(IN SRWLOCK lock, IN DWORD dwTlsIndex)
    {
        ::ReleaseSRWLockShared(&lock);
        ::TlsSetValue(dwTlsIndex, (LPVOID)MakeLockStatus(FALSE, FALSE));
        return TRUE;
    }

    static BOOL ReleaseWriterAndAcquireReader(IN SRWLOCK lock, IN DWORD dwTlsIndex)
    {
        ::ReleaseSRWLockExclusive(&lock);
        ::AcquireSRWLockShared(&lock);
        ::TlsSetValue(dwTlsIndex, (LPVOID)MakeLockStatus(TRUE, FALSE));
        return TRUE;
    }

    static BOOL ReleaseWriterLock(IN SRWLOCK lock, IN DWORD dwTlsIndex)
    {
        ::ReleaseSRWLockExclusive(&lock);
        ::TlsSetValue(dwTlsIndex, (LPVOID)MakeLockStatus(FALSE, FALSE));
        return TRUE;
    }
};