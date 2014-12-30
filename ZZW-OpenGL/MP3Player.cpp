#include "MP3Player.h"

CMciMgr::CMciMgr( void )
{
  m_mDeviceId = 0;
  m_dwLen = 0;
  m_dwPos = 0;
}

CMciMgr::~CMciMgr( void )
{
  if( m_mDeviceId != 0 )
    close();
}

int CMciMgr::open( const LPCSTR lpsFileName, const LPCSTR lpsDeviceType ) // 打开媒体 
{
  int nRet = -1;
  MCI_OPEN_PARMS mciOpenParam;
  MCI_STATUS_PARMS mciStatusParam;
  mciOpenParam.dwCallback = NULL;
  mciOpenParam.lpstrAlias = NULL;
  mciOpenParam.lpstrElementName = lpsFileName;
  mciOpenParam.lpstrDeviceType = lpsDeviceType;
  mciOpenParam.wDeviceID = NULL;
  // 打开媒体
  if( lpsDeviceType )
    nRet = mciSendCommand( NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpenParam );
  else
    nRet = mciSendCommand( NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpenParam );
  if( nRet == 0 )
    // 打开媒体 成功 
    m_mDeviceId = mciOpenParam.wDeviceID;
  // 设置媒体长度 
  setLen();
  // // 设置当前位置 
  setdwPos( 0 );
  return nRet;
}

int CMciMgr::play( void )              // 播放 
{
  int nRet = -1;
  MCI_SEEK_PARMS mciSeekParam;
  mciSeekParam.dwCallback = NULL;
  mciSeekParam.dwTo = m_dwPos;
  nRet = mciSendCommand( m_mDeviceId, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)&mciSeekParam );
  if( nRet )
    return nRet;
    
  nRet = -1;
  MCI_PLAY_PARMS mciPlayParam;
  mciPlayParam.dwCallback = NULL; // 接受设备消息的窗口句柄, 图形界面下你可以修改一下这里, 不改也无妨 
  //mciPlayParam.dwFrom = m_dwPos; 
  //mciPlayParam.dwTo = m_dwLen;
  // 播放媒体
  nRet = mciSendCommand( m_mDeviceId, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlayParam );
  return nRet;
}

int CMciMgr::play( const int &hour, const int &min, const int &sec ) // 从指定位置开始播放 
{
  int nRet = -1;
  DWORD dwPos = MCI_MAKE_HMS( hour, min, sec );
  setdwPos( dwPos );
  nRet = play();
  return nRet;
}

int CMciMgr::play( DWORD dwPos ) // 从指定位置开始播放 
{
  int nRet = -1;
  setdwPos( dwPos );
  nRet = play();
  return nRet;
}

int CMciMgr::pause( void )             // 暂停 
{
  return 0;
}

int CMciMgr::close( void ) // 关闭媒体 
{
  MCI_GENERIC_PARMS mciGenericParam;
  mciGenericParam.dwCallback = NULL;
  mciSendCommand( m_mDeviceId, MCI_CLOSE,MCI_WAIT, (DWORD)&mciGenericParam );
  return 0;
}

void CMciMgr::setLen( void ) // 设置媒体长度
{
  m_dwLen = getMediaStatus(MCI_STATUS_LENGTH);
}

DWORD CMciMgr::getLen( void ) // 获得媒体长度
{
  return m_dwLen;
}

DWORD CMciMgr::getdwPos( void )   // 获得当前位置 
{
  return getMediaStatus( MCI_STATUS_POSITION );
}

void CMciMgr::setdwPos( DWORD dwPos ) //  设置m_dwPos 
{
  m_dwPos = dwPos;
}

DWORD CMciMgr::getMediaStatus( DWORD item ) // 获得媒体状态信息 
{
  MCI_STATUS_PARMS mciStatusParam;
  mciStatusParam.dwCallback = NULL;
  mciStatusParam.dwItem = item;
  mciStatusParam.dwReturn = 0;
  mciSendCommand( m_mDeviceId, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciStatusParam );
  return mciStatusParam.dwReturn;
}

int CMciMgr::playloop()
{
	int nRet = -1;
	MCI_SEEK_PARMS mciSeekParam;
	mciSeekParam.dwCallback = NULL;
	mciSeekParam.dwTo = m_dwPos;
	nRet = mciSendCommand( m_mDeviceId, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)&mciSeekParam );
	if( nRet )
		return nRet;

	nRet = -1;
	MCI_PLAY_PARMS mciPlayParam;
	mciPlayParam.dwCallback = NULL; // 接受设备消息的窗口句柄, 图形界面下你可以修改一下这里, 不改也无妨 
	//mciPlayParam.dwFrom = m_dwPos; 
	//mciPlayParam.dwTo = m_dwLen;
	// 播放媒体
	nRet = mciSendCommand( m_mDeviceId, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&mciPlayParam );
	return nRet;
}