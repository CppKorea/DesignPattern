#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int UNDEF_SENTENCE = 0;
const int NORMAL_SENTENCE = 1;
const int INTERROGATIVE_SENTENCE = 2;
const int IMPERATIVE_SENTENCE = 3;

class Sentence
{
public:
	Sentence() { _data = ""; _type = UNDEF_SENTENCE; }
	
	int getType() { return _type; }
	string getString() { return _data; }

	void setSentenceData(string s)
	{
		setSentenceType(s);
		_data = s;
	}
protected:
	void setSentenceType(string s)
	{
		// -- ���� ������ �Ǵ��ؼ� _type�� ����, default�� �򼭹�
		_type = NORMAL_SENTENCE;
	}
private:
	string	_data;
	int		_type;
};

class Manual
{
public:
	string getContents() { return _contents; }
	void addContents(string s) { _contents += s; }
private:
	string _contents;
};

class Translator
{
public:
	Manual getResult() { return _result; }
	virtual void TransNormalSentence(string s) = 0;
	virtual void TransInterrogativeSentence(string s) = 0;
	virtual void TransImperativeSentence(string s) = 0;
protected:
	Manual _result;
};

class EnglishTranslator : public Translator
{
public:
	virtual void TransNormalSentence(string s)
	{
		string output;
		// -- s�� ����� ����
		
		_result.addContents(output);
	}
	virtual void TransInterrogativeSentence(string s)
	{
		string output;
		// -- s�� ����� ����

		_result.addContents(output);
	}
	virtual void TransImperativeSentence(string s)
	{
		string output;
		// -- s�� ����� ����

		_result.addContents(output);
	}

};

class JanpaneseTranslator : public Translator
{
public:
	virtual void TransNormalSentence(string s)
	{
		string output;
		// -- s�� �Ͼ�� ����

		_result.addContents(output);
	}
	virtual void TransInterrogativeSentence(string s)
	{
		string output;
		// -- s�� �Ͼ�� ����

		_result.addContents(output);
	}
	virtual void TransImperativeSentence(string s)
	{
		string output;
		// -- s�� �Ͼ�� ����

		_result.addContents(output);
	}

};

class FrenchTranslator : public Translator
{
public:
	virtual void TransNormalSentence(string s)
	{
		string output;
		// -- s�� ��������� ����

		_result.addContents(output);
	}
	virtual void TransInterrogativeSentence(string s)
	{
		string output;
		// -- s�� ��������� ����

		_result.addContents(output);
	}
	virtual void TransImperativeSentence(string s)
	{
		string output;
		// -- s�� ��������� ����

		_result.addContents(output);
	}

};

class Director
{
public:
	void doTranslate(char* pInFile, Translator& t)
	{
		ifstream ifs(pInFile);
		if (!ifs)
		{
			cout << "Can't open file : " << pInFile << endl;
			return;
		}

		Sentence next;
		while (!(next = getSentence(ifs)).getString().empty())
		{
			switch (next.getType())
			{
			case NORMAL_SENTENCE: // �򼭹�
				t.TransNormalSentence(next.getString());
				break;
			case INTERROGATIVE_SENTENCE: // �ǹ���
				t.TransInterrogativeSentence(next.getString());
				break;
			case IMPERATIVE_SENTENCE: // ��ɹ�
				t.TransImperativeSentence(next.getString());
				break;
			default:
				cout << "Untranslatable sentence type" << endl;
				return;
			}

		}

	}
protected:
	Sentence getSentence(ifstream& ifs)
	{
		int c;
		string s;
		Sentence sentence;
		while ((c = ifs.get()) != EOF)
		{
			s += c;
			if (c == '?' || c == '.')	break;
		}
		sentence.setSentenceData(s);
		return sentence;
	}
};


int main()
{
	Director d;
	EnglishTranslator t;
	d.doTranslate("input.txt", t);
	FrenchTranslator t2;
	d.doTranslate("input.txt", t2);


	Manual out = t.getResult();
	cout << out.getContents() << endl;
}





