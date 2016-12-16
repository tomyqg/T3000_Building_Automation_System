// T3000_Default_MainView.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "T3000_Default_MainView.h"
#include "MainFrm.h"
 #include "../SQLiteDriver/CppSQLite3.h"

// T3000_Default_MainView

IMPLEMENT_DYNCREATE(T3000_Default_MainView, CFormView)

T3000_Default_MainView::T3000_Default_MainView()
	: CFormView(T3000_Default_MainView::IDD)
{

}

T3000_Default_MainView::~T3000_Default_MainView()
{
}

void T3000_Default_MainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPMODEL_COMBO, m_ip_model);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddress);
	DDX_Control(pDX, IDC_IPADDRESS2, m_Subnet_Mask);
	DDX_Control(pDX, IDC_IPADDRESS3, m_GatewayAddress);
	DDX_Control(pDX, IDC_MAC_ADDRESS, m_Edit_MacAddress);
	DDX_Control(pDX, IDC_EDIT_LISTENPORT, m_ListenPort);
	DDX_Control(pDX, IDC_BRAUDRATECOMBO, m_brandrate_combox);
	DDX_Control(pDX, IDC_EDIT_MSTP_MAC, m_Editor_macmstp);
	DDX_Control(pDX, IDC_COMBO_MSTP_MODBUS, m_mstpmodbus_combox);
	DDX_Control(pDX, IDC_EDIT_BIPPORT, m_BipPort_Edit);
}

BEGIN_MESSAGE_MAP(T3000_Default_MainView, CFormView)
	ON_BN_CLICKED(IDC_EDIT_ID, &T3000_Default_MainView::OnBnClickedEditId)
  
    ON_BN_CLICKED(IDC_APPLYBUTTON, &T3000_Default_MainView::OnBnClickedApplybutton)
    ON_CBN_SELCHANGE(IDC_IPMODEL_COMBO, &T3000_Default_MainView::OnCbnSelchangeIpmodelCombo)
	ON_EN_KILLFOCUS(IDC_EDIT_BIPPORT, &T3000_Default_MainView::OnEnKillfocusEditBipport)
	ON_CBN_SELCHANGE(IDC_COMBO_MSTP_MODBUS, &T3000_Default_MainView::OnCbnSelchangeComboMstpModbus)
	ON_EN_KILLFOCUS(IDC_EDIT_MSTP_MAC, &T3000_Default_MainView::OnEnKillfocusEditMstpMac)
	ON_CBN_KILLFOCUS(IDC_BRAUDRATECOMBO, &T3000_Default_MainView::OnCbnKillfocusBraudratecombo)
END_MESSAGE_MAP()


// T3000_Default_MainView diagnostics

#ifdef _DEBUG
void T3000_Default_MainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void T3000_Default_MainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// T3000_Default_MainView message handlers


void T3000_Default_MainView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	 
}

void T3000_Default_MainView::Fresh(){
    CString strTemp;
	strTemp.Format(_T("%d"),g_tstat_id);
	GetDlgItem(IDC_ID_EDIT)->SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),get_serialnumber());
	GetDlgItem(IDC_SERIALNUM_EDIT)->SetWindowTextW(strTemp);
	m_brandrate_combox.ResetContent();
	m_brandrate_combox.AddString(L"9600");
	m_brandrate_combox.AddString(L"19200");
	m_brandrate_combox.AddString(L"38400");
	m_brandrate_combox.AddString(L"57600");
	m_brandrate_combox.AddString(L"115200");
	m_brandrate_combox.SetCurSel(product_register_value[15]);

	m_mstpmodbus_combox.ResetContent();
	m_mstpmodbus_combox.AddString(L"Modbus RTU");
	m_mstpmodbus_combox.AddString(L"Modbus TCPIP");
	m_mstpmodbus_combox.AddString(L"BACnet MSTP");
	m_mstpmodbus_combox.AddString(L"BACnet BIP");
	m_mstpmodbus_combox.AddString(L"GSM");
	m_mstpmodbus_combox.AddString(L"Remote IP");
	m_mstpmodbus_combox.AddString(L"BIP2MSTP");
	m_mstpmodbus_combox.AddString(L"Unknown");
	if (product_register_value[21] == MODBUS_RS485)
	{
		m_mstpmodbus_combox.SetCurSel(0);
	}
	else if (product_register_value[21] == MODBUS_TCPIP)
	{
		m_mstpmodbus_combox.SetCurSel(1);
	}
	else if (product_register_value[21] == MODBUS_BACNET_MSTP)
	{
		m_mstpmodbus_combox.SetCurSel(2);
	}
	else if (product_register_value[21] == PROTOCOL_BACNET_IP)
	{
		m_mstpmodbus_combox.SetCurSel(3);
	}
	else if (product_register_value[21] == PROTOCOL_GSM)
	{
		m_mstpmodbus_combox.SetCurSel(4);
	}
	else if (product_register_value[21] == PROTOCOL_REMOTE_IP)
	{
		m_mstpmodbus_combox.SetCurSel(5);
	}
	else if (product_register_value[21] == PROTOCOL_BIP_TO_MSTP)
	{
		m_mstpmodbus_combox.SetCurSel(6);
	}
	else
	{
		m_mstpmodbus_combox.SetCurSel(7);
	}
	strTemp.Format(_T("%d"), product_register_value[39]);
	m_Editor_macmstp.SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"), product_register_value[38]);
	m_BipPort_Edit.SetWindowTextW(strTemp);

	strTemp.Format(_T("%0.1f"),get_curtstat_version());
	GetDlgItem(IDC_FIRMWARV_EDIT)->SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),product_register_value[8]);//8
	GetDlgItem(IDC_HARDWAREV_EDIT)->SetWindowTextW(strTemp);
	int nModel=product_register_value[7];
	CString ProductName = GetProductName(nModel);
	if (nModel == PM_CS_RSM_AC||nModel == PM_CS_SM_AC)
	{
		if (product_register_value[11] == 0)
		{
			ProductName+=_T("-100A");
		}
		else if (product_register_value[11]==1)
		{
			ProductName+=_T("-200A");
		}
		else if (product_register_value[11]==2)
		{
			ProductName+=_T("-300A");
		}

	}
	
	GetDlgItem(IDC_MODEL_EDIT)->SetWindowTextW(ProductName);
	strTemp.Format(_T("%d"),product_register_value[9]);
	GetDlgItem(IDC_PIC_EDIT)->SetWindowText(strTemp);
	MODBUS_BAUDRATE = 15;
    if (product_register_value[7] == PM_T322AI 
	              || product_register_value[7] == PM_T38AI8AO6DO 
	               || product_register_value[7] == PM_T3PT12
	              ||product_register_value[7]==STM32_HUM_NET )
    {
        GetDlgItem (IDC_STATIC_IPTIPS)->ShowWindow (TRUE);
        GetDlgItem (IDC_APPLYBUTTON)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATIC_IPMODEL)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATIC_IPADDRESS)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATICSUBNETMASK)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATICGATEWAYADDRESS)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATIC_LISTENNINGPORT)->ShowWindow (TRUE);
        GetDlgItem (IDC_STATICMACADDRESS)->ShowWindow (TRUE);
        CString strtemp;
        int CO2_NET_MODBUS_MAC_ADDRESS_START = 40;
        strtemp.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+1],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+2],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+3],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+4],product_register_value[CO2_NET_MODBUS_MAC_ADDRESS_START+5]);
        m_Edit_MacAddress.SetWindowText(strtemp);
        m_Edit_MacAddress.ShowWindow (TRUE);
        int CO2_NET_MODBUS_IP_MODE = 46;
        m_ip_model.SetCurSel(product_register_value[CO2_NET_MODBUS_IP_MODE]);
        m_ip_model.ShowWindow (TRUE);
        //CO2_NET_MODBUS_IP_ADDRESS_START
        //CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START
        //CO2_NET_MODBUS_GATEWAY_ADDRESS_START
        //CO2_NET_MODBUS_TCP_SERVER_ENABLE
        //CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START
        int   CO2_NET_MODBUS_IP_ADDRESS_START = 47;
        m_ipaddress.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START],
            (BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START+1],
            (BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START+2],
            (BYTE)product_register_value[CO2_NET_MODBUS_IP_ADDRESS_START+3]);
         int   CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START  =     51;
          m_ipaddress.ShowWindow (TRUE);
        m_Subnet_Mask.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START],
            (BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START+1],
            (BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START+2],
            (BYTE)product_register_value[CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_START+3]);
             int   CO2_NET_MODBUS_GATEWAY_ADDRESS_START  =     55;
             m_Subnet_Mask.ShowWindow (TRUE);

        m_GatewayAddress.SetAddress((BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START],
            (BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START+1],
            (BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START+2],
            (BYTE)product_register_value[CO2_NET_MODBUS_GATEWAY_ADDRESS_START+3]);
          int CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START =  60;
          m_GatewayAddress.ShowWindow (TRUE);
        strtemp.Format(_T("%d"),product_register_value[CO2_NET_MODBUS_LISTEN_PORT_AT_TCP_SERVER_MODE_START]);
        m_ListenPort.SetWindowText(strtemp);
        m_ListenPort.ShowWindow (TRUE);


    }
	else if(product_register_value[7] == PWM_TRANSDUCER)
	{
		GetDlgItem(IDC_STATIC_IPTIPS)->ShowWindow(FALSE);
		GetDlgItem(IDC_APPLYBUTTON)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_IPMODEL)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_IPADDRESS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATICSUBNETMASK)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATICGATEWAYADDRESS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_LISTENNINGPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATICMACADDRESS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_BIPPORT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MAC_MSTP)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MSTP_MODBUS)->ShowWindow(FALSE);

		m_Edit_MacAddress.ShowWindow(FALSE);
		m_ip_model.ShowWindow(FALSE);
		m_ipaddress.ShowWindow(FALSE);
		m_Subnet_Mask.ShowWindow(FALSE);
		m_GatewayAddress.ShowWindow(FALSE);
		m_ListenPort.ShowWindow(FALSE);
		m_Editor_macmstp.ShowWindow(FALSE);
		m_mstpmodbus_combox.ShowWindow(FALSE);
		m_BipPort_Edit.ShowWindow(FALSE);


	}
	else
    {
        GetDlgItem (IDC_STATIC_IPTIPS)->ShowWindow (FALSE);
        GetDlgItem (IDC_APPLYBUTTON)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATIC_IPMODEL)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATIC_IPADDRESS)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATICSUBNETMASK)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATICGATEWAYADDRESS)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATIC_LISTENNINGPORT)->ShowWindow (FALSE);
        GetDlgItem (IDC_STATICMACADDRESS)->ShowWindow (FALSE);

        m_Edit_MacAddress.ShowWindow (FALSE);
        m_ip_model.ShowWindow (FALSE);
        m_ipaddress.ShowWindow (FALSE);
        m_Subnet_Mask.ShowWindow (FALSE);
        m_GatewayAddress.ShowWindow (FALSE);
         m_ListenPort.ShowWindow (FALSE);



    }

}
#include "EreaseDlg.h"

void T3000_Default_MainView::OnBnClickedEditId()
{
	 CEreaseDlg dlg;
	 dlg.DoModal();

     CString str;
     str.Format (_T("%d"),g_tstat_id);

     GetDlgItem (IDC_ID_EDIT)->SetWindowTextW(str);
}


//void T3000_Default_MainView::OnBnClickedButtonGoToInput()
//{
//     /* if (product_type == T3000_T3_MODULES )
//     {
//         SwitchToPruductType(DLG_DIALOG_T3_INPUTS_VIEW);
//    }*/
//    CMainFrame* pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
//    pFrame->OnControlInputs ();
//}


void T3000_Default_MainView::OnBnClickedApplybutton()
{
    int m_nListenPort=0;
    BeginWaitCursor();
    //m_nListenPort	
    CString strText;
    m_ListenPort.GetWindowText(strText);
    if(!strText.IsEmpty())
        m_nListenPort=_wtoi(strText);
    if(m_nListenPort>=12767)
    {
        AfxMessageBox(_T("The listen port number is too big, please change it."));
        return;
    }
    if(m_nListenPort<=0)
    {
        AfxMessageBox(_T("The listen port number must be greater than 0!"));
        return;
    }
    write_one(g_tstat_id,75,m_nListenPort);
    product_register_value[75]=m_nListenPort;
    BYTE address1,address2,address3,address4;
    m_ipaddress.GetAddress(address1,address2,address3,address4);

    int sel = m_ip_model.GetCurSel ();
     write_one(g_tstat_id,61,sel);

    int CO2_NET_MODBUS_IP_ADDRESS_GHOST_START = 62 ;
    int n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START,address1);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START+1,address2);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START+2,address3);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_IP_ADDRESS_GHOST_START+3,address4);
    int CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START = 66;
    m_Subnet_Mask.GetAddress(address1,address2,address3,address4);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+0,address1);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+1,address2);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+2,address3);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_SUBNET_MASK_ADDRESS_GHOST_START+3,address4);
    m_GatewayAddress.GetAddress(address1,address2,address3,address4);
    int CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START =   70;
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START,address1);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START+1,address2);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START+2,address3);
    n=write_one(g_tstat_id,CO2_NET_MODBUS_GATEWAY_ADDRESS_GHOST_START+3,address4);
    int CO2_NET_MODBUS_ENABLE_GHOST = 76;
    n=write_one(g_tstat_id,CO2_NET_MODBUS_ENABLE_GHOST,1);//Ê¹ÄÜÖ®ºó

    Sleep(5*1000);



    CMainFrame* pPraent=(CMainFrame*)GetParent();

    CString strBuilding,strSubBuilding;
    strBuilding=pPraent->m_strCurMainBuildingName;
    strSubBuilding=pPraent->m_strCurSubBuldingName;
    CString strIP,strPort;
    strPort.Format(_T("%d"),product_register_value[75]);
    // BYTE address1,address2,address3,address4;
    m_ipaddress.GetAddress(address1,address2,address3,address4);
    strIP.Format(_T("%d.%d.%d.%d"),address1,address2,address3,address4);
    if(g_CommunicationType==1)//TCP
    {
       /* int nPort;
        nPort=_wtoi(strPort);*/
        //m_strIP=build_info.strIp; 
        g_CommunicationType=1;
        SetCommunicationType(g_CommunicationType);
        BOOL bOk=FALSE;
        bOk=Open_Socket2(strIP,m_nListenPort);
        CString strInfo;

        strInfo.Format((_T("Open IP:%s successful")),strIP);//prompt info;
        SetPaneString(1,strInfo);
        if(bOk)
        {
            try
			{
			CppSQLite3DB SqliteDBBuilding;
			CppSQLite3Table table;
			CppSQLite3Query q;
			SqliteDBBuilding.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);


                CString strSql;
                //strSql.Format(_T("update Building set Ip_Address='%s' where Ip_Address='%s'"),strIP,pPraent->m_strIP);
                //t_pCon->Execute(strSql.GetString(),NULL,adCmdText);

                // ¸Änode
                CString strSID;

                strSID.Format(_T("%d"), get_serialnumber());
                strSql.Format(_T("update ALL_NODE set Bautrate='%s',Com_Port='%s' where Serial_ID='%s'"),strIP,strPort,strSID); //bautrate ·ÅIP
                 SqliteDBBuilding.execDML((UTF8MBSTR)strSql);

                SqliteDBBuilding.closedb();

            }
            catch(_com_error *e)
            {
                AfxMessageBox(e->ErrorMessage());
            }

            pPraent->m_strIP=strIP;
            pPraent->ScanTstatInDB();

        }
        else
        {

        }



    }
    EndWaitCursor();
}


void T3000_Default_MainView::OnCbnSelchangeIpmodelCombo()
{ 

}


void T3000_Default_MainView::OnEnKillfocusEditBipport()
{
	// TODO: Add your control notification handler code here
}


void T3000_Default_MainView::OnCbnSelchangeComboMstpModbus()
{
	// TODO: Add your control notification handler code here
}


void T3000_Default_MainView::OnEnKillfocusEditMstpMac()
{
	// TODO: Add your control notification handler code here
}


void T3000_Default_MainView::OnCbnKillfocusBraudratecombo()
{
	if (product_register_value[MODBUS_BAUDRATE] == m_brandrate_combox.GetCurSel())	//Add this to judge weather this value need to change.
		return;

	/* Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_BAUDRATE,m_braudRateCombox.GetCurSel(),
	product_register_value[MODBUS_BAUDRATE],this->m_hWnd,IDC_BRAUDRATECOMBO,_T("BAUDRATE"));*/

	int ret = write_one(g_tstat_id, MODBUS_BAUDRATE, m_brandrate_combox.GetCurSel());
	int index_brandrate = m_brandrate_combox.GetCurSel();
	int brandrate = 19200;

	if (index_brandrate == 0)
	{
		brandrate = 9600;
	}
	else if (index_brandrate == 1)
	{
		brandrate = 19200;
	}
	else if (index_brandrate == 2)
	{
		brandrate = 38400;
	}
	else if (index_brandrate == 3)
	{
		brandrate = 57600;
	}
	else if (index_brandrate == 4)
	{
		brandrate = 115200;
	}
	CString SqlText;

	SqlText.Format(_T("update ALL_NODE set Bautrate = '%d' where Serial_ID='%d'"), brandrate, get_serialnumber());
	Change_BaudRate(brandrate);


	CppSQLite3DB SqliteDBBuilding;
	CppSQLite3Table table;
	CppSQLite3Query q;
	SqliteDBBuilding.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);

	SqliteDBBuilding.execDML((UTF8MBSTR)SqlText);
	SqliteDBBuilding.closedb();
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pFrame->ScanTstatInDB();
}
