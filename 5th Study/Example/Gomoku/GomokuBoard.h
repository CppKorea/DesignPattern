#pragma once

#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GO_BOARD_SIZE     19

class GoMemento 
{
	friend class GomokuBoard;
public:
	GoMemento() 
	{
		for (int i = 0; i < GO_BOARD_SIZE; i++)
			for (int j = 0; j < GO_BOARD_SIZE; j++)
				board_[i][j] = 0;

		whiteDeadNum_ = blackDeadNum_ = 0;
		paePosX_ = paePosY_ = -1;
	}

	GoMemento(const GoMemento& rhs) { CopyBoard(rhs); }
	GoMemento& operator=(const GoMemento& rhs) { CopyBoard(rhs); }

	void GetOutDeadStone() 
	{
		// -- 확실히 죽은 돌을 골라낸다. 
		// -- 이때 whiteDeadNum_ 이나 blackDeadNum_ 값이 조정됨
	}

	bool IsPaePosition(int x, int y) 
	{
		// -- x,y 위치가 패이면 true 되돌림
		return false;
	}

protected:
	void CopyBoard(const GoMemento& src)
	{
		for (int i = 0; i < GO_BOARD_SIZE; i++)
			for (int j = 0; j < GO_BOARD_SIZE; j++)
				board_[i][j] = src.board_[i][j];

		whiteDeadNum_ = src.whiteDeadNum_;
		blackDeadNum_ = src.blackDeadNum_;
	}
private:
	// -- 0 은 돌없음, 양수는 백, 음수는 흑, 절대값은 수순
	int board_[GO_BOARD_SIZE][GO_BOARD_SIZE];

	int whiteDeadNum_; // -- 흰돌 죽은 수
	int blackDeadNum_; // -- 검은돌 죽은 수

	int paePosX_;
	int paePosY_;
};



class GomokuBoard 
{   // -- 바둑판
public:
	GomokuBoard(int firstTurn = -1) 
	{
		pCurBoard_ = nullptr;
		whoseTurn_ = firstTurn;
		totalStoneNum_ = 0;
		bReact = false;

		Init();
	}

	~GomokuBoard()
	{
		for (auto iter = historyList_.begin(); iter != historyList_.end(); iter++) 
		{
			delete *iter;
		}

		for (auto iter = AfterList_.begin(); iter != AfterList_.end(); iter++)
		{
			delete *iter;
		}
	}

	void Init()
	{
		pCurBoard_ = new GoMemento();
		historyList_.push_front(pCurBoard_);
	}

	int GetStone(int x, int y) 
	{
		return pCurBoard_->board_[x][y];
	}


	void PutStone(int x, int y) 
	{
		if (pCurBoard_->board_[x][y] != 0 ||
			(pCurBoard_->paePosX_ == x && pCurBoard_->paePosY_ == y)) 
		{
			//cout << "Can't Be Put Stone There." << endl;
			return;
		}

		GoMemento *pNewBoard = new GoMemento(*pCurBoard_);

		totalStoneNum_++;
		pNewBoard->board_[x][y] = whoseTurn_ * totalStoneNum_;
		whoseTurn_ *= -1;
		if (pCurBoard_->IsPaePosition(x, y)) 
		{
			pCurBoard_->paePosX_ = x;
			pCurBoard_->paePosY_ = y;
		}
		else 
		{
			pCurBoard_->paePosX_ = -1;
			pCurBoard_->paePosY_ = -1;
		}

		pNewBoard->GetOutDeadStone();

		historyList_.push_front(pNewBoard);
		pCurBoard_ = pNewBoard;

		if (bReact)
		{
			for (auto iter = AfterList_.begin(); iter != AfterList_.end(); iter++)
			{
				delete *iter;
			}
			AfterList_.clear();
			bReact = false;
		}
	}

	void RetractStone(int cnt) 
	{
		// -------------------------------------------
		// cnt 값만큼 수를 물린다. 
		// 이때 1수를 물리는 것은 pCurBoard_ 값을 historyList_의 
		// 첫 항목과 대치하는 것과 동일하다. 
		// -------------------------------------------
		if (cnt <= 0) return;

		bReact = true;
		totalStoneNum_--;
		whoseTurn_ *= -1;
		if (historyList_.empty())
		{
			delete pCurBoard_;
			Init();
		}
		else
		{
			GoMemento *pTmpBoard = historyList_.front();
			AfterList_.push_front(pTmpBoard);
			
			historyList_.pop_front();

			if (historyList_.empty())
			{
				Init();
			}
			else
				pCurBoard_ = historyList_.front();
		}
	}

	void AfterActStone()
	{
		totalStoneNum_++;
		whoseTurn_ *= -1;

		if (AfterList_.empty()) return;

		pCurBoard_ = AfterList_.front();
		AfterList_.pop_front();

		historyList_.push_front(pCurBoard_);
	}

private:
	list<GoMemento*> historyList_;
	list<GoMemento*> AfterList_;
	GoMemento* pCurBoard_;
	int whoseTurn_;    // -- 다음 둘 차례(1 은 백, -1 은 흑)
	int totalStoneNum_;
	bool bReact;
};
