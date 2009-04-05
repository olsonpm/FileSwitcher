/*
This file is part of Plugin Template for Notepad++
Copyright (C)2006 Jens Lorenz <jens.plugin.npp@gmx.de>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef SWITCH_DIALOG_H
#define SWITCH_DIALOG_H
#include <windows.h>
#include <tchar.h>
#include <map>
#include "StaticDialog.h"
#include "EditFile.h"
#include "resource.h" 
#include "FileSwitcher.h"

class SwitchDialog : public StaticDialog
{

public:
	SwitchDialog() : StaticDialog() {};
    
	void init(HINSTANCE hInst, NppData nppData, struct options_t *options, std::map<int, TCHAR *> *typedForFile)
	{
		_nppData = nppData;
		Window::init(hInst, nppData._nppHandle);

		// Flag that the dimensions and position have not been set
		_dialogX = -1;
		
		_typedForFile = typedForFile;

		_options = options;
		refreshSearchFlags();
	};

   	void doDialog();

	void setFilenames(TCHAR **filenames, int nbFiles);
	void setWindowPosition(int x, int y, int width, int height);
	void getWindowPosition(RECT &rc);
	

    virtual void destroy() {};
	
protected :
	virtual BOOL CALLBACK run_dlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void showAndPositionWindow(void);

private:
	/* Handles */
	NppData			_nppData;
    HWND			_HSource;

	/* Private data */
	EditFile** _editFiles;
	int _nbFiles;
	RECT _okButtonRect;
	RECT _cancelButtonRect;
	RECT _listboxRect;
	RECT _editboxRect;
	BOOL _overrideCtrlTab;

	int _dialogWidth, _dialogHeight;
	int _dialogX, _dialogY;

	/* Search flags */
	BOOL _startOnly;
	BOOL _caseSensitive;

	struct options_t *_options;
	std::map<int, TCHAR *> *_typedForFile;
	std::map<int, int> _bufferToIndex;

	/* Private methods */
    void cleanup(void);
	void searchFiles(TCHAR* searchString);
	void addListEntry(EditFile &editFile, bool selected);
	void clearList(void);
	void moveSelectionUp(BOOL wrap);
	void moveSelectionDown(BOOL wrap);
	void moveSelectionTop(void);
	void moveSelectionBottom(void);
	void updateWindowPosition(void);
	void refreshSearchFlags(void);
	void switchToSelectedBuffer(void);

	/* Constants */
	static const int SEARCH_STRING_BUFFER_MAX = 255;
	
	

	
    
		


	};



#endif // SWITCH_DIALOG_H