// State.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
using namespace std;

#define GO_BOARD_SIZE     19

class GoMemento {
	friend class GoBoard;  //friend인 GoBoard만 접근
public:
	GoMemento() {
		for (int i = 0; i < GO_BOARD_SIZE; i++)
			for (int j = 0; j < GO_BOARD_SIZE; j++)
				board_[i][j] = 0;

		whiteDeadNum_ = blackDeadNum_ = 0;
		paePosX_ = paePosY_ = -1;
	}

	GoMemento(const GoMemento& rhs) { CopyBoard(rhs); }
	GoMemento& operator=(const GoMemento& rhs) { CopyBoard(rhs); }

	void GetOutDeadStone() {
		// -- 확실히 죽은 돌을 골라낸다. 
		// -- 이때 whiteDeadNum_ 이나 blackDeadNum_ 값이 조정됨
	}

	bool IsPaePosition(int x, int y) {
		// -- x,y 위치가 패이면 true 되돌림
		return false;
	}

protected:
	void CopyBoard(const GoMemento& src) {
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

class GoBoard {   // -- 바둑판
public:
	GoBoard(int firstTurn = -1) {
		pCurBoard_ = new GoMemento();
		whoseTurn_ = firstTurn;
		totalStoneNum_ = 0;
	}

	void PutStone(int x, int y) {
		if (pCurBoard_->board_[x][y] != 0 ||
			(pCurBoard_->paePosX_ == x && pCurBoard_->paePosY_ == y)) {
			cout << "Can't Be Put Stone There." << endl;
			return;
		}

		GoMemento *pNewBoard = new GoMemento(*pCurBoard_);
		totalStoneNum_++;
		pNewBoard->board_[x][y] = whoseTurn_ * totalStoneNum_;
		whoseTurn_ *= -1;
		if (pCurBoard_->IsPaePosition(x, y)) {
			pCurBoard_->paePosX_ = x;
			pCurBoard_->paePosY_ = y;
		}
		else {
			pCurBoard_->paePosX_ = -1;
			pCurBoard_->paePosY_ = -1;
		}

		pNewBoard->GetOutDeadStone();

		historyList_.push_front(pCurBoard_);
		pCurBoard_ = pNewBoard;
	}

	void RetractStone(int cnt) {
		// -------------------------------------------
		// cnt 값만큼 수를 물린다. 
		// 이때 1수를 물리는 것은 pCurBoard_ 값을 historyList_의 
		// 첫 항목과 대치하는 것과 동일하다. 
		// -------------------------------------------
		if (cnt <= 0) return;

		for (auto i = 0; i < cnt - 1; i++) {
			GoMemento *pTmpBoard = historyList_.front();  //첫번째 참조반환
			delete pTmpBoard;
			historyList_.pop_front();  //데이터 삭제
			totalStoneNum_--;
		}

		delete pCurBoard_;
		totalStoneNum_--;
		if (historyList_.empty())
			pCurBoard_ = new GoMemento();
		else
			pCurBoard_ = historyList_.front();
	}

	void PrintBoard() {
		for (auto i = 0; i < GO_BOARD_SIZE; i++) {
			for (auto j = 0; j < GO_BOARD_SIZE; j++)
				cout << pCurBoard_->board_[i][j] << " ";
			cout << endl;
		}
		cout << "--- total stone --- " << totalStoneNum_ << endl;
	}
private:
	list<GoMemento*> historyList_;
	GoMemento* pCurBoard_;
	int whoseTurn_;    // -- 다음 둘 차례(1 은 백, -1 은 흑)
	int totalStoneNum_;
};

int main()
{
	GoBoard board;

	board.PutStone(3, 3);      //흑
	board.PutStone(16, 16);
	board.PutStone(16, 3);
	board.PutStone(3, 16);
	board.PrintBoard();

	system("pause");

	board.RetractStone(2);  //물리기
	board.PrintBoard();

	system("pause");

	return 0;
}
