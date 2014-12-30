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

int CMciMgr::open( const LPCSTR lpsFileName, const LPCSTR lpsDeviceType ) // ��ý�� 
{
  int nRet = -1;
  MCI_OPEN_PARMS mciOpenParam;
  MCI_STATUS_PARMS mciStatusParam;
  mciOpenParam.dwCallback = NULL;
  mciOpenParam.lpstrAlias = NULL;
  mciOpenParam.lpstrElementName = lpsFileName;
  mciOpenParam.lpstrDeviceType = lpsDeviceType;
  mciOpenParam.wDeviceID = NULL;
  // ��ý��
  if( lpsDeviceType )
    nRet = mciSendCommand( NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpenParam );
  else
    nRet = mciSendCommand( NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpenParam );
  if( nRet == 0 )
    // ��ý�� �ɹ� 
    m_mDeviceId = mciOpenParam.wDeviceID;
  // ����ý�峤�� 
  setLen();
  // // ���õ�ǰλ�� 
  setdwPos( 0 );
  return nRet;
}

int CMciMgr::play( void )              // ���� 
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
  mciPlayParam.dwCallback = NULL; // �����豸��Ϣ�Ĵ��ھ��, ͼ�ν�����������޸�һ������, ����Ҳ�޷� 
  //mciPlayParam.dwFrom = m_dwPos; 
  //mciPlayParam.dwTo = m_dwLen;
  // ����ý��
  nRet = mciSendCommand( m_mDeviceId, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlayParam );
  return nRet;
}

int CMciMgr::play( const int &hour, const int &min, const int &sec ) // ��ָ��λ�ÿ�ʼ���� 
{
  int nRet = -1;
  DWORD dwPos = MCI_MAKE_HMS( hour, min, sec );
  setdwPos( dwPos );
  nRet = play();
  return nRet;
}

int CMciMgr::play( DWORD dwPos ) // ��ָ��λ�ÿ�ʼ���� 
{
  int nRet = -1;
  setdwPos( dwPos );
  nRet = play();
  return nRet;
}

int CMciMgr::pause( void )             // ��ͣ 
{
  return 0;
}

int CMciMgr::close( void ) // �ر�ý�� 
{
  MCI_GENERIC_PARMS mciGenericParam;
  mciGenericParam.dwCallback = NULL;
  mciSendCommand( m_mDeviceId, MCI_CLOSE,MCI_WAIT, (DWORD)&mciGenericParam );
  return 0;
}

void CMciMgr::setLen( void ) // ����ý�峤��
{
  m_dwLen = getMediaStatus(MCI_STATUS_LENGTH);
}

DWORD CMciMgr::getLen( void ) // ���ý�峤��
{
  return m_dwLen;
}

DWORD CMciMgr::getdwPos( void )   // ��õ�ǰλ�� 
{
  return getMediaStatus( MCI_STATUS_POSITION );
}

void CMciMgr::setdwPos( DWORD dwPos ) //  ����m_dwPos 
{
  m_dwPos = dwPos;
}

DWORD CMciMgr::getMediaStatus( DWORD item ) // ���ý��״̬��Ϣ 
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
	mciPlayParam.dwCallback = NULL; // �����豸��Ϣ�Ĵ��ھ��, ͼ�ν�����������޸�һ������, ����Ҳ�޷� 
	//mciPlayParam.dwFrom = m_dwPos; 
	//mciPlayParam.dwTo = m_dwLen;
	// ����ý��
	nRet = mciSendCommand( m_mDeviceId, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&mciPlayParam );
	return nRet;
}