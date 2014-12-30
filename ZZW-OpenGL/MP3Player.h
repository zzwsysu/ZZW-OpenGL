#ifndef __CMCIMGR__
#define __CMCIMGR__

#include <iostream>
#include <windows.h>
#include <mmsystem.h> 
#include <Digitalv.h>

class CMciMgr
{
public:
	CMciMgr( void ); // 默认构造函数 
	~CMciMgr( void );
	int open( const LPCSTR lpsFileName, const LPCSTR lpsDeviceType = 0 ); // 打开媒体 
	//int Seek();
	int play( void );              // 播放 
	int playloop();
	int play( const int &hour, const int &min, const int &sec ); // 从指定位置开始播放 
	int play( DWORD dwPos );		// 从指定位置开始播放 
	int pause( void );             // 暂停 
	int close( void );				// 关闭媒体 
	DWORD getLen( void ); // 获得媒体长度
	void setLen( void );  // 设置媒体长度 
	DWORD getdwPos( void );   // 获得m_dwPos 
	DWORD getMediaStatus( DWORD item ); // 获得媒体状态信息 
	void setdwPos( DWORD dwPos ); //  设置m_dwPos 
	
private:
	MCIDEVICEID m_mDeviceId;		// 设备类型 
	DWORD       m_dwLen;			// 媒体长度 
	DWORD       m_dwPos;			// 当前位置 
};

#endif  // __CMCIMGR__