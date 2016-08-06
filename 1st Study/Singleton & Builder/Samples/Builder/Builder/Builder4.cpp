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
		// -- 문장 유형을 판단해서 _type에 설정, default는 평서문
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
		// -- s를 영어로 번역
		
		_result.addContents(output);
	}
	virtual void TransInterrogativeSentence(string s)
	{
		string output;
		// -- s를 영어로 번역

		_result.addContents(output);
	}
	virtual void TransImperativeSentence(string s)
	{
		string output;
		// -- s를 영어로 번역

		_result.addContents(output);
	}

};

class JanpaneseTranslator : public Translator
{
public:
	virtual void TransNormalSentence(string s)
	{
		string output;
		// -- s를 일어로 번역

		_result.addContents(output);
	}
	virtual void TransInterrogativeSentence(string s)
	{
		string output;
		// -- s를 일어로 번역

		_result.addContents(output);
	}
	virtual void TransImperativeSentence(string s)
	{
		string output;
		// -- s를 일어로 번역

		_result.addContents(output);
	}

};

class FrenchTranslator : public Translator
{
public:
	virtual void TransNormalSentence(string s)
	{
		string output;
		// -- s를 프랑스어로 번역

		_result.addContents(output);
	}
	virtual void TransInterrogativeSentence(string s)
	{
		string output;
		// -- s를 프랑스어로 번역

		_result.addContents(output);
	}
	virtual void TransImperativeSentence(string s)
	{
		string output;
		// -- s를 프랑스어로 번역

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
			case NORMAL_SENTENCE: // 평서문
				t.TransNormalSentence(next.getString());
				break;
			case INTERROGATIVE_SENTENCE: // 의문문
				t.TransInterrogativeSentence(next.getString());
				break;
			case IMPERATIVE_SENTENCE: // 명령문
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





