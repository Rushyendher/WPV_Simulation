#include <string>
#include<thread>
#include<chrono>

#include "DoublyLL.h"

using std::cout;
using std::endl;

extern int totalImages;

Node *head = NULL;
Node *tail = NULL;
Node *trackingNode = NULL;

DoublyLL::DoublyLL()
{
	head = NULL;
}

Node * DoublyLL::CreateNode(Image * imgData)
{
	struct Node *newNode = NULL;
	newNode = new(struct Node);

	newNode->next = NULL;
	newNode->img = imgData;

	return newNode;
}

void DoublyLL::InsertLast(Image * imgData)
{
	struct Node *tempNode = NULL;
	tempNode = CreateNode(imgData);

	if (tempNode != NULL)
	{
		if (head == NULL)
		{
			tempNode->prev = NULL;
			head = tempNode;
			tail = tempNode;
		}
		else
		{
			if (tail->next == NULL)
			{
				tail->next = tempNode;
				tempNode->prev = tail;
				tail = tempNode;
			}
		}
	}
}

Node * DoublyLL::SearchNode(size_t id)
{
	if (head == NULL)
	{
		std::cout << "No more photos" << std::endl;
		return NULL;
	}

	struct Node *current = NULL;
	current = head;

	bool found = false;

	while (current != NULL)
	{
		if (current->img->GetImageId() == id)
		{
			found = true;
			break;
		}
		else
		{
			current = current->next;
		}
	}

	if (found)
		return current;
	else
		return NULL;
}

void DoublyLL::DeleteNode(size_t id)
{
	struct Node *current = NULL;
	current = SearchNode(id);

	if (current != NULL)
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	free(current);
	return;
}

void DoublyLL::DisplayFullDetails(Node * node)
{
	if (node != NULL)
	{
		Image *image = node->img;
		image->Display2dImage();
		std::cout << "Width	: " << image->GetWidth() << std::endl;
		std::cout << "Height	: " << image->GetHeight() << std::endl;
	}
	std::cout << std::endl;
}

void DoublyLL::DisplayImageInfo()
{
	if (trackingNode != NULL)
	{
		Image * img = trackingNode->img;
		if (img != NULL)
		{
			cout << "ID		: " << img->GetImageId() << endl;
			cout << "Width		: " << img->GetWidth() << endl;
			cout << "Height		: " << img->GetHeight() << endl;
		}
	}
	cout << endl;

}

void DoublyLL::PrintImageInfo()
{
	std::cout << "Please wait while its printing...";
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	
	std::cout << std::endl;

	DisplayFullDetails(trackingNode);
}

void DoublyLL::EmailImage()
{
	std::string emailId;
	std::cout << "Enter email id ";
	std::cin >> emailId;

	std::cout << "Please wait while it send...";
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	std::cout << std::endl;
	std::cout << "Image sent to your mail :)" << std::endl << std::endl;
}

void DoublyLL::CallNext()
{
	system("cls");
	if (trackingNode != NULL)
	{
		if (trackingNode->next != NULL)
		{
			DisplayImage(trackingNode->next);
			trackingNode = trackingNode->next;
		}
		else
		{
			std::cout << "This is the last image" << std::endl;
		}
	}
}

void DoublyLL::CallPrev()
{
	system("cls");
	if (trackingNode != NULL)
	{
		if (trackingNode->prev != NULL)
		{
			DisplayImage(trackingNode->prev);
			trackingNode = trackingNode->prev;
		}
		else
		{
			std::cout << "This is the first image" << std::endl;
		}
	}
}

void DoublyLL::DisplayFirstImage()
{
	trackingNode = head;

	if (trackingNode != NULL)
	{
		trackingNode->img->Display2dImage();
	}
}

void DoublyLL::DisplayImage(Node * node, char gv)
{
	if (node != NULL)
	{
		if (gv == 'T')
			node->img->Display2dImageForGV();
		else
			node->img->Display2dImage();
	}
}

void DoublyLL::SearchImageById(size_t id)
{
	system("cls");
	Node * currentNode = SearchNode(id);

	if (currentNode != NULL)
	{
		DisplayImage(currentNode);
		trackingNode = currentNode;
	}
	else
	{
		cout << "No image with id " << id << endl;
	}

}

void DoublyLL::CropImage(int w, int h)
{
	system("cls");
	if (trackingNode)
	{
		trackingNode->img->SetWidth(w);

		int localHeight = trackingNode->img->GetHeight();

		if (h > localHeight)
		{
			cout << "Height cannot be greater than original height i.e " << strlen(trackingNode->img->GetImgData()) << endl;
			trackingNode->img->SetHeight(localHeight);
			return;
		}

		trackingNode->img->SetHeight(h);

		trackingNode->img->Display2dImage();
	}
}

void DoublyLL::ShowListView()
{
	system("cls");
	Node *current = head;

	cout << endl;
	while (current != NULL)
	{
		DisplayImage(current,'T');
		current = current->next;
	}

}

void DoublyLL::DeleteCurrentNode()
{
	Node *current = trackingNode;

	if (totalImages <= 0)
	{
		cout << "No Images" << endl;
		exit(0);
	}

	if (head == NULL || current == NULL)
		return;

	if (head == current)
	{
		head = current->next;
		trackingNode = head;
	}

	if (current->next != NULL)
	{
		current->next->prev = current->prev;
		trackingNode = current->next;
	}

	if (current->prev != NULL)
		current->prev->next = current->next;
	
	totalImages -= 1;

	delete current;
	system("cls");
	DisplayImage(trackingNode);


}

void DoublyLL::SlideShow(size_t interval)
{
	Node *current = head;
	while (current != NULL)
	{
		DisplayImage(current);

		std::this_thread::sleep_for(std::chrono::milliseconds(interval * 1000));

		current = current->next;
		system("cls");
	}
}

void DoublyLL::RotateImage()
{

	try 
	{
		system("cls");
		if (trackingNode)
		{
			if (trackingNode->img->GetHeight() != trackingNode->img->GetWidth())
				throw "Image should be a square Matrix :(";
			trackingNode->img->Rotate();
			DisplayImage(trackingNode);
		}
	}
	catch (const char *s)
	{
		cout << s << endl;
		exit(EXIT_FAILURE);
	}

}

void DoublyLL::CleanUpMemory()
{
	Node *curr = head;
	while (curr != NULL)
	{
		curr->img->~Image();
		curr = curr->next;
		delete curr;
	}
}



