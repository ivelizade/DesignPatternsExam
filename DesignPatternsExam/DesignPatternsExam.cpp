// DesignPatternsExam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<unordered_map>
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
class Component;
class Agency;
class Composite;
//-----------------------------------------------------------------------------------------
class ObserverInterface;
class Observer;
class ObserverableInterface;
class Observerable;
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
2. Sheher uzre verilen seslerin sayini cap edinclass Component class Agency class Composite
*/
class Component
{
public:
	virtual int printVotes() = 0;
	virtual void add(Component*) = 0;
};
//------------------------------------------------------------------------------------------
class Agency:public Component
{
	int numberOfVotes = 0;
public:
	int printVotes()override
	{
		return numberOfVotes;
	}
	void vote() { numberOfVotes++; }
	void add(Component *c) override
	{
		throw std::runtime_error("Not implemented");
	}
};
//------------------------------------------------------------------------------------------
class Composite:public Component
{
	std::unordered_map<Component*, Component*> Leafs;
public: 
	int printVotes()override
	{
		int numberOfVotes = 0;
		for (auto& agency:Leafs)
		{
			
			numberOfVotes+= agency.second->printVotes();
		}
		return numberOfVotes;
	}
	void add(Component*comp)override
	{
		Leafs[comp] = comp;
	}

};
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
class ObserverInterface
{
public:
	virtual void upDate(std::string data) = 0;
};
//-----------------------------------------------------------------------------------------
class Observer:ObserverInterface
{
	
public:
	void upDate(std::string data)
	{
		std::cout << data;
	}
	
};
//-----------------------------------------------------------------------------------------
class ObserverableInterface
{
public:
	virtual void notify() = 0;
};
//-----------------------------------------------------------------------------------------
class Observerable :ObserverableInterface
{
	std::vector<Observer> allObservers;
public:
	void notify()
	{
		for (auto observer:allObservers)
		{
			observer.upDate("New Version Of Program Available");
		}
	}
};
//-----------------------------------------------------------------------------------------
int main()
{
	Agency*agency1 = new Agency;
	agency1->vote();
	Agency*agency2 = new Agency;
	agency2->vote(); agency2->vote();
	Composite*Region1=new Composite;
	Region1->add(agency1);
	Region1->add(agency2);
	Composite City;
	City.add(Region1);
	std::cout << City.printVotes() << '\n';
	//------------------------------------------------------------------------------------------
	LinuxDialouge linuxDialouge;
	Button* button = linuxDialouge.createButton();
	button->showButton();
	//------------------------------------------------------------------------------------------

	return 0;
}