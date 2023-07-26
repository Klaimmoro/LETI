#include "binarytree.h"
int liness = 200;
double sc = 1.2;
int ra = 30;
int r = 30;
const int treesize = 1000;



void bFs(Node* head)
{
	queue<Node*> q;

	q.push(head);

	int i = treesize;

	while (i != 0) {
		Node* tmp = q.front();
		q.pop();
		//cout << tmp->data << endl;
		i--;
		if (tmp->nextl) {
			head->height++;
			q.push(tmp->nextl);
		}

		if (tmp->nextr) {
			//head->height++;
			q.push(tmp->nextr);
		}
	}
}

void BinTree() {
	Font font;

	font.loadFromFile("c:/windows/fonts/arial.ttf");
	Text txt("", font, 30);
	List lst;

	RenderWindow window(VideoMode(1900, 980), "binarytree");
	window.clear(Color(30, 30, 30, 2));
	double value;

	
	for (int i = 0; i < treesize; i++)
	{
		value = rand();
		lst.add(value, window, txt);
	}
	bFs(lst.head);
	cout << lst.head->height;
	window.display();


	while (window.isOpen())
	{

		

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

	}
}


void List::add(double value, RenderWindow& window, Text& txt)
{
	if (head == nullptr)
	{
		head = new Node(true, value, window.getSize().x / 2 - liness, 0 - liness);
		window.draw(head->circle);
		txt.setPosition(head->x + 20, head->y + 10);
		txt.setString(to_string(head->data));
		window.draw(txt);
	}

	else
	{
		Node* curr = head;
		while (1)
		{
			if (value > curr->data)
			{
				if (curr->nextr == nullptr)
				{
					if (curr->nextl == nullptr)
						liness /= sc;
					curr->nextr = new Node(true, value, curr->x, curr->y);
					Vertex line[2] =
					{
						Vertex(Vector2f(curr->x + r,curr->y + r)),
						Vertex(Vector2f(curr->nextr->x + r,curr->nextr->y + r))
					};
					line->color = Color::Green;
					window.draw(line, 2, Lines);
					window.draw(curr->nextr->circle);
					txt.setPosition(curr->nextr->x + 20, curr->nextr->y + 10);
					txt.setString(to_string(curr->nextr->data));
					window.draw(txt);

					break;
				}
				else
					curr = curr->nextr;
			}

			if (value < curr->data)
			{
				if (curr->nextl == nullptr)
				{
					if (curr->nextr == nullptr)
						liness /= sc;
					curr->nextl = new Node(false, value, curr->x, curr->y);
					Vertex line[2] =
					{
						Vertex(Vector2f(curr->x + r,curr->y + r)),
						Vertex(Vector2f(curr->nextl->x + r,curr->nextl->y + r))
					};
					line->color = Color::Green;
					window.draw(line, 2, Lines);
					window.draw(curr->nextl->circle);
					txt.setPosition(curr->nextl->x + 20, curr->nextl->y + 10);
					txt.setString(to_string(curr->nextl->data));
					window.draw(txt);

					break;
				}
				else
					curr = curr->nextl;
			}

		}
	}
}


Node::Node(bool flag, double value, int x1, int y1, Node* r, Node* l)
{
	this->nextr = r;
	this->nextl = l;
	this->data = value;

	circle.setRadius(ra);
	circle.setFillColor(Color::Green);

	if (flag)
	{
		x = x1 + liness;
		y = y1 + liness;
	}

	else
	{
		x = x1 - liness;
		y = y1 + liness;
	}

	circle.setPosition(x, y);
}
