#ifndef __CMCIMGR__
#define __CMCIMGR__

#include <iostream>
#include <windows.h>
#include <mmsystem.h> 
#include <Digitalv.h>

class CMciMgr
{
public:
	CMciMgr( void ); // Ĭ�Ϲ��캯�� 
	~CMciMgr( void );
	int open( const LPCSTR lpsFileName, const LPCSTR lpsDeviceType = 0 ); // ��ý�� 
	//int Seek();
	int play( void );              // ���� 
	int playloop();
	int play( const int &hour, const int &min, const int &sec ); // ��ָ��λ�ÿ�ʼ���� 
	int play( DWORD dwPos );		// ��ָ��λ�ÿ�ʼ���� 
	int pause( void );             // ��ͣ 
	int close( void );				// �ر�ý�� 
	DWORD getLen( void ); // ���ý�峤��
	void setLen( void );  // ����ý�峤�� 
	DWORD getdwPos( void );   // ���m_dwPos 
	DWORD getMediaStatus( DWORD item ); // ���ý��״̬��Ϣ 
	void setdwPos( DWORD dwPos ); //  ����m_dwPos 
	
private:
	MCIDEVICEID m_mDeviceId;		// �豸���� 
	DWORD       m_dwLen;			// ý�峤�� 
	DWORD       m_dwPos;			// ��ǰλ�� 
};

#endif  // __CMCIMGR__