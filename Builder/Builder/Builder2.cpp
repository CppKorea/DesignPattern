#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int UNDEF_SENTENCE = 0;
const int NORMAL_SENTENCE = 1;
const int INTERROGATIVE_SENTENCE = 2;
const int IMPERATIVE_SENTENCE = 3;
const int TO_ENGLISH = 1;
const int TO_JAPANESE = 2;
const int TO_FRENCH = 3;


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

void doTranslate(char* pInFile, Manual& out, int wantedLang);
Sentence getSentence(ifstream& ifs);
string TransNormalSentence(string s, int wantedLang);
string TransInterrogativeSentence(string s, int wantedLang);
string TransImperativeSentence(string s, int wantedLang);


// 인자로 주어진 파일로부터 한문장씩 읽어 이를 번역
void doTranslate(char* pInFile, Manual& out, int wantedLang)
{
	ifstream ifs(pInFile);
	if (!ifs)
	{
		cout << "Can't open file : " << pInFile << endl;
		return;
	}
	string result;
	Sentence next;
	while (!(next = getSentence(ifs)).getString().empty())
	{
		switch (next.getType())
		{
		case NORMAL_SENTENCE: // 평서문
			result = TransNormalSentence(next.getString(), wantedLang);
			break;
		case INTERROGATIVE_SENTENCE: // 의문문
			result = TransInterrogativeSentence(next.getString(), wantedLang);
			break;
		case IMPERATIVE_SENTENCE: // 명령문
			result = TransImperativeSentence(next.getString(), wantedLang);
			break;
		default:
			cout << "Untranslatable sentence type" << endl;
			return;
		}
		out.addContents(result);

	}
}

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

// 평서문
string TransNormalSentence(string s, int wantedLang)
{
	string output;
	switch (wantedLang)
	{
	case TO_ENGLISH: // 영어로 문장 번역
		break;
	case TO_JAPANESE: //일본어로 문장 번역
		break;
	case TO_FRENCH: // 프랑스어로 문장 번역
		break;
	}

	return output;
}

// 의문문
string TransInterrogativeSentence(string s, int wantedLang)
{
	string output;
	switch (wantedLang)
	{
	case TO_ENGLISH: // 영어로 문장 번역
		break;
	case TO_JAPANESE: //일본어로 문장 번역
		break;
	case TO_FRENCH: // 프랑스어로 문장 번역
		break;
	}

	return output;
}

// 명령문
string TransImperativeSentence(string s, int wantedLang)
{
	string output;
	switch (wantedLang)
	{
	case TO_ENGLISH: // 영어로 문장 번역
		break;
	case TO_JAPANESE: //일본어로 문장 번역
		break;
	case TO_FRENCH: // 프랑스어로 문장 번역
		break;
	}

	return output;
}

int main()
{
	Manual out;
	doTranslate("input.txt", out, TO_ENGLISH);
	cout << out.getContents() << endl;
}