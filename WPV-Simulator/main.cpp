#include<iostream>
#include<thread>
#include<chrono>
#include<ctime>
#include<string>

#include "Image.h"
#include "DoublyLL.h"


using namespace std;

const char symbols[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const int WIDTH = 6;
const int HEIGHT = 6;

int totalImages = 0;

char *RandomImage();
void DisplayChoiceDetails(DoublyLL *dll);

int main(void)
{
	srand(time(0));

	cout << "\n\n\n";
	cout << "--------------------------------------------------------------------------------" << endl;

	cout << "\n\n\n";

	cout << "\t\t\tWindows Photo Viewer - Simulation" << endl;
	cout << endl;
	cout << "This application just shows the simulation of Windows photo viewer. It just assumes a random matrix data as an image.";
	cout << "\n\n\n";

	cout << "--------------------------------------------------------------------------------" << endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));

	system("cls");
	unsigned long noOfImages;
	cout << "How many images you would like to load: ";
	cin >> noOfImages;

	totalImages = noOfImages;

	std::cout << "Loading images...";
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	system("cls");

	DoublyLL *dll = new DoublyLL();

	for (unsigned long i = 0; i < noOfImages; i++)
	{
		Image *img = new Image(i + 1, WIDTH, HEIGHT,RandomImage());
		dll->InsertLast(img);
	}


	dll->DisplayFirstImage();

	DisplayChoiceDetails(dll);

	dll->CleanUpMemory();

	return 0;
}

char *RandomImage()
{
	char *randStr = new char[WIDTH + 1];
	for (int i = 0; i < WIDTH; i++)
	{
		randStr[i] = symbols[rand() % 26];
	}
	return randStr;
}

void DisplayChoiceDetails(DoublyLL *dll)
{
	cout << endl;

	cout << "\t   P) Print \t"
		<< "  E) Email \t"
		<< "  R) Rotate \t"
		<< "  I) Info \t"
		<< endl;

	
	cout<< "\t   A) Prev \t"
		<< "  D) Next \t"
		<< "  C) Crop \t"
		<< "  L) Listview " << endl;

	cout << "\t   S) Search \t"
		<< "  X) Delete \t"
		<< "  T) SlideShow"
		<< "    Q) Quit" << endl;

	char choice;
	cin >> choice;

	switch (choice)
	{
	case 'T':
	case 't':
		size_t interval;

		cout << "Enter Time Interval(sec): ";
		cin >> interval;
		system("cls");
		dll->SlideShow(interval);
		dll->DisplayFirstImage();
		DisplayChoiceDetails(dll);

	case 'L':
	case 'l':
		dll->ShowListView();
		DisplayChoiceDetails(dll);

		break;

	case 'S':
	case 's':
		size_t id;
		cout << "Enter Id: ";
		cin >> id;

		dll->SearchImageById(id);
		DisplayChoiceDetails(dll);
		break;

	case 'X':
	case 'x':

		dll->DeleteCurrentNode();
		DisplayChoiceDetails(dll);
		break;

	case 'P':
	case 'p':
		dll->PrintImageInfo();
		DisplayChoiceDetails(dll);
		break;

	case 'E':
	case 'e':
		dll->EmailImage();
		DisplayChoiceDetails(dll);
		break;

	case 'Q':
	case 'q':
		exit(0);
		break;

	case 'R':
	case 'r':
		dll->RotateImage();
		DisplayChoiceDetails(dll);
		break;
		
	case 'A':
	case 'a':
		//previous image
		dll->CallPrev();
		DisplayChoiceDetails(dll);
		break;

	case 'D':
	case 'd':
		//Next image
		dll->CallNext();
		DisplayChoiceDetails(dll);
		break;

	case 'C':
	case 'c':

		int w, h;
		cout << "Enter Width: ";
		cin >> w;
		cout << "Enter Height: ";
		cin >> h;

		dll->CropImage(w, h);
		DisplayChoiceDetails(dll);

		break;

	case 'I':
	case 'i':
		dll->DisplayImageInfo();
		DisplayChoiceDetails(dll);
		break;

	default:
		system("cls");
		dll->DisplayFirstImage();
		cout << "Option unavailable !!!" << endl;
		DisplayChoiceDetails(dll);
		break;
	}

}



