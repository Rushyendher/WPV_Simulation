#include <iostream>
#include "Image.h"


struct Node
{
	Image *img;
	Node *next;
	Node *prev;
};


class DoublyLL
{
private:

	Node *SearchNode(size_t id);
	Node * CreateNode(Image *imgData);
	void DisplayImage(Node *node,char gv='F');
	void DisplayFullDetails(Node *node);

public:

	DoublyLL();

	void InsertLast(Image *imgData);
	void DeleteNode(size_t id);
	
	void DisplayImageInfo();
	void PrintImageInfo();
	void EmailImage();
	void CallNext();
	void CallPrev();
	void DisplayFirstImage();

	void SearchImageById(size_t id);

	void CropImage(int w, int h);
	void ShowListView();

	void DeleteCurrentNode();
	void SlideShow(size_t interval);
	void RotateImage();

	void CleanUpMemory();
	~DoublyLL();
};