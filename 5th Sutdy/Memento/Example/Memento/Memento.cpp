// State.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
using namespace std;

#define GO_BOARD_SIZE     19

class GoMemento {
	friend class GoBoard;  //friend�� GoBoard�� ����
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
		// -- Ȯ���� ���� ���� ��󳽴�. 
		// -- �̶� whiteDeadNum_ �̳� blackDeadNum_ ���� ������
	}

	bool IsPaePosition(int x, int y) {
		// -- x,y ��ġ�� ���̸� true �ǵ���
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
	// -- 0 �� ������, ����� ��, ������ ��, ���밪�� ����
	int board_[GO_BOARD_SIZE][GO_BOARD_SIZE];

	int whiteDeadNum_; // -- �� ���� ��
	int blackDeadNum_; // -- ������ ���� ��

	int paePosX_;
	int paePosY_;
};

class GoBoard {   // -- �ٵ���
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
		// cnt ����ŭ ���� ������. 
		// �̶� 1���� ������ ���� pCurBoard_ ���� historyList_�� 
		// ù �׸�� ��ġ�ϴ� �Ͱ� �����ϴ�. 
		// -------------------------------------------
		if (cnt <= 0) return;

		for (auto i = 0; i < cnt - 1; i++) {
			GoMemento *pTmpBoard = historyList_.front();  //ù��° ������ȯ
			delete pTmpBoard;
			historyList_.pop_front();  //������ ����
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
	int whoseTurn_;    // -- ���� �� ����(1 �� ��, -1 �� ��)
	int totalStoneNum_;
};

int main()
{
	GoBoard board;

	board.PutStone(3, 3);      //��
	board.PutStone(16, 16);
	board.PutStone(16, 3);
	board.PutStone(3, 16);
	board.PrintBoard();

	system("pause");

	board.RetractStone(2);  //������
	board.PrintBoard();

	system("pause");

	return 0;
}
