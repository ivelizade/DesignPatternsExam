// DesignPatternsExam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
/*
AbstractFactory: Dialogs
1. Linux ve Windows uchun nezerde tutulmush dialog yaradin
2. Dialogun terkibi: TextInput, Button

Composite: Polls
1. Component: Agency (Leaf), Region, City (Composite)
2. Sheher uzre verilen seslerin sayini cap edin

Observer: Events
1. ObserverInterface yaradin: Bu interface-in esasinda 2 Observer yaradin.
Minimal interface: update(std::string data)
2. Observable class-i yaradin (observer container)
Minimal interface: notify()
*/

class Button;
class TextInput;
class WindowsButton;
class LinuxButton;
class WindowsTextInput;
class LinuxTextInput;
class DialougeFactory;
class WindowsDialouge;
class LinuxDialouge;

//-----------------------------------------------------------------------------------------
class Button
{
public:
	virtual void showButton() = 0;
};
//-----------------------------------------------------------------------------------------
class TextInput
{
public:
	virtual void showTextInput()=0;
};
//-----------------------------------------------------------------------------------------
class WindowsButton :public Button
{
public:
	void showButton()override { std::cout << "Windows Button\n"; }
};
//-----------------------------------------------------------------------------------------
class LinuxButton :public Button
{
public:
	void showButton()override { std::cout << "Linux Button\n"; }
};
//-----------------------------------------------------------------------------------------
class WindowsTextInput:public TextInput
{
public:
	void showTextInput()override { std::cout << "Windows Text Input\n"; }
};
//-----------------------------------------------------------------------------------------
class LinuxTextInput:public TextInput
{
public:
	void showTextInput()override { std::cout << "Linux Text Input\n"; }
};
//-----------------------------------------------------------------------------------------
class DialougeFactory
{
public:
	virtual	Button* createButton() = 0;
	virtual TextInput*createTextInput() = 0;
}; 
//------------------------------------------------------------------------------------------
class WindowsDialouge :public DialougeFactory
{
public:
	Button * createButton()override
	{
		Button*windowsButton = new WindowsButton;
		return windowsButton;
	}
	TextInput*createTextInput()override
	{
		TextInput*windowsTextInput = new WindowsTextInput;
		return windowsTextInput;
	}
};
//------------------------------------------------------------------------------------------
class LinuxDialouge :public DialougeFactory
{
public:
	Button * createButton()override
	{
		Button*linuxButton = new LinuxButton;
		return linuxButton;
	}
	TextInput*createTextInput()override
	{
		TextInput*linuxTextInput = new LinuxTextInput;
		return linuxTextInput;
	}
};
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
/*Composite: Polls
1. Component: Agency (Leaf), Region, City (Composite)
2. Sheher uzre verilen seslerin sayini cap edin
*/
class Component
{
public:
	virtual Component* printVotes() = 0;
};
class Agency:public Component
{
public:
	//void print
};
int main()
{
	LinuxDialouge linuxDialouge;
	Button* button = linuxDialouge.createButton();
	button->showButton();
	return 0;
}