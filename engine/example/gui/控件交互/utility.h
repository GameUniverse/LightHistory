

/* CEGUI ������Ϣ�������� */ 
LRESULT CALLBACK CEGUIWindowMessageProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

/* �� Windows �����ת��Ϊ CEGUI �����ɨ���� */
CEGUI::Key::Scan ConvertVirtualKeyToScanCode( WPARAM VirtualKey );