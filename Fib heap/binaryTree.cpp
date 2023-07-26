#include "binarytree.h"
int liness = 200;
double sc = 1.2;
int ra = 30;
int r = 30;
const int treesize = 10;



void dijkstra(List lst, double** Matrix, RenderWindow& window, Text& txt)
{
	//cout << "End startPoint: ";
	int a=4; 
	//cout << "Enter finishPoint: ";
	int key=1; 
	int Dist[5];
	Dist[a] = 0;
	for (int i = 0; i < 5; i++) {
		if (i != a) {
			Dist[i] = 100000;
		}
	}
	bool marked[5];
	marked[a] = true;
	lst.add(a,window,txt);
	for (int i = 0; i < 5; i++) {
		if (i != a) {
			marked[i] = false;
		}
	}
	int currVersh = a;
	while (marked[key] != true) {
		for (int j = 0; j < 5; j++) {
			if (Matrix[currVersh][j] != 0) {
				if (marked[j] == false) {
					if (Matrix[currVersh][j] + Dist[currVersh] < Dist[j]) {
						Dist[j] = Matrix[currVersh][j] + Dist[currVersh];
					}
				}
			}
		}
		int min = 100000;
		int minInd = 0;
		for (int j = 0; j < 5; j++) {
			if (marked[j]==false) {
				if (min > Dist[j]) {
					min = Dist[j];
					minInd = j;
				}
			}
		}
		marked[minInd] = true;
		if (Matrix[minInd][key] != 0) { lst.add(minInd, window, txt); }
		if (minInd == key) { lst.add(minInd, window, txt); break; }
		currVersh = minInd;
	}
	cout << "quickest way: " << Dist[key] << endl;
}

void BinTree() {
	Font font;

	font.loadFromFile("c:/windows/fonts/arial.ttf");
	Text txt("", font, 30);
	List lst;

	RenderWindow window(VideoMode(1900, 980), "binarytree");
	window.clear(Color(30, 30, 30, 2));


	double** MatrixG; int MatrixS = 5;
	MatrixG = new double* [MatrixS];
	for (int i = 0; i < MatrixS; i++) {
		MatrixG[i] = new double[MatrixS];
	}
	cout << "Enter matrix values: " << endl;
	for (int i = 0; i < MatrixS; i++) {
		for (int j = 0; j < MatrixS; j++) {
			cin >> MatrixG[i][j];
		}
	}

	dijkstra(lst, MatrixG,window,txt);
	
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

Node* List::GetHead()
{
	return head;
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
