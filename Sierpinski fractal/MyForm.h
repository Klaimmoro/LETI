#pragma once

namespace Fractal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	public ref class TreeFractal
	{
		int N, Width, Height;
		Graphics^ g;
		public: TreeFractal(int Num, Graphics^ graphic, int XWidth, int YHeight)
		{
			N = Num;
			g = graphic;
			Width = XWidth;
			Height = YHeight;
		}
		void Rec(int x, int y, int Lenth, int N, int Count)
		{
			  if (Count > N)
				  return;
			  Pen^ PZv = gcnew Pen(Color::Black);
			  if (Count % 2 == 0)
				  PZv->Color = Color::FromArgb(255, 57, 31);
			  else
				  PZv->Color = Color::FromArgb(0, 255, 0);
			  for (int i = 0; i < 8; i++)
			  {
				  g->DrawLine(PZv, Point(x, y), Point(x - Lenth/4 + i * Lenth / 12, y + 60));
				  Rec(x - Lenth / 4 + i * Lenth / 12, y + 60, Lenth / 3, N, Count + 1);
			  }
		}
		public: void MainFunTree(int x, int y, int len)
		{
			Pen^ PZv = gcnew Pen(Color::White);
			if (N >= 1)
			{
				for (int i = 0; i < 8; i++)
				{
					g->DrawLine(PZv, Point(x, y), Point(x - len / 2 + i * len / 4, y + 30));
					if (N >= 2)
					{
						Rec(x - len / 2 + i * len / 4, y + 30, 80, N, 2);
					}
				}
			}
		}
	};

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
	/// ќсвободить все используемые ресурсы.
	/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;

	private:
		/// <summary>
	/// ќб€зательна€ переменна€ конструктора.
	/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 98);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(368, 319);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(152, 57);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 25);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(38, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Levels";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(436, 41);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(624, 398);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1072, 451);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: void DrawRectangle(Graphics^ gr, int level, RectangleF rect)
	{
		// ѕосмотрим, остановимс€ ли мы.
		if (level == 0)
		{
			gr->FillRectangle(Brushes::Blue, rect);
		}
		else
		{
			double wid = rect.Width / 3;
			double x0 = rect.Left;
			double x1 = x0 + wid;
			double x2 = x0 + wid * 2;

			double hgt = rect.Height / 3;
			double y0 = rect.Top;
			double y1 = y0 + hgt;
			double y2 = y0 + hgt * 2;

			DrawRectangle(gr, level - 1, RectangleF(x0, y0, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x1, y0, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x2, y0, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x0, y1, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x2, y1, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x0, y2, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x1, y2, wid, hgt));
			DrawRectangle(gr, level - 1, RectangleF(x2, y2, wid, hgt));
		}
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->Refresh();
		DrawRectangle(pictureBox1->CreateGraphics(), Convert::ToInt32(textBox1->Text), RectangleF(0, 0, 368, 319));
		Graphics^ g = pictureBox2->CreateGraphics();
		TreeFractal^ tree = gcnew TreeFractal(Convert::ToInt32(textBox1->Text), g, pictureBox2->Width, pictureBox2->Height);
		tree->MainFunTree(pictureBox2->Width / 2-100, 0, 300);
	}

	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
	

	
}
