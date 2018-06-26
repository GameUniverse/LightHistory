

/* CEGUI 窗口消息监听函数 */ 
LRESULT CALLBACK CEGUIWindowMessageProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

/* 将 Windows 虚拟键转换为 CEGUI 定义的扫描码 */
CEGUI::Key::Scan ConvertVirtualKeyToScanCode( WPARAM VirtualKey );